#include <vtkSmartPointer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkJPEGWriter.h>

int main(int vtkNotUsed(argc), char* vtkNotUsed(argv)[])
{
  std::string outputFilename = "output.jpg";

  // Create a 100x100 image to save into the jpeg file
  int extent[6] = { 0, 99, 0, 99, 0, 0 };
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetExtent( extent );
  imageSource->SetScalarTypeToUnsignedChar(); // vtkJPEGWriter only accepts unsigned char input
  imageSource->SetNumberOfScalarComponents( 3 ); // 3 color channels: Red, Green and Blue

  // Fill the whole image with a blue background
  imageSource->SetDrawColor( 0, 127, 255 );
  imageSource->FillBox( extent[0], extent[1], extent[2], extent[3] );

  // Paint a 30x30 white square into the image
  imageSource->SetDrawColor( 255, 255, 255 );
  imageSource->FillBox( 40, 70, 20, 50 );

  vtkSmartPointer<vtkJPEGWriter> writer =
    vtkSmartPointer<vtkJPEGWriter>::New();
  writer->SetFileName( outputFilename.c_str() );
  writer->SetInputConnection( imageSource->GetOutputPort() );
  writer->Write();

  return EXIT_SUCCESS;
}
