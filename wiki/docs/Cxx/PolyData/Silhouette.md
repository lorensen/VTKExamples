[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/Silhouette

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestSilhouette.png?raw=true" width="256" />

**Silhouette.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataSilhouette.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkCleanPolyData.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData;
  if (argc < 2)
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();

    polyData = sphereSource->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);

    vtkSmartPointer<vtkCleanPolyData> clean =
      vtkSmartPointer<vtkCleanPolyData>::New();
    clean->SetInputConnection(reader->GetOutputPort());
    clean->Update();

    polyData = clean->GetOutput();
  }

  //create mapper and actor for original model
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput(polyData);
#else
  mapper->SetInputData(polyData);
#endif

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetInterpolationToFlat();

  //create renderer and renderWindow
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  renderer->AddActor(actor); //view the original model

  //Compute the silhouette
  vtkSmartPointer<vtkPolyDataSilhouette> silhouette =
    vtkSmartPointer<vtkPolyDataSilhouette>::New();
#if VTK_MAJOR_VERSION <= 5
  silhouette->SetInput(polyData);
#else
  silhouette->SetInputData(polyData);
#endif
  silhouette->SetCamera(renderer->GetActiveCamera());
  silhouette->SetEnableFeatureAngle(0);

  //create mapper and actor for silouette
  vtkSmartPointer<vtkPolyDataMapper> mapper2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper2->SetInputConnection(silhouette->GetOutputPort());

  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);
  actor2->GetProperty()->SetColor(1.0, 0.3882, 0.2784); // tomato
  actor2->GetProperty()->SetLineWidth(5);
  renderer->AddActor(actor2);
  renderer->SetBackground(.1, .2, .3);
  renderer->ResetCamera();

  //you MUST NOT call renderWindow->Render() before
  //iren->SetRenderWindow(renderWindow);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renderWindow);

  //render and interact
  renderWindow->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Silhouette)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Silhouette MACOSX_BUNDLE Silhouette.cxx)
 
target_link_libraries(Silhouette ${VTK_LIBRARIES})
```

**Download and Build Silhouette**

Click [here to download Silhouette](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Silhouette.tar) and its *CMakeLists.txt* file.
Once the *tarball Silhouette.tar* has been downloaded and extracted,
```
cd Silhouette/build 
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
./Silhouette
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

