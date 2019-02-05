#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkImageCanvasSource2D.h>

int main(int, char *[])
{
  // Create a blank, black image
  vtkSmartPointer<vtkImageCanvasSource2D> drawing = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0, 20, 0, 50, 0, 0);
  drawing->FillBox(0,20,0,50);

  // Draw a red circle of radius 5 centered at (9,10)
  //drawing->SetDrawColor(255, 0, 0, 0.5);
  drawing->SetDrawColor(255, 0, 0, 0);
  drawing->DrawCircle(9, 10, 5);
  drawing->Update();
  
  // View the result
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkImageViewer2> imageViewer = 
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(drawing->GetOutputPort());
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->GetRenderer()->SetBackground(1,1,1); //white background
  imageViewer->GetRenderWindow()->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
