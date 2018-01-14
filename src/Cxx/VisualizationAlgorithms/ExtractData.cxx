#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkExtractGeometry.h>
#include <vtkImplicitBoolean.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkQuadric.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSampleFunction.h>
#include <vtkShrinkFilter.h>
#include <vtkSphere.h>
#include <vtkTransform.h>

int main (int, char *[])
{
// extract data
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkQuadric> quadric =
    vtkSmartPointer<vtkQuadric>::New();
  quadric->SetCoefficients(.5, 1, .2, 0, .1, 0, 0, .2, 0, 0);

  vtkSmartPointer<vtkSampleFunction> sample =
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50, 50, 50);
  sample->SetImplicitFunction(quadric);
  sample->ComputeNormalsOff();

  vtkSmartPointer<vtkTransform> trans =
    vtkSmartPointer<vtkTransform>::New();
  trans->Scale(1, .5, .333);

  vtkSmartPointer<vtkSphere> sphere =
    vtkSmartPointer<vtkSphere>::New();
  sphere->SetRadius(0.25);
  sphere->SetTransform(trans);

  vtkSmartPointer<vtkTransform> trans2 =
    vtkSmartPointer<vtkTransform>::New();
  trans2->Scale(.25, .5, 1.0);

  vtkSmartPointer<vtkSphere> sphere2 =
    vtkSmartPointer<vtkSphere>::New();
  sphere2->SetRadius(0.25);
  sphere2->SetTransform(trans2);

  vtkSmartPointer<vtkImplicitBoolean> booleanUnion =
    vtkSmartPointer<vtkImplicitBoolean>::New();
  booleanUnion->AddFunction(sphere);
  booleanUnion->AddFunction(sphere2);
  booleanUnion->SetOperationType(0); // boolean Union

  vtkSmartPointer<vtkExtractGeometry> extract =
    vtkSmartPointer<vtkExtractGeometry>::New();
  extract->SetInputConnection(sample->GetOutputPort());
  extract->SetImplicitFunction(booleanUnion);

  vtkSmartPointer<vtkShrinkFilter> shrink =
    vtkSmartPointer<vtkShrinkFilter>::New();
  shrink->SetInputConnection(extract->GetOutputPort());
  shrink->SetShrinkFactor(0.5);

  vtkSmartPointer<vtkDataSetMapper> dataMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  dataMapper->SetInputConnection(shrink->GetOutputPort());
  vtkSmartPointer<vtkActor> dataActor =
    vtkSmartPointer<vtkActor>::New();
  dataActor->SetMapper(dataMapper);

// outline
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(sample->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(0, 0, 0);


// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(outlineActor);
  ren1->AddActor(dataActor);

  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renWin->SetSize(640, 480);
  renWin->Render();
  ren1->GetActiveCamera()->Azimuth(30);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Zoom(1.5);

  iren->Start();

  return EXIT_SUCCESS;
}
