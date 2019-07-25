#include <vtkActor.h>
#include <vtkOBBTree.h>

#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkSliderWidget.h>

#include <vtkInteractorStyleTrackballCamera.h>
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

#include <vtkMath.h>
#include <vtkNamedColors.h>

#include <vtksys/SystemTools.hxx>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

namespace {
class vtkSliderCallback : public vtkCommand {
public:
  static vtkSliderCallback *New() { return new vtkSliderCallback; }

  vtkSliderCallback() : OBBTree(0), Level(0), PolyData(0), Renderer(0) {}

  virtual void Execute(vtkObject *caller, unsigned long, void *) {
    vtkSliderWidget *sliderWidget = reinterpret_cast<vtkSliderWidget *>(caller);
    this->Level = vtkMath::Round(static_cast<vtkSliderRepresentation *>(
                                     sliderWidget->GetRepresentation())
                                     ->GetValue());
    this->OBBTree->GenerateRepresentation(this->Level, this->PolyData);
    this->Renderer->Render();
  }

  vtkOBBTree *OBBTree;
  int Level;
  vtkPolyData *PolyData;
  vtkRenderer *Renderer;
};
} // namespace

int main(int argc, char *argv[]) {

  auto polyData = ReadPolyData(argc > 1 ? argv[1] : "");;

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto pointsMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputData(polyData);
  pointsMapper->ScalarVisibilityOff();

  auto pointsActor = vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
  pointsActor->GetProperty()->SetInterpolationToFlat();
  pointsActor->GetProperty()->SetColor(colors->GetColor4d("Yellow").GetData());
  pointsActor->GetProperty()->SetOpacity(.3);

  int maxLevel = 5;
  // Create the tree
  auto obbTree = vtkSmartPointer<vtkOBBTree>::New();
  obbTree->SetDataSet(polyData);
  obbTree->SetMaxLevel(maxLevel);
  obbTree->BuildLocator();

  double corner[3] = {0.0, 0.0 ,0.0};
  double max[3] = {0.0, 0.0 ,0.0};
  double mid[3] = {0.0, 0.0, 0.0};
  double min[3] = {0.0, 0.0, 0.0};
  double size[3] = {0.0, 0.0, 0.0};

  obbTree->ComputeOBB(polyData, corner, max, mid, min, size);

  std::cout << "Corner:\t"
            << corner[0] << ", " << corner[1] << ", " << corner[2] << std::endl
            << "Max:\t"
            << max[0] << ", " << max[1] << ", " << max[2] << std::endl
            << "Mid:\t"
            << mid[0] << ", " << mid[1] << ", " << mid[2] << std::endl
            << "Min:\t"
            << min[0] << ", " << min[1] << ", " << min[2] << std::endl
            << "Size:\t"
            << size[0] << ", " << size[1] << ", " << size[2] << std::endl;

  // Initialize the representation
  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  obbTree->GenerateRepresentation(0, polydata);

  auto obbtreeMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  obbtreeMapper->SetInputData(polydata);

  auto obbtreeActor = vtkSmartPointer<vtkActor>::New();
  obbtreeActor->SetMapper(obbtreeMapper);
  obbtreeActor->GetProperty()->SetInterpolationToFlat();
  obbtreeActor->GetProperty()->SetOpacity(.5);
  obbtreeActor->GetProperty()->EdgeVisibilityOn();
  obbtreeActor->GetProperty()->SetColor(
      colors->GetColor4d("SpringGreen").GetData());

  // A renderer and render window
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  auto style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->SetInteractorStyle(style);

  // Add the actors to the scene
  renderer->AddActor(pointsActor);
  renderer->AddActor(obbtreeActor);
  renderer->SetBackground(colors->GetColor3d("MidnightBlue").GetData());
  renderer->UseHiddenLineRemovalOn();

  // Render an image (lights and cameras are created automatically)
  renderWindow->SetWindowName("VisualizeOBBTree");
  renderWindow->SetSize(600, 600);
  renderWindow->Render();

  auto sliderRep =
      vtkSmartPointer<vtkSliderRepresentation2D>::New();
  sliderRep->SetMinimumValue(0);
  sliderRep->SetMaximumValue(obbTree->GetLevel());
  sliderRep->SetValue(obbTree->GetLevel() / 2);
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

  auto sliderWidget =
      vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidget->SetInteractor(renderWindowInteractor);
  sliderWidget->SetRepresentation(sliderRep);
  sliderWidget->SetAnimationModeToAnimate();
  sliderWidget->EnabledOn();

  auto callback =
      vtkSmartPointer<vtkSliderCallback>::New();
  callback->OBBTree = obbTree;
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
