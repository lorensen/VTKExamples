#include <vtkDataArray.h>
#include <vtkFloatArray.h>
#include <vtkImageData.h>
#include <vtkImageMagnitude.h>
#include <vtkIntArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkSmartPointer.h>
#include <vtkThresholdPoints.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLUnstructuredGridWriter.h>

namespace {
void CreateVectorField(vtkImageData* image);
void WriteImage(vtkImageData* image, const std::string& fileName);
void WriteVectorField(vtkPolyData* vectorField, const std::string& fileName);
} // namespace

int main(int, char*[])
{
  // Create an image
  auto image = vtkSmartPointer<vtkImageData>::New();
  CreateVectorField(image);

  auto magnitudeFilter = vtkSmartPointer<vtkImageMagnitude>::New();
  magnitudeFilter->SetInputData(image);
  magnitudeFilter->Update(); // This filter produces a vtkImageData with an
                             // array named "Magnitude"

  image->GetPointData()->AddArray(
      magnitudeFilter->GetOutput()->GetPointData()->GetScalars());
  image->GetPointData()->SetActiveScalars("Magnitude");

  auto thresholdPoints = vtkSmartPointer<vtkThresholdPoints>::New();
  // thresholdPoints->SetInputConnection(magnitudeFilter->GetOutputPort());
  thresholdPoints->SetInputData(image);
  thresholdPoints->ThresholdByUpper(.05);
  thresholdPoints->Update();

  WriteImage(image, "input.vti");
  WriteVectorField(thresholdPoints->GetOutput(), "output.vtp");

  return EXIT_SUCCESS;
}

namespace {

void CreateVectorField(vtkImageData* image)
{
  // Specify the size of the image data
  image->SetDimensions(50, 50, 1);
  image->AllocateScalars(VTK_FLOAT, 3);

  int* dims = image->GetDimensions();

  // Zero the image
  for (auto y = 0; y < dims[1]; y++)
  {
    for (auto x = 0; x < dims[0]; x++)
    {
      float* pixel = static_cast<float*>(image->GetScalarPointer(x, y, 0));
      pixel[0] = 0.0;
      pixel[1] = 0.0;
      pixel[2] = 0.0;
    }
  }

  // Set two of the pixels to non zero values
  float* pixel = static_cast<float*>(image->GetScalarPointer(20, 20, 0));
  pixel[0] = -10.0;
  pixel[1] = 5.0;
  pixel[2] = 0.0;

  pixel = static_cast<float*>(image->GetScalarPointer(30, 30, 0));
  pixel[0] = 10.0;
  pixel[1] = 10.0;
  pixel[2] = 0.0;

  image->GetPointData()->SetActiveVectors("ImageScalars");

  image->Modified();
}

void WriteVectorField(vtkPolyData* vectorField, const std::string& fileName)
{
  auto writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName(fileName.c_str());
  writer->SetInputData(vectorField);
  writer->Write();
}

void WriteImage(vtkImageData* image, const std::string& fileName)
{
  auto writer = vtkSmartPointer<vtkXMLImageDataWriter>::New();
  writer->SetFileName(fileName.c_str());
  writer->SetInputData(image);
  writer->Write();
}

} // namespace
