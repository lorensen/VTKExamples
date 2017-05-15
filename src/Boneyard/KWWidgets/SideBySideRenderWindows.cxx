#include <vtkKWApplication.h>
#include <vtkKWRenderWidget.h>
#include <vtkKWWindow.h>

#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkActor.h>

int main(int argc, char *argv[])
{
  // Initialize Tcl
  Tcl_Interp *interp = vtkKWApplication::InitializeTcl(argc, argv, &cerr);

  vtkSmartPointer<vtkKWApplication> app = 
      vtkSmartPointer<vtkKWApplication>::New();
  app->SetName("KWPolygonalObjectViewerExample");
  
  app->SetHelpDialogStartingPage("http://www.kwwidgets.org");

  // Add a window
  vtkSmartPointer<vtkKWWindow> win = 
      vtkSmartPointer<vtkKWWindow>::New();
  //win->SupportHelpOn();
  app->AddWindow(win);
  win->MainPanelVisibilityOff(); //hide left pane
  //win->SecondaryPanelVisibilityOff(); //does nothing?
  win->Create();
  

  // Add a render widget, attach it to the view frame, and pack
  
  vtkSmartPointer<vtkKWRenderWidget> rwLeft = 
      vtkSmartPointer<vtkKWRenderWidget>::New();
  rwLeft->SetParent(win->GetViewFrame());
  rwLeft->Create();
  
  vtkSmartPointer<vtkKWRenderWidget> rwRight = 
      vtkSmartPointer<vtkKWRenderWidget>::New();
  rwRight->SetParent(win->GetViewFrame());
  rwRight->Create();
  
  app->Script("grid %s -column 0 -row 0 -sticky news", rwLeft->GetWidgetName()); //"news" is North East West South
  app->Script("grid %s -column 1 -row 0 -sticky news", rwRight->GetWidgetName());
  
  // Create sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> sphereActor = 
      vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  
  // Create cube
  vtkSmartPointer<vtkCubeSource> cubeSource =
      vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();
  
    vtkSmartPointer<vtkPolyDataMapper> cubeMapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

  vtkSmartPointer<vtkActor> cubeActor = 
      vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  
  // Add the actor to the scene

  rwLeft->AddViewProp(sphereActor);
  rwLeft->ResetCamera();
  
  rwRight->AddViewProp(cubeActor);
  rwRight->ResetCamera();

  win->Display();
  app->Start(argc, argv);
  int ret = app->GetExitStatus();
  win->Close();
  
  return ret;
}
