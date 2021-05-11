#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "mindmap.h"
#include "mindmapview.h"
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPlainTextEdit *getTextEdit();

private:
    Ui::MainWindow *ui;
    QList<QAction *> actionList;
    QList<int> mapStyleList;
    QGraphicsView * createTab(MindMap * scene);
    QPlainTextEdit * textEdit;

protected:
    void saveMindMapFile(MindMap * map);
    MindMap * openMindMapFile();
};
#endif // MAINWINDOW_H
