#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mindmap.h"
#include "mindmapview.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTabWidget * tabWidget = new QTabWidget();
    QTabBar * tabBar = tabWidget->tabBar();
    MindMap * board1 = new MindMap(this, "first");
    MindMap * board2 = new MindMap(this, "second");
    MindMap * board3 = new MindMap(this, "third");

    tabWidget->addTab(createTab(board1), board1->getFilename());
    tabWidget->addTab(createTab(board2), board2->getFilename());
    tabWidget->addTab(createTab(board3), board3->getFilename());
    tabWidget->setTabsClosable(true);
    connect(tabBar,&QTabBar::tabCloseRequested,tabWidget,&QTabWidget::removeTab);
    connect(ui->actionNewFile,&QAction::triggered,[=](){
        MindMap * board = new MindMap(this, "NewFile");
        tabWidget->addTab(createTab(board),board->getFilename());
    });
    setCentralWidget(tabWidget);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsView * MainWindow::createTab(MindMap * scene){
    MindMapView * view = new MindMapView(this);
    view->setScene(scene);
    return view;
}
