#ifndef ShareCameraQt_H
#define ShareCameraQt_H

#include <QMainWindow>
#include "ui_ShareCameraQt.h"

class ShareCameraQt : public QMainWindow, public Ui::ShareCameraQt
{
  Q_OBJECT
public:

  // Constructor/Destructor
  ShareCameraQt(); 
  ~ShareCameraQt() {};

public slots:

  virtual void slotExit();

protected:
   void ModifiedHandler();
};

#endif
