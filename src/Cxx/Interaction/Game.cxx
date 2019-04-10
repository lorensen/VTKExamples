// Demonstrate moving pieces and "snapping"

#include <vtkSelectEnclosedPoints.h>
#include <vtkRendererCollection.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkTransform.h>
#include <vtkLinearTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkObjectFactory.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkInteractorStyleSwitch.h>

// Define interaction style
class MouseInteractorStyle6 : public vtkInteractorStyleTrackballActor
{
public:
  static MouseInteractorStyle6* New();
  vtkTypeMacro(MouseInteractorStyle6, vtkInteractorStyleTrackballActor);

  virtual void OnLeftButtonDown() override
  {
    std::cout << "Pressed left mouse button." << std::endl;
    // Forward events
    vtkInteractorStyleTrackballActor::OnLeftButtonDown();
  }

  virtual void OnMiddleButtonUp() override
  {
    //std::cout << "Pressed middle mouse button." << std::endl;

    int x = this->Interactor->GetEventPosition()[0];
    int y = this->Interactor->GetEventPosition()[1];
    this->FindPokedRenderer(x, y);
    this->FindPickedActor(x, y);

    if (this->CurrentRenderer == NULL || this->InteractionProp == NULL)
    {
      std::cout << "Nothing selected." << std::endl;
      return;
    }

    vtkSmartPointer<vtkPropCollection> actors =
      vtkSmartPointer<vtkPropCollection>::New();

    this->InteractionProp->GetActors(actors);
    actors->InitTraversal();
    vtkActor* actor = dynamic_cast<vtkActor*>(actors->GetNextProp());

    vtkPolyData* polydata = dynamic_cast<vtkPolyData*>(actor->GetMapper()->GetInputAsDataSet());

    vtkSmartPointer<vtkTransform> transform =
      vtkSmartPointer<vtkTransform>::New();
    transform->SetMatrix(actor->GetMatrix());

    vtkSmartPointer<vtkTransformPolyDataFilter> transformPolyData =
      vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    transformPolyData->SetInputData(polydata);
    transformPolyData->SetTransform(transform);
    transformPolyData->Update();

    vtkSmartPointer<vtkSelectEnclosedPoints> selectEnclosedPoints =
      vtkSmartPointer<vtkSelectEnclosedPoints>::New();
    selectEnclosedPoints->SetInputConnection(transformPolyData->GetOutputPort());
    selectEnclosedPoints->SetSurfaceData(this->Sphere);
    selectEnclosedPoints->Update();

    vtkDataArray* insideArray = dynamic_cast<vtkDataArray*>(selectEnclosedPoints->GetOutput()->GetPointData()->GetArray("SelectedPoints"));

    bool inside = false;
    for(vtkIdType i = 0; i < insideArray->GetNumberOfTuples(); i++)
    {
      if(insideArray->GetComponent(i,0) == 1)
      {
        inside = true;
        break;
      }
    }

    if(inside)
    {
      std::cout << "A point of the cube is inside the sphere!" << std::endl;
      // Reset the cube to its original position
      //this->CubeActor->GetMatrix()->Identity();
      //this->CubeActor->SetOrigin(0,0,0);
      this->CubeActor->SetPosition(0,0,0);
      this->CubeActor->SetOrientation(0,0,0);

      this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->Render();
      this->Interactor->GetRenderWindow()->Render();
    }

    // Release interaction
    this->StopState();

  }

  virtual void OnRightButtonDown() override
  {
    std::cout << "Pressed right mouse button." << std::endl;
    // Forward events
    vtkInteractorStyleTrackballActor::OnRightButtonDown();
  }

  vtkPolyData* Sphere;
  vtkActor* CubeActor;
};
vtkStandardNewMacro(MouseInteractorStyle6);

int main (int, char *[])
{
  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(2);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  // Cube
  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->SetCenter(5.0, 0.0, 0.0);
  cubeSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(sphereActor);
  renderer->AddActor(cubeActor);

  renderWindow->Render();

  vtkSmartPointer<MouseInteractorStyle6> style =
    vtkSmartPointer<MouseInteractorStyle6>::New();
  style->Sphere = sphereSource->GetOutput();
  style->CubeActor = cubeActor;

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
