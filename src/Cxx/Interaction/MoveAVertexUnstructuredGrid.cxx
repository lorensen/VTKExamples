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
class InteractorStyleMoveVertex : public vtkInteractorStyleTrackballActor
{
public:
  static InteractorStyleMoveVertex* New();
  vtkTypeMacro(InteractorStyleMoveVertex,vtkInteractorStyleTrackballActor);

  InteractorStyleMoveVertex()
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
    this->MoveGlyphFilter->SetInputData(this->MovePolyData);
    this->MoveGlyphFilter->Update();

    this->MoveMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    this->MoveMapper->SetInputConnection(this->MoveGlyphFilter->GetOutputPort());

    this->MoveActor = vtkSmartPointer<vtkActor>::New();
    this->MoveActor->SetMapper(this->MoveMapper);
    this->MoveActor->VisibilityOff();
    this->MoveActor->GetProperty()->SetPointSize(10);
    this->MoveActor->GetProperty()->SetColor(1,0,0);
  }

  void OnMouseMove() override
  {
    if(!this->Move)
    {
      return;
    }

    vtkInteractorStyleTrackballActor::OnMouseMove();
  }

  void OnMiddleButtonUp() override
  {
    this->EndPan();

    this->Move = false;
    this->MoveActor->VisibilityOff();

    this->Data->GetPoints()->SetPoint(this->SelectedPoint, this->MoveActor->GetPosition());
    this->Data->Modified();
    this->GetCurrentRenderer()->Render();
    this->GetCurrentRenderer()->GetRenderWindow()->Render();
  }
  void OnMiddleButtonDown() override
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

  vtkUnstructuredGrid* Data;
  vtkPolyData* GlyphData;

  vtkSmartPointer<vtkPolyDataMapper> MoveMapper;
  vtkSmartPointer<vtkActor> MoveActor;
  vtkSmartPointer<vtkPolyData> MovePolyData;
  vtkSmartPointer<vtkVertexGlyphFilter> MoveGlyphFilter;

  vtkSmartPointer<vtkPointPicker> PointPicker;

  bool Move;
  vtkIdType SelectedPoint;
};
vtkStandardNewMacro(InteractorStyleMoveVertex);

int main (int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(2,0,0);

  vtkSmartPointer<vtkUnstructuredGrid> input =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  input->SetPoints(points);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  glyphFilter->SetInputData(input);
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

  vtkSmartPointer<InteractorStyleMoveVertex> style =
    vtkSmartPointer<InteractorStyleMoveVertex>::New();
  renderWindowInteractor->SetInteractorStyle( style );
  style->Data = input;

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
