#include <vtkActor.h>
#include <vtkImageData.h>
#include <vtkIntArray.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkImageReslice.h>
 
int main(int, char *[] )
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->SetExtent(0, 9, 0, 9, 0, 0);
  image->AllocateScalars(VTK_INT,1);

  int* pixel = static_cast<int*>(image->GetScalarPointer(0,9,0));
  std::cout << "pixel: " << *pixel << std::endl;

  vtkSmartPointer<vtkImageReslice> reslice =
    vtkSmartPointer<vtkImageReslice>::New();
  reslice->SetOutputExtent(0, 9, 0, 100, 0, 0);
  reslice->SetInputData(image);
  reslice->Update();

  int* pixel2 = static_cast<int*>(reslice->GetOutput()->GetScalarPointer(0,11,0));
  std::cout << "pixel2: " << *pixel2 << std::endl;

  return EXIT_SUCCESS;
}
