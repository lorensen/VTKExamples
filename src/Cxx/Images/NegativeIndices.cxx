#include <vtkSmartPointer.h>
#include <vtkImageData.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetExtent(-5, 5, -5, 5, -5, 5);

  // Fill every entry of the image data with "2.0"
  int* extent = imageData->GetExtent();

  imageData->AllocateScalars(VTK_UNSIGNED_CHAR,1);

  std::cout << "Extent: " << " xmin: " << extent[0] << " xmax: " << extent[1]
            << " ymin: " << extent[2] << " ymax: " << extent[3]
            << " zmin: " << extent[4] << " zmax: " << extent[5] << std::endl;


  for (int z = extent[4]; z < extent[5]; z++)
  {
    for (int y = extent[2]; y < extent[3]; y++)
    {
      for (int x = extent[0]; x < extent[1]; x++)
      {
        imageData->SetScalarComponentFromDouble(x,y,z,0,2.0);
      }
    }
  }

  // Retrieve the entries from the image data and print them to the screen
  for (int z = extent[4]; z < extent[5]; z++)
  {
    for (int y = extent[2]; y < extent[3]; y++)
    {
      for (int x = extent[0]; x < extent[1]; x++)
      {
        // Zero is the component, add another loop if you have more
        // than one component
        double v = imageData->GetScalarComponentAsDouble(x,y,z,0);
        // Eo something with v
        std::cout << v << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  return EXIT_SUCCESS;
}
