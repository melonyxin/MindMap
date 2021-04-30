#ifndef COLORLINESTYLE_H
#define COLORLINESTYLE_H

#include "nodestyle.h"

class ColorLineStyle : public NodeStyle
{
public:
    ColorLineStyle();
    virtual void paint(QPainter *painter, Node *parent, Node *item) override;
    virtual QDomElement focusToDom(QDomDocument *doc) override;
    virtual QDomElement nodeToDom(QDomDocument *doc,Node *node) override;

};

#endif // COLORLINESTYLE_H
