#ifndef _BASESELECTMOUSE_H
#define _BASESELECTMOUSE_H

#include "plugin.h" 

class BaseSelectMouse: public QObject, public Plugin
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
  private:
	// add private methods and attributes here
	QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;
};

#endif
