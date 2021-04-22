#include "nodestyleanalyzer.h"
#include "colorlinestyle.h"
#include "blockstyle.h"
#include "polylinestyle.h"

NodeStyleAnalyzer::NodeStyleAnalyzer()
{

}

NodeStyle* NodeStyleAnalyzer::createNodeStyle(int index){
    switch (index) {
    case 0: return new ColorLineStyle();
    case 1: return new BlockStyle("#73A1BF");    // 天空蓝
    case 2: return new BlockStyle("#BF7373");    // 清新红
    case 3: return new BlockStyle("#BF9373");    // 泥土黄
    case 4: return new PolylineStyle("#73A1BF");    // 天空蓝
    case 5: return new PolylineStyle("#BF7373");    // 清新红
    case 6: return new PolylineStyle("#BF9373");    // 泥土黄
    default: return new ColorLineStyle();
    }
}
