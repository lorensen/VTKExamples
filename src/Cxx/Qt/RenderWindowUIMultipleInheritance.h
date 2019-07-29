#ifndef RenderWindowUIMultipleInheritance_H
#define RenderWindowUIMultipleInheritance_H

#include "ui_RenderWindowUIMultipleInheritance.h"

#include <QMainWindow>

class RenderWindowUIMultipleInheritance
  : public QMainWindow,
    private Ui::RenderWindowUIMultipleInheritance
{
  Q_OBJECT
public:
  RenderWindowUIMultipleInheritance();

public slots:

  void slotExit();
};

#endif
