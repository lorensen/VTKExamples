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
#include <vtkVersion.h>

// Constructor
ShareCameraQt::ShareCameraQt()
{
  this->setupUi(this);

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindowLeft;
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindowRight;
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  this->qvtkWidgetLeft->setRenderWindow(renderWindowLeft);
  this->qvtkWidgetRight->setRenderWindow(renderWindowRight);
#else
  this->qvtkWidgetLeft->SetRenderWindow(renderWindowLeft);
  this->qvtkWidgetRight->SetRenderWindow(renderWindowRight);
#endif

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
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  this->qvtkWidgetLeft->renderWindow()->AddRenderer(leftRenderer);
  this->qvtkWidgetRight->renderWindow()->AddRenderer(rightRenderer);
#else
  this->qvtkWidgetLeft->GetRenderWindow()->AddRenderer(leftRenderer);
  this->qvtkWidgetRight->GetRenderWindow()->AddRenderer(rightRenderer);
#endif

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

#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  this->qvtkWidgetLeft->renderWindow()->AddObserver(
      vtkCommand::ModifiedEvent, this, &ShareCameraQt::ModifiedHandler);
#else
  this->qvtkWidgetLeft->GetRenderWindow()->AddObserver(
      vtkCommand::ModifiedEvent, this, &ShareCameraQt::ModifiedHandler);
#endif
}

void ShareCameraQt::ModifiedHandler()
{
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  this->qvtkWidgetRight->renderWindow()->Render();
#else
  this->qvtkWidgetRight->GetRenderWindow()->Render();
#endif
}

void ShareCameraQt::slotExit()
{
  qApp->exit();
}
