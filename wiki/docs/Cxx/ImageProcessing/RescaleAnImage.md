[VTKExamples](/index/)/[Cxx](/Cxx)/ImageProcessing/RescaleAnImage

**RescaleAnImage.cxx**
```c++
#include <vtkImageData.h>
#include <vtkImageShiftScale.h>
#include <vtkMath.h>
#include <vtkSmartPointer.h>

static void CreateImage(vtkImageData* const image);

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
  CreateImage(image);

  vtkSmartPointer<vtkImageShiftScale> shiftScaleFilter =
    vtkSmartPointer<vtkImageShiftScale>::New();
  shiftScaleFilter->SetOutputScalarTypeToUnsignedChar();
#if VTK_MAJOR_VERSION <= 5
  shiftScaleFilter->SetInputConnection(image->GetProducerPort());
#else
  shiftScaleFilter->SetInputData(image);
#endif
  shiftScaleFilter->SetShift(-1.0f * image->GetScalarRange()[0]); // brings the lower bound to 0
  float oldRange = image->GetScalarRange()[1] - image->GetScalarRange()[0];
  std::cout << "Old range: [" << image->GetScalarRange()[0] << ", " << image->GetScalarRange()[1] << "]" << std::endl;
  std::cout << "Old range magnitude: " << oldRange << std::endl;
  float newRange = 255; // We want the output [0,255]

  shiftScaleFilter->SetScale(newRange/oldRange);
  shiftScaleFilter->Update();

  std::cout << "New range: [" << shiftScaleFilter->GetOutput()->GetScalarRange()[1] << ", " << shiftScaleFilter->GetOutput()->GetScalarRange()[1] << "]" << std::endl;
  return EXIT_SUCCESS;
}

void CreateImage(vtkImageData* const image)
{
  // Specify the size of the image data
  image->SetDimensions(2,3,1);

#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(1);
  image->SetScalarTypeToDouble();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_DOUBLE,1);
#endif
  int* dims = image->GetDimensions();

  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  for (int z = 0; z < dims[2]; z++)
  {
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double* pixel = static_cast<double*>(image->GetScalarPointer(x,y,z));
        pixel[0] =vtkMath::Random(0.0,2000.0);
      }
    }
  }
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RescaleAnImage)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RescaleAnImage MACOSX_BUNDLE RescaleAnImage.cxx)
 
target_link_libraries(RescaleAnImage ${VTK_LIBRARIES})
```

**Download and Build RescaleAnImage**

Click [here to download RescaleAnImage](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RescaleAnImage.tar) and its *CMakeLists.txt* file.
Once the *tarball RescaleAnImage.tar* has been downloaded and extracted,
```
cd RescaleAnImage/build 
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
./RescaleAnImage
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

