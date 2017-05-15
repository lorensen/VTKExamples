#include <QApplication>
#include "RenderWindowUISingleInheritance.h"
 
int main( int argc, char** argv )
{
  // QT Stuff
  QApplication app( argc, argv );
 
  RenderWindowUISingleInheritance renderWindowUISingleInheritance;
  renderWindowUISingleInheritance.show();
 
  return app.exec();
}
