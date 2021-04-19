#include "nodestyleanalyzer.h"
#include "colorlinestyle.h"
#include "blockstyle.h"

NodeStyleAnalyzer::NodeStyleAnalyzer()
{

}

NodeStyle* NodeStyleAnalyzer::createNodeStyle(int index){
    switch (index) {
        case 0: return new ColorLineStyle();
        case 1: return new BlockStyle();
        default: return new ColorLineStyle();
    }
}
