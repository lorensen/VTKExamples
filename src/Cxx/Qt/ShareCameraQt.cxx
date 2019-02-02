#include "ShareCameraQt.h"

#include <vtkCamera.h>
#include <vtkCommand.h>
#include <vtkCubeSource.h>
#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkQtTableView.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

// Constructor
ShareCameraQt::ShareCameraQt() {
  this->setupUi(this);

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindowLeft;
  this->qvtkWidgetLeft->SetRenderWindow(renderWindowLeft);
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindowRight;
  this->qvtkWidgetRight->SetRenderWindow(renderWindowRight);

  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());

  // Cube
  vtkSmartPointer<vtkCubeSource> cubeSource =
      vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetColor(
      colors->GetColor4d("MediumSeaGreen").GetData());

  // VTK Renderer
  vtkSmartPointer<vtkRenderer> leftRenderer =
      vtkSmartPointer<vtkRenderer>::New();
  leftRenderer->AddActor(sphereActor);
  leftRenderer->SetBackground(colors->GetColor3d("LightSteelBlue").GetData());

  vtkSmartPointer<vtkRenderer> rightRenderer =
      vtkSmartPointer<vtkRenderer>::New();

  // Add Actor to renderer
  rightRenderer->AddActor(cubeActor);
  rightRenderer->SetBackground(colors->GetColor3d("LightSteelBlue").GetData());

  // VTK/Qt wedded
  this->qvtkWidgetLeft->GetRenderWindow()->AddRenderer(leftRenderer);
  this->qvtkWidgetRight->GetRenderWindow()->AddRenderer(rightRenderer);

  rightRenderer->ResetCamera();
  leftRenderer->ResetCamera();

  // Here we share the camera
  rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());

  // Position the cube using the left renderer active camera
  leftRenderer->GetActiveCamera()->SetPosition(1.0, 0.8, 1.0);
  leftRenderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  leftRenderer->ResetCamera();
  leftRenderer->GetActiveCamera()->Zoom(0.8);

  // Set up action signals and slots
  connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

  this->qvtkWidgetLeft->GetRenderWindow()->AddObserver(
      vtkCommand::ModifiedEvent, this, &ShareCameraQt::ModifiedHandler);
}

void ShareCameraQt::ModifiedHandler() {
  this->qvtkWidgetRight->GetRenderWindow()->Render();
}

void ShareCameraQt::slotExit() { qApp->exit(); }
