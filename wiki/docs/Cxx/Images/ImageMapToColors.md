[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageMapToColors

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageMapToColors.png?raw=true" width="256" />

**ImageMapToColors.cxx**
```c++
//
// Displays a "grayscale" image as a full color image via the
// vtkImageMapToColors filter, which uses a lookup table to
// map scalar values to colors
//
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToColors.h>
#include <vtkImageProperty.h>
#include <vtkInteractorStyleImage.h>
#include <vtkLookupTable.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkVersion.h>

int main(int, char*[])
{
  // Create a "grayscale" 16x16 image, 1-component pixels of type "double"
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  int imageExtent[6] = { 0, 15, 0, 15, 0, 0 };
  image->SetExtent(imageExtent);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(1);
  image->SetScalarTypeToDouble();
#else
  image->AllocateScalars(VTK_DOUBLE, 1);
#endif

  double scalarvalue = 0.0;

  for (int y = imageExtent[2]; y <= imageExtent[3]; y++)
  {
    for (int x = imageExtent[0]; x <= imageExtent[1]; x++)
    {
      double* pixel = static_cast<double*>(image->GetScalarPointer(x, y, 0));
      pixel[0] = scalarvalue;
      scalarvalue += 1.0;
    }
  }

  // Map the scalar values in the image to colors with a lookup table:
  vtkSmartPointer<vtkLookupTable> lookupTable =
    vtkSmartPointer<vtkLookupTable>::New();
  lookupTable->SetNumberOfTableValues(256);
  lookupTable->SetRange(0.0, 255.0);
  lookupTable->Build();

  // Pass the original image and the lookup table to a filter to create
  // a color image:
  vtkSmartPointer<vtkImageMapToColors> scalarValuesToColors =
    vtkSmartPointer<vtkImageMapToColors>::New();
  scalarValuesToColors->SetLookupTable(lookupTable);
  scalarValuesToColors->PassAlphaToOutputOn();
#if VTK_MAJOR_VERSION <= 5
  scalarValuesToColors->SetInput(image);
#else
  scalarValuesToColors->SetInputData(image);
#endif

  // Create an image actor
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->GetMapper()->SetInputConnection(
    scalarValuesToColors->GetOutputPort());
  imageActor->GetProperty()->SetInterpolationTypeToNearest();

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageActor);
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
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
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageMapToColors)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageMapToColors MACOSX_BUNDLE ImageMapToColors.cxx)
 
target_link_libraries(ImageMapToColors ${VTK_LIBRARIES})
```

**Download and Build ImageMapToColors**

Click [here to download ImageMapToColors](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageMapToColors.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageMapToColors.tar* has been downloaded and extracted,
```
cd ImageMapToColors/build 
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
./ImageMapToColors
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

