#include "ModelInfo.h"
#include "glwidget.h"

void ModelInfo::printInfo(){
    Scene* scn= scene();
	const vector< Object >& objs= scn-> objects();
    
    // # Objectes
    cout << "Num Objs: "<< objs.size() << endl;
    
    int numV= 0, numP= 0, num3VPol= 0;
    
    for(uint i=0; i < objs.size(); ++i){
        numP += objs[i].faces().size();
        
        const vector< Face > & fcs= objs[i].faces();
        
        for(uint j=0; j < fcs.size(); ++j){
            if (fcs[i].numVertices() == 3) ++num3VPol;
            numV += fcs[i].numVertices();
        }
    }
    
    cout << "Num Vertex: " << numV << endl;
    cout << "Num Poligon: " << numP << endl;
    cout << "Percent trigangles: " << float(num3VPol/numP)*100.0 << "%" << endl;
}

void ModelInfo::onPluginLoad()
{
    printInfo();
}

void ModelInfo::preFrame()
{
	
}

void ModelInfo::postFrame()
{
    //printInfo();
}

void ModelInfo::onObjectAdd()
{
    printInfo();
}

bool ModelInfo::drawScene()
{
	return false; // return true only if implemented
}

bool ModelInfo::drawObject(int)
{
	return false; // return true only if implemented
}

bool ModelInfo::paintGL()
{
	return false; // return true only if implemented
}

void ModelInfo::keyPressEvent(QKeyEvent *)
{
	
}

void ModelInfo::mouseMoveEvent(QMouseEvent *)
{
	
}

