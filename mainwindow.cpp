#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mindmap.h"
#include "mindmapview.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QFileDialog>
#include "mapfilewriter.h"
#include "mapfilereader.h"
#include "colorlinestyle.h"
#include <QMessageBox>
#include <QDebug>
#include "exporteranalyzer.h"
#include "exporterofmap.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  样式选项互斥组
    QActionGroup *grp = new QActionGroup(this);
    QList<QAction *> itemsOfStyle = ui->menuStyle->actions();
    for(int i=0;i<itemsOfStyle.length();i++){
        QMenu * menu = itemsOfStyle[i]->menu();
        if(menu == nullptr)
            grp->addAction(itemsOfStyle[i]);
        else {
            QList<QAction *> options = menu->actions();
            for(int j=0;j<options.length();j++){
                grp->addAction(options[j]);
            }
        }
    }
    actionList = grp->actions();

    QTabWidget * tabWidget = new QTabWidget();
    QTabBar * tabBar = tabWidget->tabBar();
    tabWidget->setTabsClosable(true);

    // 样式选项被点击事件，切换样式
    connect(grp,&QActionGroup::triggered,this,[=](QAction* style){
        int index = actionList.indexOf(style);
        int current = tabBar->currentIndex();
        if(current < 0) return;
        if(current >= mapStyleList.length()) return;
        if(mapStyleList.at(current) == index) return;

        QGraphicsView * view = (QGraphicsView *) tabWidget->currentWidget();
        MindMap * currentMap = (MindMap *) view->scene();
        currentMap->setIndexOfStyle(index);
        mapStyleList[current] = index;
    });

    // 脑图标签页关闭；新建脑图按钮
    connect(tabBar,&QTabBar::tabCloseRequested,tabWidget,&QTabWidget::removeTab);
    connect(ui->actionNewFile,&QAction::triggered,[=](){
        MindMap * board = new MindMap(this, "NewFile");
        Node *masterNode = new Node();
        board->addMasterNode(masterNode);
        masterNode->setContent("开始");
        masterNode->setPos(QPointF(0,0));  
        mapStyleList.append(board->getIndexOfStyle());
        tabWidget->addTab(createTab(board),board->getFilename());
    });

    // 保存文件按钮
    connect(ui->actionSaveFile,&QAction::triggered,[=](){
        QGraphicsView * view = (QGraphicsView *) tabWidget->currentWidget();
        if(view==nullptr) {
            QMessageBox::critical(this, "错误", tr("请先打开一个脑图！"),QMessageBox::Yes);
            return;
        }
        MindMap * current = (MindMap *) view->scene();
        saveMindMapFile(current);
        tabBar->setTabText(tabBar->currentIndex(),current->getFilename());
    });

    // 打开文件按钮
    connect(ui->actionOpenFile,&QAction::triggered,[=](){
        MindMap * map = openMindMapFile();
        if(map!=nullptr){
            mapStyleList.append(map->getIndexOfStyle());
            tabWidget->addTab(createTab(map),map->getFilename());
        }
    });

    // 脑图标签栏切换点击事件：切换对应选中样式
    connect(tabBar,&QTabBar::currentChanged,[=](int index){
        if(index < 0) return;
        if(index >= mapStyleList.length()) return;
        if(mapStyleList[index] >= actionList.length()) return;
        actionList[mapStyleList[index]]->setChecked(true);
    });

    // 脑图标签移除事件
    connect(tabBar,&QTabBar::tabCloseRequested,[=](int index){
        mapStyleList.removeAt(index);
    });


    // 导出按钮组
    QActionGroup *exporterGroup = new QActionGroup(this);
    QList<QAction *> itemsOfExporter = ui->menuExport->actions();
    for(int i=0;i<itemsOfExporter.length();i++)
        exporterGroup->addAction(itemsOfExporter[i]);

    connect(exporterGroup,&QActionGroup::triggered,this,[=](QAction* style){
        int index = itemsOfExporter.indexOf(style);
        QGraphicsView * view = (QGraphicsView *) tabWidget->currentWidget();
        if(view==nullptr) {
            QMessageBox::critical(this, "错误", tr("请先打开一个脑图！"),QMessageBox::Yes);
            return;
        }
        MindMap * current = (MindMap *) view->scene();
        QString suffix[] = {
            "图片文件(*.PNG)",
            "网页文件(*.html)",
            "SVG文件(*.svg)"
        };
        QString fileName = QFileDialog::getSaveFileName(this,tr("导出"),current->getFilename(),suffix[index]);
        ExporterOfMap * exporter = ExporterAnalyzer::createExporter(index);
        if(!exporter->exportAsFile(current,fileName)){
            QMessageBox::critical(this, "错误", tr("保存失败！"),QMessageBox::Yes);
        }
    });

    setCentralWidget(tabWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveMindMapFile(MindMap *map){
    if(map->isPathEmpty()){
        QString fileName = QFileDialog::getSaveFileName(this,tr("保存当前思维导图"),map->getFilename(),tr("思维导图文件(*.mind)"));
        map->setFilePath(fileName);
        QString name = map->getFilePath().section('/',-1).section('.',0,0);
        map->setFileName(name);
    }

    MapFileWriter writer(map);
    if(!writer.writeFile()){
        QMessageBox::critical(this, "错误", tr("文件保存失败！"),QMessageBox::Yes);
    }
}

MindMap * MainWindow::openMindMapFile(){
    QString filepath = QFileDialog::getOpenFileName(this,"打开思维导图",QDir::currentPath(),tr("思维导图文件(*.mind)"));
    if(filepath.isEmpty()){
        QMessageBox::critical(this, "错误", tr("文件名不能为空！"),QMessageBox::Yes);
        return nullptr;
    }
    MapFileReader reader(filepath);
    return reader.readFile();
}

QGraphicsView * MainWindow::createTab(MindMap * scene){
    MindMapView * view = new MindMapView(this);
    view->setScene(scene);
    return view;
}
