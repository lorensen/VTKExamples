#include <vtkSmartPointer.h>

#include <vtkProjectSphereFilter.h>
#include <vtkElevationFilter.h>

#include <vtkParametricSuperEllipsoid.h>
#include <vtkParametricFunctionSource.h>

#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>

int main (int, char *[])
{

  vtkSmartPointer<vtkParametricSuperEllipsoid> surface =
    vtkSmartPointer<vtkParametricSuperEllipsoid>::New();
  surface->SetN1(2.0);
  surface->SetN2(0.5);

  vtkSmartPointer<vtkParametricFunctionSource> source =
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  source->SetParametricFunction(surface);

  vtkSmartPointer<vtkElevationFilter> elevationFilter =
    vtkSmartPointer<vtkElevationFilter>::New();
  elevationFilter->SetInputConnection(source->GetOutputPort());
  elevationFilter->SetLowPoint(0.0, 0.0, -4.0);
  elevationFilter->SetHighPoint(0.0, 0.0, 4.0);
  elevationFilter->Update();

  // Deep copy the point data since in some versions of VTK,
  // the ProjectSphereFilter modifies the input point data 
 vtkSmartPointer<vtkPolyData> pd1 =
    vtkSmartPointer<vtkPolyData>::New();
  pd1->DeepCopy(elevationFilter->GetOutput());

  vtkSmartPointer<vtkProjectSphereFilter> sphereProject1 =
    vtkSmartPointer<vtkProjectSphereFilter>::New();
  sphereProject1->SetInputConnection(elevationFilter->GetOutputPort());
  sphereProject1->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper1->SetInputConnection(sphereProject1->GetOutputPort());
  mapper1->SetScalarRange(sphereProject1->GetOutput()->GetPointData()->GetScalars()->GetRange());
  vtkSmartPointer<vtkActor> actor1 =
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(mapper1);

  vtkSmartPointer<vtkPolyDataMapper> mapper2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper2->SetInputData(pd1);
  mapper2->SetScalarRange(pd1->GetPointData()->GetScalars()->GetRange());  
  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);

  // A render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  leftRenderer->AddActor(actor2);
  rightRenderer->AddActor(actor1);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  leftRenderer->GetActiveCamera()->Azimuth(30);
  leftRenderer->GetActiveCamera()->Elevation(-30);
  leftRenderer->ResetCamera();

  // Render an image (lights and cameras are created automatically)
  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
