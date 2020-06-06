#include "drawBoundingBox.h"
#include "glwidget.h"

void DrawBoundingBox::onPluginLoad()
{
    //VAO_bbox

    GLWidget &g = *glwidget();
    g.makeCurrent();

    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../drawBoundingBox/dbb.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../drawBoundingBox/dbb.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

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

void DrawBoundingBox::postFrame()
{   

    program->bind();

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

    GLWidget &g = *glwidget();
    g.makeCurrent();

    g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    const auto &objs = scene()->objects();

    for (const auto &elem : objs){
        
        program->setUniformValue("bbm", elem.boundingBox().min());
        program->setUniformValue("bbM", elem.boundingBox().max());

        g.glBindVertexArray(VAO_bbox);              // Que enviam com a "vertex"
        g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
        g.glBindVertexArray(0);
    }

    g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    program->release();
}
