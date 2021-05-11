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
    void setRemark(QString remark);


    void addNewNode();
    bool isMasterNode();

    QString getContent();
    QString getRemark();
    QRectF getCustomRect(void) const;
    int getIndexOfMaster();
    QSize getSize();

private:
    QString content;
    QString remark;
    QSize size;
    int indexOfMaster=0;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QPainterPath shape() const override;
    void updateSize();
    qreal getDistance(QPointF a,QPointF b);
    bool isClosed();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;
//    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;


signals:

};

#endif // NODE_H
