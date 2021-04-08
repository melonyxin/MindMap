#ifndef MINDMAP_H
#define MINDMAP_H

#include <QGraphicsScene>
#include "node.h"

class MindMap : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MindMap(QWidget *parent = nullptr, QString filename="");
    QString getFilename();

private:
    QString filename;
    Node masterNode;

signals:

};

#endif // MINDMAP_H
