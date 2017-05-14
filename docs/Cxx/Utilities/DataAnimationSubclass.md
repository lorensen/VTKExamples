[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/DataAnimationSubclass

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Utilities/TestDataAnimationSubclass.png?raw=true" width="256" />

**DataAnimationSubclass.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProgrammableFilter.h>
#include <vtkCommand.h>

class CommandSubclass : public vtkCommand
{
  public:
  vtkTypeMacro(CommandSubclass, vtkCommand);
  static CommandSubclass *New()
  {
    return new CommandSubclass;
  }

  void Execute(vtkObject *caller, unsigned long vtkNotUsed(eventId),
                       void *vtkNotUsed(callData))
  {
    std::cout << "timer callback" << std::endl;

    vtkRenderWindowInteractor *iren =
      static_cast<vtkRenderWindowInteractor*>(caller);

    this->ProgrammableFilter->Modified();

    iren->Render();

  }

  vtkSmartPointer<vtkProgrammableFilter> ProgrammableFilter;

};

unsigned int counter; //global

void AdjustPoints(void* arguments)
{
  std::cout << "AdjustPoints" << std::endl;
  vtkProgrammableFilter* programmableFilter =
      static_cast<vtkProgrammableFilter*>(arguments);

  vtkPoints* inPts = programmableFilter->GetPolyDataInput()->GetPoints();
  vtkIdType numPts = inPts->GetNumberOfPoints();
  vtkSmartPointer<vtkPoints> newPts =
      vtkSmartPointer<vtkPoints>::New();
  newPts->SetNumberOfPoints(numPts);

  for(vtkIdType i = 0; i < numPts; i++)
  {
    double p[3];
    inPts->GetPoint(i, p);
    newPts->SetPoint(i, p);
  }

  double p0[3];
  inPts->GetPoint(0, p0);
  p0[2] = p0[2] + counter * 0.1;
  newPts->SetPoint(0, p0);

  programmableFilter->GetPolyDataOutput()->CopyStructure(programmableFilter->GetPolyDataInput());
  programmableFilter->GetPolyDataOutput()->SetPoints(newPts);
  counter++;
}

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkProgrammableFilter> programmableFilter =
    vtkSmartPointer<vtkProgrammableFilter>::New();
  programmableFilter->SetInputConnection(sphereSource->GetOutputPort());
  programmableFilter->SetExecuteMethod(AdjustPoints, programmableFilter);

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(programmableFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Initialize must be called prior to creating timer events.
  renderWindowInteractor->Initialize();
  renderWindowInteractor->CreateRepeatingTimer(500);

  vtkSmartPointer<CommandSubclass> timerCallback =
    vtkSmartPointer<CommandSubclass>::New();
  timerCallback->ProgrammableFilter = programmableFilter;

  renderWindowInteractor->AddObserver ( vtkCommand::TimerEvent, timerCallback );

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DataAnimationSubclass)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DataAnimationSubclass MACOSX_BUNDLE DataAnimationSubclass.cxx)
 
target_link_libraries(DataAnimationSubclass ${VTK_LIBRARIES})
```

**Download and Build DataAnimationSubclass**

Click [here to download DataAnimationSubclass](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DataAnimationSubclass.tar) and its *CMakeLists.txt* file.
Once the *tarball DataAnimationSubclass.tar* has been downloaded and extracted,
```
cd DataAnimationSubclass/build 
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
./DataAnimationSubclass
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

