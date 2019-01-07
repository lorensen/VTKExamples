#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkPointData.h>
#include <vtkImageData.h>
#include <vtkFloatArray.h>
#include <vtkThresholdPoints.h>
#include <vtkIntArray.h>
#include <vtkDataArray.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkImageMagnitude.h>

static void CreateVectorField(vtkImageData* image);
static void WriteImage(vtkImageData* image, const std::string fileName);
static void WriteVectorField(vtkPolyData* vectorField, const std::string fileName);

int main(int , char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
  CreateVectorField(image);

  vtkSmartPointer<vtkImageMagnitude> magnitudeFilter = vtkSmartPointer<vtkImageMagnitude>::New();
  magnitudeFilter->SetInputData(image);
  magnitudeFilter->Update(); // This filter produces a vtkImageData with an array named "Magnitude"

  image->GetPointData()->AddArray(magnitudeFilter->GetOutput()->GetPointData()->GetScalars());
  image->GetPointData()->SetActiveScalars("Magnitude");

  vtkSmartPointer<vtkThresholdPoints> thresholdPoints = vtkSmartPointer<vtkThresholdPoints>::New();
  //thresholdPoints->SetInputConnection(magnitudeFilter->GetOutputPort());
  thresholdPoints->SetInputData(image);
  thresholdPoints->ThresholdByUpper(.05);
  thresholdPoints->Update();

  WriteImage(image, "input.vti");
  WriteVectorField(thresholdPoints->GetOutput(), "output.vtp");

  return EXIT_SUCCESS;
}

void CreateVectorField(vtkImageData* image)
{
  // Specify the size of the image data
  image->SetDimensions(50,50,1);
  image->AllocateScalars(VTK_FLOAT, 3);

  int* dims = image->GetDimensions();

  // Zero the image
  for (int y = 0; y < dims[1]; y++)
  {
    for (int x = 0; x < dims[0]; x++)
    {
      float* pixel = static_cast<float*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 0.0;
      pixel[1] = 0.0;
      pixel[2] = 0.0;
    }
  }

  // Set two of the pixels to non zero values
  float* pixel = static_cast<float*>(image->GetScalarPointer(20,20,0));
  pixel[0] = -10.0;
  pixel[1] = 5.0;
  pixel[2] = 0.0;

  pixel = static_cast<float*>(image->GetScalarPointer(30,30,0));
  pixel[0] = 10.0;
  pixel[1] = 10.0;
  pixel[2] = 0.0;

  image->GetPointData()->SetActiveVectors("ImageScalars");

  image->Modified();
}

void WriteVectorField(vtkPolyData* vectorField, const std::string fileName)
{
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName(fileName.c_str());
    writer->SetInputData(vectorField);
    writer->Write();
}

void WriteImage(vtkImageData* image, const std::string fileName)
{
    vtkSmartPointer<vtkXMLImageDataWriter> writer = vtkSmartPointer<vtkXMLImageDataWriter>::New();
    writer->SetFileName(fileName.c_str());
    writer->SetInputData(image);
    writer->Write();
}
