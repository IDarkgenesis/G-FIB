#include "base.h"
#include "glwidget.h"

void Base::onPluginLoad()
{
	const auto &objs = scene()->objects();
	const auto &elem = objs[0];
	Point bbm = elem.boundingBox().min();
	Point bbM = elem.boundingBox().max();

	Point center= (bbM + bbm)/2.;

	//cout << center << endl;
	const auto &vertices = objs[0].vertices();
	auto fcs= objs[0].faces();
	float area = 0;
	
	for(uint i=0; i < fcs.size();++i){
		int idvtx[3];
		for (uint j=0; j < 3; ++j){
			idvtx[j]=fcs[i].vertexIndex(j);
		}
		float ymin= min( vertices[idvtx[0]].coord().y(), min( vertices[idvtx[1]].coord().y(),vertices[idvtx[2]].coord().y() ) );

		if (ymin < center.y() ){
			Vector u = vertices[idvtx[1]].coord() - vertices[idvtx[0]].coord();
			Vector v = vertices[idvtx[2]].coord() - vertices[idvtx[0]].coord();

			Vector w = Vector( ( u.y()*v.z() - u.z()*v.y() ), ( u.z()*v.x() - u.x()*v.z() ), ( u.x()*v.y() - u.y()*v.x() ) );

			area += w.length();
		}
	}
	cout << "Area: " << area/2. << endl;
}

void Base::preFrame()
{
	
}

void Base::postFrame()
{
	
}

void Base::onObjectAdd()
{
	
}

bool Base::drawScene()
{
	return false; // return true only if implemented
}

bool Base::drawObject(int)
{
	return false; // return true only if implemented
}

bool Base::paintGL()
{
	return false; // return true only if implemented
}

void Base::keyPressEvent(QKeyEvent *)
{
	
}

void Base::mouseMoveEvent(QMouseEvent *)
{
	
}

