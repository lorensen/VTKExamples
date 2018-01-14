
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredGridOutlineFilter.h>

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " combxyz.bin combq.bin" << std::endl;
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

// create pipeline
//
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->SetXYZFileName(argv[1]);
  pl3d->SetQFileName(argv[2]);
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->Update();

  vtkSmartPointer<vtkContourFilter> iso =
    vtkSmartPointer<vtkContourFilter>::New();
  iso->SetInputData(pl3d->GetOutput()->GetBlock(0));
  iso->SetValue(0, .38);
  
  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(iso->GetOutputPort());
  normals->SetFeatureAngle(45);
  
  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(normals->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetColor(colors->GetColor3d("bisque").GetData());

  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputConnection(pl3d->GetOutputPort());
  
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  
  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(outlineActor);
  ren1->AddActor(isoActor);
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renWin->SetSize(640, 480);

  ren1->GetActiveCamera()->SetFocalPoint(9.71821, 0.458166, 29.3999);
  ren1->GetActiveCamera()->SetPosition(2.7439, -37.3196, 38.7167);
  ren1->GetActiveCamera()->SetViewUp(-0.16123, 0.264271, 0.950876);
  ren1->ResetCameraClippingRange();

// render the image
//
  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
}

