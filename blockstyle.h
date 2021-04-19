#ifndef BLOCKSTYLE_H
#define BLOCKSTYLE_H

#include "nodestyle.h"

class BlockStyle : public NodeStyle
{
public:
    BlockStyle();
    virtual void paint(QPainter *painter, Node *parent, Node *item) override;
};

#endif // BLOCKSTYLE_H
