#include "mapfilereader.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QDebug>

MapFileReader::MapFileReader(QString path)
{
    filepath = path;
}

void MapFileReader::jsonToNode(QJsonObject root,Node *parent){
    QJsonObject data = root.value("data").toObject();
    QJsonArray children = root.value("children").toArray();

    Node * node = new Node();
    node->setParentItem(parent);
    node->setContent(data.value("content").toString());
    node->setIndexOfMaster(data.value("indexOfMaster").toInt());
    int x = data.value("pos_x").toInt();
    int y = data.value("pos_y").toInt();
    node->setPos(QPointF(x,y));
    for(int i=0,len=children.size();i<len;i++){
        QJsonObject child = children.at(i).toObject();
        jsonToNode(child, node);
    }
}

MindMap * MapFileReader::jsonToMap(QJsonObject root){
    QJsonObject master = root.value("MasterNode").toObject();
    QJsonObject data = master.value("data").toObject();
    QJsonArray children = master.value("children").toArray();

    MindMap * map = new MindMap();
    map->setIndexOfStyle(root.value("IndexOfStyle").toInt());
    map->setFileName(root.value("FileName").toString());

    Node * masterNode = new Node();
    map->addMasterNode(masterNode);
    masterNode->setContent(data.value("content").toString());
    masterNode->setIndexOfMaster(data.value("indexOfMaster").toInt());
    int x = data.value("pos_x").toInt();
    int y = data.value("pos_y").toInt();
    masterNode->setPos(QPointF(x,y));

    for(int i=0,len=children.size();i<len;i++){
        QJsonObject child = children.at(i).toObject();
        jsonToNode(child,masterNode);
    }

    return map;
}

MindMap * MapFileReader::readFile(){
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly)){
        return nullptr;
    } else {
        QTextStream stream(&file);
        QJsonDocument document = QJsonDocument::fromJson(stream.readAll().toUtf8());
        MindMap * map = jsonToMap(document.object());
        map->setFilePath(filepath);

        return map;
    }
}
