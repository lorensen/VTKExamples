#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkQuadric.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkNamedColors.h>

int main( int, char *[] )
{
  double range[2];
  
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
  renWin->SetSize( 300, 300 );

//
// Create surface of implicit function
//
  // Sample quadric function
  vtkSmartPointer<vtkQuadric> quadric =
    vtkSmartPointer<vtkQuadric>::New();
  quadric->SetCoefficients(1,2,3,0,1,0,0,0,0,0);

  vtkSmartPointer<vtkSampleFunction> sample =
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(25,25,25);
  sample->SetImplicitFunction(quadric);

  // Generate implicit surface
  vtkSmartPointer<vtkContourFilter> contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetInputConnection(sample->GetOutputPort());
  range[0] = 1.0; range[1] = 6.0;
  contour->GenerateValues(3,range);

  // Map contour
  vtkSmartPointer<vtkPolyDataMapper> contourMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contour->GetOutputPort());
  contourMapper->SetScalarRange(0,7);

  vtkSmartPointer<vtkActor> contourActor =
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
//
// Create outline around data
//
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(sample->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(1,1,1);

  aren->AddActor(contourActor);
  aren->AddActor(outlineActor);

  aren->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renWin->SetSize(640, 480);
  renWin->Render(); // will automatically create camera

  // interact with data
  iren->Start();

  return EXIT_SUCCESS;
}
