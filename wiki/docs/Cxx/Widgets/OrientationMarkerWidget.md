[VTKExamples](Home)/[Cxx](Cxx)/Widgets/OrientationMarkerWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestOrientationMarkerWidget.png" width="256" />

### Description
This example uses a polydata as an orientation icon. You can get the bunny data [here](https://gitlab.kitware.com/lorensen/VTKExamples/raw/master/Testing/Data/Bunny.vtp).

**OrientationMarkerWidget.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkSuperquadricSource.h>

int main (int argc, char *argv[] )
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " Filename(.vtp)" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the polydata for the icon
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkDataSetMapper> iconMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  iconMapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> iconActor =
    vtkSmartPointer<vtkActor>::New();
  iconActor->SetMapper(iconMapper);

  // Set up the renderer, window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground( 0.0980, 0.0980, 0.4392 );

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer( renderer );
  renWin->SetSize( 400, 400 );

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow( renWin );

  // Set up the widget
  vtkSmartPointer<vtkOrientationMarkerWidget> widget =
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
  widget->SetOrientationMarker( iconActor );
  widget->SetInteractor( iren );
  widget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
  widget->SetEnabled( 1 );
  widget->InteractiveOn();

  // Create a superquadric
  vtkSmartPointer<vtkSuperquadricSource> superquadricSource =
    vtkSmartPointer<vtkSuperquadricSource>::New();
  superquadricSource->SetPhiRoundness(.2);
  superquadricSource->SetThetaRoundness(.8);

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> superquadricMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  superquadricMapper->SetInputConnection(superquadricSource->GetOutputPort());

  vtkSmartPointer<vtkActor> superquadricActor =
    vtkSmartPointer<vtkActor>::New();
  superquadricActor->SetMapper(superquadricMapper);
  superquadricActor->GetProperty()->SetInterpolationToFlat();
  superquadricActor->GetProperty()->SetDiffuseColor(0.93, 0.57, 0.13);
  superquadricActor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);
  superquadricActor->GetProperty()->SetDiffuse(.6);
  superquadricActor->GetProperty()->SetSpecular(.5);
  superquadricActor->GetProperty()->SetSpecularPower(5.0);

  renderer->AddActor(superquadricActor);
  renderer->ResetCamera();

  renWin->Render();

  iren->Initialize();

  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(OrientationMarkerWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(OrientationMarkerWidget MACOSX_BUNDLE OrientationMarkerWidget.cxx)
 
target_link_libraries(OrientationMarkerWidget ${VTK_LIBRARIES})
```

**Download and Build OrientationMarkerWidget**

Click [here to download OrientationMarkerWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/OrientationMarkerWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball OrientationMarkerWidget.tar* has been downloaded and extracted,
```
cd OrientationMarkerWidget/build 
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
./OrientationMarkerWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

