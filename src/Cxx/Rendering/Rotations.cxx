
#include <vtkActor.h>
#include <vtkAxes.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>

#include <vtkPLYReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

// Readers
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkPolyData.h>
#include <vtkSphereSource.h>

#include <algorithm> // For transform()
#include <cctype>    // For to_lower
#include <string>    // For find_last_of()

#include <array>

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName);
void RotateX(vtkSmartPointer<vtkRenderWindow>& renWin,
             vtkSmartPointer<vtkActor>& actor);
void RotateY(vtkSmartPointer<vtkRenderWindow>& renWin,
             vtkSmartPointer<vtkActor>& actor);
void RotateZ(vtkSmartPointer<vtkRenderWindow>& renWin,
             vtkSmartPointer<vtkActor>& actor);
void RotateXY(vtkSmartPointer<vtkRenderWindow>& renWin,
              vtkSmartPointer<vtkActor>& actor);
} // namespace

int main(int argc, char* argv[])
{
  /*
  To match the illustrations in VTKTextbook.pdf, use BkgColor as the background
    and Wheat as the cow colour.
  Also comment out the lines:
    modelActor->GetProperty()->SetSpecular(.6);
    modelActor->GetProperty()->SetSpecularPower(30);
  and use cow.g as the input data.
  */

  auto figure = 0;
  auto book_color = false;
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename [figure] [book_color]"
              << std::endl;
    std::cout << "where: filename is the file cow.obj" << std::endl;
    std::cout << "       figure is 0, 1, 2, or 3, default 0" << std::endl;
    std::cout << "       book_color: If 1 then the vtk textbook colors are "
                 "used, default 0."
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argv[1];

  if (argc == 3)
  {
    figure = atoi(argv[2]);
  }
  else if (argc > 3)
  {
    figure = atoi(argv[2]);
    book_color = atoi(argv[3]) != 0;
  }

  // Create renderer stuff
  //
  vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char, 4> bkg{{26, 51, 102, 255}};
  // std::array<unsigned char, 4> bkg{{60, 93, 144, 255}};
  colors->SetColor("BkgColor", bkg.data());

  vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Create the pipeline.
  //
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(fileName.c_str());

  vtkSmartPointer<vtkPolyDataMapper> modelMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  modelMapper->SetInputData(polyData);

  vtkSmartPointer<vtkActor> modelActor = vtkSmartPointer<vtkActor>::New();
  modelActor->SetMapper(modelMapper);
  if (book_color)
  {
    modelActor->GetProperty()->SetDiffuseColor(
        colors->GetColor3d("Wheat").GetData());
  }
  else
  {
    modelActor->GetProperty()->SetDiffuseColor(
        colors->GetColor3d("Crimson").GetData());
    modelActor->GetProperty()->SetSpecular(.6);
    modelActor->GetProperty()->SetSpecularPower(30);
  }

  vtkSmartPointer<vtkAxes> modelAxesSource = vtkSmartPointer<vtkAxes>::New();
  modelAxesSource->SetScaleFactor(10);
  modelAxesSource->SetOrigin(0, 0, 0);

  vtkSmartPointer<vtkPolyDataMapper> modelAxesMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  modelAxesMapper->SetInputConnection(modelAxesSource->GetOutputPort());

  vtkSmartPointer<vtkActor> modelAxes = vtkSmartPointer<vtkActor>::New();
  modelAxes->SetMapper(modelAxesMapper);

  ren1->AddActor(modelAxes);
  modelAxes->VisibilityOff();

  // Add the actors to the renderer, set the background and size.
  //
  ren1->AddActor(modelActor);
  if (book_color)
  {
    ren1->SetBackground(colors->GetColor3d("BkgColor").GetData());
  }
  else
  {
    ren1->SetBackground(colors->GetColor3d("Silver").GetData());
  }
  renWin->SetSize(640, 480);
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(0);
  ren1->GetActiveCamera()->SetClippingRange(.1, 1000.0);

  modelAxes->VisibilityOn();

  renWin->Render();
  renWin->Render();

  switch (figure)
  {
  default:
  case 0:
    RotateXY(renWin, modelActor);
    break;
  case 1:
    RotateX(renWin, modelActor);
    break;
  case 2:
    RotateY(renWin, modelActor);
    break;
  case 3:
    RotateZ(renWin, modelActor);
    break;
  }
  renWin->EraseOff();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace {

void RotateX(vtkSmartPointer<vtkRenderWindow>& renWin,
             vtkSmartPointer<vtkActor>& actor)
{
  actor->SetOrientation(0, 0, 0);
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();

  for (auto i = 0; i < 6; ++i)
  {
    actor->RotateX(60);
    renWin->Render();
    renWin->Render();
  }
  renWin->EraseOn();
}

void RotateY(vtkSmartPointer<vtkRenderWindow>& renWin,
             vtkSmartPointer<vtkActor>& actor)
{
  actor->SetOrientation(0, 0, 0);
  renWin->Render();
  renWin->EraseOff();

  for (auto i = 0; i < 6; ++i)
  {
    actor->RotateY(60);
    renWin->Render();
    renWin->Render();
  }
  renWin->EraseOn();
}

void RotateZ(vtkSmartPointer<vtkRenderWindow>& renWin,
             vtkSmartPointer<vtkActor>& actor)
{
  actor->SetOrientation(0, 0, 0);
  renWin->Render();
  renWin->EraseOff();

  for (auto i = 0; i < 6; ++i)
  {
    actor->RotateZ(60);
    renWin->Render();
    renWin->Render();
  }
  renWin->EraseOn();
}

void RotateXY(vtkSmartPointer<vtkRenderWindow>& renWin,
              vtkSmartPointer<vtkActor>& actor)
{
  actor->SetOrientation(0, 0, 0);
  actor->RotateX(60);
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();

  for (auto i = 0; i < 6; ++i)
  {
    actor->RotateY(60);
    renWin->Render();
    renWin->Render();
  }
  renWin->EraseOn();
}

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
