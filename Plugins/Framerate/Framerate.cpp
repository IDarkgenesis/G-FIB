#include "Framerate.h"
#include "glwidget.h"


void Framerate::oneSecondPassed(){
    cout << "Fps: " << frames << endl;
    frames = 0;
}

void Framerate::onPluginLoad()
{
    frames=0;
    QTimer *frameTimer=new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()), this, SLOT(oneSecondPassed()));
    frameTimer->start(1000);}

void Framerate::preFrame()
{
    frames += 1;
}


