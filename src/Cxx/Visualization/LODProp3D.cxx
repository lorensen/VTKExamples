#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODProp3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkProperty.h>

void RefreshCallback( vtkObject* vtkNotUsed(caller),
                      long unsigned int vtkNotUsed(eventId),
                      void* clientData,
                      void* vtkNotUsed(callData) )
{
  vtkSmartPointer<vtkLODProp3D> lodProp = 
    static_cast<vtkLODProp3D*>(clientData);
  std::cout << "Last rendered LOD: " << lodProp->GetLastRenderedLODID() << std::endl;
}

int main (int, char *[])
{
  // High res sphere
  vtkSmartPointer<vtkSphereSource> highResSphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  int res = 100;
  highResSphereSource->SetThetaResolution(res);
  highResSphereSource->SetPhiResolution(res);
  highResSphereSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> highResMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  highResMapper->SetInputConnection(highResSphereSource->GetOutputPort());
  
  // Low res sphere
  vtkSmartPointer<vtkSphereSource> lowResSphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
    
  vtkSmartPointer<vtkPolyDataMapper> lowResMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lowResMapper->SetInputConnection(lowResSphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkProperty> propertyLowRes = 
    vtkSmartPointer<vtkProperty>::New();
  propertyLowRes->SetDiffuseColor(0.89, 0.81, 0.34);
  propertyLowRes->SetInterpolationToFlat();

  vtkSmartPointer<vtkProperty> propertyHighRes = 
    vtkSmartPointer<vtkProperty>::New();
  propertyHighRes->SetDiffuseColor(1.0, 0.3882, 0.2784);
  propertyHighRes->SetInterpolationToFlat();

  vtkSmartPointer<vtkLODProp3D> prop = 
      vtkSmartPointer<vtkLODProp3D>::New();
  prop->AddLOD(lowResMapper, propertyLowRes, 0.0);
  prop->AddLOD(highResMapper, propertyHighRes, 0.0);
  
  std::cout << "There are " << prop->GetNumberOfLODs() << " LODs" << std::endl;
    
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  //prop->SetAllocatedRenderTime(1e-6,renderer);
  prop->SetAllocatedRenderTime(1e-10,renderer);
      
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(prop);
  
  vtkSmartPointer<vtkCallbackCommand> refreshCallback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  refreshCallback->SetCallback (RefreshCallback);
  refreshCallback->SetClientData(prop);

  renderWindow->AddObserver(vtkCommand::ModifiedEvent,refreshCallback);
  
  renderWindow->Render();

  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
