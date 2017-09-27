#include <vtkSmartPointer.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>
#include <vtkTimerLog.h>
#include <vtksys/SystemTools.hxx>
#include <vtksys/RegularExpression.hxx>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}
#include <vtkActor.h>
#include <vtkCamera.h>
namespace
{
void SaveSceneToFile(std::string fileName,
                     vtkActor *actor,
                     vtkCamera *camera);
}
#include <vtkActor.h>
#include <vtkCamera.h>
namespace
{
void RestoreSceneFromFile(std::string fileName,
                          vtkActor *actor,
                          vtkCamera *camera);
}
int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;

  // Visualize
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Crimson").GetData());
  actor->GetProperty()->SetSpecular(.6);
  actor->GetProperty()->SetSpecularPower(30);
;
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  // Interact to change camera
  renderWindow->Render();
  renderWindowInteractor->Start();

  // After the interaction is done, save the scene
  SaveSceneToFile(argv[2], actor, renderer->GetActiveCamera());
  renderWindow->Render();
  renderWindowInteractor->Start();

  // After interaction , restore the scene
  RestoreSceneFromFile(argv[2], actor, renderer->GetActiveCamera());
  renderWindow->Render();
  renderWindowInteractor->Start();

return EXIT_SUCCESS;
}

namespace
{
#include <fstream>
void SaveSceneToFile(std::string fileName,
                     vtkActor * /* actor */,
                     vtkCamera *camera)
{
// Actor
//  Position, orientation, origin, scale, usrmatrix, usertransform
//Camera
//  FocalPoint, Position, ViewUp, ViewAngle, ClippingRange
  std::ofstream saveFile(fileName, std::ofstream::out);
  double vector[3];
  double scalar;

  camera->GetFocalPoint(vector);
  saveFile << "Camera:FocalPoint "
           << vector[0] << ", "
           << vector[1] << ", "
           << vector[2] << std::endl;
  camera->GetPosition(vector);
  saveFile << "Camera:Position "
           << vector[0] << ", "
           << vector[1] << ", "
           << vector[2] << std::endl;
  camera->GetViewUp(vector);
  saveFile << "Camera:ViewUp "
           << vector[0] << ", "
           << vector[1] << ", "
           << vector[2] << std::endl;
  scalar = camera->GetViewAngle();
  saveFile << "Camera:ViewAngle "
           << scalar << std::endl;
  camera->GetClippingRange(vector);
  saveFile << "Camera:ClippingRange "
           << vector[0] << ", "
           << vector[1] << std::endl;
  saveFile.close();
}
}
namespace
{
#include <fstream>
void RestoreSceneFromFile(std::string fileName,
                          vtkActor * /* actor */,
                          vtkCamera *camera)
{
  std::ifstream saveFile(fileName);
  std::string line;

  vtksys::RegularExpression reCP("^Camera:Position");
  vtksys::RegularExpression reCFP("^Camera:FocalPoint");
  vtksys::RegularExpression reCVU("^Camera:ViewUp");
  vtksys::RegularExpression reCVA("^Camera:ViewAngle");
  vtksys::RegularExpression reCCR("^Camera:ClippingRange");
  vtksys::RegularExpression floatNumber(
      "[^0-9\\.\\-]*([0-9e\\.\\-]*[^,])[^0-9\\.\\-]*([0-9e\\.\\-]*[^,])[^0-9\\.\\-]*([0-9e\\.\\-]*[^,])");
  vtksys::RegularExpression floatScalar("[^0-9\\.\\-]*([0-9\\.\\-e]*[^,])");

  while (std::getline(saveFile, line) && ! saveFile.eof())
  {
    if (reCFP.find(line))
    {
      std::string rest(line, reCFP.end());
      if (floatNumber.find(rest))
      {
        camera->SetFocalPoint(
          atof(floatNumber.match(1).c_str()),
          atof(floatNumber.match(2).c_str()),
          atof(floatNumber.match(3).c_str()));
      }
    }
    else if (reCP.find(line))
    {
      std::string rest(line, reCP.end());
      if (floatNumber.find(rest))
      {
        camera->SetPosition(
          atof(floatNumber.match(1).c_str()),
          atof(floatNumber.match(2).c_str()),
          atof(floatNumber.match(3).c_str()));
      }
    }
    else if (reCVU.find(line))
    {
      std::string rest(line, reCVU.end());
      if (floatNumber.find(rest))
      {
        camera->SetViewUp(
          atof(floatNumber.match(1).c_str()),
          atof(floatNumber.match(2).c_str()),
          atof(floatNumber.match(3).c_str()));
      }
    }
    else if (reCVA.find(line))
    {
      std::string rest(line, reCVA.end());
      if (floatScalar.find(rest))
      {
        camera->SetViewAngle(
          atof(floatScalar.match(1).c_str()));
      }
    }
    else if (reCCR.find(line))
    {
      std::string rest(line, reCCR.end());
      if (floatNumber.find(rest))
      {
        camera->SetClippingRange(
          atof(floatNumber.match(1).c_str()),
          atof(floatNumber.match(2).c_str()));
      }
    }
    else
    {
      std::cout << "Unrecognized line: " << line << std::endl;
    }
  }
  saveFile.close();
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
