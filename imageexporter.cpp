#include "imageexporter.h"
#include <QImage>

ImageExporter::ImageExporter()
{

}

bool ImageExporter::exportAsFile(MindMap *map, QString filename){
    QRectF rect = map->itemsBoundingRect();
    rect.adjust(-30,-30,30,30);
    QImage image(rect.size().toSize(),QImage::Format_RGB32);
    QPainter painter(&image);
    map->render(&painter, QRectF(),rect);   //关键函数
    if(image.save(filename));
        return true;

    return false;
}
