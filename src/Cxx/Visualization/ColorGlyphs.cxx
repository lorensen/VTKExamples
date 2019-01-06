#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkGlyph3D.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkUnsignedCharArray.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int, char *[])
{
  // Create points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(5,0,0);
  points->InsertNextPoint(10,0,0);
  
  // Setup scales. This can also be an Int array
  // char is used since it takes the least memory
  vtkSmartPointer<vtkUnsignedCharArray> colors = 
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetName("colors");
  colors->SetNumberOfComponents(3);
  unsigned char r[3] = {255,0,0};
  unsigned char g[3] = {0,255,0};
  unsigned char b[3] = {0,0,255};
  colors->InsertNextTupleValue(r);
  colors->InsertNextTupleValue(g);
  colors->InsertNextTupleValue(b);
    
  // Combine into a polydata
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->SetScalars(colors);
  
  // Create anything you want here, we will use a cube for the demo.
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  
  vtkSmartPointer<vtkGlyph3D> glyph3D = 
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph3D->SetColorModeToColorByScalar();
  glyph3D->SetSourceConnection(cubeSource->GetOutputPort());
  glyph3D->SetInputData(polydata);
  glyph3D->ScalingOff();
  glyph3D->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyph3D->GetOutputPort());
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
