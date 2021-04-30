#ifndef NODESTYLE_H
#define NODESTYLE_H

#include <QPainter>
#include "node.h"
#include <QtXml>

class Node;
class NodeStyle
{
public:
    NodeStyle();
    ~NodeStyle();
    virtual void paint(QPainter *painter, Node *parent, Node *item) = 0;
    virtual QDomElement focusToDom(QDomDocument *doc);
    virtual QDomElement nodeToDom(QDomDocument *doc,Node *node);
    QFont getFont();
    QSize getPadding();
    QSize getMargin();
    int getRadiusSize();

protected:
    QPixmap closePixmap;
    QPixmap addPixmap;
    int radiusSize;
    QSize padding;
    QSize margin;
    QFont font;
    int penWidth;
};

#endif // NODESTYLE_H
