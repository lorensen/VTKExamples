#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkContourFilter.h>
#include <vtkGaussianSplatter.h>
#include <vtkSphereSource.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create points on a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(sphereSource->GetOutput()->GetPoints());

  vtkSmartPointer<vtkGaussianSplatter> splatter = 
    vtkSmartPointer<vtkGaussianSplatter>::New();
  splatter->SetInputData(polydata);
  splatter->SetSampleDimensions(50,50,50);
  splatter->SetRadius(0.5);
  splatter->ScalarWarpingOff();

  vtkSmartPointer<vtkContourFilter> surface = 
    vtkSmartPointer<vtkContourFilter>::New();
  surface->SetInputConnection(splatter->GetOutputPort());
  surface->SetValue(0,0.01);

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(surface->GetOutputPort());
 
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
