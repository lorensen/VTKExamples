#include <QApplication>
#include "SideBySideRenderWindowsQt.h"

int main( int argc, char** argv )
{
  // QT Stuff
  QApplication app( argc, argv );
  
  SideBySideRenderWindowsQt sideBySideRenderWindowsQt;
  sideBySideRenderWindowsQt.show();
  
  return app.exec();
}
