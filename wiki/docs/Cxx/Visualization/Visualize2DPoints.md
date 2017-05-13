[VTKExamples](Home)/[Cxx](Cxx)/Visualization/Visualize2DPoints

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestVisualize2DPoints.png" width="256" />

### Description
This example shows how to render a set of points. The example reads the points from a vtp file specified as the first command line argument. An example data set can be found [here](http://www.vtk.org/Wiki/Image:Ring.vtp).

**Visualize2DPoints.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkActor2D.h>
#include <vtkMath.h>
#include <vtkProperty2D.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cout << "Required parameters: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();
  vtkPolyData* polydata = reader->GetOutput();
  //vtkPoints* Points = Polydata->GetPoints();

  vtkSmartPointer<vtkActor2D> actor =
    vtkSmartPointer<vtkActor2D>::New();
  double color[3] = {1,1,1};

  vtkSmartPointer<vtkPolyDataMapper2D> mapper =
    vtkSmartPointer<vtkPolyDataMapper2D>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput( polydata );
#else
  mapper->SetInputData( polydata );
#endif
  mapper->ScalarVisibilityOff();
  actor->SetMapper( mapper );

  vtkProperty2D *property2D = actor->GetProperty();
  property2D->SetColor( color );
  property2D->SetPointSize( 2.0 );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  // Renderer and RenderWindow
  renderer->SetBackground( 0, 0, 0);
  renderer->ResetCamera();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  renderWindow->SetSize( 200,200 );
  renderWindow->AddRenderer( renderer );
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Visualize2DPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Visualize2DPoints MACOSX_BUNDLE Visualize2DPoints.cxx)
 
target_link_libraries(Visualize2DPoints ${VTK_LIBRARIES})
```

**Download and Build Visualize2DPoints**

Click [here to download Visualize2DPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Visualize2DPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball Visualize2DPoints.tar* has been downloaded and extracted,
```
cd Visualize2DPoints/build 
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
./Visualize2DPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

