#include <vtkSmartPointer.h>
#include <vtkRegularPolygonSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkGlyph2D.h>
#include <vtkCellArray.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,1,0);
  points->InsertNextPoint(2,2,0);
  
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  
  // Create anything you want here, we will use a polygon for the demo.
  vtkSmartPointer<vtkRegularPolygonSource> polygonSource = 
      vtkSmartPointer<vtkRegularPolygonSource>::New(); //default is 6 sides
  
  vtkSmartPointer<vtkGlyph2D> glyph2D = 
    vtkSmartPointer<vtkGlyph2D>::New();
  glyph2D->SetSourceConnection(polygonSource->GetOutputPort());
  glyph2D->SetInputData(polydata);
  glyph2D->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();
 
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
 
  vtkSmartPointer<vtkInteractorStyleImage> style = 
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  renderWindowInteractor->SetInteractorStyle( style );
  
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
