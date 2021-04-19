#include "mapfilewriter.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>

MapFileWriter::MapFileWriter(MindMap *map)
{
    target = map;
}

QJsonObject MapFileWriter::nodeToJson(Node *node){
    QJsonObject root;
    QJsonObject data;
    QJsonArray children;

    data.insert("content", node->getContent());
    data.insert("pos_x", node->pos().x());
    data.insert("pos_y", node->pos().y());
    data.insert("indexOfMaster", node->getIndexOfMaster());

    QList<QGraphicsItem *> childs = node->childItems();
    for(int i=0;i<childs.length();i++){
        children.append(nodeToJson((Node *)childs[i]));
    }

    root.insert("data",data);
    root.insert("children",children);

    return root;
}

QJsonObject MapFileWriter::mindmapToJson(MindMap *map){
    QJsonObject root;
    QJsonObject masterNode = nodeToJson(map->getMasterNode());

    root.insert("MasterNode", masterNode);
    root.insert("IndexOfStyle", map->getIndexOfStyle());
    root.insert("FileName", map->getFilename());

    return root;
}

bool MapFileWriter::writeFile(){
    QJsonObject root = mindmapToJson(target);
    QJsonDocument document;
    document.setObject(root);
    QByteArray byteArray = document.toJson();

    QFile file(target->getFilePath());

    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return false;
    }
    else
    {
        QTextStream stream(&file);
        stream << byteArray;
        stream.flush();
        file.close();
        return true;
    }
}
