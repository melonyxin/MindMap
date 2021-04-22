#include "polylinestyle.h"

PolylineStyle::PolylineStyle(QString color)
{
    font.setPixelSize(25);
    font.setBold(true);
    radiusSize = 20;
    penWidth = 5;
    padding = QSize(20,10);
    margin = QSize(penWidth+lineWidth,penWidth+lineWidth);

    theme = QColor(color);   // 默认天空蓝
}

void PolylineStyle::paint(QPainter *painter, Node *parent, Node *item){
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
        parentStart = (parent->getCustomRect().bottomRight()+parent->getCustomRect().topRight())/2 - item->pos();

        QPainterPath path(parentStart);
        path.lineTo(QPointF(parentStart.x()+50, parentStart.y()));
        path.lineTo(QPointF(parentStart.x()+50, p.y()));
        path.lineTo(p);
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
