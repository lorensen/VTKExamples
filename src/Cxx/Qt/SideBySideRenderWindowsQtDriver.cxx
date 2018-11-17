#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>

#include "SideBySideRenderWindowsQt.h"

int main( int argc, char** argv )
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

  // QT Stuff
  QApplication app( argc, argv );
  
  SideBySideRenderWindowsQt sideBySideRenderWindowsQt;
  sideBySideRenderWindowsQt.show();
  
  return app.exec();
}
