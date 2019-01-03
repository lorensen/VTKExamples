#include <vtkSmartPointer.h>
#include <vtkImplicitBoolean.h>
#include <vtkNamedColors.h>
#include <vtkColorSeries.h>

#include <vtkSphere.h>
#include <vtkBox.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>

#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main (int /* argc */, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // create a sphere
  vtkSmartPointer<vtkSphere> sphere =
    vtkSmartPointer<vtkSphere>::New();
  sphere->SetRadius(1);
  sphere->SetCenter(1,0,0);

  // create a box
  vtkSmartPointer<vtkBox> box =
    vtkSmartPointer<vtkBox>::New();
  box->SetBounds(-1, 1, -1, 1, -1, 1);

  // combine the two implicit functions
  vtkSmartPointer<vtkImplicitBoolean> boolean =
    vtkSmartPointer<vtkImplicitBoolean>::New();
  boolean->AddFunction(box);
  boolean->AddFunction(sphere);

  std::vector<vtkSmartPointer<vtkRenderer> > ren;
  ren.push_back(vtkSmartPointer<vtkRenderer>::New());
  ren.push_back(vtkSmartPointer<vtkRenderer>::New());
  ren.push_back(vtkSmartPointer<vtkRenderer>::New());
  ren[0]->SetViewport(0, 0, 1.0 / 3.0, 1);  // Difference
  ren[1]->SetViewport(1.0 / 3.0, 0, 2.0 / 3.0, 1);  // Union
  ren[2]->SetViewport(2.0 / 3.0, 0, 1, 1);  // Intersection

  // Shared camera
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  camera->Azimuth(30.0);
  camera->Elevation(30.0);

  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_DIVERGING_SPECTRAL_3);

  for (int i = 0; i < 3; ++i)
  {
    if (i == 0)
    {
      boolean->SetOperationTypeToDifference();
    }
    else if (i == 1)
    {
      boolean->SetOperationTypeToUnion();
    }
    else
    {
      boolean->SetOperationTypeToIntersection();
    }

    // The sample function generates a distance function from the implicit
    // function. This is then contoured to get a polygonal surface.
    vtkSmartPointer<vtkSampleFunction> sample =
      vtkSmartPointer<vtkSampleFunction>::New();
    sample->SetImplicitFunction(boolean);
    sample->SetModelBounds(-1, 2, -1, 1, -1, 1);
    sample->SetSampleDimensions(100, 100, 100);
    sample->ComputeNormalsOff();

    // contour
    vtkSmartPointer<vtkContourFilter> surface =
      vtkSmartPointer<vtkContourFilter>::New();
    surface->SetInputConnection(sample->GetOutputPort());
    surface->SetValue(0, 0.0);
    surface->Update();

    vtkSmartPointer<vtkPolyData> polyData =
      vtkSmartPointer<vtkPolyData>::New();
    polyData->DeepCopy(surface->GetOutput());

    // mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
                       mapper->SetInputData(polyData);
    mapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
//    actor->GetProperty()->EdgeVisibilityOn();
    actor->GetProperty()->SetColor(colors->GetColor3d("peacock").GetData());

    // add the actor
    ren[i]->SetBackground(colorSeries->GetColor(i).GetRed() / 255.0,
                          colorSeries->GetColor(i).GetGreen() / 255.0,
                          colorSeries->GetColor(i).GetBlue() / 255.0);
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
  renwin->Render();
  ren[1]->ResetCamera();
  renwin->Render();

  // Start
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
