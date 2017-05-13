[VTKExamples](Home)/[Cxx](Cxx)/Interaction/SelectAVertex

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Interaction/TestSelectAVertex.png" width="256" />

### Description
Click and drag a vertex by "ghosting" a glyph over the selected vertex and using it for the interaction.

**SelectAVertex.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPointPicker.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>
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
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkAreaPicker.h>
#include <vtkExtractGeometry.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkIdFilter.h>

// Define interaction style
class InteractorStyle2 : public vtkInteractorStyleTrackballActor
{
  public:
    static InteractorStyle2* New();
    vtkTypeMacro(InteractorStyle2,vtkInteractorStyleTrackballActor);

    InteractorStyle2()
    {
      this->Move = false;
      this->PointPicker = vtkSmartPointer<vtkPointPicker>::New();

      // Setup ghost glyph
      vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();
      points->InsertNextPoint(0,0,0);
      this->MovePolyData = vtkSmartPointer<vtkPolyData>::New();
      this->MovePolyData->SetPoints(points);
      this->MoveGlyphFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
      this->MoveGlyphFilter->SetInputConnection(
        this->MovePolyData->GetProducerPort());
#else
      this->MoveGlyphFilter->SetInputData(this->MovePolyData);
#endif
      this->MoveGlyphFilter->Update();

      this->MoveMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
      this->MoveMapper->SetInputConnection(this->MoveGlyphFilter->GetOutputPort());

      this->MoveActor = vtkSmartPointer<vtkActor>::New();
      this->MoveActor->SetMapper(this->MoveMapper);
      this->MoveActor->VisibilityOff();
      this->MoveActor->GetProperty()->SetPointSize(10);
      this->MoveActor->GetProperty()->SetColor(1,0,0);
    }

    void OnMouseMove()
    {
      if(!this->Move)
      {
        return;
      }

      vtkInteractorStyleTrackballActor::OnMouseMove();

    }

    void OnMiddleButtonUp()
    {
      this->EndPan();

      this->Move = false;
      this->MoveActor->VisibilityOff();

      this->Data->GetPoints()->SetPoint(this->SelectedPoint, this->MoveActor->GetPosition());
      this->Data->Modified();
      this->GetCurrentRenderer()->Render();
      this->GetCurrentRenderer()->GetRenderWindow()->Render();

    }
    void OnMiddleButtonDown()
    {
      // Get the selected point
      int x = this->Interactor->GetEventPosition()[0];
      int y = this->Interactor->GetEventPosition()[1];
      this->FindPokedRenderer(x, y);

      this->PointPicker->Pick(this->Interactor->GetEventPosition()[0],
                 this->Interactor->GetEventPosition()[1],
                 0,  // always zero.
                 this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

      if(this->PointPicker->GetPointId() >= 0)
      {
        this->StartPan();
        this->MoveActor->VisibilityOn();
        this->Move = true;
        this->SelectedPoint = this->PointPicker->GetPointId();

        std::cout << "Dragging point " << this->SelectedPoint << std::endl;

        double p[3];
        this->Data->GetPoint(this->SelectedPoint, p);
        std::cout << "p: " << p[0] << " " << p[1] << " " << p[2] << std::endl;
        this->MoveActor->SetPosition(p);

        this->GetCurrentRenderer()->AddActor(this->MoveActor);
        this->InteractionProp = this->MoveActor;
      }
    }

  vtkPolyData* Data;
  vtkPolyData* GlyphData;

  vtkSmartPointer<vtkPolyDataMapper> MoveMapper;
  vtkSmartPointer<vtkActor> MoveActor;
  vtkSmartPointer<vtkPolyData> MovePolyData;
  vtkSmartPointer<vtkVertexGlyphFilter> MoveGlyphFilter;

  vtkSmartPointer<vtkPointPicker> PointPicker;

  bool Move;
  vtkIdType SelectedPoint;
};
vtkStandardNewMacro(InteractorStyle2);

int main (int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(2,0,0);

  vtkSmartPointer<vtkPolyData> input =
    vtkSmartPointer<vtkPolyData>::New();
  input->SetPoints(points);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  glyphFilter->SetInputConnection(input->GetProducerPort());
#else
  glyphFilter->SetInputData(input);
#endif
  glyphFilter->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(10);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  //renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  vtkSmartPointer<InteractorStyle2> style =
    vtkSmartPointer<InteractorStyle2>::New();
  renderWindowInteractor->SetInteractorStyle( style );
  style->Data = input;

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SelectAVertex)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SelectAVertex MACOSX_BUNDLE SelectAVertex.cxx)
 
target_link_libraries(SelectAVertex ${VTK_LIBRARIES})
```

**Download and Build SelectAVertex**

Click [here to download SelectAVertex](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SelectAVertex.tar) and its *CMakeLists.txt* file.
Once the *tarball SelectAVertex.tar* has been downloaded and extracted,
```
cd SelectAVertex/build 
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
./SelectAVertex
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

