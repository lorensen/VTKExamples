#include <vtkSmartPointer.h>

#include <vtkProjectedTexture.h>
#include <vtkCamera.h>
#include <vtkFrustumSource.h>
#include <vtkPlanes.h>
#include <vtkMath.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkTexture.h>
#include <vtkPointData.h>
#include <vtkImageData.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>

#include <vtkNamedColors.h>

#include <vtksys/SystemTools.hxx>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " polydata texture" << std::endl;
    return EXIT_FAILURE;
  }
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;

  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> textureFile;
  textureFile.TakeReference(
    readerFactory->CreateImageReader2(argv[2]));
  textureFile->SetFileName(argv[2]);
  textureFile->Update();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  double center[3];
  polyData->GetCenter(center);
  std::cout << "Center: "
            << center[0] << ", "
            << center[1] << ", "
            << center[2] << std::endl;
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition(center[0], center[1] + .0375, center[2] +.5);
  camera->SetFocalPoint(center[0], center[1] + .0375, center[2]);
  camera->Azimuth(-45);
  camera->Roll(-90);
  camera->SetClippingRange(.5, .6);
  double planesArray[24];
  
  camera->GetFrustumPlanes(1.0, planesArray);

  //Settings for vtkProjectedTexture

  double aspect[3];
  aspect[1] = 1.0;
  aspect[2] = 1.0;
  aspect[0] = 1.0;
//(1.0/ (vtkMath::RadiansFromDegrees(std::tan(camera->GetViewAngle())))) / 2.0;
  std::cout << "Aspect: "
            << aspect[0] << ", "
            << aspect[1] << ", "
            << aspect[2] << std::endl;

  vtkSmartPointer<vtkProjectedTexture>  projectedTexture =
    vtkSmartPointer<vtkProjectedTexture>::New();

  projectedTexture->SetAspectRatio(aspect);
  projectedTexture->SetPosition(camera->GetPosition());
  projectedTexture->SetFocalPoint(camera->GetFocalPoint());
  projectedTexture->SetUp(
    camera->GetViewUp()[0],
    camera->GetViewUp()[1],
    camera->GetViewUp()[2]);

  projectedTexture->SetInputData( polyData); //this can be the same as the one to project on
  projectedTexture->Update();

  //Map Texture on Surface
  polyData->GetPointData()->SetTCoords(
    projectedTexture->GetOutput()->GetPointData()->GetTCoords());

  vtkSmartPointer<vtkTexture> texture =
    vtkSmartPointer<vtkTexture>::New();
  texture->SetInputData(textureFile->GetOutput());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->SetTexture(texture);

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
  frustumActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  frustumActor->GetProperty()->SetOpacity(.5);
  frustumActor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->AddActor(frustumActor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renderer->SetActiveCamera(camera);
  camera->Azimuth(180);
  camera->Roll(-90);
  renderer->ResetCameraClippingRange();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renWinInteractor->Start();

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
