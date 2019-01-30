#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

#include "BorderWidgetQt.h"

int main(int argc, char* argv[])
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

  QApplication app( argc, argv );

  BorderWidgetQt borderWidgetQt;
  borderWidgetQt.show();

  return app.exec();
}
