// Translated from velProf.tcl.

#include <vtkActor.h>
#include <vtkAppendPolyData.h>
#include <vtkCamera.h>
#include <vtkLookupTable.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkWarpVector.h>

#include <array>
#include <string>

int main(int argc, char* argv[])
{
//   auto Scale = [](std::vector<double>& v, double scale) {
//     std::transform(std::begin(v), std::end(v), std::begin(v),
//                    [=](double const& n) { return n / scale; });
//     return;
//   };

  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename1 filename2" << std::endl;
    std::cout << "where: filename1 is combxyz.bin and filename2 is combq.bin."
              << std::endl;
    std::cout << "Produces figure 6-14(b) Flow momentum from the VTK Textbook."
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName1 = argv[1];
  std::string fileName2 = argv[2];

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  std::array<unsigned char , 4> bkg{{65, 99, 149}};
    colors->SetColor("BkgColor", bkg.data());

  // Read a vtk file
  //
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->SetXYZFileName(fileName1.c_str());
  pl3d->SetQFileName(fileName2.c_str());
  pl3d->SetScalarFunctionNumber(100); // Density
  pl3d->SetVectorFunctionNumber(202); // Momentum
  pl3d->Update();

  vtkStructuredGrid* pl3dOutput =
    dynamic_cast<vtkStructuredGrid*>(pl3d->GetOutput()->GetBlock(0));

  // What do we know about the data?
  // Get the extent of the data: imin,imax, jmin,jmax, kmin,kmax
  int extent[6] = {0, 0, 0, 0, 0, 0};
  pl3dOutput->GetExtent(extent);
  double scalarRange[2] = {0.0, 0.0};
  pl3dOutput->GetScalarRange(scalarRange);

  // Planes are specified using a imin,imax, jmin,jmax, kmin,kmax coordinate
  // specification. Min and max i,j,k values are clamped to 0 and maximum value.
  // See the variable named extent for the values.
  //
  vtkSmartPointer<vtkStructuredGridGeometryFilter> plane =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  plane->SetInputData(pl3dOutput);
  plane->SetExtent(10, 10, 1, extent[3], 1, extent[5]);

  vtkSmartPointer<vtkStructuredGridGeometryFilter> plane2 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  plane2->SetInputData(pl3dOutput);
  plane2->SetExtent(30, 30, 1, extent[3], 1, extent[5]);

  vtkSmartPointer<vtkStructuredGridGeometryFilter> plane3 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  plane3->SetInputData(pl3dOutput);
  plane3->SetExtent(45, 45, 1, extent[3], 1, extent[5]);

  // We use an append filter because that way we can do the warping, etc. just
  // using a single pipeline and actor.
  //
  vtkSmartPointer<vtkAppendPolyData> appendF =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendF->AddInputConnection(plane->GetOutputPort());
  appendF->AddInputConnection(plane2->GetOutputPort());
  appendF->AddInputConnection(plane3->GetOutputPort());

  // Warp
  vtkSmartPointer<vtkWarpVector> warp = vtkSmartPointer<vtkWarpVector>::New();
  warp->SetInputConnection(appendF->GetOutputPort());
  warp->SetScaleFactor(0.005);
  warp->Update();

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputData(warp->GetPolyDataOutput());
  normals->SetFeatureAngle(45);

  vtkSmartPointer<vtkPolyDataMapper> planeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  planeMapper->SetInputConnection(normals->GetOutputPort());
  planeMapper->SetScalarRange(scalarRange);

  vtkSmartPointer<vtkActor> planeActor = vtkSmartPointer<vtkActor>::New();
  planeActor->SetMapper(planeMapper);

  // The outline provides context for the data and the planes.
  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputData(pl3dOutput);

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

  // Create the RenderWindow, Renderer and both Actors
  //
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size
  //
  ren->AddActor(planeActor);
  ren->AddActor(outlineActor);
  ren->SetBackground(colors->GetColor3d("BkgColor").GetData());
  renWin->SetSize(512, 512);

  iren->Initialize();

  renWin->Render();

  ren->GetActiveCamera()->SetPosition(19.8562, -31.8912, 47.0755);
  ren->GetActiveCamera()->SetFocalPoint(8.255, 0.147815, 29.7631);
  ren->GetActiveCamera()->SetViewUp(-0.0333325, 0.465756, 0.884285);
  ren->GetActiveCamera()->SetClippingRange(17.3078, 64.6375);
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
