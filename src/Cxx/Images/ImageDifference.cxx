#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageDifference.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> source1 = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source1->SetScalarTypeToUnsignedChar();
  source1->SetNumberOfScalarComponents(3);
  source1->SetExtent(0, 100, 0, 100, 0, 0);
  source1->SetDrawColor(0,0,0,1);
  source1->FillBox(0, 100, 0, 100);
  source1->SetDrawColor(255,0,0,1);
  source1->FillBox(10, 90, 10, 90);
  source1->Update();

  // Create another image
  vtkSmartPointer<vtkImageCanvasSource2D> source2 = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source2->SetScalarTypeToUnsignedChar();
  source2->SetNumberOfScalarComponents(3);
  source2->SetExtent(0, 100, 0, 100, 0, 0);
  source2->SetDrawColor(0,0,0,1);
  source2->FillBox(0, 100, 0, 100);
  source2->SetDrawColor(255,0,0,1);
  source2->FillBox(20, 80, 20, 80);
  source2->Update();

  vtkSmartPointer<vtkImageDifference> differenceFilter = 
    vtkSmartPointer<vtkImageDifference>::New();
      
  differenceFilter->SetInputConnection(source1->GetOutputPort());
  differenceFilter->SetImageConnection(source2->GetOutputPort());
  differenceFilter->Update();
    
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double centerViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};
 
  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  
  // Setup renderers
  vtkSmartPointer<vtkRenderer> leftRenderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  vtkSmartPointer<vtkImageActor> leftActor = 
    vtkSmartPointer<vtkImageActor>::New();
  leftActor->GetMapper()->SetInputConnection(source1->GetOutputPort());
  leftRenderer->AddActor(leftActor);
  
  vtkSmartPointer<vtkRenderer> centerRenderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(centerRenderer);
  centerRenderer->SetViewport(centerViewport);
  vtkSmartPointer<vtkImageActor> centerActor = 
    vtkSmartPointer<vtkImageActor>::New();
  centerActor->GetMapper()->SetInputConnection(source2->GetOutputPort());
  centerRenderer->AddActor(centerActor);
  
  vtkSmartPointer<vtkRenderer> rightRenderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  vtkSmartPointer<vtkImageActor> rightActor = 
    vtkSmartPointer<vtkImageActor>::New();
  rightActor->GetMapper()->SetInputConnection(differenceFilter->GetOutputPort());
  rightRenderer->AddActor(rightActor);
  
  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
 
  // Render and start interaction
  renderWindowInteractor->SetRenderWindow ( renderWindow );
  renderWindow->Render();

  renderWindowInteractor->Initialize();
 
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
