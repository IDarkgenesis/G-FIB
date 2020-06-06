// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "reflection.h"
#include <QCoreApplication>

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Reflection::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    
    // Carregar shader, compile & link 
    vsInv = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsInv->compileSourceFile(g.getPluginPath()+"/../reflection/invert.vert");

    fsInv = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsInv->compileSourceFile(g.getPluginPath()+"/../reflection/invert.frag");

    vsTex = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsTex->compileSourceFile(g.getPluginPath()+"/../reflection/texturize.vert");

    fsTex = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsTex->compileSourceFile(g.getPluginPath()+"/../reflection/texturize.frag");

    vsBsc = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsBsc->compileSourceFile(g.getPluginPath()+"/../reflection/bsc.vert");

    fsBsc = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsBsc->compileSourceFile(g.getPluginPath()+"/../reflection/bsc.frag");

    program1 = new QOpenGLShaderProgram(this);
    program1->addShader(vsInv);
    program1->addShader(fsInv);
    program1->link();

    program2 = new QOpenGLShaderProgram(this);
    program2->addShader(vsBsc);
    program2->addShader(fsBsc);
    program2->link();

    program3 = new QOpenGLShaderProgram(this);
    program3->addShader(vsTex);
    program3->addShader(fsTex);
    program3->link();


    Scene* scn= scene();
    vector< Object >& objs= scn-> objects();
    objs[0].computeBoundingBox();
    
    m = objs[0].boundingBox().min();
    M = objs[0].boundingBox().max();

    // Setup texture
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures( 1, &textureId);
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		      GL_LINEAR_MIPMAP_LINEAR );
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT,
		   0, GL_RGB, GL_FLOAT, NULL);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    // Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
}

  
bool Reflection::paintGL()
{
    GLWidget & g = *glwidget();

    // Pass 1. DIBUIXAR ESCENA INVERTIDA
    g.glClearColor(0.8,0.8,0.8,1);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	program1->bind();
    program1->setUniformValue("bbm", m);
    program1->setUniformValue("bbM", M);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program1->setUniformValue("modelViewProjectionMatrix", MVP);

    if (drawPlugin()) drawPlugin()->drawScene();

    // GUARDAR TEXTURA ESCENA INVERTIDA
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,
			  IMAGE_WIDTH, IMAGE_HEIGHT);
    g.glGenerateMipmap(GL_TEXTURE_2D);

    //Pas 2. DIBUIXAR ESCENA NORMAL
    
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    program2-> bind();
    
    program2-> setUniformValue("modelViewProjectionMatrix", MVP);

    if (drawPlugin()) drawPlugin()->drawScene();
    
    // Pass 3. Draw quad using texture

    

    program3->bind();
    program3->setUniformValue("colorMap", 0);
    program3->setUniformValue("SIZE", float(IMAGE_WIDTH));
    program3->setUniformValue("modelViewProjectionMatrix", MVP);

    // quad covering viewport 
    
    float r = scene()->boundingBox().radius();
    
    drawQuad(Point(-r,m.y(), r), Point( r,m.y(), r),
	     Point( r,m.y(),  -r), Point(-r,m.y(), -r)); 
    
    g.defaultProgram()->bind();
    g.glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Reflection::drawQuad(const Point& p0, const Point& p1, const Point& p2, const Point& p3)
{
    static bool created = false;
    static GLuint VAO_rect;
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        // Create VBO with (x,y,z) coordinates
        float coords[] = { p0.x(), p0.y(), p0.z(), p1.x(), p1.y(), p1.z(), p3.x(), p3.y(), p3.z(), p2.x(), p2.y(), p2.z() };

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        //glBindVertexArray(0);

        float normals[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0};

        GLuint VBO_normals;
        g.glGenBuffers(1, &VBO_normals);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
        g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(1);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray(VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}