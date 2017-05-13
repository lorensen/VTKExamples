[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/EmbedPointsIntoVolume

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestEmbedPointsIntoVolume.png?raw=true" width="256" />

**EmbedPointsIntoVolume.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkGaussianSplatter.h>
#include <vtkSphereSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> input =
    vtkSmartPointer<vtkPolyData>::New();

  if(argc == 1) // Generate the data
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(.01);
    sphereSource->Update();
    input->ShallowCopy(sphereSource->GetOutput());
  }
  else // Read the data from a file
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    input->ShallowCopy(reader->GetOutput());

  }

  vtkSmartPointer<vtkGaussianSplatter> splatter =
    vtkSmartPointer<vtkGaussianSplatter>::New();
#if VTK_MAJOR_VERSION <= 5
  splatter->SetInputConnection(input->GetProducerPort());
#else
  splatter->SetInputData(input);
#endif

  unsigned int n = 200;
  splatter->SetSampleDimensions(n,n,n);
  splatter->SetRadius(.02);
  splatter->SetExponentFactor(-10);
  splatter->SetEccentricity(2);
  splatter->Update();

  vtkSmartPointer<vtkContourFilter> isoSurface =
    vtkSmartPointer<vtkContourFilter>::New();
  isoSurface->SetInputConnection(splatter->GetOutputPort());
  isoSurface->SetValue(0, .95 * splatter->GetRadius());

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(isoSurface->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(1.0, 0.3882, 0.2784);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.2, .3, .4);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(EmbedPointsIntoVolume)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(EmbedPointsIntoVolume MACOSX_BUNDLE EmbedPointsIntoVolume.cxx)
 
target_link_libraries(EmbedPointsIntoVolume ${VTK_LIBRARIES})
```

**Download and Build EmbedPointsIntoVolume**

Click [here to download EmbedPointsIntoVolume](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/EmbedPointsIntoVolume.tar) and its *CMakeLists.txt* file.
Once the *tarball EmbedPointsIntoVolume.tar* has been downloaded and extracted,
```
cd EmbedPointsIntoVolume/build 
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
./EmbedPointsIntoVolume
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

