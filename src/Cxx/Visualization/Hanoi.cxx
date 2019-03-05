/*

Translated from:
   http://www.new-npac.org/projects/sv2all/sv2/vtk/graphics/examplesCxx/Hanoi.cxx


Hanoi - application example does 3D towers of hanoi.
Usage:
 Hanoi -p # -s # -r # -c #
 where -p is the number of starting pucks on the peg;
       -s is the number of steps to take during animation;
       -r is the resolution of each puck
       -c controls output of the program.
*/

#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkMath.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNamedColors.h>
#include <vtkPNGWriter.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkSmartPointer.h>
#include <vtkVersion.h>
#include <vtkWindowToImageFilter.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace
{
void PrintCameraOrientation(vtkCamera* cam);

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

// Find command line parameters.
std::vector<std::string>::iterator FindParameter(std::string const& p,
                                                 std::vector<std::string>& v);

typedef std::array<std::stack<vtkSmartPointer<vtkActor>>, 3> PegArray;

/**
 * This routine is responsible for moving pucks from peg1 to peg2.
 *
 * @param peg1 Initial peg.
 * @param peg2 Final peg.
 */
void MovePuck(vtkRenderWindow* renWin, PegArray& pegStack, int peg1, int peg2);

/**
* Tower of Hanoi.
*
* @param n Number of disks.
* @param peg1 Source.
* @param peg2 Target.
* @param peg3 Helper.

*/
void Hanoi(vtkRenderWindow* renWin, PegArray& pegStack, int n, int peg1, int peg2, int peg3);

// Save a screenshot.
void Screenshot(std::string fileName, vtkRenderWindow* renWin);

// Default values.
auto numberOfPucks = 5;
auto numberOfSteps = 5;
auto puckResolution = 48;
auto configuration = 0; // Selecting output.
auto gotFigure2 = false; // Used to bail out of recursion if configuration == 2.
auto L = 1.0; // Puck height.
auto H = 1.1 * numberOfPucks * L; // Peg height.
auto R = 0.5; // Peg radius.
auto rMin = 4.0 * R; // The minimum allowable radius of disks.
auto rMax = 12.0 * R; // The maximum allowable radius of disks
auto D = 1.1 * 1.25 * rMax; // The distance between the pegs.
auto numberOfMoves = 0;
auto const maxPucks = 20;
}

int main(int argc, char* argv[])
{
  // Here we parse the command line.
  std::vector<std::string> parameters;
  for (auto i = 1; i < argc; ++i)
  {
    parameters.push_back(argv[i]);
  }
  auto p = FindParameter(std::string("?"), parameters);
  if (p != parameters.end())
  {
    std::cerr << "Usage:   " << argv[0] << " [-p #] [-s #] [r #] [-c #]"
              << std::endl;
    std::cerr << "Where:        -p specifies the number of pucks." << std::endl;
    std::cerr << "              -s specifies the number of steps." << std::endl;
    std::cerr << "              -r specifies the puck resolution." << std::endl;
    std::cerr << "              -c specifies configuration." << std::endl;
    std::cerr << "                 0 final configuration." << std::endl;
    std::cerr << "                 1 initial configuration." << std::endl;
    std::cerr << "                 2 intermediate configuration." << std::endl;
    std::cerr << "                 3 final configuration and save images"
              << std::endl;
    std::cerr << "Defaults:  -p 5 -s 5 -r 48 -c 0" << std::endl;
    return EXIT_FAILURE;
  }
  p = FindParameter(std::string("-p"), parameters);
  if (p != parameters.end() && std::next(p) != parameters.end())
  {
    numberOfPucks = std::abs(atoi(std::next(p)->c_str()));
  }
  p = FindParameter(std::string("-s"), parameters);
  if (p != parameters.end() && std::next(p) != parameters.end())
  {
    numberOfSteps = std::abs(atoi(std::next(p)->c_str()));
  }
  p = FindParameter(std::string("-r"), parameters);
  if (p != parameters.end() && std::next(p) != parameters.end())
  {
    puckResolution = std::abs(atoi(std::next(p)->c_str()));
  }
  p = FindParameter(std::string("-c"), parameters);
  if (p != parameters.end() && std::next(p) != parameters.end())
  {
    configuration = std::abs(atoi(std::next(p)->c_str()));
  }

  // Initialize variables and check input.
  if (numberOfPucks < 2)
  {
    std::cerr << "Please use more pucks!\n";
    return EXIT_FAILURE;
  }

  if (numberOfPucks > maxPucks)
  {
    std::cerr << "Too many pucks specified! Maximum is " << maxPucks << "\n";
    return EXIT_FAILURE;
  }

  if (numberOfSteps < 3)
  {
    std::cerr << "Please use more steps!\n";
    return EXIT_FAILURE;
  }

  if (configuration > 3)
  {
    std::cerr << "0>= configuration <= 3\n";
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Our rendering window.
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();

  // Create renderer and render window interactor.
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  renWin->AddRenderer(ren);
  renWin->SetSize(1200, 750);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  ren->SetBackground(colors->GetColor3d("PapayaWhip").GetData());

  vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition(41.0433, 27.9637, 30.442);
  camera->SetFocalPoint(11.5603, -1.51931, 0.95899);
  camera->SetClippingRange(18.9599, 91.6042);
  camera->SetViewUp(0, 1, 0);

  ren->SetActiveCamera(camera);

  // Create geometry: table, pegs, and pucks.
  vtkSmartPointer<vtkCylinderSource> pegGeometry =
    vtkSmartPointer<vtkCylinderSource>::New();
  pegGeometry->SetResolution(8);
  vtkSmartPointer<vtkPolyDataMapper> pegMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pegMapper->SetInputConnection(pegGeometry->GetOutputPort());

  vtkSmartPointer<vtkCylinderSource> puckGeometry =
    vtkSmartPointer<vtkCylinderSource>::New();
  puckGeometry->SetResolution(puckResolution);
  vtkSmartPointer<vtkPolyDataMapper> puckMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  puckMapper->SetInputConnection(puckGeometry->GetOutputPort());

  vtkSmartPointer<vtkPlaneSource> tableGeometry =
    vtkSmartPointer<vtkPlaneSource>::New();
  tableGeometry->SetResolution(10, 10);
  vtkSmartPointer<vtkPolyDataMapper> tableMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  tableMapper->SetInputConnection(tableGeometry->GetOutputPort());

  // Create the actors: table top, pegs, and pucks
  // The table
  vtkSmartPointer<vtkActor> table = vtkSmartPointer<vtkActor>::New();
  ren->AddActor(table);
  table->SetMapper(tableMapper);
  // table->GetProperty()->SetColor(0.9569, 0.6431, 0.3765);
  table->GetProperty()->SetColor(colors->GetColor3d("SaddleBrown").GetData());
  table->AddPosition(D, 0, 0);
  table->SetScale(4 * D, 2 * D, 3 * D);
  table->RotateX(90);

  // The pegs (using cylinder geometry).  Note that the pegs have to translated
  // in the  y-direction because the cylinder is centered about the origin.
  H = 1.1 * numberOfPucks * L;
  std::vector<vtkSmartPointer<vtkActor>> peg;
  for (auto i = 0; i < 3; ++i)
  {
    peg.push_back(vtkSmartPointer<vtkActor>::New());
    ren->AddActor(peg[i]);
    peg[i]->SetMapper(pegMapper);
    // peg[i]->GetProperty()->SetColor(1, 1, 1);
    peg[i]->GetProperty()->SetColor(colors->GetColor3d("Lavender").GetData());
    peg[i]->AddPosition(i * D, H / 2, 0);
    peg[i]->SetScale(1, H, 1);
  }

  // Three pegs, each a stack of a vector of actors.
  PegArray pegStack;

  // The pucks (using cylinder geometry). Always loaded on peg# 0.
  std::vector<vtkSmartPointer<vtkActor>> puck;
  vtkSmartPointer<vtkMinimalStandardRandomSequence> randomSequence =
    vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
  randomSequence->SetSeed(1);
  for (auto i = 0; i < numberOfPucks; ++i)
  {
    puck.push_back(vtkSmartPointer<vtkActor>::New());
    puck[i]->SetMapper(puckMapper);
    std::array<double, 3> color{{0, 0, 0}};
    for (auto j = 0; j < 3; ++j)
    {
      color[j] = randomSequence->GetValue();
      randomSequence->Next();
    }
    puck[i]->GetProperty()->SetColor(color.data());
    puck[i]->AddPosition(0, i * L + L / 2, 0);
    auto scale = rMax - i * (rMax - rMin) / (numberOfPucks - 1);
    puck[i]->SetScale(scale, 1, scale);
    ren->AddActor(puck[i]);
    pegStack[0].push(puck[i]);
  }

  // Reset the camera to view all actors.
  renWin->Render();
  renWin->SetWindowName("Towers of Hanoi");

  if (configuration == 3)
  {
    Screenshot("hanoi0.png", renWin);
  }
  if (configuration != 1)
  {
    // Begin recursion.
    Hanoi(renWin, pegStack, numberOfPucks - 1, 0, 2, 1);
    Hanoi(renWin, pegStack, 1, 0, 1, 2);
    if (!gotFigure2)
    {
      Hanoi(renWin, pegStack, numberOfPucks - 1, 2, 1, 0);

      renWin->Render();
      if (configuration == 3)
      {
        Screenshot("hanoi2.png", renWin);
      }
    }
    // Report output.
    cout << "Number of moves: " << numberOfMoves << "\n"
         << "Polygons rendered each frame: "
         << 3 * 8 + 1 + numberOfPucks * (2 + puckResolution) << "\n"
         << "Total number of frames: " << numberOfMoves * 3 * numberOfSteps
         << "\n";
  }
  vtkSmartPointer<CameraModifiedCallback> getOrientation =
    vtkSmartPointer<CameraModifiedCallback>::New();
  // Set the camera to use.
  getOrientation->cam = ren->GetActiveCamera();
  iren->AddObserver(vtkCommand::EndInteractionEvent, getOrientation);

  // Render the image.
  iren->Initialize();
  iren->Start();
  return EXIT_SUCCESS;
}

namespace
{

std::vector<std::string>::iterator FindParameter(std::string const& p,
                                                 std::vector<std::string>& v)
{
  return std::find(v.begin(), v.end(), p);
}

void MovePuck(vtkRenderWindow* renWin, PegArray& pegStack, int peg1, int peg2)
{
  numberOfMoves++;

  // Get the actor to move
  vtkActor* movingActor = pegStack[peg1].top();
  pegStack[peg1].pop();

  // Get the distance to move up.
  auto distance =
    (H - (L * (static_cast<int>(pegStack[peg1].size()) - 1)) + rMax) /
    numberOfSteps;
  for (auto i = 0; i < numberOfSteps; i++)
  {
    movingActor->AddPosition(0, distance, 0);
    renWin->Render();
  }

  // get the distance to move across
  distance = (peg2 - peg1) * D / numberOfSteps;
  auto flipAngle = 180.0 / numberOfSteps;
  for (auto i = 0; i < numberOfSteps; i++)
  {
    movingActor->AddPosition(distance, 0, 0);
    movingActor->RotateX(flipAngle);
    renWin->Render();
    if (numberOfMoves == 13 && i == 3) // for making book image
    {
      if (configuration == 3 || configuration == 2)
      {
        vtkCamera* cam =
          renWin->GetRenderers()->GetFirstRenderer()->GetActiveCamera();
        vtkSmartPointer<vtkCamera> camera1 = vtkSmartPointer<vtkCamera>::New();
        camera1->SetPosition(54.7263, 41.6467, 44.125);
        camera1->SetFocalPoint(11.5603, -1.51931, 0.95899);
        camera1->SetClippingRange(42.4226, 115.659);
        camera1->SetViewUp(0, 1, 0);
        renWin->GetRenderers()->GetFirstRenderer()->SetActiveCamera(camera1);
        renWin->Render();
        if (configuration == 3)
        {
          Screenshot("hanoi1.png", renWin);
        }
        if (configuration == 2)
        {
          gotFigure2 = true;
          break;
        }
        renWin->GetRenderers()->GetFirstRenderer()->SetActiveCamera(cam);
        renWin->Render();
      }
    }
  }

  if (gotFigure2)
  {
    pegStack[peg2].push(movingActor);
    return;
  }

  // Get the distance to move down.
  distance = ((L * (static_cast<int>(pegStack[peg2].size()) - 1)) - H - rMax) /
             numberOfSteps;

  for (auto i = 0; i < numberOfSteps; i++)
  {
    movingActor->AddPosition(0, distance, 0);
    renWin->Render();
  }

  pegStack[peg2].push(movingActor);
}

void Hanoi(vtkRenderWindow* renWin, PegArray& pegStack, int n, int peg1, int peg2, int peg3)
{
  // If gotFigure2 is true, we break out of the recursion.
  if (gotFigure2)
  {
    return;
  }
  if (n != 1)
  {
    Hanoi(renWin, pegStack, n - 1, peg1, peg3, peg2);
    if (gotFigure2)
    {
      return;
    }
    Hanoi(renWin, pegStack, 1, peg1, peg2, peg3);
    Hanoi(renWin, pegStack, n - 1, peg3, peg2, peg1);
  }
  else
  {
    MovePuck(renWin, pegStack, peg1, peg2);
  }
  return;
}

void Screenshot(std::string fileName, vtkRenderWindow* renWin)
{
  vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
    vtkSmartPointer<vtkWindowToImageFilter>::New();
  windowToImageFilter->SetInput(renWin);

#if VTK_MAJOR_VERSION >= 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  windowToImageFilter->SetScale(1); // image quality
#else
  windowToImageFilter->SetMagnification(1); // image quality
#endif

  // We are not recording the alpha (transparency) channel.
  // windowToImageFilter->SetInputBufferTypeToRGBA();
  windowToImageFilter->SetInputBufferTypeToRGB();
  // Read from the front buffer.
  windowToImageFilter->ReadFrontBufferOff();
  windowToImageFilter->Update();

  vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName(fileName.c_str());
  writer->SetInputConnection(windowToImageFilter->GetOutputPort());
  writer->Write();
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
