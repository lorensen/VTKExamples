
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkAxes.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>
#include <vtksys/SystemTools.hxx>

#include <vtkNamedColors.h>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
void  RotateX (vtkSmartPointer<vtkRenderWindow> &renWin,
               vtkSmartPointer<vtkActor> &actor);
void  RotateY (vtkSmartPointer<vtkRenderWindow> &renWin,
               vtkSmartPointer<vtkActor> &actor);
void  RotateZ (vtkSmartPointer<vtkRenderWindow> &renWin,
               vtkSmartPointer<vtkActor> &actor);
void  RotateXY (vtkSmartPointer<vtkRenderWindow> &renWin,
                vtkSmartPointer<vtkActor> &actor);
}
int main (int argc, char *argv[])
{
// Create renderer stuff
//
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

// create pipeline
//
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;

  vtkSmartPointer<vtkPolyDataMapper> modelMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  modelMapper->SetInputData(polyData);
  
  vtkSmartPointer<vtkActor> modelActor =
    vtkSmartPointer<vtkActor>::New();
  modelActor->SetMapper(modelMapper);
  modelActor->GetProperty()->SetDiffuseColor(0.9608, 0.8706, 0.7020);
  modelActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Crimson").GetData());
  modelActor->GetProperty()->SetSpecular(.6);
  modelActor->GetProperty()->SetSpecularPower(30);

  vtkSmartPointer<vtkAxes> modelAxesSource =
    vtkSmartPointer<vtkAxes>::New();
  modelAxesSource->SetScaleFactor(10);
  modelAxesSource->SetOrigin(0, 0, 0);

  vtkSmartPointer<vtkPolyDataMapper> modelAxesMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  modelAxesMapper->SetInputConnection(modelAxesSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> modelAxes =
    vtkSmartPointer<vtkActor>::New();
  modelAxes->SetMapper(modelAxesMapper);

  ren1->AddActor(modelAxes);
  modelAxes->VisibilityOff();

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(modelActor);
  ren1->SetBackground(colors->GetColor3d("Silver").GetData());
  renWin->SetSize(640, 480);
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(0);
  ren1->GetActiveCamera()->SetClippingRange(.1, 1000.0);

  modelAxes->VisibilityOn();

  renWin->Render();
  renWin->Render();

  iren->Start();
  RotateX(renWin, modelActor);
  iren->Start();
  RotateY(renWin, modelActor);
  iren->Start();
  RotateZ(renWin, modelActor);
  iren->Start();
  RotateXY(renWin, modelActor);

  renWin->EraseOff();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace
{
//
void  RotateX (vtkSmartPointer<vtkRenderWindow> &renWin,
               vtkSmartPointer<vtkActor> &actor)
{
  actor->SetOrientation(0, 0, 0);
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();

  for (int i = 0; i < 6; ++i)
  {
    actor->RotateX(60);
    renWin->Render();
    renWin->Render();
  }
  renWin->EraseOn();
}
void  RotateY (vtkSmartPointer<vtkRenderWindow> &renWin,
               vtkSmartPointer<vtkActor> &actor)
{
  actor->SetOrientation(0, 0, 0);
  renWin->Render();
  renWin->EraseOff();

  for (int i = 0; i < 6; ++i)
  {
    actor->RotateY(60);
    renWin->Render();
    renWin->Render();
  }
  renWin->EraseOn();
}
void  RotateZ (vtkSmartPointer<vtkRenderWindow> &renWin,
               vtkSmartPointer<vtkActor> &actor)
{
  actor->SetOrientation(0, 0, 0);
  renWin->Render();
  renWin->EraseOff();

  for (int i = 0; i < 6; ++i)
  {
    actor->RotateZ(60);
    renWin->Render();
    renWin->Render();
  }
  renWin->EraseOn();
}
void  RotateXY (vtkSmartPointer<vtkRenderWindow> &renWin,
               vtkSmartPointer<vtkActor> &actor)
{
  actor->SetOrientation(0, 0, 0);
  actor->RotateX(60);
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();

  for (int i = 0; i < 6; ++i)
  {
    actor->RotateY(60);
    renWin->Render();
    renWin->Render();
  }
  renWin->EraseOn();
}
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
