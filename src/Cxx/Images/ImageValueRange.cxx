#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(5,1,1);
  imageData->AllocateScalars(VTK_DOUBLE,1);

  int* dims = imageData->GetDimensions();

  for (int x = 0; x < dims[0]; x++)
  {
    double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,0,0));
    pixel[0] = x*10;
  }

  double valuesRange[2];
  dynamic_cast<vtkDoubleArray*>(imageData->GetPointData()->GetArray("ImageScalars"))->GetValueRange(valuesRange);
  std::cout << "valuesRange = " << valuesRange[0] << " " << valuesRange[1] << std::endl;

  // This should also work:
  // min = vtkImageData->GetOutput()->GetScalarRange()[0] and max = GetScalarRange()[1].
  return EXIT_SUCCESS;
}
