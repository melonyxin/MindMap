#ifndef IMAGEEXPORTER_H
#define IMAGEEXPORTER_H

#include "mindmap.h"
#include "exporterofmap.h"

class ImageExporter : public ExporterOfMap
{
public:
    ImageExporter();
    virtual bool exportAsFile(MindMap *map, QString filename) override;
};

#endif // IMAGEEXPORTER_H
