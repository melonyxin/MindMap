#ifndef NODE_H
#define NODE_H

#include <QPushButton>
#include <QGraphicsItem>
#include "nodestyle.h"

class NodeStyle;
class Node : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Node(QGraphicsItem * parent = nullptr, QString content="");
    ~Node() override;

    void setContent(QString content);
    void setIndexOfMaster(int index);
    void setNodePainter(NodeStyle * style);

    void addNewNode();
    bool isMasterNode();

    QString getContent();
    QRectF getCustomRect(void) const;
    int getIndexOfMaster();
    QSize getSize();

private:
    QString content;
    QSize size;
    int indexOfMaster=0;
    NodeStyle * nodePainter = nullptr;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QPainterPath shape() const override;
    void updateSize();
    qreal getDistance(QPointF a,QPointF b);
    bool isClosed();
    void setChildNodeStyle(NodeStyle * style);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;
//    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;


signals:

};

#endif // NODE_H
