#include <vtkSmartPointer.h>

#include "vtkImageAlgorithmFilter.h"
#include <vtkImageData.h>

void PrintImage(vtkImageData* image);

int main (int /* argc */, char * /* argv */ [])
{
  vtkSmartPointer<vtkImageData> input =
    vtkSmartPointer<vtkImageData>::New();
  // Setup the image
  input->SetDimensions(2,2,1);
  input->AllocateScalars(VTK_DOUBLE,1);

  // Fill every entry of the image data with "2.0"
  int* dims = input->GetDimensions();

  for (int y=0; y<dims[1]; y++)
  {
    for (int x=0; x<dims[0]; x++)
    {
      input->SetScalarComponentFromDouble(x,y,0,0,2.0);
    }
  }

  std::cout << "Input image: " << std::endl;
  PrintImage(input);

  vtkSmartPointer<vtkImageAlgorithmFilter> filter =
    vtkSmartPointer<vtkImageAlgorithmFilter>::New();
  filter->SetInputData(input);
  filter->Update();

  vtkImageData* output = filter->GetOutput();

  std::cout << "Output image: " << std::endl;
  PrintImage(output);

  return 0;
}

void PrintImage(vtkImageData* image)
{
  int* dims = image->GetDimensions();

  for (int y=0; y<dims[1]; y++)
  {
    for (int x=0; x<dims[0]; x++)
    {
      double v = image->GetScalarComponentAsDouble(x,y,0,0);
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
}
