#include <vtkSmartPointer.h>
#include <vtkProgrammableSource.h>
#include <vtkPolyData.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkPoints.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

// https://en.wikipedia.org/wiki/Lorenz_system
static void Lorenz(void *arg)
{
  double sigma = 10.0;	/* The Lorenz paramaters */
  double beta = 8.0 / 3.0;
  double rho = 28.0;
  double h = .001;      /* Integration step size */

  double x, y, z;
  double xx, yy, zz;
  x = 0.1;
  y = 0.1;
  z = 0.1;
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  // Get to a stable starting point
  for (int i = 0; i < 1000; ++i)
  {
    xx = x + h * sigma * (y - x);
    yy = y + h * (x * (rho - z) - y);
    zz = z + h * (x * y - (beta * z));
    x = xx; y = yy; z = zz;
  }
  for (int i = 0; i < 500000; ++i)
  {
    xx = x + h * sigma * (y - x);
    yy = y + h * (x * (rho - z) - y);
    zz = z + h * (x * y - (beta * z));
    points->InsertNextPoint(xx, yy, zz);
    x = xx; y = yy; z = zz;
  }
  vtkSmartPointer<vtkPolyData> pointsPolydata =
    vtkSmartPointer<vtkPolyData>::New();
  pointsPolydata->SetPoints(points);
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  vertexFilter->SetInputData(pointsPolydata);
  vertexFilter->Update();
  vtkProgrammableSource * ps =
    static_cast<vtkProgrammableSource *>(arg);
  vtkPolyData *output = ps->GetPolyDataOutput();
  output->DeepCopy(vertexFilter->GetOutput());
}

int main (int, char *[])
{
  vtkSmartPointer<vtkProgrammableSource> source =
    vtkSmartPointer<vtkProgrammableSource>::New();
  source->SetExecuteMethod(Lorenz, source);
  source->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(source->GetPolyDataOutput());
  
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
  renderer->SetBackground(.4, .5, .7);
  renderWindow->Render();
  renderWindowInteractor->Start();

 return EXIT_SUCCESS;
}
