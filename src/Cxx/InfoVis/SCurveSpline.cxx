#include <vtkSmartPointer.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkSCurveSpline.h>
#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource = 
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(5);
  pointSource->Update();
  
  vtkPoints* points = pointSource->GetOutput()->GetPoints();
    
  vtkSmartPointer<vtkSCurveSpline> xSpline = 
    vtkSmartPointer<vtkSCurveSpline>::New();
  vtkSmartPointer<vtkSCurveSpline> ySpline = 
    vtkSmartPointer<vtkSCurveSpline>::New();
  vtkSmartPointer<vtkSCurveSpline> zSpline = 
    vtkSmartPointer<vtkSCurveSpline>::New();

  vtkSmartPointer<vtkParametricSpline> spline = 
    vtkSmartPointer<vtkParametricSpline>::New();
  spline->SetXSpline(xSpline);
  spline->SetYSpline(ySpline);
  spline->SetZSpline(zSpline);
  spline->SetPoints(points);
  
  vtkSmartPointer<vtkParametricFunctionSource> functionSource = 
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  functionSource->SetParametricFunction(spline);
  functionSource->Update();

  // Setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(functionSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
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

  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
