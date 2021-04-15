#ifndef NODE_H
#define NODE_H

#include <QPushButton>
#include <QGraphicsItem>

class Node : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Node(QGraphicsItem * parent = nullptr, QString content="");
    ~Node() override;
    QString getContent();
    void setContent(QString content);
    void setPenColor(QColor c);
    void addNewNode();
    bool isMasterNode();

private:
    QString content;
    QSize size;
    QFont font;
    int numOfChild=0;

    QSize padding = QSize(20,10);

    // 画笔设置
    QColor penColor;
    int penWidth = 5;
    // 画刷设置
    QColor m_cBrushColor;

    QPixmap closePixmap;
    QPixmap addPixmap;
    int radiusSize = 20;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QPainterPath shape() const override;
    QRectF getCustomRect(void) const;
    void updateSize();
    qreal getDistance(QPointF a,QPointF b);
    bool isClosed();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;
//    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;


signals:

};

#endif // NODE_H
