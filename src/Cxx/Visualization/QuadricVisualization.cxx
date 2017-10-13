#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkQuadric.h>
#include <vtkAppendFilter.h>
#include <vtkExtractVOI.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkUnstructuredGrid.h>

#include <vtkNamedColors.h>

namespace
{
void CreateIsosurface(vtkSmartPointer<vtkSampleFunction> &function,
                      vtkSmartPointer<vtkActor> &actor,
                      unsigned int numberOfContours = 5);

void CreatePlanes(vtkSmartPointer<vtkSampleFunction> &function,
                  vtkSmartPointer<vtkActor> &actor,
                  unsigned numberOfPlanes);
void CreateContours(vtkSmartPointer<vtkSampleFunction> &function,
                    vtkSmartPointer<vtkActor> &actor,
                    unsigned numberOfPlanes,
                    unsigned numberOfContours);
}
int main( int, char *[] )
{ 
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  renderWindow->SetSize(640, 480);

  //
  // Create surface of implicit function
  //
  double range[2];

  // Sample quadric function
  vtkSmartPointer<vtkQuadric> quadric =
    vtkSmartPointer<vtkQuadric>::New();
  quadric->SetCoefficients(1,2,3,0,1,0,0,0,0,0);

  vtkSmartPointer<vtkSampleFunction> sample =
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(25,25,25);
  sample->SetImplicitFunction(quadric);

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  CreateIsosurface(sample, isoActor);

  vtkSmartPointer<vtkActor> planesActor =
    vtkSmartPointer<vtkActor>::New();
  CreatePlanes(sample, planesActor, 3);
  planesActor->AddPosition(isoActor->GetBounds()[0] * 2.0, 0, 0);

  vtkSmartPointer<vtkActor> contourActor =
    vtkSmartPointer<vtkActor>::New();
  CreateContours(sample,contourActor, 3, 15);
  contourActor->AddPosition(contourActor->GetBounds()[0] * 4.0, 0, 0);

  renderer->AddActor(planesActor);
  renderer->AddActor(contourActor);
  renderer->AddActor(isoActor);
  renderer->TwoSidedLightingOn();

  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  // interact with data
  interactor->Start();

  return EXIT_SUCCESS;
}
namespace
{
void CreateIsosurface(vtkSmartPointer<vtkSampleFunction> &function,
                      vtkSmartPointer<vtkActor> &actor,
                      unsigned int numberOfContours)
{
  double range[2];
  // Generate implicit surface
  vtkSmartPointer<vtkContourFilter> contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetInputConnection(function->GetOutputPort());
  range[0] = 1.0; range[1] = 6.0;
  contour->GenerateValues(numberOfContours, range);

  // Map contour
  vtkSmartPointer<vtkPolyDataMapper> contourMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contour->GetOutputPort());
  contourMapper->SetScalarRange(0,7);

  actor->SetMapper(contourMapper);
  return;
}
void CreatePlanes(vtkSmartPointer<vtkSampleFunction> &function,
                  vtkSmartPointer<vtkActor> &actor,
                  unsigned int numberOfPlanes)
{
  //
  // Extract planes from implicit function
  //

  vtkSmartPointer<vtkAppendFilter> append =
    vtkSmartPointer<vtkAppendFilter>::New();

  int dims[3];
  function->GetSampleDimensions(dims);
  int sliceIncr = (dims[2] - 1) / (numberOfPlanes + 1);

  int slice = -4;
  for (int i = 0; i< numberOfPlanes; ++i)
  {
    vtkSmartPointer<vtkExtractVOI> extract =
      vtkSmartPointer<vtkExtractVOI>::New();
    extract->SetInputConnection(function->GetOutputPort());
    extract->SetVOI(0, dims[0] - 1,
                    0, dims[1] - 1,
                    slice + sliceIncr, slice + sliceIncr);
    append->AddInputConnection(extract->GetOutputPort());
    slice += sliceIncr;
  }
  append->Update();

  // Map planes
  vtkSmartPointer<vtkDataSetMapper> planesMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  planesMapper->SetInputConnection(append->GetOutputPort());
  planesMapper->SetScalarRange(0,7);

  actor->SetMapper(planesMapper);
  actor->GetProperty()->SetAmbient(1.);
  return;
}
void CreateContours(vtkSmartPointer<vtkSampleFunction> &function,
                    vtkSmartPointer<vtkActor> &actor,
                    unsigned int numberOfPlanes,
                    unsigned int numberOfContours)
{
  //
  // Extract planes from implicit function
  //

  vtkSmartPointer<vtkAppendFilter> append =
    vtkSmartPointer<vtkAppendFilter>::New();

  int dims[3];
  function->GetSampleDimensions(dims);
  int sliceIncr = (dims[2] - 1) / (numberOfPlanes + 1);

  int slice = -4;
  for (int i = 0; i< numberOfPlanes; ++i)
  {
    vtkSmartPointer<vtkExtractVOI> extract =
      vtkSmartPointer<vtkExtractVOI>::New();
    extract->SetInputConnection(function->GetOutputPort());
    extract->SetVOI(0, dims[0] - 1,
                    0, dims[1] - 1,
                    slice + sliceIncr, slice + sliceIncr);
    double range[2];
    range[0] = 1.0; range[1] = 6.0;
    vtkSmartPointer<vtkContourFilter> contour =
      vtkSmartPointer<vtkContourFilter>::New();
    contour->SetInputConnection(extract->GetOutputPort());
    contour->GenerateValues(numberOfContours, range);
    append->AddInputConnection(contour->GetOutputPort());
    slice += sliceIncr;
  }
  append->Update();

  // Map planes
  vtkSmartPointer<vtkDataSetMapper> planesMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  planesMapper->SetInputConnection(append->GetOutputPort());
  planesMapper->SetScalarRange(0,7);

  actor->SetMapper(planesMapper);
  actor->GetProperty()->SetAmbient(1.);
  return;
}
}
