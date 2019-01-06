#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageIterator.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
      vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(10,20,30);
  imageData->AllocateScalars(VTK_DOUBLE,3);

  // Fill every entry of the image data with x,y,z
  int* dims = imageData->GetDimensions();
  double *ptr = static_cast<double *>(imageData->GetScalarPointer(0, 0, 0));
  for (int z=0; z<dims[2]; z++)
  {
    for (int y=0; y<dims[1]; y++)
    {
      for (int x=0; x<dims[0]; x++)
      {
        *ptr++ = z;
        *ptr++ = y;
        *ptr++ = x;
      }
    }
  }

  // Define the extent to be extracted
  int extent[6];
  extent[0] = 2; extent[1] = 5;
  extent[2] = 2; extent[3] = 5;
  extent[4] = 15; extent[5] = 15;

  // Retrieve the entries from the image data and print them to the screen
  vtkImageIterator<double> it(imageData, extent);
  while(!it.IsAtEnd())
  {
    double* valIt = it.BeginSpan();
    double *valEnd = it.EndSpan();
    while (valIt != valEnd)
    {
      // Increment for each component
      double x = *valIt++;
      double y = *valIt++;
      double z = *valIt++;
      std::cout << "("
                << x << ","
                << y << ","
                << z << ") ";
    }
    std::cout << std::endl;
    it.NextSpan();
  }

  return EXIT_SUCCESS;
}
