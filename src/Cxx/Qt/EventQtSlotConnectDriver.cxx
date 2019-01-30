#include <QApplication>
#include <QSurfaceFormat>
#include "EventQtSlotConnect.h"

int main(int argc, char** argv)
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

  QApplication app(argc, argv);

  EventQtSlotConnect eventQtSlotConnect;
  eventQtSlotConnect.show();

  return app.exec();
}
