#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkCamera.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageCast.h>
#include <vtkImageMapper3D.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> mandelbrotSource =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  mandelbrotSource->Update();

  vtkSmartPointer<vtkImageCast> castFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castFilter->SetInputConnection(mandelbrotSource->GetOutputPort());
  castFilter->SetOutputScalarTypeToUnsignedChar();
  castFilter->Update();

  vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
  imageSliceMapper->SetInputConnection(castFilter->GetOutputPort());

  vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice->SetMapper(imageSliceMapper);

  int extent[6];
  castFilter->GetOutput()->GetExtent(extent);

  double origin[3];
  castFilter->GetOutput()->GetOrigin(origin);

  double spacing[3];
  castFilter->GetOutput()->GetSpacing(spacing);

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageSlice);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkCamera* camera = renderer->GetActiveCamera();
  camera->ParallelProjectionOn();
  renderer->SetBackground(1,0,0);

  float xc = origin[0] + 0.5*(extent[0] + extent[1])*spacing[0];
  float yc = origin[1] + 0.5*(extent[2] + extent[3])*spacing[1];
//  float xd = (extent[1] - extent[0] + 1)*spacing[0]; // not used
  float yd = (extent[3] - extent[2] + 1)*spacing[1];

  float d = camera->GetDistance();
  camera->SetParallelScale(0.5f*static_cast<float>(yd));
  camera->SetFocalPoint(xc,yc,0.0);
  camera->SetPosition(xc,yc,+d);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
