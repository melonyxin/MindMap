#ifndef EXPORTERANALYZER_H
#define EXPORTERANALYZER_H

#include "exporterofmap.h"

class ExporterAnalyzer
{
public:
    ExporterAnalyzer();
    static ExporterOfMap* createExporter(int index);
};

#endif // EXPORTERANALYZER_H
