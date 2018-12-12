// This example shows how to color an isosurface with other
// data. Basically an isosurface is generated, and a data array is
// selected and used by the mapper to color the surface.

#include <vtkSmartPointer.h>

#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODActor.h>
#include <vtkCamera.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " combxyz.bin combq.bin" << std::endl;
    return EXIT_FAILURE;
  }
// Read some data. The important thing here is to read a function as a
// data array as well as the scalar and vector.  (here function 153 is
// named "Velocity Magnitude").Later this data array will be used to
// color the isosurface.
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->SetXYZFileName(argv[1]);
  pl3d->SetQFileName(argv[2]);
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->AddFunction(153);
  pl3d->Update();

  // The contour filter uses the labeled scalar (function number 100
  // above to generate the contour surface; all other data is
  // interpolated during the contouring process.
  vtkSmartPointer<vtkContourFilter> iso =
    vtkSmartPointer<vtkContourFilter>::New();
  iso->SetInputData(pl3d->GetOutput()->GetBlock(0));
  iso->SetValue(0, .24);

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(iso->GetOutputPort());
  normals->SetFeatureAngle(45);

  // We indicate to the mapper to use the velcoity magnitude, which is a
  // vtkDataArray that makes up part of the point attribute data.
  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(normals->GetOutputPort());
  isoMapper->ScalarVisibilityOn();
  isoMapper->SetScalarRange(0, 1500);
  isoMapper->SetScalarModeToUsePointFieldData();
  isoMapper->ColorByArrayComponent("VelocityMagnitude", 0);

  vtkSmartPointer<vtkLODActor> isoActor =
    vtkSmartPointer<vtkLODActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->SetNumberOfCloudPoints(1000);

  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputData(pl3d->GetOutput()->GetBlock(0));

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);

  // Create the usual rendering stuff.
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Add the actors to the renderer, set the background and size
  renderer->AddActor(outlineActor);
  renderer->AddActor(isoActor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  renderWindow->SetSize(640, 480);

  // Pick a good view
  vtkCamera *cam1 = renderer->GetActiveCamera();
  cam1->SetClippingRange(3.95297, 50);
  cam1->SetFocalPoint(9.71821, 0.458166, 29.3999);
  cam1->SetPosition(2.7439, -37.3196, 38.7167);
  cam1->SetViewUp(-0.16123, 0.264271, 0.950876);
  
  interactor->Initialize();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
