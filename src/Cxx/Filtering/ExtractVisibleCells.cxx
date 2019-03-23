#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkHardwareSelector.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkRendererCollection.h>
#include <vtkDataSetMapper.h>
#include <vtkExtractSelection.h>
#include <vtkSelection.h>
#include <vtkProperty.h>

// Define interaction style
class KeyPressInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
  static KeyPressInteractorStyle* New();
  vtkTypeMacro(KeyPressInteractorStyle, vtkInteractorStyleTrackballCamera);

  virtual void OnKeyPress() override
  {
    // Get the keypress
    std::string key = this->Interactor->GetKeySym();

    // "s" for "s"elect
    if(key.compare("s") == 0)
    {
      vtkSmartPointer<vtkHardwareSelector> selector =
        vtkSmartPointer<vtkHardwareSelector>::New();
      selector->SetRenderer(this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
      int* temp = this->Interactor->GetRenderWindow()->GetSize();
      unsigned int windowSize[4];
      windowSize[0] = temp[2];
      windowSize[1] = temp[3];
      windowSize[2] = temp[0];
      windowSize[3] = temp[1];
      /*
        for(unsigned int i = 0; i < 4; i++)
          {
          windowSize[i] = temp[i];
          }
        */
      selector->SetArea(windowSize);
      selector->SetFieldAssociation(vtkDataObject::FIELD_ASSOCIATION_CELLS);
      vtkSelection* selection = selector->Select();
      std::cout << "Selection has " << selection->GetNumberOfNodes() << " nodes." << std::endl;

      vtkSmartPointer<vtkExtractSelection> extractSelection =
        vtkSmartPointer<vtkExtractSelection>::New();
      extractSelection->SetInputData(0, this->Data);
      extractSelection->SetInputData(1, selection);
      extractSelection->Update();

      vtkSmartPointer<vtkDataSetMapper> mapper =
        vtkSmartPointer<vtkDataSetMapper>::New();
      mapper->SetInputConnection(extractSelection->GetOutputPort());

      vtkSmartPointer<vtkActor> actor =
        vtkSmartPointer<vtkActor>::New();
      actor->SetMapper(mapper);
      actor->GetProperty()->SetColor(1,0,0);
      this->Renderer->AddActor(actor);

    }

    // Forward events
    vtkInteractorStyleTrackballCamera::OnKeyPress();
  }
  
  vtkPolyData* Data;
  vtkRenderer* Renderer;

};
vtkStandardNewMacro(KeyPressInteractorStyle);

int main(int , char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetMultiSamples(0); // Turn off anti-aliasing
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<KeyPressInteractorStyle> style =
    vtkSmartPointer<KeyPressInteractorStyle>::New();
  style->Renderer = renderer;
  renderWindowInteractor->SetInteractorStyle(style);
  style->SetCurrentRenderer(renderer);
  style->Data = sphereSource->GetOutput();

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
