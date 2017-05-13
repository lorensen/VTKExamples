[VTKExamples](/home/)/[Cxx](/Cxx)/Picking/HighlightSelectedPoints

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Picking/TestHighlightSelectedPoints.png?raw=true" width="256" />

### Description
This example demonstrates how to select and highlight points using a rubber band. Press 'r' to enter selection mode. Selected points are shown in red. The ids of the selected points are output.

**HighlightSelectedPoints.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkIdTypeArray.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkRendererCollection.h>
#include <vtkProperty.h>
#include <vtkPlanes.h>
#include <vtkObjectFactory.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkPointSource.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkAreaPicker.h>
#include <vtkExtractGeometry.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkIdFilter.h>

// Define interaction style
class InteractorStyle : public vtkInteractorStyleRubberBandPick
{
  public:
    static InteractorStyle* New();
    vtkTypeMacro(InteractorStyle,vtkInteractorStyleRubberBandPick);

    InteractorStyle()
    {
      this->SelectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
      this->SelectedActor = vtkSmartPointer<vtkActor>::New();
      this->SelectedActor->SetMapper(SelectedMapper);
    }

    virtual void OnLeftButtonUp()
    {
      // Forward events
      vtkInteractorStyleRubberBandPick::OnLeftButtonUp();

      vtkPlanes* frustum = static_cast<vtkAreaPicker*>(this->GetInteractor()->GetPicker())->GetFrustum();

      vtkSmartPointer<vtkExtractGeometry> extractGeometry =
        vtkSmartPointer<vtkExtractGeometry>::New();
      extractGeometry->SetImplicitFunction(frustum);
#if VTK_MAJOR_VERSION <= 5
      extractGeometry->SetInput(this->Points);
#else
      extractGeometry->SetInputData(this->Points);
#endif
      extractGeometry->Update();

      vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
        vtkSmartPointer<vtkVertexGlyphFilter>::New();
      glyphFilter->SetInputConnection(extractGeometry->GetOutputPort());
      glyphFilter->Update();

      vtkPolyData* selected = glyphFilter->GetOutput();
      std::cout << "Selected " << selected->GetNumberOfPoints() << " points." << std::endl;
      std::cout << "Selected " << selected->GetNumberOfCells() << " cells." << std::endl;
#if VTK_MAJOR_VERSION <= 5
      this->SelectedMapper->SetInput(selected);
#else
      this->SelectedMapper->SetInputData(selected);
#endif
      this->SelectedMapper->ScalarVisibilityOff();

      vtkIdTypeArray* ids = vtkIdTypeArray::SafeDownCast(selected->GetPointData()->GetArray("OriginalIds"));
      for(vtkIdType i = 0; i < ids->GetNumberOfTuples(); i++)
      {
        std::cout << "Id " << i << " : " << ids->GetValue(i) << std::endl;
      }

      this->SelectedActor->GetProperty()->SetColor(1.0, 0.0, 0.0); //(R,G,B)
      this->SelectedActor->GetProperty()->SetPointSize(3);

      this->CurrentRenderer->AddActor(SelectedActor);
      this->GetInteractor()->GetRenderWindow()->Render();
      this->HighlightProp(NULL);
    }

    void SetPoints(vtkSmartPointer<vtkPolyData> points) {this->Points = points;}
  private:
    vtkSmartPointer<vtkPolyData> Points;
    vtkSmartPointer<vtkActor> SelectedActor;
    vtkSmartPointer<vtkDataSetMapper> SelectedMapper;

};
vtkStandardNewMacro(InteractorStyle);

int main (int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(20);
  pointSource->Update();

  vtkSmartPointer<vtkIdFilter> idFilter =
    vtkSmartPointer<vtkIdFilter>::New();
  idFilter->SetInputConnection(pointSource->GetOutputPort());
  idFilter->SetIdsArrayName("OriginalIds");
  idFilter->Update();

  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter =
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceFilter->SetInputConnection(idFilter->GetOutputPort());
  surfaceFilter->Update();

  vtkPolyData* input = surfaceFilter->GetOutput();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(input->GetProducerPort());
#else
  mapper->SetInputData(input);
#endif
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkAreaPicker> areaPicker =
    vtkSmartPointer<vtkAreaPicker>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetPicker(areaPicker);
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  //renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  vtkSmartPointer<InteractorStyle> style =
    vtkSmartPointer<InteractorStyle>::New();
  style->SetPoints(input);
  renderWindowInteractor->SetInteractorStyle( style );

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(HighlightSelectedPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(HighlightSelectedPoints MACOSX_BUNDLE HighlightSelectedPoints.cxx)
 
target_link_libraries(HighlightSelectedPoints ${VTK_LIBRARIES})
```

**Download and Build HighlightSelectedPoints**

Click [here to download HighlightSelectedPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/HighlightSelectedPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball HighlightSelectedPoints.tar* has been downloaded and extracted,
```
cd HighlightSelectedPoints/build 
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
./HighlightSelectedPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

