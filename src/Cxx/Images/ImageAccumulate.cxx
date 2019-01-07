/*
 * In this example, the resulting histogram has 6 pixels (all of them) in the 3rd bin (value = 2) and zero in the rest of the bins
 */
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>

static void CreateImage(vtkSmartPointer<vtkImageData> image);

int main(int, char *[] )
{
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
  CreateImage(image);

  vtkSmartPointer<vtkImageAccumulate> imageAccumulate =
    vtkSmartPointer<vtkImageAccumulate>::New();
  imageAccumulate->SetInputData(image);
  imageAccumulate->SetComponentExtent(0,255,0,0,0,0);
  imageAccumulate->SetComponentOrigin(0,0,0);
  imageAccumulate->SetComponentSpacing(1,0,0); // This will count exactly the number of pixels of each color. Use (10,0,0) to make bins of width 10 instead.
  imageAccumulate->Update();

  int dims[3];
  imageAccumulate->GetOutput()->GetDimensions(dims);
  for(vtkIdType bin = 0; bin < dims[0]; ++bin)
  {
   std::cout << *(static_cast<int*>(imageAccumulate->GetOutput()->GetScalarPointer(bin, 0, 0))) << " ";
  }

  std::cout << std::endl;

  double mean[3];
  imageAccumulate->GetMean(mean);
  std::cout << "Mean: " << mean[0] << " " << mean[1] << " " << mean[2] << std::endl;

  return  EXIT_SUCCESS;
}

void CreateImage(vtkSmartPointer<vtkImageData> image)
{
  // Specify the size of the image data
  image->SetDimensions(2,3,1);
  //image->SetExtent(0,2,0,3,0,1);
  image->AllocateScalars(VTK_DOUBLE,1);

  int* dims = image->GetDimensions();
  // int dims[3]; // can't do this

  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  // Fill every entry of the image data with "2.0"
  for (int z = 0; z < dims[2]; z++)
  {
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double* pixel = static_cast<double*>(image->GetScalarPointer(x,y,z));
        pixel[0] = 2.0;
      }
    }
  }
}
