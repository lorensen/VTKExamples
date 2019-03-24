#include <vtkAbstractPicker.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCoordinate.h>
#include <vtkFollower.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkCoordinate.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyDataMapper2D.h>

#include <vtkInteractorStyleImage.h>
#include <vtkObjectFactory.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkVectorText.h>
#include <vtkMath.h>
#include <sstream>

class MyStyle : public vtkInteractorStyleImage
{
public:
  static MyStyle* New();
  vtkTypeMacro(MyStyle, vtkInteractorStyleImage);

  std::vector<vtkActor2D*> Numbers;

  void OnLeftButtonDown() override
  {
    this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                                        this->Interactor->GetEventPosition()[1],
                                        0,  // always zero.
                                        this->CurrentRenderer );
    double picked[3];
    this->Interactor->GetPicker()->GetPickPosition(picked);
    this->AddNumber(picked);

    // Forward events
    vtkInteractorStyleImage::OnLeftButtonDown();

    //this->Interactor->GetRenderWindow()->Render();
    this->Interactor->Render();
  }

  void AddNumber(double p[3])
  {
    std::cout << "Adding marker at " << p[0] << " " << p[1] ;//<< std::endl;

    // normally, with an image you would do
    // double* s = image->GetSpacing();
    // double* o = image->GetOrigin();
    // p[0] = static_cast<int>( (p[0] - o[0]) / s[0] + 0.5 );
    p[0] = static_cast<int>( p[0] + 0.5 );
    p[1] = static_cast<int>( p[1] + 0.5 );

    std::cout << " -> " << p[0] << " " << p[1] << std::endl;

    // Convert the current number to a string
    std::stringstream ss;
    ss << Numbers.size();

    // Create an actor for the text
    vtkSmartPointer<vtkVectorText> textSource = vtkSmartPointer<vtkVectorText>::New();
    textSource->SetText( ss.str().c_str() );

    //get the bounds of the text
    textSource->Update();
    double* bounds = textSource->GetOutput()->GetBounds();
    //transform the polydata to be centered over the pick position
    double center[3] = {0.5*(bounds[1]+bounds[0]), 0.5*(bounds[3]+bounds[2]), 0.0 };

    vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
    trans->Translate( -center[0], -center[1], 0 );
    trans->Translate( p[0], p[1], 0 );

    vtkSmartPointer<vtkTransformPolyDataFilter> tpd = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    tpd->SetTransform( trans );
    tpd->SetInputConnection(  textSource->GetOutputPort() );

    // Create a mapper
    vtkSmartPointer<vtkPolyDataMapper2D> mapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
    vtkSmartPointer<vtkCoordinate> coordinate = vtkSmartPointer<vtkCoordinate>::New();
    coordinate->SetCoordinateSystemToWorld();
    mapper->SetTransformCoordinate( coordinate );
    mapper->SetInputConnection( tpd->GetOutputPort() );

    vtkSmartPointer<vtkActor2D> actor = vtkSmartPointer<vtkActor2D>::New();
    actor->SetMapper( mapper );
    actor->GetProperty()->SetColor( 1, 1, 0 ); // yellow

    this->CurrentRenderer->AddViewProp( actor );
    this->Numbers.push_back(actor);
  }

};

vtkStandardNewMacro(MyStyle);

int main (int, char *[])
{
  // Create a blank, black image
  vtkSmartPointer<vtkImageCanvasSource2D> drawing = vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0, 20, 0, 50, 0, 0);
  drawing->FillBox(0,20,0,50);

  // Draw a red circle of radius 5 centered at (9,10)
  drawing->SetDrawColor(255, 0, 0, 0);
  drawing->DrawCircle(9, 10, 5);
  drawing->Update();

  vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(
    drawing->GetOutputPort());
  actor->InterpolateOff();

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  renderer->GradientBackgroundOn();
  renderer->SetBackground2(0,0,1); // Background 2 color blue

  renderWindow->Render();

  vtkSmartPointer<MyStyle> style = vtkSmartPointer<MyStyle>::New();

  renderWindowInteractor->SetInteractorStyle( style );
  style->SetDefaultRenderer( renderer );
  style->SetCurrentRenderer( renderer );
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
