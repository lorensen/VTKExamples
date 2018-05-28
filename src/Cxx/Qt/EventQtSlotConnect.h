#ifndef EventQtSlotConnect_H
#define EventQtSlotConnect_H

#include "ui_EventQtSlotConnect.h"

#include <QMainWindow>

#include <vtkSmartPointer.h>
#include <vtkObject.h>
class vtkEventQtSlotConnect;

class EventQtSlotConnect : public QMainWindow, private Ui::EventQtSlotConnect
{
  Q_OBJECT
public:

  EventQtSlotConnect();

public slots:

  void slot_clicked(vtkObject*, unsigned long, void*, void*);

private:

  vtkSmartPointer<vtkEventQtSlotConnect> Connections;
};

#endif
