#ifndef MINDMAPVIEW_H
#define MINDMAPVIEW_H

#include <QObject>
#include <QGraphicsView>

class MindMapView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MindMapView(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPoint _mouseLBtnDown;
    bool _isLBtnDown = false;

signals:

};

#endif // MINDMAPVIEW_H
