[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/ExtractPolyLinesFromPolyData

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestExtractPolyLinesFromPolyData.png?raw=true" width="256" />

### Description
This example uses vtkCutter to create contour lines. It processes these lines with vtkStripper to create continuous poly lines. After exiting the example with the "e" key, the lines are printed.

**ExtractPolyLinesFromPolyData.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkStripper.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkSphereSource.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkSphereSource> modelSource =
    vtkSmartPointer<vtkSphereSource>::New();

  vtkSmartPointer<vtkPlane> plane =
    vtkSmartPointer<vtkPlane>::New();

  vtkSmartPointer<vtkCutter> cutter =
    vtkSmartPointer<vtkCutter>::New();
  cutter->SetInputConnection(modelSource->GetOutputPort());
  cutter->SetCutFunction(plane);
  cutter->GenerateValues(10, -.5, .5);

  vtkSmartPointer<vtkPolyDataMapper> modelMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  modelMapper->SetInputConnection(modelSource->GetOutputPort());

  vtkSmartPointer<vtkActor> model =
    vtkSmartPointer<vtkActor>::New();
  model->SetMapper(modelMapper);

  vtkSmartPointer<vtkStripper> stripper =
    vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputConnection(cutter->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> linesMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  linesMapper->SetInputConnection(stripper->GetOutputPort());

  vtkSmartPointer<vtkActor> lines =
    vtkSmartPointer<vtkActor>::New();
  lines->SetMapper(linesMapper);
  lines->GetProperty()->SetDiffuseColor(.2, .2, .2);

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();

  renWin->AddRenderer(ren);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer
  ren->AddActor(model);
  ren->AddActor(lines);
  ren->SetBackground(0.1, 0.2, 0.4);

  // This starts the event loop and as a side effect causes an initial
  // render.
  renWin->Render();
  iren->Start();


  // Extract the lines from the polydata
  vtkIdType numberOfLines = cutter->GetOutput()->GetNumberOfLines();


  std::cout << "-----------Lines without using vtkStripper" << std::endl;
  std::cout << "There are "
            << numberOfLines
            << " lines in the polydata" << std::endl;

  numberOfLines = stripper->GetOutput()->GetNumberOfLines();
  vtkPoints *points = stripper->GetOutput()->GetPoints();
  vtkCellArray *cells = stripper->GetOutput()->GetLines();

  std::cout << "-----------Lines using vtkStripper" << std::endl;
  std::cout << "There are "
            << numberOfLines
            << " lines in the polydata" << std::endl;

  vtkIdType *indices;
  vtkIdType numberOfPoints;
  unsigned int lineCount = 0;
  for (cells->InitTraversal();
       cells->GetNextCell(numberOfPoints, indices);
       lineCount++)
  {
    std::cout << "Line " << lineCount << ": " << std::endl;
    for (vtkIdType i = 0; i < numberOfPoints; i++)
    {
      double point[3];
      points->GetPoint(indices[i], point);
      std::cout << "\t("
                << point[0] << ", "
                << point[1] << ", "
                << point[2] << ")" << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractPolyLinesFromPolyData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractPolyLinesFromPolyData MACOSX_BUNDLE ExtractPolyLinesFromPolyData.cxx)
 
target_link_libraries(ExtractPolyLinesFromPolyData ${VTK_LIBRARIES})
```

**Download and Build ExtractPolyLinesFromPolyData**

Click [here to download ExtractPolyLinesFromPolyData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractPolyLinesFromPolyData.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractPolyLinesFromPolyData.tar* has been downloaded and extracted,
```
cd ExtractPolyLinesFromPolyData/build 
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
./ExtractPolyLinesFromPolyData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

