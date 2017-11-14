/*
Demonstrate the use of a callback.

We also add call data.

*/

#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <iterator>
#include <sstream>
#include <vector>

#define USE_CALLBACKCOMMAND_CLASS
// Uncomment this if you want to use the function instead.
//#undef USE_CALLBACKCOMMAND_CLASS

namespace
{
void PrintCameraOrientation(vtkCamera* cam);
void MakeAxesActor(vtkAxesActor* axesActor);

#if defined(USE_CALLBACKCOMMAND_CLASS)
/**
Here we inherit from vtkCallbackCommand and set pointers to any
client and/or call data as needed.
When the class is implemented, it becomes the callback function.
*/
class CameraModifiedCallback : public vtkCallbackCommand
{
public:
  static CameraModifiedCallback* New() { return new CameraModifiedCallback; }
  // Here we Create a vtkCallbackCommand and reimplement it.
  void Execute(vtkObject* caller, unsigned long evId, void*) override
  {
    // Note the use of reinterpret_cast to cast the caller to the expected type.
    vtkRenderWindowInteractor* interactor =
      reinterpret_cast<vtkRenderWindowInteractor*>(caller);
    // Just do this to demonstrate who called callback and the event that
    // triggered it.
    std::cout << interactor->GetClassName() << "  Event Id: " << evId
              << std::endl;

    // Now print the camera orientation.
    PrintCameraOrientation(this->cam);
  }
  CameraModifiedCallback()
    : cam(nullptr)
  {
  }
  // Set pointers to any clientData or callData here.
  vtkCamera* cam;

private:
  CameraModifiedCallback(const CameraModifiedCallback&) = delete;
  void operator=(const CameraModifiedCallback&) = delete;
};

#else
/**
An alternative method is to create a function with this signature:
void f(vtkObject* caller, long unsigned int evId, void* clientData, void*
callData)
and, where needed, create a vtkCallbackCommand setting its callback to the
function we have created.
*/
void vtkCallbackFunc(vtkObject* caller, long unsigned int evId,
                     void* clientData, void* /*callData*/)
{
  // Note the use of reinterpret_cast to cast the caller and callData to the
  // expected types.
  vtkRenderWindowInteractor* interactor =
    reinterpret_cast<vtkRenderWindowInteractor*>(caller);
  std::cout << interactor->GetClassName() << "  Event Id: " << evId
            << std::endl;
  vtkSmartPointer<vtkCamera> cam = reinterpret_cast<vtkCamera*>(clientData);

  // Now print the camera orientation.
  PrintCameraOrientation(cam);
};
#endif
}

int main(int, char* [])
{

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create the Renderer, RenderWindow and RenderWindowInteractor.
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Use a cone as a source.
  vtkSmartPointer<vtkConeSource> source = vtkSmartPointer<vtkConeSource>::New();
  source->SetCenter(0, 0, 0);
  source->SetRadius(1);
  // Use the golden ratio for the height. Because we can!
  source->SetHeight(1.6180339887498948482);
  source->SetResolution(128);
  source->Update();

  // Pipeline
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(source->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("peacock").GetData());
  // Lighting
  actor->GetProperty()->SetAmbient(0.3);
  actor->GetProperty()->SetDiffuse(0.0);
  actor->GetProperty()->SetSpecular(1.0);
  actor->GetProperty()->SetSpecularPower(20.0);

  // Get an outline of the data set for context.
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputData(source->GetOutput());
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

  // Add the actors to the renderer, set the background and size.
  ren->AddActor(actor);

  ren->AddActor(outlineActor);
  ren->SetBackground(colors->GetColor3d("AliceBlue").GetData());
  renWin->SetSize(512, 512);

  // Set up a nice camera position.
  vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition(4.6, -2.0, 3.8);
  camera->SetFocalPoint(0.0, 0.0, 0.0);
  camera->SetClippingRange(3.2, 10.2);
  camera->SetViewUp(0.3, 1.0, 0.13);
  ren->SetActiveCamera(camera);

  renWin->Render();
  renWin->SetWindowName("CallBack");

  vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
  MakeAxesActor(axes);
  vtkSmartPointer<vtkOrientationMarkerWidget> om =
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  om->SetOrientationMarker(axes);
  // Position lower left in the viewport.
  om->SetViewport(0, 0, 0.2, 0.2);
  om->SetInteractor(iren);
  om->EnabledOn();
  om->InteractiveOn();

#if defined(USE_CALLBACKCOMMAND_CLASS)
  // When we implement the class, it automatically becomes the callback
  // function.
  vtkSmartPointer<CameraModifiedCallback> getOrientation =
    vtkSmartPointer<CameraModifiedCallback>::New();
  // Set the camera to use.
  getOrientation->cam = ren->GetActiveCamera();
#else
  // Create the vtkCallbackCommand.
  vtkSmartPointer<vtkCallbackCommand> getOrientation =
    vtkSmartPointer<vtkCallbackCommand>::New();
  // Set the callback to the function we created.
  getOrientation->SetCallback(vtkCallbackFunc);
  // Set the client data.
  getOrientation->SetClientData(ren->GetActiveCamera());
#endif
  iren->AddObserver(vtkCommand::EndInteractionEvent, getOrientation);
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace
{
void MakeAxesActor(vtkAxesActor* axes)
{
  axes->SetShaftTypeToCylinder();
  axes->SetXAxisLabelText("X");
  axes->SetYAxisLabelText("Y");
  axes->SetZAxisLabelText("Z");
  axes->SetTotalLength(1.0, 1.0, 1.0);
  axes->SetCylinderRadius(0.5 * axes->GetCylinderRadius());
  axes->SetConeRadius(1.025 * axes->GetConeRadius());
  axes->SetSphereRadius(1.5 * axes->GetSphereRadius());
}

/**
Get a comma separated list.
*/
template <typename T>
std::string CommaSeparatedList(std::vector<T> v)
{
  std::ostringstream os;
  std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(os, ", "));
  os << v.back();
  return os.str();
}

/**
Print the camera orientation.
*/
void PrintCameraOrientation(vtkCamera* cam)
{
  auto width = 16;
  double pos[3];
  cam->GetPosition(pos);
  double fp[3];
  cam->GetFocalPoint(fp);
  double vu[3];
  cam->GetViewUp(vu);
  double cr[2];
  cam->GetClippingRange(cr);
  std::cout << setw(width) << "Position: "
            << CommaSeparatedList(std::vector<double>(pos, pos + 3))
            << std::endl;
  std::cout << setw(width) << "Focal point: "
            << CommaSeparatedList(std::vector<double>(fp, fp + 3)) << std::endl;
  std::cout << setw(width) << "Clipping range: "
            << CommaSeparatedList(std::vector<double>(cr, cr + 2)) << std::endl;
  std::cout << setw(width) << "View up: "
            << CommaSeparatedList(std::vector<double>(vu, vu + 3)) << std::endl;
  std::cout << setw(width) << "Distance: " << cam->GetDistance() << std::endl;
};
}