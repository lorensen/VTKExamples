#include <vtkSmartPointer.h>
#include <vtkKochanekSpline.h>
#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>

#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkGlyph3DMapper.h>
#include <vtkSphereSource.h>
#include <vtkNamedColors.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  int numberOfPoints = 10;
  vtkSmartPointer<vtkPointSource> pointSource = 
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(numberOfPoints);
  pointSource->Update();
  
  vtkPoints* points = pointSource->GetOutput()->GetPoints();
    
  vtkSmartPointer<vtkKochanekSpline> xSpline = 
    vtkSmartPointer<vtkKochanekSpline>::New();
  vtkSmartPointer<vtkKochanekSpline> ySpline = 
    vtkSmartPointer<vtkKochanekSpline>::New();
  vtkSmartPointer<vtkKochanekSpline> zSpline = 
    vtkSmartPointer<vtkKochanekSpline>::New();

  vtkSmartPointer<vtkParametricSpline> spline = 
    vtkSmartPointer<vtkParametricSpline>::New();
  spline->SetXSpline(xSpline);
  spline->SetYSpline(ySpline);
  spline->SetZSpline(zSpline);
  spline->SetPoints(points);
  
  vtkSmartPointer<vtkParametricFunctionSource> functionSource = 
      vtkSmartPointer<vtkParametricFunctionSource>::New();
  functionSource->SetParametricFunction(spline);
  functionSource->SetUResolution(50 * numberOfPoints);
  functionSource->SetVResolution(50 * numberOfPoints);
  functionSource->SetWResolution(50 * numberOfPoints);
  functionSource->Update();

  // Setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(functionSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("DarkSlateGrey").GetData());
  actor->GetProperty()->SetLineWidth(3.0);
  
  // Glyph the points
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetPhiResolution(21);
  sphere->SetThetaResolution(21);
  sphere->SetRadius(.02);

  // Create a polydata to store everything in
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);

  vtkSmartPointer<vtkGlyph3DMapper> pointMapper =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  pointMapper->SetInputData(polyData);
  pointMapper->SetSourceConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);
  pointActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());

  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->AddActor(pointActor);;
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
