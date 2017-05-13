[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/GreedyTerrainDecimation

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestGreedyTerrainDecimation.png?raw=true" width="256" />

**GreedyTerrainDecimation.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkMath.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkGreedyTerrainDecimation.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->SetDimensions(3,3,1);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(1);
  image->SetScalarTypeToUnsignedChar();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,1);
#endif
  int dims[3];
  image->GetDimensions(dims);
  for(int i = 0; i < dims[0]; i++)
  {
    for(int j = 0; j < dims[1]; j++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(i,j,0));
      //pixel[0] = vtkMath::Round(vtkMath::Random(0, 255));
      pixel[0] = vtkMath::Round(vtkMath::Random(0, 1));
    }
  }

  vtkSmartPointer<vtkGreedyTerrainDecimation> decimation =
    vtkSmartPointer<vtkGreedyTerrainDecimation>::New();
#if VTK_MAJOR_VERSION <= 5
  decimation->SetInputConnection(image->GetProducerPort());
#else
  decimation->SetInputData(image);
#endif
  decimation->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(decimation->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetInterpolationToFlat();
  actor->GetProperty()->EdgeVisibilityOn();
  actor->GetProperty()->SetEdgeColor(1,0,0);

  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GreedyTerrainDecimation)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GreedyTerrainDecimation MACOSX_BUNDLE GreedyTerrainDecimation.cxx)
 
target_link_libraries(GreedyTerrainDecimation ${VTK_LIBRARIES})
```

**Download and Build GreedyTerrainDecimation**

Click [here to download GreedyTerrainDecimation](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GreedyTerrainDecimation.tar) and its *CMakeLists.txt* file.
Once the *tarball GreedyTerrainDecimation.tar* has been downloaded and extracted,
```
cd GreedyTerrainDecimation/build 
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
./GreedyTerrainDecimation
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

