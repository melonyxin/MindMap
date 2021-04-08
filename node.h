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
    QSize n_size = QSize(20,20);
    int m_nInterval = 20;
    int m_nEllipseWidth = 12;    // 半径

    // 画笔设置
    QColor m_cPenColor;
    int m_nPenWidth = 1;
    // 画刷设置
    QColor m_cBrushColor;

protected:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QRectF getCustomRect(void) const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


signals:

};

#endif // NODE_H
