#include <vtkActor.h>
#include <vtkAreaPicker.h>
#include <vtkDataSetMapper.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkExtractPolyDataGeometry.h>
#include <vtkIdFilter.h>
#include <vtkIdTypeArray.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkNamedColors.h>
#include <vtkObjectFactory.h>
#include <vtkPlanes.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVersion.h>
#include <vtkVertexGlyphFilter.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtksys/SystemTools.hxx>

#define VTKISRBP_ORIENT 0
#define VTKISRBP_SELECT 1

namespace {
// Define interaction style
class HighlightInteractorStyle : public vtkInteractorStyleRubberBandPick
{
public:
  static HighlightInteractorStyle* New();
  vtkTypeMacro(HighlightInteractorStyle, vtkInteractorStyleRubberBandPick);

  HighlightInteractorStyle() : vtkInteractorStyleRubberBandPick()
  {
    this->SelectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    this->SelectedActor = vtkSmartPointer<vtkActor>::New();
    this->SelectedActor->SetMapper(SelectedMapper);
  }

  virtual void OnLeftButtonUp() override
  {
    // Forward events
    vtkInteractorStyleRubberBandPick::OnLeftButtonUp();

    if (this->CurrentMode == VTKISRBP_SELECT)
    {
      auto colors = vtkSmartPointer<vtkNamedColors>::New();

      vtkPlanes* frustum =
          static_cast<vtkAreaPicker*>(this->GetInteractor()->GetPicker())
              ->GetFrustum();

      auto extractPolyDataGeometry =
          vtkSmartPointer<vtkExtractPolyDataGeometry>::New();
      extractPolyDataGeometry->SetInputData(this->PolyData);
      extractPolyDataGeometry->SetImplicitFunction(frustum);
      extractPolyDataGeometry->Update();

      std::cout << "Extracted "
                << extractPolyDataGeometry->GetOutput()->GetNumberOfCells()
                << " cells." << std::endl;
      this->SelectedMapper->SetInputData(extractPolyDataGeometry->GetOutput());
      this->SelectedMapper->ScalarVisibilityOff();

      //        vtkIdTypeArray* ids =
      //        dynamic_cast<vtkIdTypeArray*>(selected->GetPointData()->GetArray("OriginalIds"));

      this->SelectedActor->GetProperty()->SetColor(
          colors->GetColor3d("Tomato").GetData());
      this->SelectedActor->GetProperty()->SetPointSize(5);
      this->SelectedActor->GetProperty()->SetRepresentationToWireframe();

      this->GetInteractor()
          ->GetRenderWindow()
          ->GetRenderers()
          ->GetFirstRenderer()
          ->AddActor(SelectedActor);
      this->GetInteractor()->GetRenderWindow()->Render();
      this->HighlightProp(NULL);
    }
  }

  void SetPolyData(vtkSmartPointer<vtkPolyData> polyData)
  {
    this->PolyData = polyData;
  }

private:
  vtkSmartPointer<vtkPolyData> PolyData;
  vtkSmartPointer<vtkActor> SelectedActor;
  vtkSmartPointer<vtkDataSetMapper> SelectedMapper;
};
vtkStandardNewMacro(HighlightInteractorStyle);

vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName);
} // namespace


int main(int argc, char* argv[])
{
  auto polyData = ReadPolyData(argc > 1 ? argv[1] : "");
  ;

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto idFilter = vtkSmartPointer<vtkIdFilter>::New();
  idFilter->SetInputData(polyData);
#if VTK890
  idFilter->SetCellIdsArrayName("OriginalIds");
  idFilter->SetPointIdsArrayName("OriginalIds");
#else
  idFilter->SetIdsArrayName("OriginalIds");
#endif
  idFilter->Update();

  // This is needed to convert the ouput of vtkIdFilter (vtkDataSet) back to
  // vtkPolyData
  auto surfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceFilter->SetInputConnection(idFilter->GetOutputPort());
  surfaceFilter->Update();

  vtkPolyData* input = surfaceFilter->GetOutput();

  // Create a mapper and actor
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);
  mapper->ScalarVisibilityOff();

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(5);
  actor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("Peacock").GetData());
  // Visualize
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto areaPicker = vtkSmartPointer<vtkAreaPicker>::New();
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetPicker(areaPicker);
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Tan").GetData());

  renderWindow->Render();

  auto style = vtkSmartPointer<HighlightInteractorStyle>::New();
  style->SetPolyData(input);
  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension =
      vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));
  if (extension == ".ply")
  {
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader = vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->SetPhiResolution(21);
    source->SetThetaResolution(40);
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
} // namespace
