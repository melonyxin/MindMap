#ifndef HTMLEXPORTER_H
#define HTMLEXPORTER_H

#include  "exporterofmap.h"
#include <QtXml>
#include <QDebug>

class HTMLExporter : public ExporterOfMap
{
public:
    HTMLExporter();
    virtual bool exportAsFile(MindMap *map, QString filename) override;

private:
    QDomDocument doc;
    QDomElement svg;
protected:
    void initHtml(QString filename, int indexOfStyle);
    QDomElement nodeToElement(Node *node);
};

#endif // HTMLEXPORTER_H
