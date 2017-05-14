#include <QApplication>
#include "BorderWidgetQt.h"

int main(int argc, char* argv[])
{
  QApplication app( argc, argv );

  BorderWidgetQt borderWidgetQt;
  borderWidgetQt.show();

  return app.exec();
}
