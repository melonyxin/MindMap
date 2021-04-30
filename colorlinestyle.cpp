#include "colorlinestyle.h"
#include "coloranalyzer.h"
#include <QDebug>

ColorLineStyle::ColorLineStyle()
{
    font.setPixelSize(25);
    font.setBold(true);
    radiusSize = 20;
    penWidth = 5;
    padding = QSize(20,10);
    margin = QSize(penWidth*2,penWidth*2);
}

void ColorLineStyle::paint(QPainter *painter, Node *parent, Node *item){
    QPen pen;
    pen.setWidth(penWidth);
    QColor c = ColorAnalyzer::getColor(item->getIndexOfMaster());
    pen.setColor(c);
    painter->setPen(pen);

    QRectF itemRect = item->getCustomRect();
    QPointF p = itemRect.bottomLeft();

    // 绘制轮廓线
    if(item->isMasterNode()){
        painter->fillRect(itemRect,Qt::white);
        painter->drawRect(itemRect);
    } else {
        painter->drawLine(p.x(),p.y(),p.x()+item->getSize().width(),p.y());
        QPointF parentStart;
        if(parent->isMasterNode()){
            parentStart = parent->getCustomRect().center() - item->pos();
        } else {
            parentStart = parent->getCustomRect().bottomRight() - item->pos();
        }
        QPainterPath path(parentStart);
        QPointF c1 = QPointF((parentStart.x() + p.x()) / 2, parentStart.y());
        QPointF c2 = QPointF((parentStart.x() + p.x()) / 2, p.y());
        path.cubicTo(c1, c2, p);
        painter->drawPath(path);
    }

    // 绘制内容文字
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(p.x()+padding.width(), p.y()-padding.height()-2,item->getContent());

    // 绘制焦点框线
    if (item->isSelected()){
        pen.setColor(QColor(213,213,237));
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

QDomElement ColorLineStyle::focusToDom(QDomDocument *doc){
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

QDomElement ColorLineStyle::nodeToDom(QDomDocument *doc,Node *node){
    QDomElement nodeElement = doc->createElement("g");
    nodeElement.setAttribute("class","node-container");
    nodeElement.setAttribute("fill","#ffffff");
    QString transform;
    if(node->isMasterNode()){
        nodeElement.setAttribute("isMaster",true);
        transform = "matrix(1,0,0,1,"+QString::number(525)+","+QString::number(360)+")";
    } else {
        transform = "matrix(1,0,0,1,"+QString::number(node->pos().x())+","+QString::number(node->pos().y())+")";
    }
    nodeElement.setAttribute("stroke","#ffffff");
    nodeElement.setAttribute("transform",transform);
    nodeElement.setAttribute("stroke-width",penWidth);

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
    else {
        rect.setAttribute("fill-opacity","0");
        rect.setAttribute("stroke-opacity","0");
    }
    content.appendChild(rect);

    QDomElement text = doc->createElement("text");
    text.setAttribute("fill","#000000");
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
            parentStart = parent->getCustomRect().bottomRight() - node->pos();
        }
        QPointF p = node->getCustomRect().bottomLeft();
        QPointF c1 = QPointF((parentStart.x() + p.x()) / 2, parentStart.y());
        QPointF c2 = QPointF((parentStart.x() + p.x()) / 2, p.y());
        QPointF end = node->getCustomRect().bottomRight();
        QString pathString = "M"+QString::number(parentStart.x())+","+QString::number(parentStart.y())
                              +" C"+QString::number(c1.x())+","+QString::number(c1.y())
                              +" "+QString::number(c2.x())+","+QString::number(c2.y())
                              +" "+QString::number(p.x())+","+QString::number(p.y())
                              +" L"+QString::number(end.x())+","+QString::number(end.y());
        QDomElement path = doc->createElement("path");
        path.setAttribute("class","child-line");
        path.setAttribute("d",pathString);
        QColor c = ColorAnalyzer::getColor(node->getIndexOfMaster());
        path.setAttribute("stroke",c.name());
        nodeElement.appendChild(path);
    }

    return nodeElement;
}
