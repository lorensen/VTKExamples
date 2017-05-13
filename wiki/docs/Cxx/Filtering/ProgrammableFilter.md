[VTKExamples](Home)/[Cxx](Cxx)/Filtering/ProgrammableFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Filtering/TestProgrammableFilter.png" width="256" />

**ProgrammableFilter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkProgrammableFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

struct params
{
  vtkPolyData* data;
  vtkProgrammableFilter* filter;
};

void AdjustPoints(void* arguments)
{
  params* input = static_cast<params*>(arguments);

  vtkPoints* inPts = input->data->GetPoints();
  vtkIdType numPts = inPts->GetNumberOfPoints();
  vtkSmartPointer<vtkPoints> newPts =
      vtkSmartPointer<vtkPoints>::New();
  newPts->SetNumberOfPoints(numPts);

  for(vtkIdType i = 0; i < numPts/2; i++)
  {
    double p[3];
    inPts->GetPoint(i, p);
    p[0] = p[0] + .5;
    p[1] = p[1] + .5;
    p[2] = p[2] + .5;
    newPts->SetPoint(i, p);
  }

  for(vtkIdType i = numPts/2; i < numPts; i++)
  {
    double p[3];
    inPts->GetPoint(i, p);
    p[0] = p[0] - .5;
    p[1] = p[1] - .5;
    p[2] = p[2] - .5;
    newPts->SetPoint(i, p);
  }

  input->filter->GetPolyDataOutput()->CopyStructure(input->data);
  input->filter->GetPolyDataOutput()->SetPoints(newPts);

}

int main(int, char *[])
{
  //Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkProgrammableFilter> programmableFilter =
      vtkSmartPointer<vtkProgrammableFilter>::New();
  programmableFilter->SetInputConnection(sphereSource->GetOutputPort());

  params myParams;
  myParams.data = sphereSource->GetOutput();
  myParams.filter = programmableFilter;

  programmableFilter->SetExecuteMethod(AdjustPoints, &myParams);
  programmableFilter->Update();

  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(programmableFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.4, .5, .6); // Background color white

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ProgrammableFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ProgrammableFilter MACOSX_BUNDLE ProgrammableFilter.cxx)
 
target_link_libraries(ProgrammableFilter ${VTK_LIBRARIES})
```

**Download and Build ProgrammableFilter**

Click [here to download ProgrammableFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ProgrammableFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball ProgrammableFilter.tar* has been downloaded and extracted,
```
cd ProgrammableFilter/build 
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
./ProgrammableFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

