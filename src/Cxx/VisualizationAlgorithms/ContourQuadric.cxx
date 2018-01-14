#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkQuadric.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSampleFunction.h>

int main( int, char *[] )
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> aren =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(aren);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

//
// Create surfaces F(x,y,z) = constant
//
  // Sample quadric function
  vtkSmartPointer<vtkQuadric> quadric =
    vtkSmartPointer<vtkQuadric>::New();
  quadric->SetCoefficients(.5,1,.2,0,.1,0,0,.2,0,0);
  vtkSmartPointer<vtkSampleFunction> sample =
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(quadric);

  vtkSmartPointer<vtkContourFilter> contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetInputConnection(sample->GetOutputPort());
  contour->GenerateValues(5,0,1.2);

  vtkSmartPointer<vtkPolyDataMapper> contourMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contour->GetOutputPort());
  contourMapper->SetScalarRange(0,1.2);

  vtkSmartPointer<vtkActor> contourActor =
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);

  // Create outline
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(sample->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Brown").GetData());
  outlineActor->GetProperty()->SetLineWidth(3.0);

//
// Rendering stuff
//
  aren->SetBackground(colors->GetColor3d("SlateGray").GetData());
  aren->AddActor(contourActor);
  aren->AddActor(outlineActor);

  aren->ResetCamera();
  aren->GetActiveCamera()->Azimuth(30);
  aren->GetActiveCamera()->Elevation(30);

  renWin->SetSize(640, 512);
  renWin->Render();

  // interact with data
  iren->Start();

  return EXIT_SUCCESS;
}
