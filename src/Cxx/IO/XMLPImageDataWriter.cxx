#include <vtkSmartPointer.h>
#include <vtkXMLPImageDataWriter.h>
#include <vtkImageCanvasSource2D.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkImageCanvasSource2D> drawing =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetExtent(0, 20, 0, 50, 0, 1);
  drawing->SetDrawColor(255.0, 255.0, 255.0);
  drawing->DrawCircle(5, 5, 3);

  int numberOfPieces = 4;
  
  vtkSmartPointer<vtkXMLPImageDataWriter> writer =
    vtkSmartPointer<vtkXMLPImageDataWriter>::New();
  writer->SetInputConnection(drawing->GetOutputPort());
  writer->SetFileName("Test.pvti");
  writer->SetNumberOfPieces(numberOfPieces);
  writer->SetEndPiece(numberOfPieces-1);
  writer->SetStartPiece(0);
  writer->Update();

  return EXIT_SUCCESS;
}
