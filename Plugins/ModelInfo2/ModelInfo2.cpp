#include "ModelInfo2.h"
#include "glwidget.h"

void ModelInfo2::getInfo(int& numO,int& numV, int& numP, int& prcnt){
    Scene* scn= scene();
	const vector< Object >& objs= scn-> objects();
    
    // # Objectes
    numO= objs.size();
    
    int num3VPol= 0;
    
    for(uint i=0; i < objs.size(); ++i){
        numP += objs[i].faces().size();
        
        const vector< Face > & fcs= objs[i].faces();
        
        for(uint j=0; j < fcs.size(); ++j){
            if (fcs[i].numVertices() == 3) ++num3VPol;
            numV += fcs[i].numVertices();
        }
    }
    
    prcnt = float(num3VPol/numP)*100.0;
}

void ModelInfo2::postFrame()
{
	int numO = 0, numV = 0, numP = 0, prcnt = 0;
    getInfo(numO,numV,numP,prcnt);
    
    QFont font;
    font.setPixelSize(32);
    painter.begin(glwidget());
    painter.setFont(font);
    
    int x = 10;
    int y = 40;
    
    QString str = QString("NumObjects: %1 NumVertices: %L2 NumPoligons: %L3 Percentage: %L4").arg(numO).arg(numV).arg(numP).arg(prcnt);
    
    painter.drawText(x, y, str);    
    painter.end();
}

