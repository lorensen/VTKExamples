#include <vtkSmartPointer.h>
#include <vtkImageData.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(2,3,1);
  imageData->AllocateScalars(VTK_DOUBLE,1);

  int* dims = imageData->GetDimensions();
  // int dims[3]; // can't do this

  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  std::cout << "Number of points: " << imageData->GetNumberOfPoints() << std::endl;
  std::cout << "Number of cells: " << imageData->GetNumberOfCells() << std::endl;

  // Fill every entry of the image data with "2.0"
  for (int z = 0; z < dims[2]; z++)
  {
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
        pixel[0] = 2.0;
      }
    }
  }

  // Retrieve the entries from the image data and print them to the screen
  for (int z = 0; z < dims[2]; z++)
  {
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
        // do something with v
        std::cout << pixel[0] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  // Access the data linearly
  /*
    vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->SetExtent(0,1,0,1,0,0);
  image->SetScalarTypeToInt();
  image->SetNumberOfScalarComponents(1);

  int* pixel;

  pixel = static_cast<int*>(image->GetScalarPointer(0,0,0));
  pixel[0] = 1;

  pixel = static_cast<int*>(image->GetScalarPointer(1,0,0));
  pixel[0] = 2;

  pixel = static_cast<int*>(image->GetScalarPointer(0,1,0));
  pixel[0] = 3;

  pixel = static_cast<int*>(image->GetScalarPointer(1,1,0));
  pixel[0] = 4;

  vtkIntArray* scalars = dynamic_cast<vtkIntArray*>(image->GetPointData()->GetArray("ImageScalars"));
  std::cout << "Scalars has " << scalars->GetNumberOfComponents() << " components" << std::endl;
  std::cout << "Scalars has " << scalars->GetNumberOfTuples() << " tuples" << std::endl;

  for(vtkIdType i = 0; i < scalars->GetNumberOfTuples(); i++)
    {
    std::cout << scalars->GetValue(i) << std::endl;
    }
  */
  return EXIT_SUCCESS;
}
