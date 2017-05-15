#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkSmartPointer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageCast.h>

int main(int argc, char *argv[])
{
  std::string outputFilename;
  if( argc > 1)
  {
    outputFilename = argv[1];
  }
  else
  {
    outputFilename = "output.png";
  }

  int extent[6] = {0, 99, 0, 99, 0, 0};
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetExtent(extent);
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetDrawColor(127, 45, 255);
  imageSource->FillBox(0, 99, 0, 99);
  imageSource->SetDrawColor(255,255,255);
  imageSource->FillBox(40, 70, 20, 50);
  imageSource->Update();

  vtkSmartPointer<vtkImageCast> castFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castFilter->SetOutputScalarTypeToUnsignedChar ();
  castFilter->SetInputConnection(imageSource->GetOutputPort());
  castFilter->Update();

  vtkSmartPointer<vtkPNGWriter> writer =
    vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName(outputFilename.c_str());
  writer->SetInputConnection(castFilter->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
