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
