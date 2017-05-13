#include <iostream>

#include "ShowEvent.h"

ShowEvent::ShowEvent(QWidget *myParent) : QWidget(myParent)
{
  this->setupUi(this);

  // Do not do anything related to VTK display here!
}

void ShowEvent::showEvent(QShowEvent *)
{
  // Instead, do the VTK display things here!
}
