[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/MeshQuality

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestMeshQuality.png?raw=true" width="256" />

### Description
This example uses one of many selectable methods to determine the quality of a mesh. In this case, we have selected to use the area of the triangles. We show how to retrieve the quality metric computed on each triangle after the process is completed.

**MeshQuality.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkDataSet.h>
#include <vtkMeshQuality.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(sphereSource->GetOutputPort());
  triangleFilter->Update();

  vtkPolyData* mesh = triangleFilter->GetOutput();
  std::cout << "There are " << mesh->GetNumberOfCells() << " cells." << std::endl;

  vtkSmartPointer<vtkMeshQuality> qualityFilter =
    vtkSmartPointer<vtkMeshQuality>::New();
#if VTK_MAJOR_VERSION <= 5
  qualityFilter->SetInputConnection(mesh->GetProducerPort());
#else
  qualityFilter->SetInputData(mesh);
#endif
  qualityFilter->SetTriangleQualityMeasureToArea();
  qualityFilter->Update();

  vtkSmartPointer<vtkDoubleArray> qualityArray =
    vtkDoubleArray::SafeDownCast(qualityFilter->GetOutput()->GetCellData()->GetArray("Quality"));

  std::cout << "There are " << qualityArray->GetNumberOfTuples() << " values." << std::endl;

  for(vtkIdType i = 0; i < qualityArray->GetNumberOfTuples(); i++)
  {
    double val = qualityArray->GetValue(i);
    std::cout << "value " << i << " : " << val << std::endl;
  }

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->ShallowCopy(qualityFilter->GetOutput());

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(polydata->GetProducerPort());
#else
  mapper->SetInputData(polydata);
#endif
  mapper->SetScalarRange(polydata->GetScalarRange());

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
 
PROJECT(MeshQuality)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MeshQuality MACOSX_BUNDLE MeshQuality.cxx)
 
target_link_libraries(MeshQuality ${VTK_LIBRARIES})
```

**Download and Build MeshQuality**

Click [here to download MeshQuality](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MeshQuality.tar) and its *CMakeLists.txt* file.
Once the *tarball MeshQuality.tar* has been downloaded and extracted,
```
cd MeshQuality/build 
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
./MeshQuality
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

