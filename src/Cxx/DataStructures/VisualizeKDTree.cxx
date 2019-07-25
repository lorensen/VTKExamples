#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkKdTree.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
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
#include <vtkTextProperty.h>
#include <vtkWidgetEvent.h>
#include <vtkWidgetEventTranslator.h>

// Readers
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkSphereSource.h>

#include <algorithm> // For transform()
//#include <array>
#include <cctype> // For to_lower
#include <iostream>
#include <string> // For find_last_of()

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName);

class vtkSliderCallback : public vtkCommand
{
public:
  static vtkSliderCallback* New()
  {
    return new vtkSliderCallback;
  }
  vtkSliderCallback() : KdTree(0), Level(0), PolyData(0), Renderer(0)
  {
  }

  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
    this->Level = vtkMath::Round(
        static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())
            ->GetValue());
    this->KdTree->GenerateRepresentation(this->Level, this->PolyData);
    this->Renderer->Render();
  }

  vtkKdTree* KdTree;
  int Level;
  vtkPolyData* PolyData;
  vtkRenderer* Renderer;
};
} // namespace

int main(int argc, char* argv[])
{
  auto polyData = ReadPolyData(argc > 1 ? argv[1] : "");
  ;

  vtkNew<vtkNamedColors> colors;

  auto pointsMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputData(polyData);
  pointsMapper->ScalarVisibilityOff();

  auto pointsActor = vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
  pointsActor->GetProperty()->SetInterpolationToFlat();
  pointsActor->GetProperty()->SetColor(colors->GetColor4d("Yellow").GetData());

  int maxLevel = 20;
  // Create the tree
  auto kdTree = vtkSmartPointer<vtkKdTree>::New();
  kdTree->SetDataSet(polyData);
  kdTree->SetMaxLevel(maxLevel);
  kdTree->BuildLocator();

  // Initialize the representation
  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  kdTree->GenerateRepresentation(maxLevel / 2, polydata);

  auto octreeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  octreeMapper->SetInputData(polydata);

  auto octreeActor = vtkSmartPointer<vtkActor>::New();
  octreeActor->SetMapper(octreeMapper);
  octreeActor->GetProperty()->SetInterpolationToFlat();
  octreeActor->GetProperty()->SetOpacity(.6);
  octreeActor->GetProperty()->EdgeVisibilityOn();
  octreeActor->GetProperty()->SetColor(
      colors->GetColor4d("SpringGreen").GetData());

  // A renderer and render window
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(pointsActor);
  renderer->AddActor(octreeActor);
  renderer->SetBackground(colors->GetColor3d("MidnightBlue").GetData());
  renderer->SetUseDepthPeeling(1);

  // Render an image (lights and cameras are created automatically)
  renderWindow->SetWindowName("VisualizeKDTree");
  renderWindow->SetSize(600, 600);
  renderWindow->Render();

  auto sliderRep = vtkSmartPointer<vtkSliderRepresentation2D>::New();
  sliderRep->SetMinimumValue(0);
  sliderRep->SetMaximumValue(kdTree->GetLevel());
  sliderRep->SetValue(kdTree->GetLevel() / 2);
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

  auto sliderWidget = vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidget->SetInteractor(renderWindowInteractor);
  sliderWidget->SetRepresentation(sliderRep);
  sliderWidget->SetAnimationModeToAnimate();
  sliderWidget->EnabledOn();

  auto callback = vtkSmartPointer<vtkSliderCallback>::New();
  callback->KdTree = kdTree;
  callback->PolyData = polydata;
  callback->Renderer = renderer;
  callback->Execute(sliderWidget, 0, 0);

  sliderWidget->AddObserver(vtkCommand::InteractionEvent, callback);

  // Ensure the current level is set
  callback->Execute(sliderWidget, 0, 0);
  renderWindowInteractor->Initialize();
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = "";
  if (fileName.find_last_of(".") != std::string::npos)
  {
    extension = fileName.substr(fileName.find_last_of("."));
  }
  // Make the extension lowercase
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower);
  if (extension == ".ply")
  {
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader = vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    // Return a polydata sphere if the extension is unknown.
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->SetThetaResolution(20);
    source->SetPhiResolution(11);
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
} // namespace
