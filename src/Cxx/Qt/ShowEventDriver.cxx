#include <QApplication>

#include "ShowEvent.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  ShowEvent showEvent;

  showEvent.show();
  return app.exec();
}
