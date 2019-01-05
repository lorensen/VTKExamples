#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkIdTypeArray.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkRendererCollection.h>
#include <vtkProperty.h>
#include <vtkPlanes.h>
#include <vtkObjectFactory.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkPointSource.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkAreaPicker.h>
#include <vtkExtractGeometry.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkIdFilter.h>

// Define interaction style
class InteractorStyle : public vtkInteractorStyleRubberBandPick
{
  public:
    static InteractorStyle* New();
    vtkTypeMacro(InteractorStyle,vtkInteractorStyleRubberBandPick);

    InteractorStyle()
    {
      this->SelectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
      this->SelectedActor = vtkSmartPointer<vtkActor>::New();
      this->SelectedActor->SetMapper(SelectedMapper);
    }

    virtual void OnLeftButtonUp()
    {
      // Forward events
      vtkInteractorStyleRubberBandPick::OnLeftButtonUp();

      vtkPlanes* frustum = static_cast<vtkAreaPicker*>(this->GetInteractor()->GetPicker())->GetFrustum();

      vtkSmartPointer<vtkExtractGeometry> extractGeometry =
        vtkSmartPointer<vtkExtractGeometry>::New();
      extractGeometry->SetImplicitFunction(frustum);
      extractGeometry->SetInputData(this->Points);
      extractGeometry->Update();

      vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
        vtkSmartPointer<vtkVertexGlyphFilter>::New();
      glyphFilter->SetInputConnection(extractGeometry->GetOutputPort());
      glyphFilter->Update();

      vtkPolyData* selected = glyphFilter->GetOutput();
      std::cout << "Selected " << selected->GetNumberOfPoints() << " points." << std::endl;
      std::cout << "Selected " << selected->GetNumberOfCells() << " cells." << std::endl;
      this->SelectedMapper->SetInputData(selected);
      this->SelectedMapper->ScalarVisibilityOff();

      vtkIdTypeArray* ids = vtkIdTypeArray::SafeDownCast(selected->GetPointData()->GetArray("OriginalIds"));
      for(vtkIdType i = 0; i < ids->GetNumberOfTuples(); i++)
      {
        std::cout << "Id " << i << " : " << ids->GetValue(i) << std::endl;
      }

      this->SelectedActor->GetProperty()->SetColor(1.0, 0.0, 0.0); //(R,G,B)
      this->SelectedActor->GetProperty()->SetPointSize(3);

      this->CurrentRenderer->AddActor(SelectedActor);
      this->GetInteractor()->GetRenderWindow()->Render();
      this->HighlightProp(NULL);
    }

    void SetPoints(vtkSmartPointer<vtkPolyData> points) {this->Points = points;}
  private:
    vtkSmartPointer<vtkPolyData> Points;
    vtkSmartPointer<vtkActor> SelectedActor;
    vtkSmartPointer<vtkDataSetMapper> SelectedMapper;

};
vtkStandardNewMacro(InteractorStyle);

int main (int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(20);
  pointSource->Update();

  vtkSmartPointer<vtkIdFilter> idFilter =
    vtkSmartPointer<vtkIdFilter>::New();
  idFilter->SetInputConnection(pointSource->GetOutputPort());
  idFilter->SetIdsArrayName("OriginalIds");
  idFilter->Update();

  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter =
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceFilter->SetInputConnection(idFilter->GetOutputPort());
  surfaceFilter->Update();

  vtkPolyData* input = surfaceFilter->GetOutput();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(input);
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkAreaPicker> areaPicker =
    vtkSmartPointer<vtkAreaPicker>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetPicker(areaPicker);
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  //renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  vtkSmartPointer<InteractorStyle> style =
    vtkSmartPointer<InteractorStyle>::New();
  style->SetPoints(input);
  renderWindowInteractor->SetInteractorStyle( style );

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
