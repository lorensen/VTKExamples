#include <QApplication>
#include "ShareCameraQt.h"

int main( int argc, char** argv )
{
  // QT Stuff
  QApplication app( argc, argv );
  
  ShareCameraQt shareCameraQt;
  shareCameraQt.show();
  
  return app.exec();
}
