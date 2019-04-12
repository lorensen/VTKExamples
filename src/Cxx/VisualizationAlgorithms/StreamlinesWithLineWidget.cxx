/*
Modified from VTK/Examples/GUI/Python/StreamlinesWithLineWidget.py.
This program encompasses the functionality of
StreamlinesWithLineWidget.tcl and LineWidget.tcl.

        Produce streamlines in the combustor dataset.

This example demonstrates how to use the vtkLineWidget to seed and
manipulate streamlines. Two line widgets are created. The first is invoked
by pressing 'i', the second by pressing 'L' (capital). Both can exist
together.

If the fourth parameter is non-zero:
 1) The third parameter value is changed to 25.
 2) The camera position and first line widget are positioned differently.
 3) The streamlines are displayed running from the first line widget.
 4) The second line widget is still available.
This is used to test the code.

*/

#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCamera.h>
#include <vtkLineWidget.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRibbonFilter.h>
#include <vtkRungeKutta4.h>
#include <vtkSmartPointer.h>
#include <vtkStreamTracer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridOutlineFilter.h>

namespace
{

class EnableActorCallback : public vtkCommand
{
public:
  static EnableActorCallback* New() { return new EnableActorCallback; }
  void Execute(vtkObject* /*caller*/, unsigned long, void*) override
  {
    this->actor->VisibilityOn();
  }
  EnableActorCallback()
    : actor(nullptr)
  {
  }
  vtkActor* actor;
};

// The Line Widget callback.
class LWCallback : public vtkCommand
{
public:
  static LWCallback* New() { return new LWCallback; }
  void Execute(vtkObject* caller, unsigned long, void*) override
  {
    vtkLineWidget* lineWidget = reinterpret_cast<vtkLineWidget*>(caller);
    lineWidget->GetPolyData(this->polyData);
    this->renWin->Render();
  }
  LWCallback()
    : polyData(nullptr)
    , renWin(nullptr)
  {
  }
  vtkPolyData* polyData;
  vtkRenderWindow* renWin;
};
}

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0]
              << " filename1 filename2 [numOfStreamLines] [illustration]"
              << std::endl;
    std::cout << "where: filename1 is combxyz.bin and filename2 is combq.bin."
              << std::endl;
    std::cout
      << "       numOfStreamLines is the number of streamlines, default 25"
      << std::endl;
    std::cout << "       illustration, if non-zero, reproduce Fig 7-39 of the "
                 "VTK Textbook."
              << std::endl;
    return EXIT_FAILURE;
  }
  auto numOfStreamLines = 25;
  auto illustration = false;
  std::string fileName1 = argv[1];
  std::string fileName2 = argv[2];
  if (argc > 3)
  {
    numOfStreamLines = atoi(argv[3]);
  }
  if (argc > 4)
  {
    illustration = atoi(argv[4]) != 0;
    if (illustration)
    {
      numOfStreamLines = 25;
    }
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Start by loading some data.
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->SetXYZFileName(fileName1.c_str());
  pl3d->SetQFileName(fileName2.c_str());
  pl3d->SetScalarFunctionNumber(100); // Density
  pl3d->SetVectorFunctionNumber(202); // Momentum
  pl3d->Update();

  vtkStructuredGrid* pl3d_output =
    dynamic_cast<vtkStructuredGrid*>(pl3d->GetOutput()->GetBlock(0));

  // Create the Renderer, RenderWindow and RenderWindowInteractor.
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Needed by: vtkStreamTracer and vtkLineWidget.
  vtkSmartPointer<vtkPolyData> seeds = vtkSmartPointer<vtkPolyData>::New();
  vtkSmartPointer<vtkActor> streamline = vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkPolyData> seeds2 = vtkSmartPointer<vtkPolyData>::New();
  vtkSmartPointer<vtkActor> streamline2 = vtkSmartPointer<vtkActor>::New();

  // The line widget is used seed the streamlines.
  vtkSmartPointer<vtkLineWidget> lineWidget =
    vtkSmartPointer<vtkLineWidget>::New();
  lineWidget->SetResolution(numOfStreamLines);
  lineWidget->SetInputData(pl3d_output);
  lineWidget->GetPolyData(seeds);
  if (illustration)
  {
    lineWidget->SetAlignToNone();
    lineWidget->SetPoint1(0.974678, 5.073630, 31.217961);
    lineWidget->SetPoint2(0.457544, -4.995921, 31.080175);
  }
  else
  {
    lineWidget->SetAlignToYAxis();
  }
  lineWidget->ClampToBoundsOn();
  lineWidget->PlaceWidget();

  lineWidget->SetInteractor(iren);

  // Associate the line widget with the interactor and setup the callbacks.
  vtkSmartPointer<LWCallback> GenerateStreamlines =
    vtkSmartPointer<LWCallback>::New();
  GenerateStreamlines->polyData = seeds;
  GenerateStreamlines->renWin = renWin;
  vtkSmartPointer<EnableActorCallback> BeginInteraction =
    vtkSmartPointer<EnableActorCallback>::New();
  BeginInteraction->actor = streamline;
  lineWidget->AddObserver(vtkCommand::StartInteractionEvent, BeginInteraction);
  lineWidget->AddObserver(vtkCommand::InteractionEvent, GenerateStreamlines);

  // The second line widget is used seed more streamlines.
  vtkSmartPointer<vtkLineWidget> lineWidget2 =
    vtkSmartPointer<vtkLineWidget>::New();
  lineWidget2->SetResolution(numOfStreamLines);
  lineWidget2->SetInputData(pl3d_output);
  lineWidget2->GetPolyData(seeds2);
  lineWidget2->SetKeyPressActivationValue('L');
  lineWidget2->SetAlignToZAxis();
  lineWidget->ClampToBoundsOn();
  lineWidget2->PlaceWidget();

  lineWidget2->SetInteractor(iren);

  // Associate the line widget with the interactor and setup the callbacks.
  vtkSmartPointer<LWCallback> GenerateStreamlines2 =
    vtkSmartPointer<LWCallback>::New();
  GenerateStreamlines2->polyData = seeds2;
  GenerateStreamlines2->renWin = renWin;
  vtkSmartPointer<EnableActorCallback> BeginInteraction2 =
    vtkSmartPointer<EnableActorCallback>::New();
  BeginInteraction2->actor = streamline2;
  lineWidget2->AddObserver(vtkCommand::StartInteractionEvent,
                           BeginInteraction2);
  lineWidget2->AddObserver(vtkCommand::InteractionEvent, GenerateStreamlines2);

  // Here we set up two streamlines.
  vtkSmartPointer<vtkRungeKutta4> rk4 = vtkSmartPointer<vtkRungeKutta4>::New();
  vtkSmartPointer<vtkStreamTracer> streamer =
    vtkSmartPointer<vtkStreamTracer>::New();
  streamer->SetInputData(pl3d_output);
  streamer->SetSourceData(seeds);
  streamer->SetMaximumPropagation(100);
  streamer->SetInitialIntegrationStep(0.2);
  streamer->SetIntegrationDirectionToForward();
  streamer->SetComputeVorticity(1);
  streamer->SetIntegrator(rk4);
  vtkSmartPointer<vtkRibbonFilter> rf = vtkSmartPointer<vtkRibbonFilter>::New();
  rf->SetInputConnection(streamer->GetOutputPort());
  rf->SetWidth(0.1);
  rf->SetWidthFactor(5);
  vtkSmartPointer<vtkPolyDataMapper> streamMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  streamMapper->SetInputConnection(rf->GetOutputPort());
  streamMapper->SetScalarRange(pl3d_output->GetScalarRange());
  streamline->SetMapper(streamMapper);
  streamline->VisibilityOff();

  vtkSmartPointer<vtkStreamTracer> streamer2 =
    vtkSmartPointer<vtkStreamTracer>::New();
  streamer2->SetInputData(pl3d_output);
  streamer2->SetSourceData(seeds2);
  streamer2->SetMaximumPropagation(100);
  streamer2->SetInitialIntegrationStep(0.2);
  streamer2->SetIntegrationDirectionToForward();
  streamer2->SetComputeVorticity(1);
  streamer2->SetIntegrator(rk4);
  vtkSmartPointer<vtkRibbonFilter> rf2 =
    vtkSmartPointer<vtkRibbonFilter>::New();
  rf2->SetInputConnection(streamer2->GetOutputPort());
  rf2->SetWidth(0.1);
  rf2->SetWidthFactor(5);
  vtkSmartPointer<vtkPolyDataMapper> streamMapper2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  streamMapper2->SetInputConnection(rf2->GetOutputPort());
  streamMapper2->SetScalarRange(pl3d_output->GetScalarRange());
  streamline2->SetMapper(streamMapper2);
  streamline2->VisibilityOff();

  // Get an outline of the data set for context.
  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputData(pl3d_output);
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());
  outlineActor->SetMapper(outlineMapper);

  // Add the actors to the renderer, set the background and size.
  ren->AddActor(outlineActor);
  ren->AddActor(streamline);
  ren->AddActor(streamline2);
  renWin->SetSize(512, 512);
  vtkCamera* cam = ren->GetActiveCamera();
  if (illustration)
  {
    // We need to directly display the streamlines in this case.
    lineWidget->EnabledOn();
    streamline->VisibilityOn();
    lineWidget->GetPolyData(seeds);
    renWin->Render();

    cam->SetClippingRange(14.216207, 68.382915);
    cam->SetFocalPoint(9.718210, 0.458166, 29.399900);
    cam->SetPosition(-15.827551, -16.997463, 54.003120);
    cam->SetViewUp(0.616076, 0.179428, 0.766979);
    ren->SetBackground(colors->GetColor3d("Silver").GetData());
  }
  else
  {
    cam->SetClippingRange(3.95297, 50);
    cam->SetFocalPoint(9.71821, 0.458166, 29.3999);
    cam->SetPosition(2.7439, -37.3196, 38.7167);
    cam->SetViewUp(-0.16123, 0.264271, 0.950876);
    ren->SetBackground(colors->GetColor3d("Silver").GetData());
  }

  iren->Initialize();
  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
}
