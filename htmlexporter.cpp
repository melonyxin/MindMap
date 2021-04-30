#include "htmlexporter.h"
#include "nodestyle.h"

HTMLExporter::HTMLExporter()
{

}

bool HTMLExporter::exportAsFile(MindMap *map, QString filename){
    QFile file(filename);
    if(!file.open(QFile::WriteOnly))
        return false;

    initHtml(map->getFilename(),map->getIndexOfStyle());

    NodeStyle* painter = map->getNodePainter();
    Node* masterNode = map->getMasterNode();

    svg.appendChild(painter->focusToDom(&doc));
    svg.appendChild(painter->nodeToDom(&doc,masterNode));

    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格

    QFile jsfile(":/html/myfun.js");
    if(jsfile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString jsString(jsfile.readAll());
        out_stream<<"<script>\n"+jsString+"\n</script>\n"<<endl;
        jsfile.close();
    }

    file.close();

    return true;
}

void HTMLExporter::initHtml(QString filename, int indexOfStyle){
    QDomElement html=doc.createElement("html");
    doc.appendChild(html);

    QDomElement head=doc.createElement("head");
    html.appendChild(head);

    QDomElement title=doc.createElement("title");
    title.appendChild(doc.createTextNode(filename));
    head.appendChild(title);

    QDomElement jquery=doc.createElement("script");
    jquery.setAttribute("src","https://cdn.staticfile.org/jquery/1.10.2/jquery.min.js");
    jquery.appendChild(doc.createTextNode(""));
    head.appendChild(jquery);

    QFile cssfile(":/html/mystyle.css");
    if(cssfile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QDomElement style=doc.createElement("style");
        QString styleString(cssfile.readAll());
        style.appendChild(doc.createTextNode(styleString));
        html.appendChild(style);
        cssfile.close();
    }


    QDomElement body=doc.createElement("body");
    html.appendChild(body);

    svg=doc.createElement("svg");
    svg.setAttribute("width","100%");
    svg.setAttribute("height","100%");
    svg.setAttribute("xmlns","http://www.w3.org/2000/svg");
    svg.setAttribute("xmlns:xlink","http://www.w3.org/1999/xlink");
    svg.setAttribute("version","1.2");
    svg.setAttribute("baseProfile","tiny");
    svg.setAttribute("id","mysvg");
    svg.setAttribute("indexofstyle",QString::number(indexOfStyle));
    body.appendChild(svg);
}
