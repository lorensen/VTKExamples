#include <vtkImageData.h>
#include <vtkImageExport.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  int dims[3] = {2,3,1};

  imageData->SetDimensions(dims[0], dims[1], dims[2]);
  imageData->AllocateScalars(VTK_UNSIGNED_CHAR,1);

  unsigned char value = 0;
  for(int row = 0; row < dims[0]; ++row)
  {
    for(int col = 0; col < dims[1]; ++col)
    {
      unsigned char* pixel =
        static_cast<unsigned char*>(imageData->GetScalarPointer(row, col, 0));
      pixel[0] = value;
      value += 10;
    }
  }

  // Create the c-style image to convert the VTK image to
  unsigned char *cImage = new unsigned char[dims[0]*dims[1]*dims[2]];

  vtkSmartPointer<vtkImageExport> exporter =
    vtkSmartPointer<vtkImageExport>::New();
  exporter->SetInputData(imageData);
  exporter->ImageLowerLeftOn();
  exporter->Update();
  exporter->Export(cImage);

  // Output the raw c-style image
  for(int row = 0; row < dims[0]; ++row)
  {
    for(int col = 0; col < dims[1]; ++col)
    {
      std::cout << static_cast<int>(cImage[col * dims[0] + row]) << " ";
    }
    std::cout << std::endl;
  }
  delete [] cImage;

  return EXIT_SUCCESS;
}
