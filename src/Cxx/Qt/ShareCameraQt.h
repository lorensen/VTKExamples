#ifndef ShareCameraQt_H
#define ShareCameraQt_H

#include "ui_ShareCameraQt.h"
#include <QMainWindow>

class ShareCameraQt : public QMainWindow, public Ui::ShareCameraQt
{
  Q_OBJECT
public:
  // Constructor/Destructor
  ShareCameraQt();
  ~ShareCameraQt() = default;

public slots:

  void slotExit();

protected:
  void ModifiedHandler();
};

#endif
