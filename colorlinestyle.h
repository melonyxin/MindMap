#ifndef COLORLINESTYLE_H
#define COLORLINESTYLE_H

#include "nodestyle.h"

class ColorLineStyle : public NodeStyle
{
public:
    ColorLineStyle();
    virtual void paint(QPainter *painter, Node *parent, Node *item) override;

};

#endif // COLORLINESTYLE_H
