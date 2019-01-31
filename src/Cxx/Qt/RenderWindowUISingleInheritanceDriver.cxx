#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

#include "RenderWindowUISingleInheritance.h"
 
int main( int argc, char** argv )
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

  // QT Stuff
  QApplication app( argc, argv );
 
  RenderWindowUISingleInheritance renderWindowUISingleInheritance;
  renderWindowUISingleInheritance.show();
 
  return app.exec();
}
