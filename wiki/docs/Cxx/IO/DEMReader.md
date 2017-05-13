[VTKExamples](/home/)/[Cxx](/Cxx)/IO/DEMReader

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestDEMReader.png?raw=true" width="256" />

**DEMReader.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkDEMReader.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  // Verify arguments
  if(argc < 2)
  {
    std::cerr << "Required: filename.dem" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the file
  vtkSmartPointer<vtkDEMReader> reader =
    vtkSmartPointer<vtkDEMReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetHueRange(0.6, 0);
  lut->SetSaturationRange(1.0, 0);
  lut->SetValueRange(0.5, 1.0);
  lut->SetTableRange(reader->GetOutput()->GetScalarRange());

  // Visualize
  vtkSmartPointer<vtkImageMapToColors> mapColors =
    vtkSmartPointer<vtkImageMapToColors>::New();
  mapColors->SetLookupTable(lut);
  mapColors->SetInputConnection(reader->GetOutputPort());

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(mapColors->GetOutputPort());

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

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
 
PROJECT(DEMReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DEMReader MACOSX_BUNDLE DEMReader.cxx)
 
target_link_libraries(DEMReader ${VTK_LIBRARIES})
```

**Download and Build DEMReader**

Click [here to download DEMReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DEMReader.tar) and its *CMakeLists.txt* file.
Once the *tarball DEMReader.tar* has been downloaded and extracted,
```
cd DEMReader/build 
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
./DEMReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

