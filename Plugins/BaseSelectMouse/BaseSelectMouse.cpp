#include "BaseSelectMouse.h"
#include "glwidget.h"

void BaseSelectMouse::onPluginLoad()
{
	GLWidget & g = *glwidget();
    g.makeCurrent();
	
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../BaseSelectMouse/baseMouseSel.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../BaseSelectMouse/baseMouseSel.frag");

	program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

void BaseSelectMouse::preFrame()
{
	program->bind();

	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
	program->setUniformValue("select_on", false);
}

void BaseSelectMouse::postFrame()
{
	
}

void BaseSelectMouse::onObjectAdd()
{
	
}

bool BaseSelectMouse::drawScene()
{
	return false; // return true only if implemented
}

bool BaseSelectMouse::drawObject(int)
{
	return false; // return true only if implemented
}

bool BaseSelectMouse::paintGL()
{
	return false; // return true only if implemented
}

void BaseSelectMouse::keyPressEvent(QKeyEvent *)
{
	
}

void BaseSelectMouse::mouseMoveEvent(QMouseEvent *)
{
	
}

void BaseSelectMouse::mouseReleaseEvent(QMouseEvent* e) 
{
	if(!(e->button()&Qt::RightButton))return;
	if(e->modifiers()&(Qt::ShiftModifier))return;
	if(!(e->modifiers()&Qt::ControlModifier))return;

	GLWidget & g = *glwidget();
    g.makeCurrent();

	g.glClearColor(1,1,1,1);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	program->bind();

	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

	program->setUniformValue("select_on", true);

	for (uint i=0; i < scene()->objects().size(); i++) {
		GLubyte color[4];
		encodeID(i,color);
		
		// cout << int(color[0]) << " " << int(color[1]) << " " << int(color[2]) << endl;

		program->setUniformValue("color",QVector4D(color[0]/255.,color[1]/255.,color[2]/255.,1.));
		drawPlugin()->drawObject(i);
	}

	int x = e->x();
	int y = glwidget()->height() - e->y();
	GLubyte read[4];
	glReadPixels(x,y,1,1,GL_RGBA, GL_UNSIGNED_BYTE,read);
	int index = read[2] + read[1]*256 + read[0]*256*256;

	if(read[0] != 255 && read[1] != 255 && read[2] != 255) scene()->setSelectedObject(index);
	// cout << int(read[0]) << " " << int(read[1]) << " " << int(read[2]) << "->" << index << endl;
	 
	g.update();

}

void BaseSelectMouse::encodeID(uint i, GLubyte* color)
{
	color[0]= (i/(256*256))%256;
	color[1]= (i/256)%256;
	color[2]= i%256;
	color[3]= 1.0;
}