#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkGlyph3D.h>
#include <vtkPointWidget.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProbeFilter.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkNamedColors.h>

#include <sstream>

// This does the actual work: updates the probe.
// Callback for the interaction
class vtkmyPWCallback : public vtkCommand
{
public:
  vtkmyPWCallback() = default;

  static vtkmyPWCallback* New()
  {
    return new vtkmyPWCallback;
  }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkPointWidget* pointWidget = reinterpret_cast<vtkPointWidget*>(caller);
    pointWidget->GetPolyData(this->PolyData);
    double position[3];
    pointWidget->GetPosition(position);
    std::ostringstream text;
    text << "cursor: " << std::fixed << std::setprecision(4) << position[0]
         << ", " << position[1] << ", " << position[2];
    this->PositionActor->SetInput(text.str().c_str());
    this->CursorActor->VisibilityOn();
  }

  vtkPolyData* PolyData = nullptr;
  vtkActor* CursorActor = nullptr;
  vtkTextActor* PositionActor = nullptr;
};

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkPolyData> inputPolyData;

  if (argc > 1)
  {
    auto reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    inputPolyData = reader->GetOutput();
  }
  else
  {
    auto sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetPhiResolution(15);
    sphereSource->SetThetaResolution(15);
    sphereSource->Update();
    inputPolyData = sphereSource->GetOutput();
  }

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  auto point =
    vtkSmartPointer<vtkPolyData>::New();

  auto probe =
    vtkSmartPointer<vtkProbeFilter>::New();
  probe->SetInputData(point);
  probe->SetSourceData(inputPolyData);

  // create glyph
  auto cone =
    vtkSmartPointer<vtkConeSource>::New();
  cone->SetResolution(16);

  auto glyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph->SetInputConnection(probe->GetOutputPort());
  glyph->SetSourceConnection(cone->GetOutputPort());
  glyph->SetVectorModeToUseVector();
  glyph->SetScaleModeToDataScalingOff();
  glyph->SetScaleFactor(inputPolyData->GetLength() * 0.1);

  auto glyphMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyphMapper->SetInputConnection(glyph->GetOutputPort());

  auto glyphActor =
    vtkSmartPointer<vtkActor>::New();
  glyphActor->SetMapper(glyphMapper);
  glyphActor->VisibilityOn();

  auto mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(inputPolyData);

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();
  actor->GetProperty()->SetColor(colors->GetColor3d("gold").GetData());

  auto textActor =
    vtkSmartPointer<vtkTextActor>::New();
  textActor->GetTextProperty()->SetFontSize(12);
  textActor->SetPosition(10, 20);
  textActor->SetInput("cursor:");
  textActor->GetTextProperty()->SetColor(colors->GetColor3d("White").GetData());

  // Create the RenderWindow, Render1er and both Actors
  //
  auto ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  auto renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  auto iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // The SetInteractor method is how 3D widgets are associated with the render
  // window interactor. Internally, SetInteractor sets up a bunch of callbacks
  // using the Command/Observer mechanism (AddObserver()).
  auto myCallback =
    vtkSmartPointer<vtkmyPWCallback>::New();
  myCallback->PolyData = point;
  myCallback->CursorActor = glyphActor;
  myCallback->PositionActor = textActor;

  // The point widget is used probe the dataset.
  //
  auto pointWidget =
    vtkSmartPointer<vtkPointWidget>::New();
  pointWidget->SetInteractor(iren);
  pointWidget->SetInputData(inputPolyData);
  pointWidget->AllOff();
  pointWidget->PlaceWidget();
  pointWidget->AddObserver(vtkCommand::InteractionEvent, myCallback);

  ren1->AddActor(glyphActor);
  ren1->AddActor(actor);
  ren1->AddActor2D(textActor);

  // Add the actors to the renderer, set the background and size
  //
  ren1->GradientBackgroundOn();
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  ren1->SetBackground2(colors->GetColor3d("Wheat").GetData());

  renWin->SetSize(300, 300);
  renWin->Render();
  pointWidget->On();
  // render the image
  //
  iren->Initialize();
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
