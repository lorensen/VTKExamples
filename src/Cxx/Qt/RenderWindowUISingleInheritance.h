#ifndef RenderWindowUISingleInheritance_H
#define RenderWindowUISingleInheritance_H

#include <vtkSmartPointer.h>

#include <QMainWindow>

// Forward Qt class declarations
class Ui_RenderWindowUISingleInheritance;

class RenderWindowUISingleInheritance : public QMainWindow
{
  Q_OBJECT
public:
  // Constructor/Destructor
  RenderWindowUISingleInheritance();
  ~RenderWindowUISingleInheritance() = default;

public slots:

  void slotExit();

private:
  // Designer form
  Ui_RenderWindowUISingleInheritance* ui;
};

#endif
