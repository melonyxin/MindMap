#include "nodestyle.h"

NodeStyle::NodeStyle()
{
    closePixmap = QPixmap::fromImage(QImage(":/img/close.png"));
    addPixmap =  QPixmap::fromImage(QImage(":/img/add.png"));
}

NodeStyle::~NodeStyle(){

}

QFont NodeStyle::getFont(){
    return font;
}

QSize NodeStyle::getPadding(){
    return padding;
}

QSize NodeStyle::getMargin(){
    return margin;
}

int NodeStyle::getRadiusSize(){
    return radiusSize;
}

QDomElement NodeStyle::focusToDom(QDomDocument *doc){

}
QDomElement NodeStyle::nodeToDom(QDomDocument *doc,Node *node){

}
