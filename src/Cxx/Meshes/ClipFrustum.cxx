#include <vtkSmartPointer.h>

#include <vtkFrustumSource.h>
#include <vtkClipPolyData.h>

#include <vtkPlanes.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataNormals.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtksys/SystemTools.hxx>

#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>

#include <vtkCamera.h>
namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
void PositionCamera(vtkSmartPointer<vtkRenderer> &renderer,
                    double *viewUp,
                    double *position);
}

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Crimson").GetData());
  actor->GetProperty()->SetSpecular(.6);
  actor->GetProperty()->SetSpecularPower(30);
  renderer->AddActor(actor);

  vtkSmartPointer<vtkPolyDataMapper> outMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outMapper->SetInputData(polyData);
  outMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> outActor =
    vtkSmartPointer<vtkActor>::New();
  outActor->SetMapper(outMapper);
  outActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Gold").GetData());
  outActor->GetProperty()->SetSpecular(.6);
  outActor->GetProperty()->SetSpecularPower(30);

  // Position the camera so that we can see the frustum
  double viewUp[3] = {0.0,1.0,0.0};
  double position[3] = {1.0,0.0,0.0};
  PositionCamera(renderer, viewUp, position);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->SetViewAngle(10.0);

  double planesArray[24];
  renderer->GetActiveCamera()->GetFrustumPlanes(1.0, planesArray);

  vtkSmartPointer<vtkPlanes> planes =
    vtkSmartPointer<vtkPlanes>::New();
  planes->SetFrustumPlanes(planesArray);

  vtkSmartPointer<vtkFrustumSource> frustumSource =
    vtkSmartPointer<vtkFrustumSource>::New();
  frustumSource->ShowLinesOff();
  frustumSource->SetPlanes(planes);
  frustumSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> frustumMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  frustumMapper->SetInputConnection(frustumSource->GetOutputPort());

  vtkSmartPointer<vtkActor> frustumActor =
    vtkSmartPointer<vtkActor>::New();
  frustumActor->SetMapper(frustumMapper);
  frustumActor->GetProperty()->EdgeVisibilityOn();
  frustumActor->GetProperty()->SetOpacity(.5);
  frustumActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());

  vtkSmartPointer<vtkClipPolyData> clip =
    vtkSmartPointer<vtkClipPolyData>::New();
  clip->SetInputData(polyData);
  clip->SetClipFunction(planes);
  clip->InsideOutOn();
  clip->GenerateClippedOutputOn();
  clip->Update();

  mapper->SetInputConnection(clip->GetOutputPort());
  outMapper->SetInputData(clip->GetClippedOutput());

  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderer->AddActor(frustumActor);
  renderer->AddActor(outActor);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.5);
  renderer->ResetCameraClippingRange();
  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  // begin mouse interaction
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}

// Snippets
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

void PositionCamera(vtkSmartPointer<vtkRenderer> &renderer,
                    double *viewUp,
                    double *position)
{
  renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
  renderer->GetActiveCamera()->SetViewUp(viewUp);
  renderer->GetActiveCamera()->SetPosition(position);
  renderer->ResetCamera();
  return;
}
}
