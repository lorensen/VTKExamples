#include <vtkActor.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkWarpScalar.h>
#include <vtkMath.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Create Scalars
  vtkSmartPointer<vtkDoubleArray> scalars =
    vtkSmartPointer<vtkDoubleArray>::New();
  int numberOfPoints = sphereSource->GetOutput()->GetNumberOfPoints();
  scalars->SetNumberOfTuples(numberOfPoints);

  vtkMath::RandomSeed(8775070); // for reproducibility
  for(vtkIdType i = 0; i < numberOfPoints; ++i)
  {
    scalars->SetTuple1(i, vtkMath::Random(0.0, 1.0 / 7.0));
  }

  sphereSource->GetOutput()->GetPointData()->SetScalars(scalars);

  vtkSmartPointer<vtkWarpScalar> warpScalar =
    vtkSmartPointer<vtkWarpScalar>::New();
  warpScalar->SetInputConnection(sphereSource->GetOutputPort());
  warpScalar->SetScaleFactor(1); // use the scalars themselves

  // Required for SetNormal to have an effect
  warpScalar->UseNormalOn();
  warpScalar->SetNormal(0, 0, 1);

  warpScalar->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(warpScalar->GetOutputPort());

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
  renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
