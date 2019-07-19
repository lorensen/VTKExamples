#include "vtkSmartPointer.h"
#include "vtkCollisionDetectionFilter.h"

#include "vtkProperty.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"
#include "vtkSphereSource.h"
#include "vtkMatrix4x4.h"
#include "vtkTransform.h"
#include "vtkTextProperty.h"
#include "vtkTextActor.h"
#include "vtkNamedColors.h"

#include <thread>
#include <string>
#include <chrono>
#include <sstream>

int main(int argc, char *argv[])
{
  int contactMode = 0;
  if (argc > 1)
  {
    contactMode = std::stoi(std::string(argv[1]));
  }
  auto sphere0 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere0->SetRadius(.29);
  sphere0->SetPhiResolution(31);
  sphere0->SetThetaResolution(31);
  sphere0->SetCenter(0.0, 0, 0);

  auto sphere1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere1->SetPhiResolution(30);
  sphere1->SetThetaResolution(30);
  sphere1->SetRadius(0.3);

  auto matrix1 =
    vtkSmartPointer<vtkMatrix4x4>::New();
  auto transform0 =
    vtkSmartPointer<vtkTransform>::New();

  auto collide =
    vtkSmartPointer<vtkCollisionDetectionFilter>::New();
  collide->SetInputConnection(0, sphere0->GetOutputPort());
  collide->SetTransform(0, transform0);
  collide->SetInputConnection(1, sphere1->GetOutputPort());
  collide->SetMatrix(1, matrix1);
  collide->SetBoxTolerance(0.0);
  collide->SetCellTolerance(0.0);
  collide->SetNumberOfCellsPerNode(2);
  if (contactMode == 0)
  {
    collide->SetCollisionModeToAllContacts();
  }
  else if (contactMode == 1)
  {
    collide->SetCollisionModeToFirstContact();
  }
  else
  {
    collide->SetCollisionModeToHalfContacts();
  }
  collide->GenerateScalarsOn();

  // Visualize
  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  auto mapper1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper1->SetInputConnection(collide->GetOutputPort(0));
  mapper1->ScalarVisibilityOff();
  auto actor1 =
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(mapper1);
  actor1->GetProperty()->BackfaceCullingOn();
  actor1->SetUserTransform(transform0);
  actor1->GetProperty()->SetDiffuseColor(colors->GetColor3d("tomato").GetData());
  actor1->GetProperty()->SetRepresentationToWireframe();

  auto mapper2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper2->SetInputConnection(collide->GetOutputPort(1));

  auto actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);
  actor2->GetProperty()->BackfaceCullingOn();
  actor2->SetUserMatrix(matrix1);

  auto mapper3 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper3->SetInputConnection(collide->GetContactsOutputPort());
  mapper3->SetResolveCoincidentTopologyToPolygonOffset();

  auto actor3 =
    vtkSmartPointer<vtkActor>::New();
  actor3->SetMapper(mapper3);
  actor3->GetProperty()->SetColor(0,0,0);
  actor3->GetProperty()->SetLineWidth(3.0);

  auto txt =
    vtkSmartPointer<vtkTextActor>::New();
  txt->GetTextProperty()->SetFontSize(18);

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();
  renderer->AddActor(actor1);
  renderer->AddActor(actor2);
  renderer->AddActor(actor3);
  renderer->AddActor(txt);
  renderer->SetBackground(0.5,0.5,0.5);
  renderer->UseHiddenLineRemovalOn();

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);

  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Move the first object
  int numSteps = 100;;
  double dx = 1.0/ static_cast<double>(numSteps) * 2.0;
  transform0->Translate(-numSteps * dx - .3, 0.0, 0.0);
  renderWindow->Render();
  renderer->GetActiveCamera()->Azimuth(-60);
  renderer->GetActiveCamera()->Elevation(45);
  renderer->GetActiveCamera()->Dolly(1.2);

  for (int i = 0; i < numSteps; ++i)
  {
    transform0->Translate(dx, 0.0, 0.0);
    renderer->ResetCameraClippingRange();
    std::ostringstream textStream;
    textStream << collide->GetCollisionModeAsString() << ": Number of contact cells is " << collide->GetNumberOfContacts();
    txt->SetInput(textStream.str().c_str());
    renderWindow->Render();
    if (collide->GetNumberOfContacts() > 0)
    {
      break;
    }
    // The total animation time is 3 seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(3000/numSteps));
  }
  renderer->ResetCamera();
  renderWindow->Render();
  interactor->Start();
  collide->GetOutput(0)->Print(std::cout);
  collide->GetOutput(1)->Print(std::cout);
  return EXIT_SUCCESS;
}
