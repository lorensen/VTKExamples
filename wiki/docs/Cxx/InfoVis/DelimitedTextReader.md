[VTKExamples](/index/)/[Cxx](/Cxx)/InfoVis/DelimitedTextReader

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/InfoVis/TestDelimitedTextReader.png?raw=true" width="256" />

### Description
This example takes a plain text file of coordinates and normals (x y z nx ny nz) and reads them into a vtkPolyData and displays them on the screen. This can be easily changed to reading a file with any delimiter by changing the argument of <source lang="cpp">Reader->SetFieldDelimiterCharacters(" ");</source>

Here is an example file:

 0.0 0.0 0.0 1.0 2.0 3.0
 1.0 0.0 0.0 4.0 5.0 6.1
 0.0 1.0 0.0 7.2 8.3 9.4

**DelimitedTextReader.cxx**
```c++
#include <vtkVersion.h>

#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkDelimitedTextReader.h>
#include <vtkDoubleArray.h>
#include <vtkTable.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if(argc != 2)
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.xyz)" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  vtkSmartPointer<vtkDelimitedTextReader> reader =
    vtkSmartPointer<vtkDelimitedTextReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->DetectNumericColumnsOn();
  reader->SetFieldDelimiterCharacters(" ");
  reader->Update();

  vtkTable* table = reader->GetOutput();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkDoubleArray> normals =
    vtkSmartPointer<vtkDoubleArray>::New();

  normals->SetNumberOfComponents(3); //3d normals (ie x,y,z)

  std::cout << "Table has " << table->GetNumberOfRows()
            << " rows." << std::endl;
  std::cout << "Table has " << table->GetNumberOfColumns()
            << " columns." << std::endl;

  for(vtkIdType i = 0; i < table->GetNumberOfRows(); i++)
  {
    std::cout << "x: " << (table->GetValue(i,0)).ToDouble()
              << " y: " << (table->GetValue(i,1)).ToDouble()
              << " z: " << (table->GetValue(i,2)).ToDouble();

    points->InsertNextPoint((table->GetValue(i,0)).ToDouble(),
                            (table->GetValue(i,1)).ToDouble(),
                            (table->GetValue(i,2)).ToDouble());

    double n[3];
    n[0] = (table->GetValue(i,3)).ToDouble();
    n[1] = (table->GetValue(i,4)).ToDouble();
    n[2] = (table->GetValue(i,5)).ToDouble();

    std::cout << " n: " << n[0] << " " << n[1] << " " << n[2] << std::endl;
    normals->InsertNextTuple(n);
  }

  std::cout << "There are " << points->GetNumberOfPoints()
            << " points." << std::endl;

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->SetNormals(normals);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  glyphFilter->SetInputConnection(polydata->GetProducerPort());
#else
  glyphFilter->SetInputData(polydata);
#endif
  glyphFilter->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(3);
  actor->GetProperty()->SetColor(1,0,0);

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
 
PROJECT(DelimitedTextReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DelimitedTextReader MACOSX_BUNDLE DelimitedTextReader.cxx)
 
target_link_libraries(DelimitedTextReader ${VTK_LIBRARIES})
```

**Download and Build DelimitedTextReader**

Click [here to download DelimitedTextReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DelimitedTextReader.tar) and its *CMakeLists.txt* file.
Once the *tarball DelimitedTextReader.tar* has been downloaded and extracted,
```
cd DelimitedTextReader/build 
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
./DelimitedTextReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

