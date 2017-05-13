#include <QApplication>
#include "RenderWindowUIMultipleInheritance.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  RenderWindowUIMultipleInheritance renderWindowUIMultipleInheritance;
  renderWindowUIMultipleInheritance.show();

  return app.exec();
}
