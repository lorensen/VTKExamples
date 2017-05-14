#include <vtkSmartPointer.h>
//#include <vtkJPEGReader.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkAVIWriter.h>

int main (int argc, char *argv[])
{

  //vtkSmartPointer<vtkJPEGReader> reader =
    //  vtkSmartPointer<vtkJPEGReader>::New();
  vtkSmartPointer<vtkImageCanvasSource2D> source =
      vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(3);
  source->SetExtent(0, 100, 0, 100, 0, 0);

  vtkSmartPointer<vtkAVIWriter> writer =
      vtkSmartPointer<vtkAVIWriter>::New();

  writer->SetInputConnection(source->GetOutputPort());
  writer->SetFileName("test.avi");
  writer->Start();

  for(unsigned int i = 0; i < 100; i++)
  {
    source->SetDrawColor(0,0,0,1); //black
    source->FillBox(0, 100, 0, 100); //clear image
    source->SetDrawColor(255,0,0,1); //red
    source->FillBox(i, 20, 10, 20);
    source->Update();

    writer->Write();
  }
  writer->End();

  return EXIT_SUCCESS;
}
