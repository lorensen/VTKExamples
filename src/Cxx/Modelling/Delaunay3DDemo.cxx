#include <vtkDelaunay3D.h>
#include <vtkSmartPointer.h>

#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCleanPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellIterator.h>
#include <vtkCellData.h>
#include <vtkUnsignedCharArray.h>
#include <vtkNamedColors.h>

#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>

#include <vtkCommand.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>

#include <sstream>

#include <vtksys/SystemTools.hxx>
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}
namespace
{
void MakeWidget(vtkSmartPointer<vtkSliderWidget> &,
                vtkSmartPointer<vtkDelaunay3D> &,
                vtkSmartPointer<vtkTextMapper> &,
                vtkSmartPointer<vtkRenderer> &,
                vtkSmartPointer<vtkRenderWindowInteractor> &);
}

int main ( int argc, char *argv[] )
{
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " filename.vtp" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");

  auto color =
    vtkSmartPointer<vtkNamedColors>::New();

  auto originalMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  originalMapper->SetInputData(polyData);
  originalMapper->ScalarVisibilityOff();
  originalMapper->SetScalarModeToUseCellData();

  auto originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(color->GetColor3d("tomato").GetData());
  originalActor->GetProperty()->SetInterpolationToFlat();

  // Clean the polydata. This will remove duplicate points that may be
  // present in the input data.
  auto cleaner =
    vtkSmartPointer<vtkCleanPolyData>::New();
  cleaner->SetInputData (polyData);

  // Generate a tetrahedral mesh from the input points. By
  // default, the generated volume is the convex hull of the points.
  auto delaunay3D =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay3D->SetInputConnection (cleaner->GetOutputPort());

  auto delaunayMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  delaunayMapper->SetInputConnection(delaunay3D->GetOutputPort());
  delaunayMapper->SetScalarModeToUseCellData();

  auto delaunayActor =
    vtkSmartPointer<vtkActor>::New();
  delaunayActor->SetMapper(delaunayMapper);
  delaunayActor->GetProperty()->SetColor(color->GetColor3d("banana").GetData());
  delaunayActor->GetProperty()->SetInterpolationToFlat();

  // Generate a mesh from the input points. If Alpha is non-zero, then
  // tetrahedra, triangles, edges and vertices that lie within the
  // alpha radius are output.
  auto delaunay3DAlpha =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay3DAlpha->SetInputConnection (cleaner->GetOutputPort());
  delaunay3DAlpha->SetAlpha(.5);
  delaunay3DAlpha->Update();

  auto cellData =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  cellData->SetNumberOfComponents(3);

  int numTetras = 0;
  int numLines = 0;
  int numTris = 0;
  int numVerts = 0;

  auto it =
    delaunay3DAlpha->GetOutput()->NewCellIterator();
  for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell())
  {
    if (it->GetCellType() == VTK_TETRA)
    {
      numTetras++;
      cellData->InsertNextTypedTuple(color->GetColor3ub("Banana").GetData());
    }
    else if (it->GetCellType() == VTK_LINE)
    {
      numLines++;
      cellData->InsertNextTypedTuple(color->GetColor3ub("Peacock").GetData());
    }
    else if (it->GetCellType() == VTK_TRIANGLE)
    {
      numTris++;
      cellData->InsertNextTypedTuple(color->GetColor3ub("Tomato").GetData());
    }
    else if (it->GetCellType() == VTK_VERTEX)
    {
      numVerts++;
      cellData->InsertNextTypedTuple(color->GetColor3ub("Lime").GetData());
    }
  }
  it->Delete();

  std::stringstream ss;
  ss << "numTetras: " << numTetras << std::endl;
  ss << "numLines: " << numLines << std::endl;
  ss << "numTris: " << numTris << std::endl;
  ss << "numVerts: " << numVerts;

  // Set the cell color depending on cell type
  delaunay3DAlpha->GetOutput()->GetCellData()->SetScalars(cellData);

  auto delaunayAlphaMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  delaunayAlphaMapper->SetInputConnection(delaunay3DAlpha->GetOutputPort());
  delaunayAlphaMapper->SetScalarModeToUseCellData();

  auto delaunayAlphaActor =
    vtkSmartPointer<vtkActor>::New();
  delaunayAlphaActor->SetMapper(delaunayAlphaMapper);
  delaunayAlphaActor->GetProperty()->SetPointSize(5.0);
  delaunayAlphaActor->GetProperty()->SetInterpolationToFlat();

  // Visualize

  auto textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(16);
  textProperty->SetColor(color->GetColor3d("Black").GetData());

  auto textMapper =
    vtkSmartPointer<vtkTextMapper>::New();  
  textMapper->SetInput(ss.str().c_str());
  textMapper->SetTextProperty(textProperty);

  auto textActor =
    vtkSmartPointer<vtkActor2D>::New();
  textActor->SetMapper(textMapper);
  textActor->SetPosition(10, 10);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double centerViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};

  // Shared camera
  auto sharedCamera =
    vtkSmartPointer<vtkCamera>::New();

  // Create a renderer, render window, and interactor
  auto originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetActiveCamera(sharedCamera);
  originalRenderer->UseHiddenLineRemovalOn();

  auto delaunayRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  delaunayRenderer->SetActiveCamera(sharedCamera);
  delaunayRenderer->UseHiddenLineRemovalOn();

  auto delaunayAlphaRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  delaunayAlphaRenderer->SetActiveCamera(sharedCamera);
  delaunayAlphaRenderer->UseHiddenLineRemovalOn();

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900,300);

  renderWindow->AddRenderer(originalRenderer);
  originalRenderer->SetViewport(leftViewport);

  renderWindow->AddRenderer(delaunayRenderer);
  delaunayRenderer->SetViewport(centerViewport);

  renderWindow->AddRenderer(delaunayAlphaRenderer);
  delaunayAlphaRenderer->SetViewport(rightViewport);

  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  auto widget =
    vtkSmartPointer<vtkSliderWidget>::New();
  MakeWidget(widget, delaunay3DAlpha, textMapper, delaunayAlphaRenderer, renderWindowInteractor);

  originalRenderer->AddActor(originalActor);
  delaunayRenderer->AddActor(delaunayActor);
  delaunayAlphaRenderer->AddActor(delaunayAlphaActor);
  delaunayAlphaRenderer->AddViewProp(textActor);

  originalRenderer->SetBackground(
    color->GetColor3d("Slate_Grey").GetData());
  delaunayRenderer->SetBackground(
    color->GetColor3d("Light_Grey").GetData());
  delaunayAlphaRenderer->SetBackground(
    color->GetColor3d("Grey").GetData());

  originalRenderer->ResetCamera();
  renderWindow->Render();

  // Render and interact
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}

namespace
{
// These callbacks do the actual work.
// Callbacks for the interactions
class SliderCallbackAlpha : public vtkCommand
{
public:
  static SliderCallbackAlpha *New()
  {
    return new SliderCallbackAlpha;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    this->Delaunay3D->SetAlpha(value);
    this->Delaunay3D->Update();

    auto cellData =
      vtkSmartPointer<vtkUnsignedCharArray>::New();
    cellData->SetNumberOfComponents(3);

    // Set the cell color depending on cell type
    auto color =
      vtkSmartPointer<vtkNamedColors>::New();
    int numTetras = 0;
    int numLines = 0;
    int numTris = 0;
    int numVerts = 0;

    auto it =
      this->Delaunay3D->GetOutput()->NewCellIterator();
    for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell())
    {
      if (it->GetCellType() == VTK_TETRA)
      {
        numTetras++;
        cellData->InsertNextTypedTuple(color->GetColor3ub("Banana").GetData());
      }
      else if (it->GetCellType() == VTK_LINE)
      {
        numLines++;
        cellData->InsertNextTypedTuple(color->GetColor3ub("Peacock").GetData());
      }
      else if (it->GetCellType() == VTK_TRIANGLE)
      {
        numTris++;
        cellData->InsertNextTypedTuple(color->GetColor3ub("Tomato").GetData());
      }
      else if (it->GetCellType() == VTK_VERTEX)
      {
        numVerts++;
        cellData->InsertNextTypedTuple(color->GetColor3ub("Lime").GetData());
      }
    }
    it->Delete();

    this->Delaunay3D->GetOutput()->GetCellData()->SetScalars(cellData);
    std::stringstream ss;
    ss << "numTetras: " << numTetras << std::endl;
    ss << "numLines: " << numLines << std::endl;
    ss << "numTris: " << numTris << std::endl;
    ss << "numVerts: " << numVerts;
    this->TextMapper->SetInput(ss.str().c_str());

  }
  SliderCallbackAlpha():Delaunay3D(0),TextMapper(0) {}
  vtkDelaunay3D *Delaunay3D;
  vtkTextMapper *TextMapper;
};

void
MakeWidget(vtkSmartPointer<vtkSliderWidget> &widget,
           vtkSmartPointer<vtkDelaunay3D> &delaunay3D,
           vtkSmartPointer<vtkTextMapper> &textMapper,
           vtkSmartPointer<vtkRenderer> &renderer,
           vtkSmartPointer<vtkRenderWindowInteractor> &interactor)
{
  // Setup a slider widget for each varying parameter
  double tubeWidth(.02);
  double sliderLength(.04);
  double titleHeight(.04);
  double labelHeight(.04);

  auto sliderRepAlpha =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepAlpha->SetRenderer(renderer);

  sliderRepAlpha->SetMinimumValue(0.0001);
  sliderRepAlpha->SetMaximumValue(1.0);
  sliderRepAlpha->SetValue(delaunay3D->GetAlpha());
  sliderRepAlpha->SetTitleText("Alpha");
  sliderRepAlpha->SetRenderer(renderer);
  sliderRepAlpha->GetPoint1Coordinate()->SetValue(0.1, .1);
  sliderRepAlpha->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
  sliderRepAlpha->GetPoint2Coordinate()->SetValue(.9, .1);
  sliderRepAlpha->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();

  sliderRepAlpha->SetTubeWidth(tubeWidth);
  sliderRepAlpha->SetSliderLength(sliderLength);
  sliderRepAlpha->SetTitleHeight(titleHeight);
  sliderRepAlpha->SetLabelHeight(labelHeight);
  sliderRepAlpha->SetEndCapLength(tubeWidth*1.5);
  sliderRepAlpha->SetSliderWidth(tubeWidth*1.5);
  sliderRepAlpha->BuildRepresentation();

  widget->SetRepresentation(sliderRepAlpha);
  widget->SetAnimationModeToAnimate();
  widget->SetNumberOfAnimationSteps(2);
  widget->SetInteractor(interactor);
  widget->EnabledOn();

  auto callbackAlpha =
    vtkSmartPointer<SliderCallbackAlpha>::New();
  callbackAlpha->Delaunay3D = delaunay3D;
  callbackAlpha->TextMapper = textMapper;

  widget->AddObserver(vtkCommand::InteractionEvent,callbackAlpha);
}
}
namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameExtension(std::string(fileName));
  if (extension == ".ply")
  {
    auto reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    auto source =
      vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
}

