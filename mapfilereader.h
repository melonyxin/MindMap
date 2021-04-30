#ifndef MAPFILEREADER_H
#define MAPFILEREADER_H

#include "mindmap.h"

class MapFileReader
{
public:
    MapFileReader(QString path="");
    MindMap *readFile();

private:
    QString filepath;

protected:
    void jsonToNode(QJsonObject root, Node *parent);
    MindMap *jsonToMap(QJsonObject root);
};

#endif // MAPFILEREADER_H
