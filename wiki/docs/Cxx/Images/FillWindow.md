[VTKExamples](/home/)/[Cxx](/Cxx)/Images/FillWindow

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestFillWindow.png?raw=true" width="256" />

**FillWindow.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkCamera.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageCast.h>
#include <vtkImageMapper3D.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> mandelbrotSource =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  mandelbrotSource->Update();

  vtkSmartPointer<vtkImageCast> castFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castFilter->SetInputConnection(mandelbrotSource->GetOutputPort());
  castFilter->SetOutputScalarTypeToUnsignedChar();
  castFilter->Update();

  vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
  imageSliceMapper->SetInputConnection(castFilter->GetOutputPort());

  vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice->SetMapper(imageSliceMapper);

  int extent[6];
  castFilter->GetOutput()->GetExtent(extent);

  double origin[3];
  castFilter->GetOutput()->GetOrigin(origin);

  double spacing[3];
  castFilter->GetOutput()->GetSpacing(spacing);

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageSlice);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkCamera* camera = renderer->GetActiveCamera();
  camera->ParallelProjectionOn();
  renderer->SetBackground(1,0,0);

  float xc = origin[0] + 0.5*(extent[0] + extent[1])*spacing[0];
  float yc = origin[1] + 0.5*(extent[2] + extent[3])*spacing[1];
//  float xd = (extent[1] - extent[0] + 1)*spacing[0]; // not used
  float yd = (extent[3] - extent[2] + 1)*spacing[1];

  float d = camera->GetDistance();
  camera->SetParallelScale(0.5f*static_cast<float>(yd));
  camera->SetFocalPoint(xc,yc,0.0);
  camera->SetPosition(xc,yc,+d);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FillWindow)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FillWindow MACOSX_BUNDLE FillWindow.cxx)
 
target_link_libraries(FillWindow ${VTK_LIBRARIES})
```

**Download and Build FillWindow**

Click [here to download FillWindow](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FillWindow.tar) and its *CMakeLists.txt* file.
Once the *tarball FillWindow.tar* has been downloaded and extracted,
```
cd FillWindow/build 
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
./FillWindow
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

