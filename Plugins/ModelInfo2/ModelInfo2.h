#ifndef _MODELINFO2_H
#define _MODELINFO2_H

#include "plugin.h" 
#include <QPainter>

class ModelInfo2: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
    void postFrame() Q_DECL_OVERRIDE;
    void getInfo(int& numO, int& numV, int& numP, int& prcnt);
  private:
	// add private methods and attributes here
    QPainter painter;
};

#endif
