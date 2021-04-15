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
    Node *jsonToNode(QJsonObject root);
    MindMap *jsonToMap(QJsonObject root);
};

#endif // MAPFILEREADER_H
