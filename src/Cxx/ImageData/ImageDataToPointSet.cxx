#include <vtkImageData.h>
#include <vtkPoints.h>
#include <vtkImageDataToPointSet.h>
#include <vtkSmartPointer.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkStructuredGrid.h>

static void CreateImage(vtkImageData* image);

int main(int, char *[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  CreateImage(image);

  vtkSmartPointer<vtkImageDataToPointSet> imageDataToPointSet =
    vtkSmartPointer<vtkImageDataToPointSet>::New();
  imageDataToPointSet->SetInputData(image);
  imageDataToPointSet->Update();

  vtkSmartPointer<vtkXMLStructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
  writer->SetInputConnection(imageDataToPointSet->GetOutputPort());
  writer->SetFileName("Test.vts");
  writer->Write();

  return EXIT_SUCCESS;
}

void CreateImage(vtkImageData* image)
{
  // Create an image
  image->SetDimensions(3,3,1);
  image->AllocateScalars(VTK_UNSIGNED_CHAR,1);

  int dims[3];
  image->GetDimensions(dims);
  for(int i = 0; i < dims[0]; i++)
  {
    for(int j = 0; j < dims[1]; j++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(i,j,0));
      pixel[0] = 1;
    }
  }
}
