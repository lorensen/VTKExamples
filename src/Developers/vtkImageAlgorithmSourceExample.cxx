#include "vtkImageAlgorithmSource.h"

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkXMLImageDataWriter.h>

void PrintImage(vtkImageData* image);

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkImageAlgorithmSource> source =
    vtkSmartPointer<vtkImageAlgorithmSource>::New();
  source->Update();

  vtkImageData* output = source->GetOutput();

  std::cout << "Output image: " << std::endl;

  PrintImage(output);

  vtkSmartPointer<vtkXMLImageDataWriter> writer =
    vtkSmartPointer<vtkXMLImageDataWriter>::New();
  writer->SetFileName("test.vti");
  writer->SetInputConnection(source->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
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
