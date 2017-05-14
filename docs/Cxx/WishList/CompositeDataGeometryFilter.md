[VTKExamples](/index/)/[Cxx](/Cxx)/WishList/CompositeDataGeometryFilter

**CompositeDataGeometryFilter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkLSDynaReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkCompositeDataPipeline.h>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cout << "Required arguments: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  vtkCompositeDataPipeline* pipeline = vtkCompositeDataPipeline::New();
  vtkAlgorithm::SetDefaultExecutive(pipeline);
  //pipeline->Delete();

  std::string filename = argv[1];
  vtkSmartPointer<vtkLSDynaReader> reader =
    vtkSmartPointer<vtkLSDynaReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  vtkSmartPointer<vtkCompositeDataGeometryFilter> compositeFilter =
    vtkSmartPointer<vtkCompositeDataGeometryFilter>::New();
  compositeFilter->SetInputConnection(reader->GetOutputPort());
  compositeFilter->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(compositeFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CompositeDataGeometryFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CompositeDataGeometryFilter MACOSX_BUNDLE CompositeDataGeometryFilter.cxx)
 
target_link_libraries(CompositeDataGeometryFilter ${VTK_LIBRARIES})
```

**Download and Build CompositeDataGeometryFilter**

Click [here to download CompositeDataGeometryFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CompositeDataGeometryFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball CompositeDataGeometryFilter.tar* has been downloaded and extracted,
```
cd CompositeDataGeometryFilter/build 
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
./CompositeDataGeometryFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

