#include <vtkSmartPointer.h>
#include <vtkSampleFunction.h>
#include <vtkSphere.h>
#include <vtkCylinder.h>
#include <vtkMarchingCubes.h>
#include <vtkProbeFilter.h>

#include <vtkImageData.h>
#include <vtkPointData.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkUnsignedCharArray.h>

int main(int argc, char *argv[])
{
  int resolution = 50;
  if (argc > 1)
  {
    resolution = atoi(argv[1]);
  }

  // Create a sampled sphere
  vtkSmartPointer<vtkSphere> implicitSphere =
    vtkSmartPointer<vtkSphere>::New();
  double radius = 1.0;
  implicitSphere->SetRadius(radius);

  vtkSmartPointer<vtkSampleFunction> sampledSphere =
    vtkSmartPointer<vtkSampleFunction>::New();
  sampledSphere->SetSampleDimensions(resolution, resolution, resolution);
  double xMin = -radius * 2.0;
  double xMax =  radius * 2.0;
  sampledSphere->SetModelBounds(xMin, xMax,
                                xMin, xMax,
                                xMin, xMax);
  sampledSphere->SetImplicitFunction(implicitSphere);

  vtkSmartPointer<vtkMarchingCubes> isoSphere =
    vtkSmartPointer<vtkMarchingCubes>:: New();
  isoSphere->SetValue(0,1.0);
  isoSphere->SetInputConnection(sampledSphere->GetOutputPort());

  // Create a sampled cylinder
  vtkSmartPointer<vtkCylinder> implicitCylinder =
    vtkSmartPointer<vtkCylinder>::New();
  implicitCylinder->SetRadius(radius/2.0);
  vtkSmartPointer<vtkSampleFunction> sampledCylinder =
    vtkSmartPointer<vtkSampleFunction>::New();
  sampledCylinder->SetSampleDimensions(resolution, resolution, resolution);
  sampledCylinder->SetModelBounds(xMin, xMax,
                                  xMin, xMax,
                                  xMin, xMax);
  sampledCylinder->SetImplicitFunction(implicitCylinder);

  // Probe cylinder with the sphere isosurface
  vtkSmartPointer<vtkProbeFilter> probeCylinder =
    vtkSmartPointer<vtkProbeFilter>::New();
  probeCylinder->SetInputConnection(0, isoSphere->GetOutputPort());
  probeCylinder->SetInputConnection(1, sampledCylinder->GetOutputPort());
  probeCylinder->Update();

  // Restore the original normals
  probeCylinder->GetOutput()->GetPointData()->SetNormals(
    isoSphere->GetOutput()->GetPointData()->GetNormals());

  std::cout << "Scalar range: "
            << probeCylinder->GetOutput()->GetScalarRange()[0] << ", "
            << probeCylinder->GetOutput()->GetScalarRange()[1] << std::endl;

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapSphere =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapSphere->SetInputConnection(probeCylinder->GetOutputPort());
  mapSphere->SetScalarRange(probeCylinder->GetOutput()->GetScalarRange());

  vtkSmartPointer<vtkActor> sphere =
    vtkSmartPointer<vtkActor>::New();
  sphere->SetMapper(mapSphere);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(sphere);
  renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
