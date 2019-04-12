#include <vtkActor.h>
#include <vtkAppendPolyData.h>
#include <vtkCamera.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkWarpScalar.h>

// This example demonstrates how to extract "computational planes" from a
// structured dataset. Structured data has a natural, logical coordinate
// system based on i-j-k indices. Specifying imin,imax, jmin,jmax, kmin,kmax
// pairs can indicate a point, line, plane, or volume of data.
//
// In this example, we extract three planes and warp them using scalar values
// in the direction of the local normal at each point. This gives a sort of
// "velocity profile" that indicates the nature of the flow.

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " combxyz.bin combq.bin" << std::endl;
    return EXIT_FAILURE;
  }
  // Here we read data from a annular combustor. A combustor burns fuel and air
  // in a gas turbine (e.g., a jet engine) and the hot gas eventually makes its
  // way to the turbine section.
  //
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->SetXYZFileName(argv[1]);
  pl3d->SetQFileName(argv[2]);
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->Update();

  vtkStructuredGrid *pl3dOutput =
    dynamic_cast<vtkStructuredGrid*>(pl3d->GetOutput()->GetBlock(0));

  // Planes are specified using a imin,imax, jmin,jmax, kmin,kmax coordinate
  // specification. Min and max i,j,k values are clamped to 0 and maximum value.
  //
  vtkSmartPointer<vtkStructuredGridGeometryFilter> plane =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  plane->SetInputData(pl3dOutput);
  plane->SetExtent(10, 10, 1, 100, 1, 100);
  
  vtkSmartPointer<vtkStructuredGridGeometryFilter> plane2 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  plane2->SetInputData(pl3dOutput);
  plane2->SetExtent(30, 30, 1, 100, 1, 100);
  vtkSmartPointer<vtkStructuredGridGeometryFilter> plane3 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  plane3->SetInputData(pl3dOutput);
  plane3->SetExtent(45, 45, 1, 100, 1, 100);

  // We use an append filter because that way we can do the warping, etc. just
  // using a single pipeline and actor.
  //
  vtkSmartPointer<vtkAppendPolyData> appendF =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendF->AddInputConnection(plane->GetOutputPort());
  appendF->AddInputConnection(plane2->GetOutputPort());
  appendF->AddInputConnection(plane3->GetOutputPort());

  vtkSmartPointer<vtkWarpScalar> warp =
    vtkSmartPointer<vtkWarpScalar>::New();
  warp->SetInputConnection(appendF->GetOutputPort());
  warp->UseNormalOn();
  warp->SetNormal(1.0, 0.0, 0.0);
  warp->SetScaleFactor(2.5);

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(warp->GetOutputPort());
  normals->SetFeatureAngle(60);

  vtkSmartPointer<vtkPolyDataMapper> planeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  planeMapper->SetInputConnection(normals->GetOutputPort());
  planeMapper->SetScalarRange(pl3dOutput->GetScalarRange());

  vtkSmartPointer<vtkActor> planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->SetMapper(planeMapper);

  // The outline provides context for the data and the planes.
  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputData(pl3dOutput);

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

  // Create the usual graphics stuff/
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  ren1->AddActor(outlineActor);
  ren1->AddActor(planeActor);
  ren1->SetBackground(colors->GetColor3d("Silver").GetData());
  renWin->SetSize(640, 480);

// Create an initial view.
  ren1->GetActiveCamera()->SetClippingRange(3.95297, 50);
  ren1->GetActiveCamera()->SetFocalPoint(8.88908, 0.595038, 29.3342);
  ren1->GetActiveCamera()->SetPosition(-12.3332, 31.7479, 41.2387);
  ren1->GetActiveCamera()->SetViewUp(0.060772, -0.319905, 0.945498);
  iren->Initialize();

// render the image
//
  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
}
