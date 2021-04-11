#include "mindmap.h"
#include <QPushButton>
#include <QToolButton>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>

MindMap::MindMap(QWidget *parent, QString filename) : QGraphicsScene(parent)
{
    this->filename = filename;
    masterNode.setContent("开始");

    m.setParent(&masterNode);
    m.setContent("来不不不不");
    m.setPos(QPointF(30,30));

    this->addItem(&masterNode);
    this->addItem(&m);
}

QString MindMap::getFilename(){
    return this->filename;
}

void MindMap::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    //qDebug() << "scene" << event->scenePos();
}

void MindMap::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseMoveEvent(event);

    //qDebug() << "scene" << event->scenePos();
}

void MindMap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}
