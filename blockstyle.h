#ifndef BLOCKSTYLE_H
#define BLOCKSTYLE_H

#include "nodestyle.h"

class BlockStyle : public NodeStyle
{
public:
    BlockStyle(QString color="#73A1BF");
    virtual void paint(QPainter *painter, Node *parent, Node *item) override;

private:
    int lineWidth = 3;
    QColor theme;
};

#endif // BLOCKSTYLE_H
