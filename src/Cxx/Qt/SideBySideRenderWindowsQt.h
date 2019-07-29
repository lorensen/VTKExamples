#ifndef SideBySideRenderWindowsQt_H
#define SideBySideRenderWindowsQt_H

#include <vtkSmartPointer.h>

#include <QMainWindow>

#include "ui_SideBySideRenderWindowsQt.h"

class SideBySideRenderWindowsQt : public QMainWindow,
                                  private Ui::SideBySideRenderWindowsQt
{
  Q_OBJECT
public:
  // Constructor/Destructor
  SideBySideRenderWindowsQt();
  ~SideBySideRenderWindowsQt() = default;

public slots:

  void slotExit();
};

#endif
