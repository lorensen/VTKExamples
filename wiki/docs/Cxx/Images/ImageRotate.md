[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageRotate

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageRotate.png?raw=true" width="256" />

**ImageRotate.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageReslice.h>
#include <vtkImageViewer2.h>
#include <vtkTransform.h>

int main(int argc, char *argv[])
{
  // Verify command line arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " InputFilename" << std::endl;
    return EXIT_FAILURE;
  }

  double angle = 45;
  if (argc > 2)
  {
    angle = atof(argv[2]);
  }

  // Read file
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();

  vtkImageReader2 *reader =
    readerFactory->CreateImageReader2(argv[1]);
  reader->SetFileName(argv[1]);
  reader->Update();
  double bounds[6];
  reader->GetOutput()->GetBounds(bounds);

  // Rotate about the center of the image
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();

  // Compute the center of the image
  double center[3];
  center[0] = (bounds[1] + bounds[0]) / 2.0;
  center[1] = (bounds[3] + bounds[2]) / 2.0;
  center[2] = (bounds[5] + bounds[4]) / 2.0;

  // Rotate about the center
  transform->Translate(center[0], center[1], center[2]);
  transform->RotateWXYZ(angle, 0, 0, 1);
  transform->Translate(-center[0], -center[1], -center[2]);

  // Reslice does all of the work
  vtkSmartPointer<vtkImageReslice> reslice =
    vtkSmartPointer<vtkImageReslice>::New();
  reslice->SetInputConnection(reader->GetOutputPort());
  reslice->SetResliceTransform(transform);
  reslice->SetInterpolationModeToCubic();
  reslice->SetOutputSpacing(
    reader->GetOutput()->GetSpacing()[0],
    reader->GetOutput()->GetSpacing()[1],
    reader->GetOutput()->GetSpacing()[2]);
  reslice->SetOutputOrigin(
    reader->GetOutput()->GetOrigin()[0],
    reader->GetOutput()->GetOrigin()[1],
    reader->GetOutput()->GetOrigin()[2]);
  reslice->SetOutputExtent(reader->GetOutput()->GetExtent()); // Use a larger extent than the original image's to prevent clipping

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(reslice->GetOutputPort());
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();

  renderWindowInteractor->Start();

  reader->Delete();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageRotate)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageRotate MACOSX_BUNDLE ImageRotate.cxx)
 
target_link_libraries(ImageRotate ${VTK_LIBRARIES})
```

**Download and Build ImageRotate**

Click [here to download ImageRotate](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageRotate.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageRotate.tar* has been downloaded and extracted,
```
cd ImageRotate/build 
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
./ImageRotate
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

