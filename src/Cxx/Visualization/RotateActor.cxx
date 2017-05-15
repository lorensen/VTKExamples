#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkObjectFactory.h>
#include <vtkMatrix4x4.h>

// Define interaction style
class MyInteractorStyle : public vtkInteractorStyleTrackballActor
{
  public:
    static MyInteractorStyle* New();
    vtkTypeMacro(MyInteractorStyle, vtkInteractorStyleTrackballActor);
 
    virtual void OnLeftButtonDown() 
    {
      std::cout << "Pressed left mouse button." << std::endl;
      
      vtkSmartPointer<vtkMatrix4x4> m = 
          vtkSmartPointer<vtkMatrix4x4>::New();
      this->Actor->GetMatrix(m);
      std::cout << "Matrix: " << endl << *m << std::endl;
      
      // Forward events
      vtkInteractorStyleTrackballActor::OnLeftButtonDown();
    }
    
    virtual void OnLeftButtonUp() 
    {
      std::cout << "Released left mouse button." << std::endl;
      
      vtkSmartPointer<vtkMatrix4x4> m = 
          vtkSmartPointer<vtkMatrix4x4>::New();
      this->Actor->GetMatrix(m);
      std::cout << "Matrix: " << endl << *m << std::endl;
      
      // Forward events
      vtkInteractorStyleTrackballActor::OnLeftButtonUp();
    }
    
    void SetActor(vtkSmartPointer<vtkActor> actor) {this->Actor = actor;}
    
  private:
    vtkSmartPointer<vtkActor> Actor;
 
 
};
vtkStandardNewMacro(MyInteractorStyle);

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkConeSource> coneSource = 
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(coneSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->RotateY(45);
  
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  vtkSmartPointer<MyInteractorStyle> style = 
    vtkSmartPointer<MyInteractorStyle>::New();
  style->SetActor(actor);
  
  renderWindowInteractor->SetInteractorStyle( style );

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); //white

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
         
  return EXIT_SUCCESS;
}
