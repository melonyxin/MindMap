#include "svgexporter.h"
#include <QtSvg/QSvgGenerator>

SVGExporter::SVGExporter()
{

}

bool SVGExporter::exportAsFile(MindMap *map, QString filename){
    QSvgGenerator generator;
    generator.setFileName(filename);

    QRectF rect = map->itemsBoundingRect();
    rect.adjust(-30,-30,30,30);

    generator.setSize(rect.size().toSize());
    //generator.setViewBox(rect);

    generator.setTitle(("SVG Generator Example Drawing"));

    generator.setDescription(("An SVG drawing created by the SVG Generator Example provided with Qt."));

    QPainter painter(&generator);
    map->render(&painter, QRectF(),rect);   //关键函数

    return true;
}
