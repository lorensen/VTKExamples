[VTKExamples](Home)/[Cxx](Cxx)/Meshes/Subdivision

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Meshes/TestSubdivision.png" width="256" />

### Description
In this example a mesh is read from a file and then subdivided using linear subdivision.  The SetNumberOfSubdivisions(n) function controls how many times the mesh is subdivided. For each n, the number of triangles will increase by approximately a factor of 4. For example, if n=2, the number of triangles in the resulting mesh will be 16x the number of triangles in the original mesh. 

Different types of subdivisions can be obtained by replacing vtkLinearSubdivisionFilter with either vtkLoopSubdivisionFilter or vtkButterflySubdivisionFilter.

**Subdivision.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkCellData.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkTriangle.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <string>

#include <vtkButterflySubdivisionFilter.h>
#include <vtkLoopSubdivisionFilter.h>
#include <vtkLinearSubdivisionFilter.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> originalMesh;

  if(argc > 1) //If a file name is specified, open and use the file.
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);

    // Subdivision filters only work on triangles
    vtkSmartPointer<vtkTriangleFilter> triangles =
      vtkSmartPointer<vtkTriangleFilter>::New();
    triangles->SetInputConnection(reader->GetOutputPort());
    triangles->Update();
    originalMesh = triangles->GetOutput();
  }
  else //If a file name is not specified, create a sphere
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();
    originalMesh = sphereSource->GetOutput();
  }

  std::cout << "Before subdivision" << std::endl;
  std::cout << "    There are " << originalMesh->GetNumberOfPoints()
            << " points." << std::endl;
  std::cout << "    There are " << originalMesh->GetNumberOfPolys()
            << " triangles." << std::endl;

  double numberOfViewports = 3.;

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(200* numberOfViewports,200); //(width, height)

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();

  renderWindowInteractor->SetRenderWindow(renderWindow);


  int numberOfSubdivisions = 2;
  for(unsigned i = 0; i < numberOfViewports; i++)
  {
    // Note: Here we create a superclass pointer (vtkPolyDataAlgorithm) so that we can easily instantiate different
    // types of subdivision filters. Typically you would not want to do this, but rather create the pointer to be the type
    // filter you will actually use, e.g.
    // vtkSmartPointer<vtkLinearSubdivisionFilter>  subdivisionFilter = vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
    vtkSmartPointer<vtkPolyDataAlgorithm> subdivisionFilter;
    switch(i)
    {
      case 0:
        subdivisionFilter = vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
        dynamic_cast<vtkLinearSubdivisionFilter *> (subdivisionFilter.GetPointer())->SetNumberOfSubdivisions(numberOfSubdivisions);
        break;
      case 1:
        subdivisionFilter =  vtkSmartPointer<vtkLoopSubdivisionFilter>::New();
        dynamic_cast<vtkLoopSubdivisionFilter *> (subdivisionFilter.GetPointer())->SetNumberOfSubdivisions(numberOfSubdivisions);
        break;
      case 2:
        subdivisionFilter = vtkSmartPointer<vtkButterflySubdivisionFilter>::New();
        dynamic_cast<vtkButterflySubdivisionFilter *> (subdivisionFilter.GetPointer())->SetNumberOfSubdivisions(numberOfSubdivisions);
        break;
      default:
        break;
    }
#if VTK_MAJOR_VERSION <= 5
    subdivisionFilter->SetInputConnection(originalMesh->GetProducerPort());
#else
    subdivisionFilter->SetInputData(originalMesh);
#endif
    subdivisionFilter->Update();

    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();

    renderWindow->AddRenderer(renderer);
    renderer->SetViewport(static_cast<double>(i)/numberOfViewports,0,static_cast<double>(i+1)/numberOfViewports,1);

    //Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(subdivisionFilter->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
    renderer->ResetCamera();

    renderWindow->Render();
    renderWindow->SetWindowName("Multiple ViewPorts");

  }

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Subdivision)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Subdivision MACOSX_BUNDLE Subdivision.cxx)
 
target_link_libraries(Subdivision ${VTK_LIBRARIES})
```

**Download and Build Subdivision**

Click [here to download Subdivision](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Subdivision.tar) and its *CMakeLists.txt* file.
Once the *tarball Subdivision.tar* has been downloaded and extracted,
```
cd Subdivision/build 
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
./Subdivision
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

