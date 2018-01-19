#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkGaussianSplatter.h>
#include <vtkMaskPoints.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " fran_cut.vtk" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();


// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

// read cyberware file
//
  vtkSmartPointer<vtkPolyDataReader> cyber =
    vtkSmartPointer<vtkPolyDataReader>::New();
  cyber->SetFileName(argv[1]);

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(cyber->GetOutputPort());

  vtkSmartPointer<vtkMaskPoints> mask =
    vtkSmartPointer<vtkMaskPoints>::New();
  mask->SetInputConnection(normals->GetOutputPort());
  mask->SetOnRatio(8);
//   mask->RandomModeOn();

  vtkSmartPointer<vtkGaussianSplatter> splatter =
    vtkSmartPointer<vtkGaussianSplatter>::New();
  splatter->SetInputConnection(mask->GetOutputPort());
  splatter->SetSampleDimensions(100, 100, 100);
  splatter->SetEccentricity(2.5);
  splatter->NormalWarpingOn();
  splatter->SetScaleFactor(1.0);
  splatter->SetRadius(0.025);

  vtkSmartPointer<vtkContourFilter> contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetInputConnection(splatter->GetOutputPort());
  contour->SetValue(0, 0.25);

  vtkSmartPointer<vtkPolyDataMapper> splatMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  splatMapper->SetInputConnection(contour->GetOutputPort());
  splatMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> splatActor =
    vtkSmartPointer<vtkActor>::New();
  splatActor->SetMapper(splatMapper);
  splatActor->GetProperty()->SetColor(colors->GetColor3d("Flesh").GetData());

  vtkSmartPointer<vtkPolyDataMapper> cyberMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cyberMapper->SetInputConnection(cyber->GetOutputPort());
  cyberMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> cyberActor =
    vtkSmartPointer<vtkActor>::New();
  cyberActor->SetMapper(cyberMapper);
  cyberActor->GetProperty()->SetRepresentationToWireframe();
  cyberActor->GetProperty()->SetColor(colors->GetColor3d("Turquoise").GetData());

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(cyberActor);
  ren1->AddActor(splatActor);
  ren1->SetBackground(colors->GetColor3d("Wheat").GetData());
  renWin->SetSize(640, 480);

  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  camera->SetClippingRange(0.0332682, 1.66341);
  camera->SetFocalPoint(0.0511519, -0.127555, -0.0554379);
  camera->SetPosition(0.516567, -0.124763, -0.349538);
  camera->SetViewAngle(18.1279);
  camera->SetViewUp(-0.013125, 0.99985, -0.0112779);
  ren1->SetActiveCamera(camera);

// render the image
//
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
