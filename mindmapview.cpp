#include "mindmapview.h"
#include <QMouseEvent>
#include <QtDebug>
#include <QGraphicsItem>
#include <QInputDialog>
#include <node.h>
#include "mainwindow.h"

MindMapView::MindMapView(QWidget *parent,QPlainTextEdit *textEdit) : QGraphicsView(parent)
{
    //隐藏水平/竖直滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    //设置场景范围
    setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);
    //反锯齿
    setRenderHints(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);

    setBackgroundBrush(QColor(238,238,243));
    this->textEdit = textEdit;
}

void MindMapView::mousePressEvent(QMouseEvent *event) {
    QGraphicsView::mousePressEvent(event);

    QPointF pointScene=mapToScene(event->pos()); //转换到Scene坐标
    QGraphicsItem  *item=NULL;
    QGraphicsScene * scene = this->scene();
    item=scene->itemAt(pointScene,transform()); //获取光标下的绘图项

    if (item == NULL){ //没有绘图项
        if(focusNode != nullptr){
            focusNode->setRemark(textEdit->toPlainText());
        }
        focusNode = nullptr;
        textEdit->clear();
        return;
    }

    if(item->type()==65536){
        if(focusNode != nullptr){
            focusNode->setRemark(textEdit->toPlainText());
        }
        focusNode = (Node *) item;
        textEdit->clear();
        textEdit->appendPlainText(focusNode->getRemark());
    }
}

void MindMapView::mouseDoubleClickEvent(QMouseEvent *event){
    QGraphicsView::mouseDoubleClickEvent(event);

    QPointF pointScene=mapToScene(event->pos()); //转换到Scene坐标
    QGraphicsItem  *item=NULL;
    QGraphicsScene * scene = this->scene();
    item=scene->itemAt(pointScene,transform()); //获取光标下的绘图项

    if (item == NULL) //没有绘图项
        return;

    if(item->type()==65536){
        Node * target = (Node *) item;
        QString newContent = QInputDialog::getText(this, tr(""),"修改内容：", QLineEdit::Normal,target->getContent(),
                                                    Q_NULLPTR, Qt::SplashScreen);
        target->setContent(newContent);
    }
}
