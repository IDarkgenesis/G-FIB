#include "showDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{   
    numVR = 0;
    float totalV=0;
    
	Scene* scn= scene();
	const vector< Object >& objs= scn-> objects();
    
    for(uint i=0; i < objs.size(); ++i){
        
        const vector< Face > & fcs= objs[i].faces();
        
        totalV += objs[i].vertices().size();
        
        for(uint j=0; j < fcs.size(); ++j){
            numVR += fcs[i].numVertices();
        }
    }
    numVR /= totalV;
}

void ShowDegree::postFrame()
{
	QFont font;
    font.setPixelSize(32);
    painter.begin(glwidget());
    painter.setFont(font);
    
    int x = 10;
    int y = 40;
    
    QString str = QString("Average: %1 ").arg(numVR);
    
    painter.drawText(x, y, str);    
    painter.end();
}







