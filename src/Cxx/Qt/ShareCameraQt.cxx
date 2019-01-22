#include "ShareCameraQt.h"

#include <vtkCommand.h>
#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>

#include <vtkSmartPointer.h>

// Constructor
ShareCameraQt::ShareCameraQt()
{
  this->setupUi(this);

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  // 8.1.0+
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindowLeft;
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindowRight;
#else
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindowLeft = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindowRight = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
#endif
  this->qvtkWidgetLeft->SetRenderWindow(renderWindowLeft);
  this->qvtkWidgetRight->SetRenderWindow(renderWindowRight);

  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  // Cube
  vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);

  // VTK Renderer
  vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
  leftRenderer->AddActor(sphereActor);

  vtkSmartPointer<vtkRenderer> rightRenderer = vtkSmartPointer<vtkRenderer>::New();

  // Add Actor to renderer
  rightRenderer->AddActor(cubeActor);

  // VTK/Qt wedded
  this->qvtkWidgetLeft->GetRenderWindow()->AddRenderer(leftRenderer);
  this->qvtkWidgetRight->GetRenderWindow()->AddRenderer(rightRenderer);

  rightRenderer->ResetCamera();
  leftRenderer->ResetCamera();

  rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());

  // Set up action signals and slots
  connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

  //this->qvtkWidgetLeft->GetRenderWindow()->AddObserver(vtkCommand::ModifiedEvent, this, &ShareCameraQt::ModifiedHandler);
  this->qvtkWidgetLeft->GetRenderWindow()->AddObserver(vtkCommand::AnyEvent, this, &ShareCameraQt::ModifiedHandler);

}

void ShareCameraQt::ModifiedHandler()
{
  this->qvtkWidgetRight->GetRenderWindow()->Render();
}

void ShareCameraQt::slotExit()
{
  qApp->exit();
}
