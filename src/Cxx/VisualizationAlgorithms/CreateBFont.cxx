#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkClipPolyData.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkNamedColors.h>
#include <vtkPNMReader.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " image.pgm" << std::endl;
    return EXIT_FAILURE;
  }
// Now create the RenderWindow, Renderer and Interactor
//
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

  vtkSmartPointer<vtkPNMReader> imageIn =
    vtkSmartPointer<vtkPNMReader>::New();
  imageIn->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageGaussianSmooth> gaussian =
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  gaussian->SetStandardDeviations(2, 2);
  gaussian->SetDimensionality(2);
  gaussian->SetRadiusFactors(1, 1);
  gaussian->SetInputConnection(imageIn->GetOutputPort());

  vtkSmartPointer<vtkImageDataGeometryFilter> geometry =
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  geometry->SetInputConnection(gaussian->GetOutputPort());

  vtkSmartPointer<vtkClipPolyData> aClipper =
  vtkSmartPointer<vtkClipPolyData>::New();
  aClipper->SetInputConnection(geometry->GetOutputPort());
  aClipper->SetValue(127.5);
  aClipper->GenerateClipScalarsOff();
  aClipper->InsideOutOn();
  aClipper->GetOutput()->GetPointData()->CopyScalarsOff();
  aClipper->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(aClipper->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> letter =
    vtkSmartPointer<vtkActor>::New();
  letter->SetMapper(mapper);

  ren1->AddActor(letter);
  letter->GetProperty()->SetDiffuseColor(colors->GetColor3d("LampBlack").GetData());
  letter->GetProperty()->SetRepresentationToWireframe();

  ren1->SetBackground(colors->GetColor3d("WhiteSmoke").GetData());
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Dolly(1.2);
  ren1->ResetCameraClippingRange();

  renWin->SetSize(640, 480);

// render the image
//
  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
  }
