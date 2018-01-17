#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkConeSource.h>
#include <vtkContourFilter.h>
#include <vtkDoubleArray.h>
#include <vtkGaussianSplatter.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main( int, char *[] )
{
  double x[3], n[3];

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> aren =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(aren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Create single splat point
  vtkSmartPointer<vtkPoints> pts =
    vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> verts =
    vtkSmartPointer<vtkCellArray>::New();
  vtkSmartPointer<vtkDoubleArray> norms =
    vtkSmartPointer<vtkDoubleArray>::New();
  vtkSmartPointer<vtkDoubleArray> scalars =
    vtkSmartPointer<vtkDoubleArray>::New();

  x[0] = x[1] = x[2] = 0.0;
  pts->InsertNextPoint(x);
  norms->SetNumberOfTuples(1);
  norms->SetNumberOfComponents(3);
  n[0] = 0.707; n[1] = 0.707; n[2] = 0.0;
  norms->InsertTuple(0, n);
  scalars->SetNumberOfTuples(1);
  scalars->SetNumberOfComponents(1);
  scalars->InsertTuple1(0, 1.0);

  verts->InsertNextCell(1);
  verts->InsertCellPoint(0);

  vtkSmartPointer<vtkPolyData> pData =
    vtkSmartPointer<vtkPolyData>::New();
  pData->SetPoints(pts);
  pData->SetVerts(verts);
  pData->GetPointData()->SetNormals(norms);
  pData->GetPointData()->SetScalars(scalars);

  // Splat point and generate isosurface
  vtkSmartPointer<vtkGaussianSplatter> splat =
    vtkSmartPointer<vtkGaussianSplatter>::New();
  splat->SetInputData(pData);
  splat->SetModelBounds(-1.0,1.0, -1.0,1.0, -1.0,1.0);
  splat->SetSampleDimensions(75,75,75);
  splat->SetRadius(0.5);
  splat->SetEccentricity(5.0);
  splat->SetExponentFactor(-3.25);
  vtkSmartPointer<vtkContourFilter> contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetInputConnection(splat->GetOutputPort());
  contour->SetValue(0, 0.9);
  vtkSmartPointer<vtkPolyDataMapper> splatMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  splatMapper->SetInputConnection(contour->GetOutputPort());
  vtkSmartPointer<vtkActor> splatActor =
    vtkSmartPointer<vtkActor>::New();
  splatActor->SetMapper(splatMapper);

  // Create outline
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(splat->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Brown").GetData());

  // Create cone to indicate direction
  vtkSmartPointer<vtkConeSource> cone =
    vtkSmartPointer<vtkConeSource>::New();
  cone->SetResolution(24);
  vtkSmartPointer<vtkPolyDataMapper> coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(cone->GetOutputPort());
  vtkSmartPointer<vtkActor> coneActor =
    vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);
  coneActor->SetScale(0.75,0.75,0.75);
  coneActor->RotateZ(45.0);
  coneActor->AddPosition(0.50,0.50,0.0);
  coneActor->GetProperty()->SetColor(colors->GetColor3d("DeepPink").GetData());
//
// Rendering stuff
//
  aren->SetBackground(colors->GetColor3d("Beige").GetData());
  aren->AddActor(splatActor);
  aren->AddActor(outlineActor);
  aren->AddActor(coneActor);

  renWin->SetSize(640, 480);
  renWin->Render();

  // interact with data
  iren->Start();

  return EXIT_SUCCESS;
}
