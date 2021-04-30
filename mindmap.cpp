#include "mindmap.h"
#include <QPushButton>
#include <QToolButton>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>
#include "nodestyleanalyzer.h"

MindMap::MindMap(QWidget *parent, QString filename) : QGraphicsScene(parent)
{
    this->filename = filename;
    this->setBackgroundBrush(Qt::white);
    this->nodePainter = NodeStyleAnalyzer::createNodeStyle(indexOfStyle);
}

QString MindMap::getFilename(){
    return this->filename;
}

void MindMap::setFileName(QString name){
    filename = name;
}

Node * MindMap::getMasterNode(){
    return masterNode;
}

void MindMap::addMasterNode(Node *node){
    masterNode = node;

    this->addItem(masterNode);
}

QString MindMap::getFilePath(){
    return filepath;
}

void MindMap::setFilePath(QString path){
    filepath = path;
}

int MindMap::getIndexOfStyle(){
    return indexOfStyle;
}

void MindMap::setIndexOfStyle(int index){
    indexOfStyle = index;
    this->nodePainter = NodeStyleAnalyzer::createNodeStyle(indexOfStyle);
}

bool MindMap::isPathEmpty(){
    return filepath.isEmpty();
}

NodeStyle* MindMap::getNodePainter(){
    return nodePainter;
}
