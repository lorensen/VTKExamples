#include <QApplication>
#include <QSurfaceFormat>
#include "BorderWidgetQt.h"

int main(int argc, char* argv[])
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

  QApplication app( argc, argv );

  BorderWidgetQt borderWidgetQt;
  borderWidgetQt.show();

  return app.exec();
}
