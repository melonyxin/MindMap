#ifndef EXPORTEROFMAP_H
#define EXPORTEROFMAP_H

#include "mindmap.h"

class ExporterOfMap
{
public:
    ExporterOfMap();
    virtual bool exportAsFile(MindMap *map, QString filename) = 0;
};

#endif // EXPORTEROFMAP_H
