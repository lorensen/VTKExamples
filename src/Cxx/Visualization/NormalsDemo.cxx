#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCleanPolyData.h>
#include <vtkColor.h>
#include <vtkImplicitBoolean.h>
#include <vtkNamedColors.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSTLReader.h>
#include <vtksys/SystemTools.hxx>
#include <vtkXMLPolyDataReader.h>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData =
    ReadPolyData(argc > 1 ? argv[1] : "");

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("White").GetData());

  // Create background colors for each viewport
  std::vector<vtkColor3d> backgroundColors;
  backgroundColors.push_back(colors->GetColor3d("Cornsilk"));
  backgroundColors.push_back(colors->GetColor3d("NavajoWhite"));
  backgroundColors.push_back(colors->GetColor3d("Tan"));

  // Create a renderer for each view port
  std::vector<vtkSmartPointer<vtkRenderer> > ren;
  ren.push_back(vtkSmartPointer<vtkRenderer>::New());
  ren.push_back(vtkSmartPointer<vtkRenderer>::New());
  ren.push_back(vtkSmartPointer<vtkRenderer>::New());
  ren[0]->SetViewport(0, 0, 1.0 / 3.0, 1);  // Input
  ren[1]->SetViewport(1.0 / 3.0, 0, 2.0 / 3.0, 1);  // Normals (no split)
  ren[2]->SetViewport(2.0 / 3.0, 0, 1, 1);  // Normals (split)

  // Shared camera
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputData(polyData);
  normals->SetFeatureAngle(30.0);
  for (int i = 0; i < 3; ++i)
  {
    if (i == 0)
    {
      normals->ComputePointNormalsOff();
    }
    else if (i == 1)
    {
      normals->ComputePointNormalsOn();
      normals->SplittingOff();
    }
    else
    {
      normals->ComputePointNormalsOn();
      normals->SplittingOn();
    }

    normals->Update();

    vtkSmartPointer<vtkPolyData> normalsPolyData =
      vtkSmartPointer<vtkPolyData>::New();
    normalsPolyData->DeepCopy(normals->GetOutput());

    // mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(normalsPolyData);
    mapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> actor = 
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->
      SetDiffuseColor(colors->GetColor3d("Peacock").GetData());
    actor->GetProperty()->
      SetDiffuse(.7);
    actor->GetProperty()->
      SetSpecularPower(20);
    actor->GetProperty()->
      SetSpecular(.5);

    // add the actor
    ren[i]->SetBackground(backgroundColors[i].GetData());
    ren[i]->SetActiveCamera(camera);
    ren[i]->AddActor(actor);
  }

  // render window
  vtkSmartPointer<vtkRenderWindow> renwin = 
    vtkSmartPointer<vtkRenderWindow>::New();
    renwin->AddRenderer(ren[0]);
    renwin->AddRenderer(ren[1]);
    renwin->AddRenderer(ren[2]);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renwin);

  renwin->SetSize(900, 300);
  ren[0]->GetActiveCamera()->SetFocalPoint(0,0,0);
  ren[0]->GetActiveCamera()->SetPosition(1,0,0);
  ren[0]->GetActiveCamera()->SetViewUp(0,0,-1);
  ren[0]->ResetCamera();

  ren[0]->GetActiveCamera()->Azimuth(120);
  ren[0]->GetActiveCamera()->Elevation(30);
  ren[0]->GetActiveCamera()->Dolly(1.1);
  ren[0]->ResetCameraClippingRange();

  renwin->Render();
  ren[0]->ResetCamera();
  renwin->Render();

  // Start
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
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
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
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
    vtkSmartPointer<vtkSphereSource> sphere =
      vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetPhiResolution(11);
    sphere->SetThetaResolution(11);

    sphere->Update();
    polyData = sphere->GetOutput();
  }
  vtkSmartPointer<vtkCleanPolyData> clean =
    vtkSmartPointer<vtkCleanPolyData>::New();
  clean->SetInputData(polyData);
  clean->Update();
  return clean->GetOutput();
}
}
