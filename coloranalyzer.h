#ifndef COLORANALYZER_H
#define COLORANALYZER_H
#include <QColor>

class ColorAnalyzer
{
public:
    ColorAnalyzer();
    static QColor getColor(int index);

private:
    const static int color[6][3];
    const static int grad = 25;
    const static int round = 3;
    const static int num = 6;
};

#endif // COLORANALYZER_H
