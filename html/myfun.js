
let indexOfStyle = parseInt($("#mysvg").attr("indexofstyle"));
let target;
let nodePos;
let mousePos;
let currentMousePos;
let isPressDown = false;
let targetNode = null;
let parentPos;
let isMasterNode = false;
let nodePath = null;

function matrixToInt(matrix) {
    let strs = matrix.split(',');
    return {
        x: parseInt(strs[4]),
        y: parseInt(strs[5])
    }
}

function intTomatrix(x,y){
    let mat = "matrix(1,0,0,1,"+x+","+y+")";
    return mat;
}

function getParentPos(pathString){
    let strs = pathString.split(" ")[0].split(',');
    return {
        x: parseInt(strs[0].substr(1,strs[0].length)),
        y: parseInt(strs[1])
    }
}

function computePath(style,parentPos,size){
    if(style === 0){
        let p = {   x: -(size.width/2),     y: size.height/2  }
        let c1 = {  x: (parentPos.x+p.x)/2, y: parentPos.y  }
        let c2 = {  x: (parentPos.x+p.x)/2, y: p.y  }
        let end = { x: size.width/2,        y: size.height/2 }
        
        return "M"+parentPos.x+","+parentPos.y+" C"+c1.x+","+c1.y+" "+c2.x+","+c2.y+" "+p.x+","+p.y+" L"+end.x+","+end.y;
    } else if(style > 0 && style <= 3) {
        let end = { x: -(size.width/2), y: 0 }
        let c = {   x: parentPos.x*0.9+end.x*0.1, y:end.y }
        return "M"+parentPos.x+","+parentPos.y+" Q"+c.x+","+c.y+" "+end.x+","+end.y;
    } else if(style > 3 && style <=6) {
        let end = { x: -(size.width/2), y: 0 }
        let c1 = {  x: parentPos.x+50,  y: parentPos.y }
        let c2 = {  x: c1.x,            y: end.y }
        
        return "M"+parentPos.x+","+parentPos.y+" L"+c1.x+","+c1.y+" L"+c2.x+","+c2.y+" L"+end.x+","+end.y;
    } else {
        return "";
    }    
}

function getColor(index){
    color = [[255,150,90],[115,200,255],[175,80,200],[255,205,60],[255,95,105],[100,200,205]];

    if(index <= 0) return "rgb(255,255,255)";

    let i = index % 6;
    let r = index / 6 % 4;

    return "rgb("+(color[i][0]-r*25)+","+(color[i][1]-r*25)+","+(color[i][2]-r*25)+")";
}

function createNewNode(index,parent_content){
    let parent = parent_content.parent();
    let parent_rect = parent_content.children().eq(0);
    let parent_text = parent_rect.next();
    let node = document.createElementNS("http://www.w3.org/2000/svg", "g");
    let node_content = document.createElementNS("http://www.w3.org/2000/svg", "g");
    console.log(node);
    node.setAttribute("class","node-container");
    node.setAttribute("transform","matrix(1,0,0,1,100,100)");
    node.setAttribute("stroke-width",parent.attr("stroke-width"));
    node.setAttribute("fill","#ffffff");
    node.setAttribute("stroke",parent.attr("stroke"));
    node_content.setAttribute("class","node");
    node.appendChild(node_content);

    let rect = document.createElementNS("http://www.w3.org/2000/svg", "rect");
    let text = document.createElementNS("http://www.w3.org/2000/svg", "text");
    rect.setAttribute("x","-72");
    rect.setAttribute("y","-22");
    rect.setAttribute("width","144");
    rect.setAttribute("height","45");
    rect.setAttribute("fill-opacity","0");
    text.setAttribute("x","-52");
    text.setAttribute("y","11");
    text.setAttribute("fill","#000000");
    text.appendChild(document.createTextNode("输入内容"));
    node_content.appendChild(rect);
    node_content.appendChild(text);

    let path = document.createElementNS("http://www.w3.org/2000/svg", "path");
    path.setAttribute("class","child-line");
    node.appendChild(path);
    if(index == 0){
        let pr = parent_rect[0].getBoundingClientRect();
        let parpos;
        rect.setAttribute("stroke-opacity","0");
        if(parseInt(parent.attr("isMaster"))){
            parpos = { x: -100, y: -100 }
            childlength = parent.children('.node-container').length;
            path.setAttribute("stroke",getColor(childlength));
        } else {
            parpos = { x: pr.width/2 - 100,y: pr.height/2 - 100}
            let parent_path = parent_content.next();
            path.setAttribute("stroke",parent_path.attr("stroke"));
        }
        path.setAttribute("d",computePath(index,parpos,{width: 144, height: 45}));
    } else if(index > 0 && index <= 3){
        let pr = parent_rect[0].getBoundingClientRect();
        let parpos = {
            x: pr.width/2 - 100,
            y: 0 - 100
        }
        path.setAttribute("d",computePath(index,parpos,{width: 144, height: 45}));
    } else if(index > 3 && index <= 6){
        let pr = parent_rect[0].getBoundingClientRect();
        let parpos = {
            x: pr.width/2 - 100,
            y: 0 - 100
        }
        path.setAttribute("d",computePath(index,parpos,{width: 144, height: 45}));
    }

    parent_content.before(node);
    removeListener();
    initNodeListener();
}


function initNodeListener(){
    
$(".node").dblclick(function(){
    let rect = $(this).children().eq(0);
    let txt = rect.next();
    let name = prompt("修改文本",txt.text());
    txt.text(name);
    
    let newWidth = txt[0].getBoundingClientRect().width+40;
    let newHeight = txt[0].getBoundingClientRect().height+20;
    let rex = -newWidth/2;
    let rey = -newHeight/2;
    let move = (newWidth - rect.attr("width"))/2;

    rect.attr("x",""+rex);
    rect.attr("y",""+rey);
    rect.attr("width",""+newWidth);
    rect.attr("height",""+newHeight);
    txt.attr("x",""+(rex+20));
    txt.attr("y",""+(rey+newHeight-10-2));

    let isMaster = parseInt(txt.parent().parent().attr("isMaster"));
    if(!isMaster){
        let path = txt.parent().next();
        let parentPos = getParentPos(path.attr("d"));
        path.attr("d",computePath(indexOfStyle,parentPos,{width:newWidth,height:newHeight}));
    }
    
    let parent = txt.parent().parent();
    if(!parseInt(parent.attr("isMaster")) || (indexOfStyle>3&&indexOfStyle<=6)){
        let children = txt.parent().parent().children('.node-container');
        for(let i=0;i<children.length;i++){
            let child = children.eq(i);
            let point = matrixToInt(child.attr("transform"));
            point.x = point.x + move;
            child.attr("transform",intTomatrix(point.x,point.y));
        }
    }  
});

$('.node').mousedown(function(event){
    targetNode = $(this).parent();
    if(parseInt(targetNode.attr("isMaster")))
        isMasterNode = true;
    else {
        nodePath = $(this).next();
        parentPos = getParentPos(nodePath.attr("d"));
    }
    
    nodePos = matrixToInt(targetNode.attr("transform"));
    mousePos = {
        x: event.pageX,
        y: event.pageY
    }
    isPressDown = true;
});

$('.node').mouseup(function(event){
    isPressDown = false;
    isMasterNode = false;
    targetNode = null;
    nodePath = null;
});

$('.node').focus(function(){
    let node = $(this);
    let rec = $("#markupRect");
    let recRect = $('#outline');
    let addIcon = $('#add_icon');
    let closeIcon = $('#close_icon');

    let nodeRect = node.children()[0].getBoundingClientRect();
    let width = nodeRect.width+10;
    let height = nodeRect.height+10;

    recRect.attr('x',""+(-width/2));
    recRect.attr('y',""+(-height/2));
    recRect.attr("width",""+width);
    recRect.attr("height",""+height);

    addIcon.attr('x',""+(width/2-10));
    addIcon.attr('y',""+(height/2-10));

    closeIcon.attr('x',""+(-width/2-10));
    closeIcon.attr('y',""+(-height/2-10));

    rec.css('display','inline-block');
    node.append(rec);
});

$('.node').blur(function(){
    let rec = $("#markupRect");
    rec.css('display','none');
});

}

function removeListener(){
    $('.node').unbind();
}

$("#mysvg").mousemove(function(event){
    if(isPressDown && targetNode!=null){
        currentMousePos = {
            x: event.pageX,
            y: event.pageY
        }

        let gap = {
            dx: currentMousePos.x - mousePos.x,
            dy: currentMousePos.y - mousePos.y
        }

        let newPos = {
            x: nodePos.x + gap.dx,
            y: nodePos.y + gap.dy
        }

        targetNode.attr("transform",intTomatrix(newPos.x,newPos.y));
        if(!isMasterNode){
            let newParent = {
                x: parentPos.x - gap.dx,
                y: parentPos.y - gap.dy
            }
            let rect = targetNode.children('.node').children('rect')[0].getBoundingClientRect();
            let size = {
                width: rect.width,
                height: rect.height
            }
            nodePath.attr("d",computePath(indexOfStyle,newParent,size));
        }
    }
});

$(document).ready(function(){
    $("#close_icon").attr("href","data:image/png;base64,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");
    $("#add_icon").attr("href","data:image/png;base64,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");
    initNodeListener();
});

$('#close_icon').click(function(){
    let node = $(this).parent().parent().parent();
    let parent = node.parent();
    let rec = $("#markupRect");
    rec.css('display','none');
    parent.append(rec);
    node.remove();
})

$('#add_icon').click(function(){
    let node_content = $(this).parent().parent();
    createNewNode(indexOfStyle,node_content);
})
