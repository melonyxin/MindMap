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

private:
    QString content;
    QSize size;
    QFont font;

    QSize padding = QSize(20,10);

    // 画笔设置
    QColor m_cPenColor;
    int m_nPenWidth = 3;
    // 画刷设置
    QColor m_cBrushColor;

    QPointF pressPos;
    QPointF startPos;
    QPointF screenPos;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QPainterPath shape() const override;
    QRectF getCustomRect(void) const;
    void updateSize();
//    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;
//    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;
//    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;


signals:

};

#endif // NODE_H
