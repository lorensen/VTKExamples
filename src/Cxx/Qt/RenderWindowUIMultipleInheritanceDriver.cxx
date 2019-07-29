#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

#include "RenderWindowUIMultipleInheritance.h"

int main(int argc, char** argv)
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

  QApplication app(argc, argv);

  RenderWindowUIMultipleInheritance renderWindowUIMultipleInheritance;
  renderWindowUIMultipleInheritance.show();

  return app.exec();
}
