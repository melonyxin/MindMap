#include "coloranalyzer.h"

ColorAnalyzer::ColorAnalyzer()
{

}

const int ColorAnalyzer::color[6][3]={
    {255,150,90},    // 橙
    {115,200,255},   // 蓝
    {175,80,200},   // 紫
    {255,205,60},    // 黄
    {255,95,105},    // 红
    {100,200,205}    // 青
};

QColor ColorAnalyzer::getColor(int index){
    int i = index % num;
    int r = index / num % round;

    return QColor(color[i][0]-r*25,color[i][1]-r*25,color[i][2]-r*25);
}
