#include "nodestyleanalyzer.h"
#include "colorlinestyle.h"
#include "blockstyle.h"

NodeStyleAnalyzer::NodeStyleAnalyzer()
{

}

NodeStyle* NodeStyleAnalyzer::createNodeStyle(int index){
    switch (index) {
    case 0: return new ColorLineStyle();
    case 1: return new BlockStyle("#73A1BF");    // 天空蓝
    case 2: return new BlockStyle("#BF7373");    // 清新红
    case 3: return new BlockStyle("#BF9373");    // 泥土黄
    default: return new ColorLineStyle();
    }
}
