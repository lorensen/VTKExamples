#ifndef ShowEventQt_H
#define ShowEventQt_H

#include "ui_ShowEvent.h"

class ShowEvent : public QWidget, private Ui::ShowEvent
{
Q_OBJECT

public:
  ShowEvent(QWidget *parent = 0);

protected:
  void showEvent ( QShowEvent * event );
};

#endif
