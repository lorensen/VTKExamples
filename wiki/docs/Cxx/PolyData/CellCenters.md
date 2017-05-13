[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/CellCenters

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestCellCenters.png?raw=true" width="256" />

**CellCenters.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkProperty.h>
#include <vtkCellCenters.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(3,3,2);
  imageData->SetSpacing(1.0, 1.0, 1.0);
  imageData->SetOrigin(0.0, 0.0, 0.0);

  vtkSmartPointer<vtkCellCenters> cellCentersFilter =
    vtkSmartPointer<vtkCellCenters>::New();
#if VTK_MAJOR_VERSION <= 5
  cellCentersFilter->SetInputConnection(imageData->GetProducerPort());
#else
  cellCentersFilter->SetInputData(imageData);
#endif
  cellCentersFilter->VertexCellsOn();
  cellCentersFilter->Update();

  // Access the cell centers
  for(vtkIdType i = 0; i < cellCentersFilter->GetOutput()->GetNumberOfPoints(); i++)
  {
    double p[3];
    cellCentersFilter->GetOutput()->GetPoint(i, p);
    cout << "Point " << i << " : " << p[0] << " , " << p[1] << " , " << p[2] << endl;
  }

  // Display the cell centers
  vtkSmartPointer<vtkDataSetMapper> centerMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  centerMapper->SetInputConnection(cellCentersFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> centerActor =
    vtkSmartPointer<vtkActor>::New();
  centerActor->SetMapper(centerMapper);

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(imageData->GetProducerPort());
#else
  mapper->SetInputData(imageData);
#endif
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  renderWindow->AddRenderer(renderer);

  renderer->AddActor(actor);
  renderer->AddActor(centerActor);

  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CellCenters)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CellCenters MACOSX_BUNDLE CellCenters.cxx)
 
target_link_libraries(CellCenters ${VTK_LIBRARIES})
```

**Download and Build CellCenters**

Click [here to download CellCenters](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CellCenters.tar) and its *CMakeLists.txt* file.
Once the *tarball CellCenters.tar* has been downloaded and extracted,
```
cd CellCenters/build 
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
./CellCenters
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

