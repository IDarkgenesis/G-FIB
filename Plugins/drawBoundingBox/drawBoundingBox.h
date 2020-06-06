#ifndef _DRAWBOUNDINGBOX_H
#define _DRAWBOUNDINGBOX_H

#include "plugin.h" 

class DrawBoundingBox: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
    void onPluginLoad();
    void postFrame();
  private:
	// add private methods and attributes here
    GLuint VAO_bbox;
    GLuint VBO_vertices;
    GLuint VBO_colors;
    QOpenGLShaderProgram* program;
    QOpenGLShader *fs; 
    QOpenGLShader *vs;
};

#endif
