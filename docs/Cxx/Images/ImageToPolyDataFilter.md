[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageToPolyDataFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageToPolyDataFilter.png?raw=true" width="256" />

**ImageToPolyDataFilter.cxx**
```c++
#include <vtkActor.h>
#include <vtkLookupTable.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkImageToPolyDataFilter.h>
#include <vtkImageQuantizeRGBToIndex.h>
#include <vtkCamera.h>
#include <vtkPNGReader.h>
#include <vtkTriangleFilter.h>

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    std::cerr << "Required arguments: filename.png" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkPNGReader> reader =
    vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageQuantizeRGBToIndex> quant =
    vtkSmartPointer<vtkImageQuantizeRGBToIndex>::New();
  quant->SetInputConnection(reader->GetOutputPort());
  quant->SetNumberOfColors(16);

  vtkSmartPointer<vtkImageToPolyDataFilter> i2pd =
    vtkSmartPointer<vtkImageToPolyDataFilter>::New();
  i2pd->SetInputConnection(quant->GetOutputPort());
  i2pd->SetLookupTable(quant->GetLookupTable());
  i2pd->SetColorModeToLUT();
  i2pd->SetOutputStyleToPolygonalize();
  i2pd->SetError(0);
  i2pd->DecimationOn();
  i2pd->SetDecimationError(0.0);
  i2pd->SetSubImageSize(25);

  // Need a triangle filter because the polygons are complex and concave
  vtkSmartPointer<vtkTriangleFilter> tf =
    vtkSmartPointer<vtkTriangleFilter>::New();
  tf->SetInputConnection(i2pd->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(tf->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);

  renderer->SetBackground(1, 1, 1);
  renderWindow->SetSize(300, 250);

  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageToPolyDataFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageToPolyDataFilter MACOSX_BUNDLE ImageToPolyDataFilter.cxx)
 
target_link_libraries(ImageToPolyDataFilter ${VTK_LIBRARIES})
```

**Download and Build ImageToPolyDataFilter**

Click [here to download ImageToPolyDataFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageToPolyDataFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageToPolyDataFilter.tar* has been downloaded and extracted,
```
cd ImageToPolyDataFilter/build 
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
./ImageToPolyDataFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

