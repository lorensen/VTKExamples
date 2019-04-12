#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCutter.h>
#include <vtkDataSetMapper.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkNamedColors.h>
#include <vtkPlane.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " combxyz.bin combq.bin" << std::endl;
    return EXIT_FAILURE;
  }

// Create the RenderWindow, Renderer and both Actors
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

// cut data
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->SetXYZFileName(argv[1]);
  pl3d->SetQFileName(argv[2]);
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->Update();

  vtkStructuredGrid *sg =
    dynamic_cast<vtkStructuredGrid*>(pl3d->GetOutput()->GetBlock(0));

  vtkSmartPointer<vtkPlane> plane =
    vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(sg->GetCenter());
  plane->SetNormal(-0.287, 0, 0.9579);

  vtkSmartPointer<vtkCutter> planeCut =
    vtkSmartPointer<vtkCutter>::New();
  planeCut->SetInputData(pl3d->GetOutput()->GetBlock(0));
  planeCut->SetCutFunction(plane);

  vtkSmartPointer<vtkDataSetMapper> cutMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  cutMapper->SetInputConnection(planeCut->GetOutputPort());
  cutMapper->SetScalarRange(sg->GetPointData()->GetScalars()->GetRange());

  vtkSmartPointer<vtkActor> cutActor =
    vtkSmartPointer<vtkActor>::New();
  cutActor->SetMapper(cutMapper);

//extract plane
  vtkSmartPointer<vtkStructuredGridGeometryFilter> compPlane =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  compPlane->SetInputData(sg);
  compPlane->SetExtent(0, 100, 0, 100, 9, 9);

  vtkSmartPointer<vtkPolyDataMapper> planeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  planeMapper->SetInputConnection(compPlane->GetOutputPort());
  planeMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->SetMapper(planeMapper);
  planeActor->GetProperty()->SetRepresentationToWireframe();
  planeActor->GetProperty()->SetColor(colors->GetColor3d("Wheat").GetData());

//outline
  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputData(pl3d->GetOutput()->GetBlock(0));

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Wheat").GetData());

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(outlineActor);
  ren1->AddActor(planeActor);
  ren1->AddActor(cutActor);
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renWin->SetSize(640, 480);

  ren1->GetActiveCamera()->SetClippingRange(3.95297, 50);
  ren1->GetActiveCamera()->SetFocalPoint(9.71821, 0.458166, 29.3999);
  ren1->GetActiveCamera()->SetPosition(2.7439, -37.3196, 38.7167);
  ren1->GetActiveCamera()->SetViewUp(-0.16123, 0.264271, 0.950876);
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Elevation(30);

// render the image
//
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
