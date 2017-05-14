//This example describes the transformation pipeline. Robotic arm was used to demonstrate an example.
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground( 0.1, 0.2, 0.4 );

  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(600, 600);
  renWin->SetWindowName("Robotic Arm");

  vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  //arm
  vtkSmartPointer<vtkCylinderSource> arm = vtkSmartPointer<vtkCylinderSource>::New();
  arm->SetRadius(8);
  arm->SetHeight(20);
  arm->SetResolution(20);

  vtkSmartPointer<vtkPolyDataMapper> armMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  armMapper->SetInputConnection(arm->GetOutputPort());

  vtkSmartPointer<vtkTransform> armTransform = vtkSmartPointer<vtkTransform>::New();

  vtkSmartPointer<vtkActor> armActor = vtkSmartPointer<vtkActor>::New();
  armActor->SetUserTransform(armTransform);
  armActor->SetMapper(armMapper);
  armActor->GetProperty()->SetColor(0.7,0.6,0.3);

  //forearm
  vtkSmartPointer<vtkCylinderSource> forearm = vtkSmartPointer<vtkCylinderSource>::New();
  forearm->SetRadius(6);
  forearm->SetHeight(15);
  forearm->SetResolution(20);
  forearm->SetCenter(*(arm->GetCenter()),*(arm->GetCenter()+1)+forearm->GetHeight(),*(arm->GetCenter()+2));

  vtkSmartPointer<vtkPolyDataMapper> forearmMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  forearmMapper->SetInputConnection(forearm->GetOutputPort());

  vtkSmartPointer<vtkTransform> forearmTransform = vtkSmartPointer<vtkTransform>::New();
  forearmTransform->SetInput(armTransform);

  vtkSmartPointer<vtkActor> forearmActor = vtkSmartPointer<vtkActor>::New();
  forearmActor->SetUserTransform(forearmTransform);
  forearmActor->SetMapper(forearmMapper);
  forearmActor->GetProperty()->SetColor(0.1,0.2,0.9);

  //hand
  vtkSmartPointer<vtkCylinderSource> hand = vtkSmartPointer<vtkCylinderSource>::New();
  hand->SetRadius(4);
  hand->SetHeight(10);
  hand->SetResolution(20);
  hand->SetCenter(*(forearm->GetCenter()),*(forearm->GetCenter()+1)+hand->GetHeight(),*(forearm->GetCenter()+2));

  vtkSmartPointer<vtkPolyDataMapper> handMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  handMapper->SetInputConnection(hand->GetOutputPort());

  vtkSmartPointer<vtkTransform> handTransform = vtkSmartPointer<vtkTransform>::New();
  handTransform->SetInput(forearmTransform);

  vtkSmartPointer<vtkActor> handActor = vtkSmartPointer<vtkActor>::New();
  handActor->SetUserTransform(handTransform);
  handActor->SetMapper(handMapper);
  handActor->GetProperty()->SetColor(0.6,0.9,0.1);


  ren1->AddActor(armActor);
  ren1->AddActor(forearmActor);
  ren1->AddActor(handActor);

  renWin->Render();

  //execution of robot arm motion
  for (int i = 0; i <45; i++)
  {
    armTransform->Identity();
    armTransform->RotateZ(-i);
    renWin->Render();
  }
  //execution of robot forearm motion
  for (int i = 0; i <45; i++)
  {
    forearmTransform->Identity();
    forearmTransform->RotateZ(i);
    renWin->Render();
  }

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
