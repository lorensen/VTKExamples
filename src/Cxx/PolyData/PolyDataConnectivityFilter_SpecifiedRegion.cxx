#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
 
int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource1 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->Update();
  
  vtkSmartPointer<vtkSphereSource> sphereSource2 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetRadius(10);
  sphereSource2->SetCenter(25,0,0);
  sphereSource2->Update();
  
  vtkSmartPointer<vtkAppendPolyData> appendFilter = 
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
  appendFilter->Update();
  
  vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter = 
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
  connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
  connectivityFilter->SetExtractionModeToSpecifiedRegions(); 
  connectivityFilter->AddSpecifiedRegion(1); //select the region to extract here
  connectivityFilter->Update();
  
  // Create a mapper and actor for original data
  vtkSmartPointer<vtkPolyDataMapper> originalMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(appendFilter->GetOutputPort());
  originalMapper->Update();
  
  vtkSmartPointer<vtkActor> originalActor = 
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  
  // create a mapper and actor for extracted data
  vtkSmartPointer<vtkPolyDataMapper> extractedMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  extractedMapper->SetInputConnection(connectivityFilter->GetOutputPort());
  extractedMapper->Update();
  
  vtkSmartPointer<vtkActor> extractedActor = 
    vtkSmartPointer<vtkActor>::New();
  extractedActor->GetProperty()->SetColor(1,0,0);
  extractedActor->SetMapper(extractedMapper);
  
  // create a renderer
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(extractedActor);
  
  // create a render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  // create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  interactor->Initialize();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
