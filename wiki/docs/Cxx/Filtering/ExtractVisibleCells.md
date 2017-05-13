[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/ExtractVisibleCells

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestExtractVisibleCells.png?raw=true" width="256" />

**ExtractVisibleCells.cxx**
```c++
#include <vtkVersion.h>

#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkHardwareSelector.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkRendererCollection.h>
#include <vtkDataSetMapper.h>
#include <vtkExtractSelection.h>
#include <vtkSelection.h>
#include <vtkProperty.h>

// Define interaction style
class KeyPressInteractorStyle : public vtkInteractorStyleTrackballCamera
{
  public:
    static KeyPressInteractorStyle* New();
    vtkTypeMacro(KeyPressInteractorStyle, vtkInteractorStyleTrackballCamera);

    virtual void OnKeyPress()
    {
      // Get the keypress
      std::string key = this->Interactor->GetKeySym();

      // "s" for "s"elect
      if(key.compare("s") == 0)
      {
        vtkSmartPointer<vtkHardwareSelector> selector =
          vtkSmartPointer<vtkHardwareSelector>::New();
        selector->SetRenderer(this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
        int* temp = this->Interactor->GetRenderWindow()->GetSize();
        unsigned int windowSize[4];
        windowSize[0] = temp[2];
        windowSize[1] = temp[3];
        windowSize[2] = temp[0];
        windowSize[3] = temp[1];
        /*
        for(unsigned int i = 0; i < 4; i++)
          {
          windowSize[i] = temp[i];
          }
        */
        selector->SetArea(windowSize);
        selector->SetFieldAssociation(vtkDataObject::FIELD_ASSOCIATION_CELLS);
        vtkSelection* selection = selector->Select();
        std::cout << "Selection has " << selection->GetNumberOfNodes() << " nodes." << std::endl;

        vtkSmartPointer<vtkExtractSelection> extractSelection =
          vtkSmartPointer<vtkExtractSelection>::New();
#if VTK_MAJOR_VERSION <= 5
        extractSelection->SetInput(0, this->Data);
        extractSelection->SetInput(1, selection);
#else
        extractSelection->SetInputData(0, this->Data);
        extractSelection->SetInputData(1, selection);
#endif
        extractSelection->Update();

        vtkSmartPointer<vtkDataSetMapper> mapper =
          vtkSmartPointer<vtkDataSetMapper>::New();
        mapper->SetInputConnection(extractSelection->GetOutputPort());

        vtkSmartPointer<vtkActor> actor =
          vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(1,0,0);
        this->Renderer->AddActor(actor);

      }

      // Forward events
      vtkInteractorStyleTrackballCamera::OnKeyPress();
    }

    vtkPolyData* Data;
    vtkRenderer* Renderer;

};
vtkStandardNewMacro(KeyPressInteractorStyle);

int main(int , char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetMultiSamples(0); // Turn off anti-aliasing
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<KeyPressInteractorStyle> style =
    vtkSmartPointer<KeyPressInteractorStyle>::New();
  style->Renderer = renderer;
  renderWindowInteractor->SetInteractorStyle(style);
  style->SetCurrentRenderer(renderer);
  style->Data = sphereSource->GetOutput();

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractVisibleCells)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractVisibleCells MACOSX_BUNDLE ExtractVisibleCells.cxx)
 
target_link_libraries(ExtractVisibleCells ${VTK_LIBRARIES})
```

**Download and Build ExtractVisibleCells**

Click [here to download ExtractVisibleCells](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractVisibleCells.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractVisibleCells.tar* has been downloaded and extracted,
```
cd ExtractVisibleCells/build 
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
./ExtractVisibleCells
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

