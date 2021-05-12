#include "node.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QInputDialog>
#include "coloranalyzer.h"
#include "colorlinestyle.h"
#include "mindmap.h"

Node::Node(QGraphicsItem *parent, QString content)
    : QGraphicsItem(parent)
{
    this->content = content;
    this->setFlags(QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsFocusable |
                   QGraphicsItem::ItemIsMovable |
                   QGraphicsItem::ItemStacksBehindParent);

    this->setCursor(Qt::PointingHandCursor);
}

Node::~Node(){

}

QRectF Node::boundingRect() const {
    QRectF rectF = getCustomRect();
    NodeStyle *nodePainter = ((MindMap*)scene())->getNodePainter();
    if(nodePainter==nullptr) return rectF;
    QSize margin = nodePainter->getMargin();
    rectF.adjust(-margin.width(),-margin.height(),margin.width(),margin.height());

    return rectF;
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing, true);              // 图元边缘抗锯齿
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);     // 平滑的像素图变换算法
    painter->setRenderHint(QPainter::TextAntialiasing, true);          // 文本抗锯齿

    NodeStyle *nodePainter = ((MindMap*)scene())->getNodePainter();
    nodePainter->paint(painter,(Node *)parentItem(),this);
}

QString Node::getContent(){
    return this->content;
}

QString Node::getRemark(){
    return this->remark;
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

void Node::setRemark(QString remark){
    this->remark = remark;
}

void Node::setIndexOfMaster(int index){
    indexOfMaster = index;
}

void Node::updateSize(){
    NodeStyle *nodePainter = ((MindMap*)scene())->getNodePainter();
    if(nodePainter==nullptr) return;
    QFontMetrics fm(nodePainter->getFont());
    this->size.setWidth(fm.width(this->content)+nodePainter->getPadding().width()*2);
    this->size.setHeight(fm.height()+nodePainter->getPadding().height()*2);
}

qreal Node::getDistance(QPointF a,QPointF b){
    qreal dx = a.x() - b.x();
    qreal dy = a.y() - b.y();
    return sqrt(dx*dx+dy*dy);
}

int Node::getIndexOfMaster(){
    return indexOfMaster;
}

QSize Node::getSize(){
    return size;
}

bool Node::isClosed() {
    return (!isMasterNode()) && isSelected();
}

bool Node::isMasterNode(){
    return parentItem()==0;
}

void Node::addNewNode(){
    Node * newNode = new Node();
    newNode->setParentItem(this);
    newNode->setPos(QPointF(100,100));
    newNode->setContent("输入内容");
    if(isMasterNode()){
        indexOfMaster--;
        newNode->setIndexOfMaster(-indexOfMaster);
    } else {
        newNode->setIndexOfMaster(getIndexOfMaster());
    }
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    QRectF itemRect = this->getCustomRect();
    NodeStyle *nodePainter = ((MindMap*)scene())->getNodePainter();
    int radiusSize = nodePainter->getRadiusSize();
    if(getDistance(pos,itemRect.topLeft()) <= radiusSize/2 && isClosed()){
        delete this;
    } else if(getDistance(pos,itemRect.bottomRight()) <= radiusSize/2 && isSelected()){
        addNewNode();
    }

    QGraphicsItem::mousePressEvent(event);
}
