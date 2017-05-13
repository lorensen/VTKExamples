[VTKExamples](Home)/[Cxx](Cxx)/Modelling/MarchingCubes

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Modelling/TestMarchingCubes.png" width="256" />

### Description
Creates a surface from a volume using Marching Cubes.

# Without arguments, the examples generates a voxelized  sphere with vtkVoxelModeller. '''NOTE:''' vtkVoxelModeller by default produces a VTK_BIT scalar image. Marching Cubes does not support this type. The scalar output is set to float for this example.
# To generate a surface from a DICOM series, provide a folder containing the series and specify an isovalue for the surface.

This [Midas Repository](http://placid.nlm.nih.gov/community/21) contains a number of DICOM datasets.

**MarchingCubes.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> volume =
    vtkSmartPointer<vtkImageData>::New();
  double isoValue;
  if (argc < 3)
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetPhiResolution(20);
    sphereSource->SetThetaResolution(20);
    sphereSource->Update();

    double bounds[6];
    sphereSource->GetOutput()->GetBounds(bounds);
    for (unsigned int i = 0; i < 6; i += 2)
    {
      double range = bounds[i+1] - bounds[i];
      bounds[i]   = bounds[i] - .1 * range;
      bounds[i+1] = bounds[i+1] + .1 * range;
    }
    vtkSmartPointer<vtkVoxelModeller> voxelModeller =
      vtkSmartPointer<vtkVoxelModeller>::New();
    voxelModeller->SetSampleDimensions(50,50,50);
    voxelModeller->SetModelBounds(bounds);
    voxelModeller->SetScalarTypeToFloat();
    voxelModeller->SetMaximumDistance(.1);

    voxelModeller->SetInputConnection(sphereSource->GetOutputPort());
    voxelModeller->Update();
    isoValue = 0.5;
    volume->DeepCopy(voxelModeller->GetOutput());
  }
  else
  {
    vtkSmartPointer<vtkDICOMImageReader> reader =
      vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetDirectoryName(argv[1]);
    reader->Update();
    volume->DeepCopy(reader->GetOutput());
    isoValue = atof(argv[2]);
  }

  vtkSmartPointer<vtkMarchingCubes> surface =
    vtkSmartPointer<vtkMarchingCubes>::New();

#if VTK_MAJOR_VERSION <= 5
  surface->SetInput(volume);
#else
  surface->SetInputData(volume);
#endif
  surface->ComputeNormalsOn();
  surface->SetValue(0, isoValue);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.1, .2, .3);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(surface->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  renderer->AddActor(actor);

  renderWindow->Render();
  interactor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MarchingCubes)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MarchingCubes MACOSX_BUNDLE MarchingCubes.cxx)
 
target_link_libraries(MarchingCubes ${VTK_LIBRARIES})
```

**Download and Build MarchingCubes**

Click [here to download MarchingCubes](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MarchingCubes.tar) and its *CMakeLists.txt* file.
Once the *tarball MarchingCubes.tar* has been downloaded and extracted,
```
cd MarchingCubes/build 
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
./MarchingCubes
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

