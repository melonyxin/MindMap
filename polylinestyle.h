#ifndef POLYLINESTYLE_H
#define POLYLINESTYLE_H

#include "nodestyle.h"

class PolylineStyle : public NodeStyle
{
public:
    PolylineStyle(QString color="#73A1BF");
    virtual void paint(QPainter *painter, Node *parent, Node *item) override;

private:
    int lineWidth = 3;
    QColor theme;
};

#endif // POLYLINESTYLE_H
