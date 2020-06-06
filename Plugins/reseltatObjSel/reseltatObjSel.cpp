#include "reseltatObjSel.h"
#include "glwidget.h"

void ReseltatObjSel::onPluginLoad()
{
	GLWidget & g = *glwidget();
    g.makeCurrent();
	
	//CREAR I COMPILAR SHADERS PER SELECCIONAR
	vsSel = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsSel->compileSourceFile(g.getPluginPath()+"/../reseltatObjSel/baseMouseSel.vert");

    fsSel = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsSel->compileSourceFile(g.getPluginPath()+"/../reseltatObjSel/baseMouseSel.frag");

	programSel = new QOpenGLShaderProgram(this);
    programSel->addShader(vsSel);
    programSel->addShader(fsSel);
    programSel->link();

	//CREAR I COMPILAR SHADERS PER DIBUIXAR SA BBOX
	vsDbb= new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsDbb->compileSourceFile(g.getPluginPath()+"/../reseltatObjSel/dbb.vert");

	fsDbb= new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsDbb->compileSourceFile(g.getPluginPath()+"/../reseltatObjSel/dbb.frag");

	programDbb = new QOpenGLShaderProgram(this);
    programDbb->addShader(vsDbb);
    programDbb->addShader(fsDbb);
    programDbb->link();

	//CREAR VAO I VBO'S PER SA BBOX
	createBuffers();
}

void ReseltatObjSel::preFrame()
{
	programSel->bind();

	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programSel->setUniformValue("modelViewProjectionMatrix", MVP);
	programSel->setUniformValue("select_on", false);
}

void ReseltatObjSel::postFrame()
{
	if(scene()->selectedObject() > -1){
		programDbb->bind();

    	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    	programDbb->setUniformValue("modelViewProjectionMatrix", MVP);

    	GLWidget &g = *glwidget();
    	g.makeCurrent();
		
		// MODE PINTAR WIREFRAME
    	g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		const auto &objs = scene()->objects();
		const auto &elem = objs[scene()->selectedObject()];

		programDbb->setUniformValue("bbm", elem.boundingBox().min());
        programDbb->setUniformValue("bbM", elem.boundingBox().max());

        g.glBindVertexArray(VAO_bbox);              // Que enviam com a "vertex"
        g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
        g.glBindVertexArray(0);

		// MODE PINTAR PER DEFECTE
		g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    	programDbb->release();
	}
	
}

void ReseltatObjSel::onObjectAdd()
{
	
}

bool ReseltatObjSel::drawScene()
{
	return false; // return true only if implemented
}

bool ReseltatObjSel::drawObject(int)
{
	return false; // return true only if implemented
}

bool ReseltatObjSel::paintGL()
{
	return false; // return true only if implemented
}

void ReseltatObjSel::keyPressEvent(QKeyEvent *)
{
	
}

void ReseltatObjSel::mouseMoveEvent(QMouseEvent *)
{
	
}

void ReseltatObjSel::mouseReleaseEvent(QMouseEvent* e) 
{
	if(!(e->button()&Qt::RightButton))return;
	if(e->modifiers()&(Qt::ShiftModifier))return;
	if(!(e->modifiers()&Qt::ControlModifier))return;

	GLWidget & g = *glwidget();
    g.makeCurrent();

	g.glClearColor(1,1,1,1);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	programSel->bind();

	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programSel->setUniformValue("modelViewProjectionMatrix", MVP);

	programSel->setUniformValue("select_on", true);

	for (uint i=0; i < scene()->objects().size(); i++) {
		GLubyte color[4];
		encodeID(i,color);
		
		// cout << int(color[0]) << " " << int(color[1]) << " " << int(color[2]) << endl;

		programSel->setUniformValue("color",QVector4D(color[0]/255.,color[1]/255.,color[2]/255.,1.));
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

void ReseltatObjSel::encodeID(uint i, GLubyte* color)
{
	color[0]= (i/(256*256))%256;
	color[1]= (i/256)%256;
	color[2]= i%256;
	color[3]= 1.0;
}

void ReseltatObjSel::createBuffers(){
	GLWidget &g = *glwidget();
    g.makeCurrent();
	
	g.glGenVertexArrays(1, &VAO_bbox);
    g.glBindVertexArray(VAO_bbox);

    float vertices[] = {
        0, 1, 0, // Front-top-left      1
        1, 1, 0, // Front-top-right     2
        0, 1, 1, // Front-bottom-left   3
        1, 1, 1, // Front-bottom-right  4
        1, 0, 1, // Back-bottom-right   5
        1, 1, 0, // Front-top-right     6
        1, 0, 0, // Back-top-right      7
        0, 1, 0, // Front-top-left      8
        0, 0, 0, // Back-top-left       9
        0, 1, 1, // Front-bottom-left   10
        0, 0, 1, // Back-bottom-left    11
        1, 0, 1, // Back-bottom-right   12
        0, 0, 0, // Back-top-left       13
        1, 0, 0  // Back-top-right      14
    };

    g.glGenBuffers(1, &VBO_vertices);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);


   float colors[] = { 1, 0, 0,  
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0,
                      1, 0, 0};

    GLuint VBO_colors;
    g.glGenBuffers(1, &VBO_colors);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);

    g.glBindVertexArray(0);
}