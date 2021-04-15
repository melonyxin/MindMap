#include "mindmap.h"
#include <QPushButton>
#include <QToolButton>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>

MindMap::MindMap(QWidget *parent, QString filename) : QGraphicsScene(parent)
{
    this->filename = filename;
    masterNode.setContent("开始");
    masterNode.setPos(QPointF(0,0));
    masterNode.setPenColor(Qt::white);

    this->addItem(&masterNode);
}

QString MindMap::getFilename(){
    return this->filename;
}

void MindMap::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    // qDebug() << "scene" << event->scenePos();
}

void MindMap::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseMoveEvent(event);

    //qDebug() << "scene" << event->scenePos();
}

void MindMap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}
