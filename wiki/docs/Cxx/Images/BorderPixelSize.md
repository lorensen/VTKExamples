[VTKExamples](/home/)/[Cxx](/Cxx)/Images/BorderPixelSize

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestBorderPixelSize.png?raw=true" width="256" />

**BorderPixelSize.cxx**
```c++
#include <vtkVersion.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkImageProperty.h>

static void CreateRandomImage(vtkImageData* image, const unsigned int dimension);

int main(int, char *[])
{
  // Big image
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
  CreateRandomImage(image, 50);

  vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  imageSliceMapper->SetInputConnection(image->GetProducerPort());
#else
  imageSliceMapper->SetInputData(image);
#endif
  imageSliceMapper->BorderOn(); // This line tells the mapper to draw the full border pixels.
  vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice->SetMapper(imageSliceMapper);
  imageSlice->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(imageSlice);
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CreateRandomImage(vtkImageData* image, const unsigned int dimension)
{
  image->SetDimensions(dimension, dimension, 1);
  image->SetOrigin(.5,.5,0);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(3);
  image->SetScalarTypeToUnsignedChar();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);
#endif

  for(unsigned int x = 0; x < dimension; x++)
  {
    for(unsigned int y = 0; y < dimension; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = rand() % 255;
      pixel[1] = rand() % 255;
      pixel[2] = rand() % 255;
    }
  }

  image->Modified();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BorderPixelSize)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BorderPixelSize MACOSX_BUNDLE BorderPixelSize.cxx)
 
target_link_libraries(BorderPixelSize ${VTK_LIBRARIES})
```

**Download and Build BorderPixelSize**

Click [here to download BorderPixelSize](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BorderPixelSize.tar) and its *CMakeLists.txt* file.
Once the *tarball BorderPixelSize.tar* has been downloaded and extracted,
```
cd BorderPixelSize/build 
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
./BorderPixelSize
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

