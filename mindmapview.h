#ifndef MINDMAPVIEW_H
#define MINDMAPVIEW_H

#include <QObject>
#include <QGraphicsView>
#include "node.h"
#include <QPlainTextEdit>

class MindMapView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MindMapView(QWidget *parent = nullptr,QPlainTextEdit *textEdit=nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPoint _mouseLBtnDown;
    bool _isLBtnDown = false;
    Node * focusNode = nullptr;
    QPlainTextEdit *textEdit;

signals:

};

#endif // MINDMAPVIEW_H
