#include <vtkPolyData.h>
#include <vtkPointSource.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkSelectVisiblePoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
 
class MyInteractor : public vtkInteractorStyleTrackballCamera
{
public:

  static MyInteractor* New();
  vtkTypeMacro(MyInteractor, vtkInteractorStyleTrackballCamera);
    
  virtual void OnLeftButtonDown()  override
  {
    this->VisibleFilter->Update();
    std::cout << "There are currently: " << this->VisibleFilter->GetOutput()->GetNumberOfPoints() 
              << " visible." << std::endl;
    // Forward events
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
  }
    
  void SetVisibleFilter(vtkSmartPointer<vtkSelectVisiblePoints> vis) {this->VisibleFilter = vis;}
private:
  vtkSmartPointer<vtkSelectVisiblePoints> VisibleFilter;
};

vtkStandardNewMacro(MyInteractor);

int main(int, char *[])
{ 
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(5.0, 0, 0);
  sphereSource->Update();
    
  vtkSmartPointer<vtkPointSource> pointSource = 
      vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetRadius(2.0);
  pointSource->SetNumberOfPoints(200);
  pointSource->Update();
    
  // Create an actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> sphereActor = 
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
 
  vtkSmartPointer<vtkPolyDataMapper> pointsMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputConnection(pointSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> pointsActor = 
    vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  // Add the actors to the scene
  renderer->AddActor(sphereActor);
  renderer->AddActor(pointsActor);
  
  vtkSmartPointer<vtkSelectVisiblePoints> selectVisiblePoints = 
    vtkSmartPointer<vtkSelectVisiblePoints>::New();
  selectVisiblePoints->SetInputConnection(pointSource->GetOutputPort());
  selectVisiblePoints->SetRenderer(renderer);
  selectVisiblePoints->Update();
   
  vtkSmartPointer<MyInteractor> style = 
    vtkSmartPointer<MyInteractor>::New();
  renderWindowInteractor->SetInteractorStyle( style );
  style->SetVisibleFilter(selectVisiblePoints);
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
