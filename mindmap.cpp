#include "mindmap.h"
#include <QPushButton>
#include <QToolButton>

MindMap::MindMap(QWidget *parent, QString filename) : QGraphicsScene(parent)
{
    this->filename = filename;
    masterNode.setContent("开始");
    this->addItem(&masterNode);
}

QString MindMap::getFilename(){
    return this->filename;
}
