#include <vtkSmartPointer.h>
#include <vtkExtractEnclosedPoints.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtkGlyph3DMapper.h>
#include <vtkPoints.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>
#include <vtksys/SystemTools.hxx>
#include <random>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");
  std::mt19937 mt(4355412); //Standard mersenne_twister_engine
  double bounds[6];
  polyData->GetBounds(bounds);
  std::cout << "Bounds: "
            << bounds[0] << ", " << bounds[1] << " "
            << bounds[2] << ", " << bounds[3] << " "
            << bounds[4] << ", " << bounds[5] << std::endl;
  // Generate random points within the bounding box of the polydata
  std::uniform_real_distribution<double> distributionX(bounds[0], bounds[1]);
  std::uniform_real_distribution<double> distributionY(bounds[2], bounds[3]);
  std::uniform_real_distribution<double> distributionZ(bounds[4], bounds[5]);
  vtkSmartPointer<vtkPolyData> pointsPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  pointsPolyData->SetPoints(points);

  points->SetNumberOfPoints(10000);
  for (auto i = 0; i < 10000; ++i)
    {
      double point[3];
      point[0] = distributionX(mt);
      point[1] = distributionY(mt);
      point[2] = distributionZ(mt);
      points->SetPoint(i, point);
    }

  vtkSmartPointer<vtkExtractEnclosedPoints> extract =
    vtkSmartPointer<vtkExtractEnclosedPoints>::New();
  extract->SetSurfaceData(polyData);
  extract->SetInputData(pointsPolyData);
  extract->SetTolerance(.0001);
  extract->CheckSurfaceOn();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkSphereSource> source = 
    vtkSmartPointer<vtkSphereSource>::New();
  source->SetRadius((bounds[1] - bounds[0]) * .005);

  vtkSmartPointer<vtkGlyph3DMapper> glyph3Dmapper = 
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  glyph3Dmapper->SetSourceConnection(source->GetOutputPort());
  glyph3Dmapper->SetInputConnection(extract->GetOutputPort());

  vtkSmartPointer<vtkActor> glyphActor =
    vtkSmartPointer<vtkActor>::New();
  glyphActor->SetMapper(glyph3Dmapper);
  glyphActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Crimson").GetData());
  glyphActor->GetProperty()->SetSpecular(.6);
  glyphActor->GetProperty()->SetSpecularPower(30);
;

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);

  vtkSmartPointer<vtkProperty> backProp =
    vtkSmartPointer<vtkProperty>::New();
  backProp->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
  backProp->SetSpecular(.6);
  backProp->SetSpecularPower(30);
;

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->SetBackfaceProperty(backProp);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Crimson").GetData());
  actor->GetProperty()->SetSpecular(.6);
  actor->GetProperty()->SetSpecularPower(30);
  actor->GetProperty()->SetOpacity(.3);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->AddActor(glyphActor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderer->UseHiddenLineRemovalOn();

  renderWindow->SetSize(640, 512);

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
