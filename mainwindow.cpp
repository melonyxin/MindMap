#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mindmap.h"
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

    QGraphicsRectItem * rect1 = new QGraphicsRectItem(-100,-100,200,200);
    QGraphicsRectItem * rect2 = new QGraphicsRectItem(-100,-100,200,200);
    QGraphicsRectItem * rect3 = new QGraphicsRectItem(-100,-100,200,200);
    rect1->setBrush(QBrush(Qt::blue));
    rect2->setBrush(QBrush(Qt::red));
    rect3->setBrush(QBrush(Qt::yellow));

    //board1->addItem(rect1);
    //board2->addItem(rect2);
    //board3->addItem(rect3);

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

//    QGraphicsScene * scene = new QGraphicsScene(this);
//    QGraphicsRectItem * rect = new QGraphicsRectItem(-100,-100,200,200);
//    rect->setBrush(QBrush(Qt::blue));
//    QGraphicsRectItem * rect2 = new QGraphicsRectItem(-100,-100,200,200);
//    rect2->setBrush(QBrush(Qt::red));
//    scene->addItem(rect);
//    scene->addItem(rect2);
//    QGraphicsView * view = new QGraphicsView(this);
//    view->resize(800, 400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsView * MainWindow::createTab(MindMap * scene){
    QGraphicsView * view = new QGraphicsView(scene, this);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    //view->resize(800, 400);
    return view;
}
