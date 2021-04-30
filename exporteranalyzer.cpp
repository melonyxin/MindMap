#include "exporteranalyzer.h"
#include "imageexporter.h"
#include "svgexporter.h"
#include "htmlexporter.h"

ExporterAnalyzer::ExporterAnalyzer()
{

}

ExporterOfMap* ExporterAnalyzer::createExporter(int index){
    switch (index) {
    case 0: return new ImageExporter();
    case 1: return new HTMLExporter();
    case 2: return new SVGExporter();
    default: return new ImageExporter();
    }
}
