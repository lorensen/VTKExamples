#include <vtkSmartPointer.h>
#include <vtkPolyDataConnectivityFilter.h>

#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
 
#include <vtkNamedColors.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkSphereSource> sphereSource1 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->SetRadius(5);
  
  vtkSmartPointer<vtkSphereSource> sphereSource2 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetRadius(10);
  sphereSource2->SetCenter(25,0,0);
  
  vtkSmartPointer<vtkAppendPolyData> appendFilter = 
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
  
  vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter = 
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
  connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
  connectivityFilter->SetExtractionModeToSpecifiedRegions(); 
  connectivityFilter->AddSpecifiedRegion(0); //select the region to extract here
  connectivityFilter->Update();
  
  // Create a mapper and actor for original data
  vtkSmartPointer<vtkPolyDataMapper> originalMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(appendFilter->GetOutputPort());
  
  vtkSmartPointer<vtkActor> originalActor = 
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  
  // create a mapper and actor for extracted data
  vtkSmartPointer<vtkPolyDataMapper> extractedMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  extractedMapper->SetInputConnection(connectivityFilter->GetOutputPort());
  
  vtkSmartPointer<vtkActor> extractedActor = 
    vtkSmartPointer<vtkActor>::New();
  extractedActor->SetMapper(extractedMapper);
  extractedActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  extractedActor->SetPosition(0,-20,0);
  
  // create a renderer
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(extractedActor);
  renderer->GradientBackgroundOn();
  renderer->SetBackground (colors->GetColor3d("Gold").GetData());
  renderer->SetBackground2 (colors->GetColor3d("Silver").GetData());
  
  // create a render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  // create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  interactor->Initialize();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
