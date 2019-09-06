#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCellIterator.h>
#include <vtkCommand.h>
#include <vtkDataSetMapper.h>
#include <vtkGenericCell.h>
#include <vtkGlyph3D.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkQuadraticHexahedron.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkSliderWidget.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTessellatorFilter.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkUnstructuredGrid.h>

#include <map>
#include <sstream>

namespace
{
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticHexahedron();
void MakeWidget(vtkSmartPointer<vtkSliderWidget> &,
                vtkSmartPointer<vtkTessellatorFilter> &,
                vtkSmartPointer<vtkTextMapper> &,
                vtkSmartPointer<vtkRenderWindowInteractor> &);
}

int main (int, char *[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    MakeQuadraticHexahedron();

  vtkSmartPointer<vtkTessellatorFilter> tessellate =
    vtkSmartPointer<vtkTessellatorFilter>::New();
  tessellate->SetInputData(uGrid);
  tessellate->SetChordError(0.035);
  tessellate->Update();

  typedef std::map<const char *,int> CellContainer;
  CellContainer cellMap;

  int numTets = 0;
  vtkSmartPointer<vtkGenericCell> cell =
    vtkSmartPointer<vtkGenericCell>::New();
  vtkSmartPointer<vtkCellIterator> it = tessellate->GetOutput()->NewCellIterator();
  for (it->InitTraversal();
       !it->IsDoneWithTraversal();
       it->GoToNextCell())
  {
    it->GetCell(cell);
    cellMap[cell->GetRepresentativeCell()->GetClassName()]++;
    ++numTets;
  }
  it->Delete();

  vtkSmartPointer<vtkDataSetMapper> mapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(tessellate->GetOutputPort());
  mapper->ScalarVisibilityOff();
 
  // Create an actor for the grid
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(
    namedColors->GetColor3d("Tomato").GetData());
  actor->GetProperty()->SetEdgeColor(
    namedColors->GetColor3d("IvoryBlack").GetData());
  actor->GetProperty()->EdgeVisibilityOn();

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(0.02);

  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph3D->SetInputData(uGrid);
  glyph3D->SetSourceConnection(sphereSource->GetOutputPort());
  glyph3D->ScalingOff();
  glyph3D->Update();

  vtkSmartPointer<vtkDataSetMapper> glyph3DMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());
  glyph3DMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> glyph3DActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DActor->SetMapper(glyph3DMapper);
  glyph3DActor->GetProperty()->SetColor(
    namedColors->GetColor3d("Banana").GetData());

  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(24);

  std::stringstream ss;
  ss << "# of Tetras: " << numTets << std::endl;
  vtkSmartPointer<vtkTextMapper> textMapper =
    vtkSmartPointer<vtkTextMapper>::New();  
  textMapper->SetInput(ss.str().c_str());
  textMapper->SetTextProperty(textProperty);

  vtkSmartPointer<vtkActor2D> textActor =
    vtkSmartPointer<vtkActor2D>::New();
  textActor->SetMapper(textMapper);
  textActor->SetPosition(10, 400);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();

  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Quadratic Hexahedron Demo");
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 512);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkSliderWidget> widget =
    vtkSmartPointer<vtkSliderWidget>::New();
  MakeWidget(widget, tessellate, textMapper, interactor);
 
  renderer->AddActor(actor);
  renderer->AddActor(glyph3DActor);
  renderer->AddViewProp(textActor);
  renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());

  renderWindow->Render();

  interactor->Start();
 
  return EXIT_SUCCESS;
}

namespace
{
// These callbacks do the actual work.
// Callbacks for the interactions
class SliderCallbackChordError : public vtkCommand
{
public:
  static SliderCallbackChordError *New()
  {
    return new SliderCallbackChordError;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    this->Tessellator->SetChordError(value);
    this->Tessellator->SetMaximumNumberOfSubdivisions(4);
    this->Tessellator->Update();

    typedef std::map<const char *,int> CellContainer;
    CellContainer cellMap;

    int numTets = 0;
    vtkSmartPointer<vtkGenericCell> cell =
      vtkSmartPointer<vtkGenericCell>::New();
    vtkSmartPointer<vtkCellIterator> it = this->Tessellator->GetOutput()->NewCellIterator();
    for (it->InitTraversal();
         !it->IsDoneWithTraversal();
         it->GoToNextCell())
    {
      it->GetCell(cell);
      cellMap[cell->GetRepresentativeCell()->GetClassName()]++;
      ++numTets;
    }
    std::stringstream ss;
    ss << "# of Tetras: " << numTets << std::endl;
    TextMapper->SetInput(ss.str().c_str());

  }
  SliderCallbackChordError():Tessellator(0),TextMapper(0) {}
  vtkTessellatorFilter *Tessellator;
  vtkTextMapper *TextMapper;
};

void
MakeWidget(vtkSmartPointer<vtkSliderWidget> &widget,
           vtkSmartPointer<vtkTessellatorFilter> &tessellate,
           vtkSmartPointer<vtkTextMapper> &textMapper,
           vtkSmartPointer<vtkRenderWindowInteractor> &interactor)
{
  // Setup a slider widget for each varying parameter
  double tubeWidth(0.008);
  double sliderLength(0.008);
  double titleHeight(0.04);
  double labelHeight(0.04);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepChordError =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepChordError->SetMinimumValue(0.0);
  sliderRepChordError->SetMaximumValue(0.07);
  sliderRepChordError->SetValue(tessellate->GetChordError());
  sliderRepChordError->SetTitleText("Chord error");

  sliderRepChordError->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepChordError->GetPoint1Coordinate()->SetValue(0.1, 0.1);
  sliderRepChordError->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepChordError->GetPoint2Coordinate()->SetValue(0.9, 0.1);

  sliderRepChordError->SetTubeWidth(tubeWidth);
  sliderRepChordError->SetSliderLength(sliderLength);
  sliderRepChordError->SetTitleHeight(titleHeight);
  sliderRepChordError->SetLabelHeight(labelHeight);

  widget->SetInteractor(interactor);
  widget->SetRepresentation(sliderRepChordError);
  widget->SetAnimationModeToAnimate();
  widget->EnabledOn();

  vtkSmartPointer<SliderCallbackChordError> callbackChordError =
    vtkSmartPointer<SliderCallbackChordError>::New();
  callbackChordError->Tessellator = tessellate;
  callbackChordError->TextMapper = textMapper;

  widget->AddObserver(vtkCommand::InteractionEvent,callbackChordError);
}

vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticHexahedron()
{
  vtkSmartPointer<vtkQuadraticHexahedron> aHexahedron =
    vtkSmartPointer<vtkQuadraticHexahedron>::New();
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  double *pcoords = aHexahedron->GetParametricCoords();
  vtkSmartPointer<vtkMinimalStandardRandomSequence> rng =
    vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
  points->SetNumberOfPoints(aHexahedron->GetNumberOfPoints());
  rng->SetSeed(5070); // for testing
  for (auto i = 0; i < aHexahedron->GetNumberOfPoints(); ++i)
  {
    double perturbation[3];
    for (auto j = 0; j < 3; ++j)
    {
      rng->Next();
      perturbation[j] = rng->GetRangeValue(-0.1, 0.1);
    }
    aHexahedron->GetPointIds()->SetId(i, i);
    points->SetPoint(i,
                     *(pcoords + 3 * i) + perturbation[0],
                     *(pcoords + 3 * i + 1) + perturbation[1],
                     *(pcoords + 3 * i + 2) + perturbation[2]);
  }

  // Add the points and hexahedron to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(aHexahedron->GetCellType(), aHexahedron->GetPointIds());

  return uGrid;
}
}
