#include <vtkActor.h>
#include <vtkAreaPicker.h>
#include <vtkDataSetMapper.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkExtractGeometry.h>
#include <vtkIdFilter.h>
#include <vtkIdTypeArray.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkNamedColors.h>
#include <vtkObjectFactory.h>
#include <vtkPlanes.h>
#include <vtkPointData.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVersion.h>
#include <vtkVertexGlyphFilter.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif

// Define interaction style
class InteractorStyle : public vtkInteractorStyleRubberBandPick
{
public:
  static InteractorStyle* New();
  vtkTypeMacro(InteractorStyle, vtkInteractorStyleRubberBandPick);

  InteractorStyle()
  {
    this->SelectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    this->SelectedActor = vtkSmartPointer<vtkActor>::New();
    this->SelectedActor->SetMapper(SelectedMapper);
  }

  virtual void OnLeftButtonUp() override
  {
    auto colors = vtkSmartPointer<vtkNamedColors>::New();

    // Forward events
    vtkInteractorStyleRubberBandPick::OnLeftButtonUp();

    vtkPlanes* frustum =
        static_cast<vtkAreaPicker*>(this->GetInteractor()->GetPicker())
            ->GetFrustum();

    auto extractGeometry = vtkSmartPointer<vtkExtractGeometry>::New();
    extractGeometry->SetImplicitFunction(frustum);
    extractGeometry->SetInputData(this->Points);
    extractGeometry->Update();

    auto glyphFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
    glyphFilter->SetInputConnection(extractGeometry->GetOutputPort());
    glyphFilter->Update();

    vtkPolyData* selected = glyphFilter->GetOutput();
    std::cout << "Selected " << selected->GetNumberOfPoints() << " points."
              << std::endl;
    std::cout << "Selected " << selected->GetNumberOfCells() << " cells."
              << std::endl;
    this->SelectedMapper->SetInputData(selected);
    this->SelectedMapper->ScalarVisibilityOff();

    vtkIdTypeArray* ids = dynamic_cast<vtkIdTypeArray*>(
        selected->GetPointData()->GetArray("OriginalIds"));
    for (vtkIdType i = 0; i < ids->GetNumberOfTuples(); i++)
    {
      std::cout << "Id " << i << " : " << ids->GetValue(i) << std::endl;
    }

    this->SelectedActor->GetProperty()->SetColor(
        colors->GetColor3d("Red").GetData());
    this->SelectedActor->GetProperty()->SetPointSize(3);

    this->CurrentRenderer->AddActor(SelectedActor);
    this->GetInteractor()->GetRenderWindow()->Render();
    this->HighlightProp(NULL);
  }

  void SetPoints(vtkSmartPointer<vtkPolyData> points)
  {
    this->Points = points;
  }

private:
  vtkSmartPointer<vtkPolyData> Points;
  vtkSmartPointer<vtkActor> SelectedActor;
  vtkSmartPointer<vtkDataSetMapper> SelectedMapper;
};
vtkStandardNewMacro(InteractorStyle);

int main(int, char*[])
{
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto pointSource = vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(20);
  pointSource->Update();

  auto idFilter = vtkSmartPointer<vtkIdFilter>::New();
  idFilter->SetInputConnection(pointSource->GetOutputPort());
#if VTK890
  idFilter->SetCellIdsArrayName("OriginalIds");
  idFilter->SetPointIdsArrayName("OriginalIds");
#else
  idFilter->SetIdsArrayName("OriginalIds");
#endif
  idFilter->Update();

  auto surfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceFilter->SetInputConnection(idFilter->GetOutputPort());
  surfaceFilter->Update();

  vtkPolyData* input = surfaceFilter->GetOutput();

  // Create a mapper and actor
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(input);
  mapper->ScalarVisibilityOff();

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Visualize
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto areaPicker = vtkSmartPointer<vtkAreaPicker>::New();
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetPicker(areaPicker);
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Black").GetData());

  renderWindow->Render();

  auto style = vtkSmartPointer<InteractorStyle>::New();
  style->SetPoints(input);
  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
