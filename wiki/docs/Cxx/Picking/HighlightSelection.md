[VTKExamples](/index/)/[Cxx](/Cxx)/Picking/HighlightSelection

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Picking/TestHighlightSelection.png?raw=true" width="256" />

### Description
This example demonstrates how to select and highlight cells using a rubber band. Press 'r' to enter selection mode.

**HighlightSelection.cxx**
```c++
#include <vtkVersion.h>

#include <vtkActor.h>
#include <vtkAreaPicker.h>
#include <vtkDataSetMapper.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkExtractPolyDataGeometry.h>
#include <vtkIdFilter.h>
#include <vtkIdTypeArray.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkObjectFactory.h>
#include <vtkPlanes.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVersion.h>
#include <vtkVertexGlyphFilter.h>

#define VTKISRBP_ORIENT 0
#define VTKISRBP_SELECT 1

// Define interaction style
class HighlightInteractorStyle : public vtkInteractorStyleRubberBandPick
{
  public:
    static HighlightInteractorStyle* New();
    vtkTypeMacro(HighlightInteractorStyle,vtkInteractorStyleRubberBandPick);

    HighlightInteractorStyle() : vtkInteractorStyleRubberBandPick()
    {
      this->SelectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
      this->SelectedActor = vtkSmartPointer<vtkActor>::New();
      this->SelectedActor->SetMapper(SelectedMapper);
    }

    virtual void OnLeftButtonUp()
    {
      // Forward events
      vtkInteractorStyleRubberBandPick::OnLeftButtonUp();

      if(this->CurrentMode == VTKISRBP_SELECT)
      {
        vtkPlanes* frustum = static_cast<vtkAreaPicker*>(this->GetInteractor()->GetPicker())->GetFrustum();

        vtkSmartPointer<vtkExtractPolyDataGeometry> extractPolyDataGeometry =
          vtkSmartPointer<vtkExtractPolyDataGeometry>::New();
#if VTK_MAJOR_VERSION <= 5
        extractPolyDataGeometry->SetInput(this->PolyData);
#else
        extractPolyDataGeometry->SetInputData(this->PolyData);
#endif
        extractPolyDataGeometry->SetImplicitFunction(frustum);
        extractPolyDataGeometry->Update();

        std::cout << "Extracted " << extractPolyDataGeometry->GetOutput()->GetNumberOfCells() << " cells." << std::endl;

#if VTK_MAJOR_VERSION <= 5
        this->SelectedMapper->SetInputConnection(
          extractPolyDataGeometry->GetOutputPort());
#else
        this->SelectedMapper->SetInputData(extractPolyDataGeometry->GetOutput());
#endif
        this->SelectedMapper->ScalarVisibilityOff();

//        vtkIdTypeArray* ids = vtkIdTypeArray::SafeDownCast(selected->GetPointData()->GetArray("OriginalIds"));

        this->SelectedActor->GetProperty()->SetColor(1.0, 0.0, 0.0); //(R,G,B)
        this->SelectedActor->GetProperty()->SetPointSize(5);

        this->GetInteractor()->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(SelectedActor);
        this->GetInteractor()->GetRenderWindow()->Render();
        this->HighlightProp(NULL);
      }
    }

    void SetPolyData(vtkSmartPointer<vtkPolyData> polyData) {this->PolyData = polyData;}
  private:
    vtkSmartPointer<vtkPolyData> PolyData;
    vtkSmartPointer<vtkActor> SelectedActor;
    vtkSmartPointer<vtkDataSetMapper> SelectedMapper;

};
vtkStandardNewMacro(HighlightInteractorStyle);

int main (int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkIdFilter> idFilter =
    vtkSmartPointer<vtkIdFilter>::New();
  idFilter->SetInputConnection(sphereSource->GetOutputPort());
  idFilter->SetIdsArrayName("OriginalIds");
  idFilter->Update();

  // This is needed to convert the ouput of vtkIdFilter (vtkDataSet) back to vtkPolyData
  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter =
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceFilter->SetInputConnection(idFilter->GetOutputPort());
  surfaceFilter->Update();

  vtkPolyData* input = surfaceFilter->GetOutput();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(5);

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

  vtkSmartPointer<HighlightInteractorStyle> style =
    vtkSmartPointer<HighlightInteractorStyle>::New();
  style->SetPolyData(input);
  renderWindowInteractor->SetInteractorStyle( style );

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(HighlightSelection)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(HighlightSelection MACOSX_BUNDLE HighlightSelection.cxx)
 
target_link_libraries(HighlightSelection ${VTK_LIBRARIES})
```

**Download and Build HighlightSelection**

Click [here to download HighlightSelection](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/HighlightSelection.tar) and its *CMakeLists.txt* file.
Once the *tarball HighlightSelection.tar* has been downloaded and extracted,
```
cd HighlightSelection/build 
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
./HighlightSelection
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

