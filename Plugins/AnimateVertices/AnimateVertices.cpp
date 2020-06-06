#include "AnimateVertices.h"
#include "glwidget.h"

void AnimateVertices::onPluginLoad()
{   
    // Posar path i compilar es vertex shader
    QString vs_path="../../../../G-FIB/Shaders/animate-vertices1.vert";
    vertexShader= new QOpenGLShader(QOpenGLShader::Vertex,this);
    vertexShader->compileSourceFile(vs_path);
    
    // Posar path i compilar es vertex shader
    QString fs_path="../../../../G-FIB/Shaders/animate-vertices1.frag";
    fragmentShader= new QOpenGLShader(QOpenGLShader::Fragment,this);
    fragmentShader->compileSourceFile(fs_path);
    
    // Linkar shaders
    program= new QOpenGLShaderProgram(this);
    program->addShader(vertexShader);
    program->addShader(fragmentShader);
    program->link();
    
    // Crear timer per es vertexShader
    elapsedTimer= QElapsedTimer();
    elapsedTimer.start();
}

void AnimateVertices::preFrame()
{
    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0f));
    QMatrix3x3 NM= camera()->viewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", NM); 
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
}

void AnimateVertices::postFrame()
{
	// unbind shader
    program->release();
}

void AnimateVertices::onObjectAdd()
{
	
}

bool AnimateVertices::drawScene()
{
	return false; // return true only if implemented
}

bool AnimateVertices::drawObject(int)
{
	return false; // return true only if implemented
}

bool AnimateVertices::paintGL()
{
	return false; // return true only if implemented
}

void AnimateVertices::keyPressEvent(QKeyEvent *)
{
	
}

void AnimateVertices::mouseMoveEvent(QMouseEvent *)
{
	
}

