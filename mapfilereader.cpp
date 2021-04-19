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

Node * MapFileReader::jsonToNode(QJsonObject root){
    QJsonObject data = root.value("data").toObject();
    QJsonArray children = root.value("children").toArray();

    Node * node = new Node();
    node->setContent(data.value("content").toString());
    node->setIndexOfMaster(data.value("indexOfMaster").toInt());

    for(int i=0,len=children.size();i<len;i++){
        QJsonObject child = children.at(i).toObject();
        Node * childNode = jsonToNode(child);
        childNode->setParentItem(node);
        QJsonObject childData = child.value("data").toObject();
        int x = childData.value("pos_x").toInt();
        int y = childData.value("pos_y").toInt();
        childNode->setPos(QPointF(x,y));
    }

    return node;
}

MindMap * MapFileReader::jsonToMap(QJsonObject root){
    QJsonObject master = root.value("MasterNode").toObject();

    MindMap * map = new MindMap();
    map->setFileName(root.value("FileName").toString());
    Node * masterNode = jsonToNode(master);
    map->addMasterNode(masterNode);
    masterNode->setParentItem(0);
    map->setIndexOfStyle(root.value("IndexOfStyle").toInt());
    int x = master.value("pos_x").toInt();
    int y = master.value("pos_y").toInt();
    masterNode->setPos(QPointF(x,y));

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
