#include "node.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

Node::Node(QGraphicsItem *parent, QString content)
    : QGraphicsItem(parent)
    ,m_cPenColor(255, 0, 0)
    ,m_cBrushColor(200, 100, 100)
{
    this->content = content;
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

Node::~Node(){

}

QRectF Node::boundingRect() const {
    //QRectF rectF = getCustomRect();
    //if (!this->isSelected())
        //return rectF;

    //rectF.adjust(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
    //rectF.adjust(-m_nEllipseWidth, -m_nEllipseWidth, m_nEllipseWidth, m_nEllipseWidth);

    //return rectF;
    return QRectF(-10,-10,50,30);
}

QPainterPath Node::shape() const {
    QPainterPath path;
    //path.addRect(boundingRect());
    path.addRect(QRect(-10,-10,50,30));
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    QPen pen;
    pen.setWidth(m_nPenWidth);
    pen.setColor(m_cPenColor);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::red));

    // 绘制轮廓线
    QRectF itemRect = this->getCustomRect();
    painter->drawRect(QRect(-10,-10,50,30));
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->setBrush(QBrush());
    painter->drawText(0,10,content);
    if (this->isSelected()){
        pen.setColor(m_cPenColor);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(QBrush());
        QRectF outLintRect = itemRect.adjusted(-20, -20, 50, 30);
        painter->drawRect(outLintRect);
    }
}

QString Node::getContent(){
    return this->content;
}

QRectF Node::getCustomRect(void) const
{
    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - n_size.width() / 2, centerPos.y() - n_size.height() / 2, \
                  n_size.width(), n_size.height());
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event){
    return QGraphicsItem::mousePressEvent(event);
}

void Node::setContent(QString content){
    this->content = content;
}



