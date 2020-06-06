#ifndef _RESELTATOBJSEL_H
#define _RESELTATOBJSEL_H

#include "plugin.h" 

class ReseltatObjSel: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
	 bool drawScene();
	 bool drawObject(int);

	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);
	 void mouseReleaseEvent(QMouseEvent *);

	 void encodeID(uint, GLubyte*);
	 void createBuffers();
  private:
	// add private methods and attributes here
	QOpenGLShaderProgram* programSel;
    QOpenGLShaderProgram* programDbb;
	QOpenGLShader* vsSel;
    QOpenGLShader* fsSel;
	QOpenGLShader* vsDbb;
    QOpenGLShader* fsDbb;
	GLuint VAO_bbox;
    GLuint VBO_vertices;
    GLuint VBO_colors;
};

#endif



