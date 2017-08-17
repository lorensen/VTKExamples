#include <vtkSmartPointer.h>
#include <vtkRegularPolygonSource.h>

#include <vtkShrinkPolyData.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>

int main(int , char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create a pentagon
  vtkSmartPointer<vtkRegularPolygonSource> polygonSource = 
    vtkSmartPointer<vtkRegularPolygonSource>::New();
  polygonSource->SetNumberOfSides(5);
  polygonSource->SetRadius(5);
  polygonSource->SetCenter(0,0,0);
  
  vtkSmartPointer<vtkShrinkPolyData> shrink =
    vtkSmartPointer<vtkShrinkPolyData>::New();
  shrink->SetInputConnection(polygonSource->GetOutputPort());
  shrink->SetShrinkFactor(.9);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(shrink->GetOutputPort());

  vtkSmartPointer<vtkProperty> back =
    vtkSmartPointer<vtkProperty>::New();
  back->SetColor(colors->GetColor3d("Tomato").GetData());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->EdgeVisibilityOn();
  actor->GetProperty()->SetLineWidth(5);
  actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  actor->SetBackfaceProperty(back);
 
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
 
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
