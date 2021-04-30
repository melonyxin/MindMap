#ifndef SVGEXPORTER_H
#define SVGEXPORTER_H

#include "mindmap.h"
#include "exporterofmap.h"

class SVGExporter : public ExporterOfMap
{
public:
    SVGExporter();
    virtual bool exportAsFile(MindMap *map, QString filename) override;
};

#endif // SVGEXPORTER_H
