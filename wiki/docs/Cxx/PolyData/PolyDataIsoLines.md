[VTKExamples](Home)/[Cxx](Cxx)/PolyData/PolyDataIsoLines

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/PolyData/TestPolyDataIsoLines.png" width="256" />

**PolyDataIsoLines.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkCamera.h>
#include <vtkBandedPolyDataContourFilter.h>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cout << "Required arguments: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  //float range[2];
  double range[2];
  reader->GetOutput()->GetPointData()->GetScalars()->GetRange(range);
  //std::cout << "Range: " << range[0] << " , " << range[1] << std::endl;

  vtkSmartPointer<vtkBandedPolyDataContourFilter> bf =
    vtkSmartPointer<vtkBandedPolyDataContourFilter>::New();
  bf->SetInputConnection(reader->GetOutputPort());
  int numContours = 30;
  bf->GenerateValues(numContours, range);
  bf->GenerateContourEdgesOn();
  bf->Update();

  // Color the contours
  bf->GetOutput(1)->GetPointData()->SetScalars(bf->GetOutput()->GetPointData()->GetScalars());

  // Make sure the mapper uses the new colors
  bf->GetOutput(0)->GetPointData()->SetActiveScalars("Scalars");

  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(bf->GetOutputPort());
  writer->SetFileName("output.vtp");
  writer->Update();
  }

  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(bf->GetOutputPort(1));
  writer->SetFileName("ContourEdges.vtp");
  writer->Update();
  }

  /*
  // See which isocontours are being generated
  double values[10];
  bf->GetValues(values);
  for(unsigned int i = 0; i < 10; i++)
    {
    cout << values[i] << " ";
    }
  cout << endl;
  */


  // Color actor
  vtkSmartPointer<vtkPolyDataMapper> colorMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  colorMapper->SetInputConnection(bf->GetOutputPort(0));
  colorMapper->SetScalarRange(range);

  vtkSmartPointer<vtkActor> colorActor =
    vtkSmartPointer<vtkActor>::New();
  colorActor->SetMapper(colorMapper);

  // Edge actor
  vtkSmartPointer<vtkPolyDataMapper> edgeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  edgeMapper->SetInputConnection(bf->GetOutputPort(1));
  edgeMapper->SetScalarRange(range);

  vtkSmartPointer<vtkActor> edgeActor =
      vtkSmartPointer<vtkActor>::New();
  edgeActor->SetMapper(edgeMapper);

  // Create the RenderWindow, Renderer and both Actors

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer
  renderer->AddActor(colorActor);
  renderer->AddActor(edgeActor);

  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolyDataIsoLines)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataIsoLines MACOSX_BUNDLE PolyDataIsoLines.cxx)
 
target_link_libraries(PolyDataIsoLines ${VTK_LIBRARIES})
```

**Download and Build PolyDataIsoLines**

Click [here to download PolyDataIsoLines](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataIsoLines.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataIsoLines.tar* has been downloaded and extracted,
```
cd PolyDataIsoLines/build 
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
./PolyDataIsoLines
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

