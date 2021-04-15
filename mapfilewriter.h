#ifndef MAPFILEWRITER_H
#define MAPFILEWRITER_H

#include "mindmap.h"

class MapFileWriter
{
public:
    MapFileWriter(MindMap *map);
    bool writeFile();

private:
    MindMap * target;

protected:
    QJsonObject nodeToJson(Node *node);
    QJsonObject mindmapToJson(MindMap *map);
};

#endif // MAPFILEWRITER_H
