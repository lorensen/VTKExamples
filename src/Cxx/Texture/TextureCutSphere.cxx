//
// Cut an outer sphere to reveal an inner sphere.
//
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkImplicitTextureCoords.h>
#include <vtkNamedColors.h>
#include <vtkPlanes.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkStructuredPointsReader.h>
#include <vtkTexture.h>

int main(int /* argc */, char* argv[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Hidden sphere.
  vtkSmartPointer<vtkSphereSource> sphere1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere1->SetRadius(0.5);

  vtkSmartPointer<vtkPolyDataMapper> innerMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  innerMapper->SetInputConnection(sphere1->GetOutputPort());

  vtkSmartPointer<vtkActor> innerSphere = vtkSmartPointer<vtkActor>::New();
  innerSphere->SetMapper(innerMapper);
  innerSphere->GetProperty()->SetColor(
    colors->GetColor3d("BlanchedAlmond").GetData());

  // Sphere to texture.
  vtkSmartPointer<vtkSphereSource> sphere2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere2->SetRadius(1.0);
  sphere2->SetPhiResolution(21);
  sphere2->SetThetaResolution(21);

  vtkSmartPointer<vtkPlanes> planes = vtkSmartPointer<vtkPlanes>::New();

  double pts[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(2);
  points->SetPoint(0, pts);
  points->SetPoint(1, pts + 3);

  double nrms[6] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0};
  vtkSmartPointer<vtkDoubleArray> normals =
    vtkSmartPointer<vtkDoubleArray>::New();
  normals->SetNumberOfComponents(3);
  normals->SetNumberOfTuples(2);
  normals->SetTuple(0, nrms);
  normals->SetTuple(1, nrms + 3);

  planes->SetPoints(points);
  planes->SetNormals(normals);

  vtkSmartPointer<vtkImplicitTextureCoords> tcoords =
    vtkSmartPointer<vtkImplicitTextureCoords>::New();
  tcoords->SetInputConnection(sphere2->GetOutputPort());
  tcoords->SetRFunction(planes);

  vtkSmartPointer<vtkDataSetMapper> outerMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  outerMapper->SetInputConnection(tcoords->GetOutputPort());

  vtkSmartPointer<vtkStructuredPointsReader> tmap =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  tmap->SetFileName(argv[1]);

  vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(tmap->GetOutputPort());
  texture->InterpolateOff();
  texture->RepeatOff();

  vtkSmartPointer<vtkActor> outerSphere = vtkSmartPointer<vtkActor>::New();
  outerSphere->SetMapper(outerMapper);
  outerSphere->SetTexture(texture);
  outerSphere->GetProperty()->SetColor(
    colors->GetColor3d("LightSalmon").GetData());

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkRenderer> aren = vtkSmartPointer<vtkRenderer>::New();
  iren->SetRenderWindow(renWin);
  renWin->AddRenderer(aren);

  aren->AddActor(innerSphere);
  aren->AddActor(outerSphere);
  aren->SetBackground(colors->GetColor3d("SlateGray").GetData());
  aren->GetActiveCamera()->Azimuth(-20);
  aren->GetActiveCamera()->Elevation(-10);
  aren->ResetCamera();

  renWin->SetSize(500, 500);

  // Interact with the data.
  renWin->Render();

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
