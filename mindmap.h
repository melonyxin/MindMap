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

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;

signals:

};

#endif // MINDMAP_H
