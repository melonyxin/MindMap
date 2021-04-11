#include "node.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QInputDialog>

Node::Node(QGraphicsItem *parent, QString content)
    : QGraphicsItem(parent)
    ,m_cPenColor(255, 0, 0)
    ,m_cBrushColor(200, 100, 100)
{
    this->content = content;
    this->setFlags(QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsFocusable |
                   QGraphicsItem::ItemIsMovable);
    this->font.setPixelSize(25);
    this->font.setBold(true);
    this->updateSize();
    this->setCursor(Qt::PointingHandCursor);

    closePixmap = QPixmap::fromImage(QImage(":/img/close.png"));
    addPixmap =  QPixmap::fromImage(QImage(":/img/add.png"));
}

Node::~Node(){

}

QRectF Node::boundingRect() const {
    QRectF rectF = getCustomRect();
    rectF.adjust(-10,-10,10,10);

    return rectF;
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    QPen pen;
    pen.setWidth(m_nPenWidth);
    pen.setColor(m_cPenColor);
    painter->setPen(pen);

    // 绘制轮廓线
    QRectF itemRect = this->getCustomRect();
    QPointF p = itemRect.bottomLeft();
    painter->drawLine(p.x(),p.y(),p.x()+size.width(),p.y());
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(p.x()+padding.width(), p.y()-padding.height()-2,content);
    if (this->isSelected()){
        pen.setColor(QColor(87,170,253));
        painter->setPen(pen);
        painter->drawRect(itemRect);
        if(isClosed()){
            painter->drawPixmap(QRect(itemRect.topLeft().x()-radiusSize/2,itemRect.topLeft().y()-radiusSize/2,
                                radiusSize,radiusSize),closePixmap);
        }
        if(!addPixmap.isNull()){
            painter->drawPixmap(QRect(itemRect.bottomRight().x()-radiusSize/2,itemRect.bottomRight().y()-radiusSize/2,
                                radiusSize,radiusSize),addPixmap);
        }
    }

    // 主节点跳出不绘制连线
    if(parentItem() == 0){
        return;
    }
    pen.setWidth(m_nPenWidth);
    pen.setColor(m_cPenColor);
    painter->setPen(pen);
    QPointF parentStart = parentItem()->boundingRect().bottomRight() - QPointF(10,10) - pos();
    QPainterPath path(parentStart);
    QPointF c1 = QPointF((parentStart.x() + p.x()) / 2, parentStart.y());
    QPointF c2 = QPointF((parentStart.x() + p.x()) / 2, p.y());
    path.cubicTo(c1, c2, p);
    painter->drawPath(path);
}

QString Node::getContent(){
    return this->content;
}

QRectF Node::getCustomRect(void) const {
    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - size.width() / 2, centerPos.y() - size.height() / 2, \
                      size.width(), size.height());
}

void Node::setContent(QString content){
    this->content = content;
    this->updateSize();
}

void Node::updateSize(){
    QFontMetrics fm(this->font);
    this->size.setWidth(fm.width(this->content)+this->padding.width()*2);
    this->size.setHeight(fm.height()+this->padding.height()*2);
}

qreal Node::getDistance(QPointF a,QPointF b){
    qreal dx = a.x() - b.x();
    qreal dy = a.y() - b.y();
    return sqrt(dx*dx+dy*dy);
}

bool Node::isClosed() {
    return (parentItem()!=0) && (!closePixmap.isNull()) && isSelected();
}

void Node::addNewNode(){
    Node * newNode = new Node(nullptr,"输入内容");
    newNode->setParentItem(this);
    newNode->setPos(QPointF(100,100));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    QRectF itemRect = this->getCustomRect();
    if(getDistance(pos,itemRect.topLeft()) <= radiusSize/2 && isClosed()){
        delete this;
    } else if(getDistance(pos,itemRect.bottomRight()) <= radiusSize/2 && isSelected()){
        addNewNode();
    }

    QGraphicsItem::mousePressEvent(event);
}

//void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
//    QGraphicsItem::mouseMoveEvent(event);
//    QPointF mv = pressPos - event->scenePos();
//    setPos(startPos - mv);
//    update();
//}

//void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
//    QGraphicsItem::mouseReleaseEvent(event);
//    qDebug() << "scene" <<event->scenePos();
//    qDebug() << "node" <<pos();
//    qDebug() << "screen" <<event->pos();
//}
