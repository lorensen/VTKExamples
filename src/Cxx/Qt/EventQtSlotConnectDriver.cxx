#include <QApplication>
#include "EventQtSlotConnect.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  EventQtSlotConnect eventQtSlotConnect;
  eventQtSlotConnect.show();

  return app.exec();
}
