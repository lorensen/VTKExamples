#include <vtkSmartPointer.h>
#include <vtkCellPicker.h>
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
class InteractorStyleMoveGlyph : public vtkInteractorStyleTrackballActor
{
public:
  static InteractorStyleMoveGlyph* New();
  vtkTypeMacro(InteractorStyleMoveGlyph,vtkInteractorStyleTrackballActor);

  InteractorStyleMoveGlyph()
  {
    this->MoveSphereSource = vtkSmartPointer<vtkSphereSource>::New();
    this->MoveSphereSource->SetRadius(.1);
    this->MoveSphereSource->Update();

    this->MoveMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    this->MoveMapper->SetInputConnection(this->MoveSphereSource->GetOutputPort());

    this->MoveActor = vtkSmartPointer<vtkActor>::New();
    this->MoveActor->SetMapper(this->MoveMapper);
    //this->MoveActor->VisibilityOff();

    this->Move = false;
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
    // Forward events
    vtkInteractorStyleTrackballActor::OnMiddleButtonUp();
    this->Move = false;
    this->MoveActor->VisibilityOff();

    this->Data->GetPoints()->SetPoint(this->SelectedPoint, this->MoveActor->GetPosition());
    this->Data->Modified();
    this->GetCurrentRenderer()->Render();
    this->GetCurrentRenderer()->GetRenderWindow()->Render();
  }
  void OnMiddleButtonDown() override
  {
    // Forward events
    vtkInteractorStyleTrackballActor::OnMiddleButtonDown();
    this->MoveActor->VisibilityOn();
    if(static_cast<vtkCellPicker*>(this->InteractionPicker)->GetPointId() >= 0)
    {
      vtkIdType id = dynamic_cast<vtkIdTypeArray*>(this->GlyphData->GetPointData()->GetArray("InputPointIds"))
        ->GetValue(static_cast<vtkCellPicker*>(this->InteractionPicker)->GetPointId());
      std::cout << "Id: " << id << std::endl;
      this->Move = true;
      this->SelectedPoint = id;

      double p[3];
      this->Data->GetPoint(id, p);
      std::cout << "p: " << p[0] << " " << p[1] << " " << p[2] << std::endl;
      this->MoveActor->SetPosition(p);
    }

    this->GetCurrentRenderer()->AddActor(this->MoveActor);
    this->InteractionProp = this->MoveActor;

  }
  vtkPolyData* Data;
  vtkPolyData* GlyphData;

  vtkSmartPointer<vtkPolyDataMapper> MoveMapper;
  vtkSmartPointer<vtkActor> MoveActor;
  vtkSmartPointer<vtkSphereSource> MoveSphereSource;

  bool Move;
  vtkIdType SelectedPoint;
};
vtkStandardNewMacro(InteractorStyleMoveGlyph);

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

  vtkSmartPointer<vtkSphereSource> glyphSource =
    vtkSmartPointer<vtkSphereSource>::New();
  glyphSource->SetRadius(.1);
  glyphSource->Update();

  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph3D->GeneratePointIdsOn();
  glyph3D->SetSourceConnection(glyphSource->GetOutputPort());
  glyph3D->SetInputData(input);
  glyph3D->SetScaleModeToDataScalingOff();
  glyph3D->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyph3D->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

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

  vtkSmartPointer<InteractorStyleMoveGlyph> style =
    vtkSmartPointer<InteractorStyleMoveGlyph>::New();
  renderWindowInteractor->SetInteractorStyle( style );
  style->Data = input;
  style->GlyphData = glyph3D->GetOutput();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
