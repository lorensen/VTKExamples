#include <vtkSmartPointer.h>
#include <vtkShepardMethod.h>
#include <vtkContourFilter.h>
#include <vtkProbeFilter.h>
#include <vtkSphereSource.h>

#include <vtkNamedColors.h>
#include <vtkImageData.h>
#include <vtkPointData.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtksys/SystemTools.hxx>

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyData> polyData =
    ReadPolyData(argc > 1 ? argv[1] : "");

  unsigned int resolution = 100;
  if (argc >= 3)
  {
    resolution = std::atoi(argv[2]);
  }
  vtkSmartPointer<vtkShepardMethod> interpolator =
    vtkSmartPointer<vtkShepardMethod>::New();
  interpolator->SetInputData(polyData);
  interpolator->SetModelBounds(polyData->GetBounds());
  interpolator->SetSampleDimensions(resolution, resolution, resolution);
  interpolator->SetNullValue(-10000);
  interpolator->Update();
  std::cout << "Scalar Range: "
            << interpolator->GetOutput()->GetScalarRange()[0] << ", "
            << interpolator->GetOutput()->GetScalarRange()[1]
            << std::endl;
    
  vtkSmartPointer<vtkProbeFilter> probe =
    vtkSmartPointer<vtkProbeFilter>::New();
  probe->SetInputData(0, polyData);
  probe->SetInputConnection(1, interpolator->GetOutputPort());

  vtkSmartPointer<vtkContourFilter> interpolatedContour =
    vtkSmartPointer<vtkContourFilter>::New();
  interpolatedContour->SetInputConnection(probe->GetOutputPort());
  interpolatedContour->SetValue(0, 0.0);

  vtkSmartPointer<vtkContourFilter> originalContour =
    vtkSmartPointer<vtkContourFilter>::New();
  originalContour->SetInputData(polyData);
  originalContour->SetValue(0, 0.0);

  vtkSmartPointer<vtkPolyDataMapper> interpolatedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  interpolatedMapper->SetInputConnection(interpolatedContour->GetOutputPort());
  interpolatedMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> interpolatedActor =
    vtkSmartPointer<vtkActor>::New();
  interpolatedActor->SetMapper(interpolatedMapper);
  interpolatedActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  interpolatedActor->GetProperty()->SetLineWidth(4.0);

  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(originalContour->GetOutputPort());
  originalMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  originalActor->GetProperty()->SetLineWidth(4.0);
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(interpolatedActor);
  renderer->AddActor(originalActor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(120);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.5);
  renderer->ResetCameraClippingRange();

  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindowInteractor->Start();

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
