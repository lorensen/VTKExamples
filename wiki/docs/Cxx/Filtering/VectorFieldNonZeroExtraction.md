[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/VectorFieldNonZeroExtraction

**VectorFieldNonZeroExtraction.cxx**
```c++
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
#include <vtkVersion.h>

static void CreateVectorField(vtkImageData* image);
static void WriteImage(vtkImageData* image, const std::string fileName);
static void WriteVectorField(vtkPolyData* vectorField, const std::string fileName);

int main(int , char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
  CreateVectorField(image);

  vtkSmartPointer<vtkImageMagnitude> magnitudeFilter = vtkSmartPointer<vtkImageMagnitude>::New();

#if VTK_MAJOR_VERSION <= 5
  magnitudeFilter->SetInputConnection(image->GetProducerPort());
#else
  magnitudeFilter->SetInputData(image);
#endif
  magnitudeFilter->Update(); // This filter produces a vtkImageData with an array named "Magnitude"

  image->GetPointData()->AddArray(magnitudeFilter->GetOutput()->GetPointData()->GetScalars());
  image->GetPointData()->SetActiveScalars("Magnitude");

  vtkSmartPointer<vtkThresholdPoints> thresholdPoints = vtkSmartPointer<vtkThresholdPoints>::New();
  //thresholdPoints->SetInputConnection(magnitudeFilter->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  thresholdPoints->SetInputConnection(image->GetProducerPort());
#else
  thresholdPoints->SetInputData(image);
#endif

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
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(3);
  image->SetScalarTypeToFloat();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_FLOAT, 3);
#endif

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
    #if VTK_MAJOR_VERSION <= 5
      writer->SetInput(vectorField);
    #else
      writer->SetInputData(vectorField);
    #endif
    writer->Write();
}

void WriteImage(vtkImageData* image, const std::string fileName)
{
    vtkSmartPointer<vtkXMLImageDataWriter> writer = vtkSmartPointer<vtkXMLImageDataWriter>::New();
    writer->SetFileName(fileName.c_str());
    #if VTK_MAJOR_VERSION <= 5
      writer->SetInput(image);
    #else
      writer->SetInputData(image);
    #endif
    writer->Write();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VectorFieldNonZeroExtraction)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VectorFieldNonZeroExtraction MACOSX_BUNDLE VectorFieldNonZeroExtraction.cxx)
 
target_link_libraries(VectorFieldNonZeroExtraction ${VTK_LIBRARIES})
```

**Download and Build VectorFieldNonZeroExtraction**

Click [here to download VectorFieldNonZeroExtraction](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VectorFieldNonZeroExtraction.tar) and its *CMakeLists.txt* file.
Once the *tarball VectorFieldNonZeroExtraction.tar* has been downloaded and extracted,
```
cd VectorFieldNonZeroExtraction/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./VectorFieldNonZeroExtraction
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

