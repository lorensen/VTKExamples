#include <vtkSmartPointer.h>
#include <vtkSampleFunction.h>
#include <vtkSphereSource.h>
#include <vtkCone.h>
#include <vtkGlyph3D.h>
#include <vtkProbeFilter.h>
#include <vtkPointSource.h>
#include <vtkThreshold.h>
#include <vtkThresholdPoints.h>
#include <vtkImageData.h>
#include <vtkPointData.h>

#include <vtkDataSetMapper.h>
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

  // Create a sampled cone
  vtkSmartPointer<vtkCone> implicitCone =
    vtkSmartPointer<vtkCone>::New();
  implicitCone->SetAngle(30.0);

  double radius = 1.0;
  vtkSmartPointer<vtkSampleFunction> sampledCone =
    vtkSmartPointer<vtkSampleFunction>::New();
  sampledCone->SetSampleDimensions(resolution, resolution, resolution);
  double xMin = -radius * 2.0;
  double xMax =  radius * 2.0;
  sampledCone->SetModelBounds(xMin, xMax,
                              xMin, xMax,
                              xMin, xMax);
  sampledCone->SetImplicitFunction(implicitCone);

  vtkSmartPointer<vtkThreshold> thresholdCone =
    vtkSmartPointer<vtkThreshold>:: New();
  thresholdCone->SetInputConnection(sampledCone->GetOutputPort());
  thresholdCone->ThresholdByLower(0);

  vtkSmartPointer<vtkPointSource> randomPoints =
    vtkSmartPointer<vtkPointSource>::New();
  randomPoints->SetCenter (0.0, 0.0, 0.0);
  randomPoints->SetNumberOfPoints(10000);
  randomPoints->SetDistributionToUniform();
  randomPoints->SetRadius(xMax);

  // Probe the cone dataset with random points
  vtkSmartPointer<vtkProbeFilter> randomProbe =
    vtkSmartPointer<vtkProbeFilter>::New();
  randomProbe->SetInputConnection(0, randomPoints->GetOutputPort());
  randomProbe->SetInputConnection(1, thresholdCone->GetOutputPort());
  randomProbe->Update();
  randomProbe->GetOutput()->GetPointData()->SetActiveScalars("vtkValidPointMask");

  vtkSmartPointer<vtkThresholdPoints> selectPoints =
    vtkSmartPointer<vtkThresholdPoints>::New();
  selectPoints->SetInputConnection(randomProbe->GetOutputPort());
  selectPoints->ThresholdByUpper(1.0);

  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetRadius(.05);

  vtkSmartPointer<vtkGlyph3D> glyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph->SetSourceConnection(sphere->GetOutputPort());
  glyph->SetInputConnection(selectPoints->GetOutputPort());

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(glyph->GetOutputPort());
  mapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.1, .5, .8);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
