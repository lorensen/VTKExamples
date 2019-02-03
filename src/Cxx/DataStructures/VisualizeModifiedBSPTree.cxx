#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkMath.h>
#include <vtkModifiedBSPTree.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkSliderWidget.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTextProperty.h>
#include <vtkWidgetEvent.h>
#include <vtkWidgetEventTranslator.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtksys/SystemTools.hxx>

#include <cmath>

namespace {
class vtkSliderCallback : public vtkCommand {
public:
  static vtkSliderCallback *New() { return new vtkSliderCallback; }
  vtkSliderCallback() : BSPTree(0), Level(0), PolyData(0), Renderer(0) {}

  virtual void Execute(vtkObject *caller, unsigned long, void *) {
    vtkSliderWidget *sliderWidget = reinterpret_cast<vtkSliderWidget *>(caller);
    this->Level = vtkMath::Round(static_cast<vtkSliderRepresentation *>(
                                     sliderWidget->GetRepresentation())
                                     ->GetValue());
    this->BSPTree->GenerateRepresentation(this->Level, this->PolyData);
    this->Renderer->Render();
  }

  vtkModifiedBSPTree *BSPTree;
  int Level;
  vtkPolyData *PolyData;
  vtkRenderer *Renderer;
};
} // namespace

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main(int argc, char *argv[]) {

  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;

  vtkNew<vtkNamedColors> colors;

  vtkSmartPointer<vtkPolyDataMapper> pointsMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputData(polyData);
  pointsMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> pointsActor = vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
  pointsActor->GetProperty()->SetInterpolationToFlat();
  pointsActor->GetProperty()->SetOpacity(.3);
  pointsActor->GetProperty()->SetColor(colors->GetColor4d("Yellow").GetData());

  // Create the tree
  vtkSmartPointer<vtkModifiedBSPTree> bspTree =
      vtkSmartPointer<vtkModifiedBSPTree>::New();
  bspTree->SetDataSet(polyData);
  bspTree->BuildLocator();

  int maxLevel = 10;
  // Initialize the representation
  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  bspTree->SetMaxLevel(maxLevel);
  bspTree->GenerateRepresentation(0, polydata);

  vtkSmartPointer<vtkPolyDataMapper> bspTreeMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  bspTreeMapper->SetInputData(polydata);

  vtkSmartPointer<vtkActor> bspTreeActor = vtkSmartPointer<vtkActor>::New();
  bspTreeActor->SetMapper(bspTreeMapper);
  bspTreeActor->GetProperty()->SetInterpolationToFlat();
  bspTreeActor->GetProperty()->SetOpacity(.5);
  bspTreeActor->GetProperty()->EdgeVisibilityOn();
  bspTreeActor->GetProperty()->SetColor(
    colors->GetColor4d("SpringGreen").GetData());

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(pointsActor);
  renderer->AddActor(bspTreeActor);
  renderer->SetBackground(colors->GetColor3d("SteelBLue").GetData());

  // Render an image (lights and cameras are created automatically)
  renderWindow->SetWindowName("VisualizeModifiedBSPTree");
  renderWindow->SetSize(600, 600);
  renderWindow->Render();

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRep =
      vtkSmartPointer<vtkSliderRepresentation2D>::New();
  sliderRep->SetMinimumValue(0);
  sliderRep->SetMaximumValue(bspTree->GetLevel());
  sliderRep->SetValue(bspTree->GetLevel() / 2);
  sliderRep->SetTitleText("Level");
  sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRep->GetPoint1Coordinate()->SetValue(.2, .2);
  sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRep->GetPoint2Coordinate()->SetValue(.8, .2);
  sliderRep->SetSliderLength(0.075);
  sliderRep->SetSliderWidth(0.05);
  sliderRep->SetEndCapLength(0.05);
  sliderRep->GetTitleProperty()->SetColor(
      colors->GetColor3d("Beige").GetData());
  sliderRep->GetCapProperty()->SetColor(
      colors->GetColor3d("MistyRose").GetData());
  sliderRep->GetSliderProperty()->SetColor(
      colors->GetColor3d("LightBlue").GetData());
  sliderRep->GetSelectedProperty()->SetColor(
      colors->GetColor3d("Violet").GetData());

  vtkSmartPointer<vtkSliderWidget> sliderWidget =
      vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidget->SetInteractor(renderWindowInteractor);
  sliderWidget->SetRepresentation(sliderRep);
  sliderWidget->SetAnimationModeToAnimate();
  sliderWidget->EnabledOn();

  vtkSmartPointer<vtkSliderCallback> callback =
      vtkSmartPointer<vtkSliderCallback>::New();
  callback->BSPTree = bspTree;
  callback->PolyData = polydata;
  callback->Renderer = renderer;

  callback->Execute(sliderWidget, 0, 0);
  sliderWidget->AddObserver(vtkCommand::InteractionEvent, callback);

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));
  if (extension == ".ply")
  {
    vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    vtkSmartPointer<vtkBYUReader> reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> source =
      vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
}
