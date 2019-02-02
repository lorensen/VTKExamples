#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMirrorPad.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> source = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetExtent(0, 20, 0, 20, 0, 0);
  source->SetScalarTypeToUnsignedChar();
  source->SetDrawColor(0.0, 0.0, 0.0, 1.0);
  source->FillBox(-VTK_INT_MAX, VTK_INT_MAX, -VTK_INT_MAX, VTK_INT_MAX);
  source->SetDrawColor(255.0, 0.0, 0.0, 0.5);
  source->DrawCircle(10, 10, 5);
  source->Update();
  
  vtkSmartPointer<vtkImageMirrorPad> mirrorPadFilter = 
    vtkSmartPointer<vtkImageMirrorPad>::New();
  mirrorPadFilter->SetInputConnection(source->GetOutputPort());
  mirrorPadFilter->SetOutputWholeExtent(-10, 30, -10, 30, 0, 0);
  mirrorPadFilter->Update();
  
  // Create an actor
  vtkSmartPointer<vtkImageActor> actor = 
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(
    mirrorPadFilter->GetOutputPort());
 
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();
 
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer ( renderer );
 
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
 
  renderWindowInteractor->SetRenderWindow ( renderWindow );
  renderWindow->Render();
  renderWindowInteractor->Initialize();
 
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
