[VTKExamples](/index/)/[Cxx](/Cxx)/Meshes/QuadricClustering

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestQuadricClustering.png?raw=true" width="256" />

**QuadricClustering.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkQuadricClustering.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> inputPolyData;
  if(argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    inputPolyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(30);
    sphereSource->SetPhiResolution(15);
    sphereSource->Update();
    inputPolyData = sphereSource->GetOutput();
  }

  std::cout << "Before decimation" << std::endl << "------------" << std::endl;
  std::cout << "There are "
            << inputPolyData->GetNumberOfPoints() << " points." << std::endl;
  std::cout << "There are "
            << inputPolyData->GetNumberOfPolys() << " polygons." << std::endl;

  vtkSmartPointer<vtkQuadricClustering> decimate =
    vtkSmartPointer<vtkQuadricClustering>::New();
#if VTK_MAJOR_VERSION <= 5
  decimate->SetInputConnection(inputPolyData->GetProducerPort());
#else
  decimate->SetInputData(inputPolyData);
#endif
  decimate->Update();

  vtkSmartPointer<vtkPolyData> decimated =
    vtkSmartPointer<vtkPolyData>::New();
  decimated->ShallowCopy(decimate->GetOutput());

  std::cout << "After decimation" << std::endl << "------------" << std::endl;

  std::cout << "There are "
            << decimated->GetNumberOfPoints() << " points." << std::endl;
  std::cout << "There are "
            << decimated->GetNumberOfPolys() << " polygons." << std::endl;

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  inputMapper->SetInputConnection(inputPolyData->GetProducerPort());
#else
  inputMapper->SetInputData(inputPolyData);
#endif
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);
  inputActor->GetProperty()->SetInterpolationToFlat();

  vtkSmartPointer<vtkPolyDataMapper> decimatedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  decimatedMapper->SetInputConnection(decimated->GetProducerPort());
#else
  decimatedMapper->SetInputData(decimated);
#endif
  vtkSmartPointer<vtkActor> decimatedActor =
    vtkSmartPointer<vtkActor>::New();
  decimatedActor->SetMapper(decimatedMapper);

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  // Add the sphere to the left and the cube to the right
  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(decimatedActor);

  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  leftRenderer->SetActiveCamera(camera);
  rightRenderer->SetActiveCamera(camera);

  leftRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(QuadricClustering)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(QuadricClustering MACOSX_BUNDLE QuadricClustering.cxx)
 
target_link_libraries(QuadricClustering ${VTK_LIBRARIES})
```

**Download and Build QuadricClustering**

Click [here to download QuadricClustering](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/QuadricClustering.tar) and its *CMakeLists.txt* file.
Once the *tarball QuadricClustering.tar* has been downloaded and extracted,
```
cd QuadricClustering/build 
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
./QuadricClustering
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

