#include "blockstyle.h"

BlockStyle::BlockStyle(QString color)
{
    font.setPixelSize(25);
    font.setBold(true);
    radiusSize = 20;
    penWidth = 5;
    padding = QSize(20,10);
    margin = QSize(penWidth+lineWidth,penWidth+lineWidth);

    theme = QColor(color);   // 默认天空蓝
}

void BlockStyle::paint(QPainter *painter, Node *parent, Node *item){
    QPen pen;
    pen.setWidth(lineWidth);
    pen.setColor(theme);
    painter->setPen(pen);

    QRectF itemRect = item->getCustomRect();
    QPointF p = (itemRect.bottomLeft()+itemRect.topLeft())/2;

    // 绘制轮廓线
    if(item->isMasterNode()){
        painter->fillRect(itemRect,theme);
        painter->drawRect(itemRect);
    } else {
        painter->drawRect(itemRect);
        QPointF parentStart;
        if(parent->isMasterNode()){
            parentStart = parent->getCustomRect().center() - item->pos();
        } else {
            parentStart = (parent->getCustomRect().bottomRight()+parent->getCustomRect().topRight())/2 - item->pos();
        }

        QPainterPath path(parentStart);
        QPointF c = QPointF(parentStart.x()*0.9+p.x()*0.1, p.y());
        path.quadTo(c,p);
        painter->drawPath(path);
    }

    // 绘制内容文字
    if(item->isMasterNode())
        pen.setColor(Qt::white);
    else
        pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->setFont(font);
    p = itemRect.bottomLeft();
    painter->drawText(p.x()+padding.width(), p.y()-padding.height()-2,item->getContent());

    // 绘制焦点框线
    if (item->isSelected()){
        pen.setColor(QColor(213,213,237));
        pen.setWidth(penWidth);
        painter->setPen(pen);
        itemRect.adjust(-penWidth,-penWidth,penWidth,penWidth);
        painter->drawRect(itemRect);
        if(!item->isMasterNode() && !closePixmap.isNull()){
            painter->drawPixmap(QRect(itemRect.topLeft().x()-radiusSize/2,itemRect.topLeft().y()-radiusSize/2,
                                radiusSize,radiusSize),closePixmap);
        }
        if(!addPixmap.isNull()){
            painter->drawPixmap(QRect(itemRect.bottomRight().x()-radiusSize/2,itemRect.bottomRight().y()-radiusSize/2,
                                radiusSize,radiusSize),addPixmap);
        }
    }
}

QDomElement BlockStyle::focusToDom(QDomDocument *doc){
    QDomElement focus = doc->createElement("g");
    focus.setAttribute("id","markupRect");
    focus.setAttribute("fill","none");
    focus.setAttribute("stroke","#d5d5ed");
    focus.setAttribute("stroke-width",QString::number(penWidth));

    QDomElement rect = doc->createElement("rect");
    rect.setAttribute("id","outline");
    rect.setAttribute("x","0");
    rect.setAttribute("y","0");
    rect.setAttribute("width","0");
    rect.setAttribute("height","0");
    focus.appendChild(rect);

    QDomElement closeIcon = doc->createElement("image");
    closeIcon.setAttribute("id","close_icon");
    closeIcon.setAttribute("x","0");
    closeIcon.setAttribute("y","0");
    closeIcon.setAttribute("width",QString::number(radiusSize));
    closeIcon.setAttribute("height",QString::number(radiusSize));
    focus.appendChild(closeIcon);

    QDomElement addIcon = doc->createElement("image");
    addIcon.setAttribute("id","add_icon");
    addIcon.setAttribute("x","0");
    addIcon.setAttribute("y","0");
    addIcon.setAttribute("width",QString::number(radiusSize));
    addIcon.setAttribute("height",QString::number(radiusSize));
    focus.appendChild(addIcon);

    return focus;
}

QDomElement BlockStyle::nodeToDom(QDomDocument *doc,Node *node){
    QDomElement nodeElement = doc->createElement("g");
    nodeElement.setAttribute("class","node-container");
    QString transform;
    if(node->isMasterNode()){
        nodeElement.setAttribute("isMaster",true);
        nodeElement.setAttribute("fill",theme.name());
        transform = "matrix(1,0,0,1,"+QString::number(525)+","+QString::number(360)+")";
    } else {
        nodeElement.setAttribute("fill","#ffffff");
        transform = "matrix(1,0,0,1,"+QString::number(node->pos().x())+","+QString::number(node->pos().y())+")";
    }
    nodeElement.setAttribute("stroke",theme.name());
    nodeElement.setAttribute("transform",transform);
    nodeElement.setAttribute("stroke-width",lineWidth);

    // 子结点
    QList<QGraphicsItem*> list = node->childItems();
    for(int i=0;i<list.length();i++){
        nodeElement.appendChild(nodeToDom(doc,(Node*)list[i]));
    }

    QDomElement content = doc->createElement("g");
    content.setAttribute("class","node");
    nodeElement.appendChild(content);

    QSize size = node->getSize();
    int x = -size.width()/2;
    int y = -size.height()/2;

    QDomElement rect = doc->createElement("rect");
    rect.setAttribute("x",QString::number(x));
    rect.setAttribute("y",QString::number(y));
    rect.setAttribute("width",QString::number(size.width()));
    rect.setAttribute("height",QString::number(size.height()));
    if(node->isMasterNode()) rect.setAttribute("fill-opacity","1");
    else rect.setAttribute("fill-opacity","0");
    content.appendChild(rect);

    QDomElement text = doc->createElement("text");
    if(node->isMasterNode()){
        text.setAttribute("fill","#ffffff");
    } else {
        text.setAttribute("fill","#000000");
    }
    text.setAttribute("x",QString::number(x+padding.width()));
    text.setAttribute("y",QString::number(y+size.height()-padding.height()-2));
    text.appendChild(doc->createTextNode(node->getContent()));
    content.appendChild(text);

    if(!node->isMasterNode()){
        Node* parent = (Node*)node->parentItem();
        QPointF parentStart;
        if(parent->isMasterNode()){
            parentStart = parent->getCustomRect().center() - node->pos();
        } else {
            parentStart = (parent->getCustomRect().bottomRight()+parent->getCustomRect().topRight())/2 - node->pos();
        }
        QRectF itemRect = node->getCustomRect();
        QPointF p = (itemRect.bottomLeft()+itemRect.topLeft())/2;
        QPointF c = QPointF(parentStart.x()*0.9+p.x()*0.1, p.y());
        QString pathString = "M"+QString::number(parentStart.x())+","+QString::number(parentStart.y())
                +" Q"+QString::number(c.x())+","+QString::number(c.y())
                +" "+QString::number(p.x())+","+QString::number(p.y());
        QDomElement path = doc->createElement("path");
        path.setAttribute("class","child-line");
        path.setAttribute("d",pathString);
        nodeElement.appendChild(path);
    }

    return nodeElement;
}
