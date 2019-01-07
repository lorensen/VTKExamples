#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkFloatArray.h>
#include <vtkGlyph3DMapper.h>
#include <vtkNamedColors.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkActor.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkUnsignedCharArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,1,1);
  points->InsertNextPoint(2,2,2);
  
  vtkSmartPointer<vtkFloatArray> scaleFactors =
    vtkSmartPointer<vtkFloatArray>::New();
  scaleFactors->SetNumberOfComponents(3);
  scaleFactors->SetName("Scale Factors");
  scaleFactors->InsertNextTuple3(0.7, 1.0, 1.0);
  scaleFactors->InsertNextTuple3(1.0, 0.7, 1.0);
  scaleFactors->InsertNextTuple3(1.0, 1.0, 0.7);

  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkUnsignedCharArray> colors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetName("Colors");
  colors->SetNumberOfComponents(3);
  colors->InsertNextTypedTuple(namedColors->GetColor3ub("Red").GetData());
  colors->InsertNextTypedTuple(namedColors->GetColor3ub("Green").GetData());
  colors->InsertNextTypedTuple(namedColors->GetColor3ub("Blue").GetData());

  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->AddArray(colors);
  polydata->GetPointData()->AddArray(scaleFactors);
  
  // Create anything you want here, we will use a cube for the demo.
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  
  vtkSmartPointer<vtkGlyph3DMapper> glyph3Dmapper = 
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  glyph3Dmapper->SetSourceConnection(cubeSource->GetOutputPort());
  glyph3Dmapper->SetInputData(polydata);
  glyph3Dmapper->SetScalarModeToUsePointFieldData();
  glyph3Dmapper->SetScaleArray("Scale Factors");
  glyph3Dmapper->SetScaleModeToScaleByVectorComponents();
  glyph3Dmapper->SelectColorArray("Colors");
  glyph3Dmapper->Update();

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(glyph3Dmapper);
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actor to the scene
  renderer->AddActor(actor);

  // Position the camera
  renderer->GetActiveCamera()->SetPosition(-10, 5, 0);
  renderer->GetActiveCamera()->SetFocalPoint(1, 1, 1);
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
