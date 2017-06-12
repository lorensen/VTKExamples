#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkParametricFunctionSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

// Select one of the following:
#include <vtkParametricTorus.h>
//#include <vtkParametricBoy.h>
//#include <vtkParametricConicSpiral.h>
//#include <vtkParametricCrossCap.h>
//#include <vtkParametricDini.h>
//#include <vtkParametricEllipsoid.h>
//#include <vtkParametricEnneper.h>
//#include <vtkParametricFigure8Klein.h>
//#include <vtkParametricKlein.h>
//#include <vtkParametricMobius.h>
//#include <vtkParametricRandomHills.h>
//#include <vtkParametricRoman.h>
//#include <vtkParametricSpline.h>
//#include <vtkParametricSuperEllipsoid.h>
//#include <vtkParametricSuperToroid.h>
//#include <vtkParametricTorus.h>

int main(int, char* [])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Select one of the following (matching the selection above)
  vtkSmartPointer<vtkParametricTorus> parametricObject =
    vtkSmartPointer<vtkParametricTorus>::New();
  // vtkSmartPointer<vtkParametricBoy> parametricObject =
  // vtkSmartPointer<vtkParametricBoy>::New();
  // vtkSmartPointer<vtkParametricConicSpiral> parametricObject =
  // vtkSmartPointer<vtkParametricConicSpiral>::New();
  // vtkSmartPointer<vtkParametricCrossCap> parametricObject =
  // vtkSmartPointer<vtkParametricCrossCap>::New();
  // vtkSmartPointer<vtkParametricDini> parametricObject =
  // vtkSmartPointer<vtkParametricDini>::New();
  // vtkSmartPointer<vtkParametricEllipsoid> parametricObject =
  // vtkSmartPointer<vtkParametricEllipsoid>::New();
  // vtkSmartPointer<vtkParametricEnneper> parametricObject =
  // vtkSmartPointer<vtkParametricEnneper>::New();
  // vtkSmartPointer<vtkParametricFigure8Klein> parametricObject =
  // vtkSmartPointer<vtkParametricFigure8Klein>::New();
  // vtkSmartPointer<vtkParametricKlein> parametricObject =
  // vtkSmartPointer<vtkParametricKlein>::New();
  // vtkSmartPointer<vtkParametricMobius> parametricObject =
  // vtkSmartPointer<vtkParametricMobius>::New();
  // vtkSmartPointer<vtkParametricRandomHills> parametricObject =
  // vtkSmartPointer<vtkParametricRandomHills>::New();
  // vtkSmartPointer<vtkParametricRoman> parametricObject =
  // vtkSmartPointer<vtkParametricRoman>::New();
  // vtkSmartPointer<vtkParametricSpline> parametricObject =
  // vtkSmartPointer<vtkParametricSpline>::New();
  // vtkSmartPointer<vtkParametricSuperEllipsoid> parametricObject =
  // vtkSmartPointer<vtkParametricSuperEllipsoid>::New();
  // vtkSmartPointer<vtkParametricSuperToroid> parametricObject =
  // vtkSmartPointer<vtkParametricSuperToroid>::New();
  // vtkSmartPointer<vtkParametricTorus> parametricObject =
  // vtkSmartPointer<vtkParametricTorus>::New();

  vtkSmartPointer<vtkParametricFunctionSource> parametricFunctionSource =
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  parametricFunctionSource->SetParametricFunction(parametricObject);
  parametricFunctionSource->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(parametricFunctionSource->GetOutputPort());

  // Create an actor for the contours
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(
    namedColors->GetColor3d("Burlywood").GetData());
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(namedColors->GetColor3d("Beige").GetData());

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
