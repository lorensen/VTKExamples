#include <vtkActor.h>
#include <vtkBridgeDataSet.h> // Must build VTK with BUILD_TESTING=ON
#include <vtkCellData.h>
#include <vtkContourFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkDelaunay3D.h>
#include <vtkElevationFilter.h>
#include <vtkGenericClip.h>
#include <vtkImageData.h>
#include <vtkImplicitDataSet.h>
#include <vtkIdFilter.h>
#include <vtkIdTypeArray.h>
#include <vtkNamedColors.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSampleFunction.h>
#include <vtkSmartPointer.h>
#include <vtkPlane.h>
#include <vtkUnstructuredGrid.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

    // If we try to use a PointSource with vtkBridgeDataSet, an error is produced:
//    vtkBridgeCell.cxx:141: virtual int vtkBridgeCell::GetType(): Assertion `"check: impossible case" && 0' failed.
    // There does not seem to be a case to handle VTK_VERTEX (which is what is produced by PointSource) in vtkBridgeDataSet.
//  vtkSmartPointer<vtkPointSource> pointSource =
//      vtkSmartPointer<vtkPointSource>::New();
//  pointSource->SetNumberOfPoints(100);
//  pointSource->SetRadius(1.0);
//  pointSource->Update();

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(5);
  sphereSource->SetThetaResolution(10);
  sphereSource->SetPhiResolution(10);
  sphereSource->Update();

  // Add ids to the points and cells of the sphere
  vtkSmartPointer<vtkIdFilter> idFilter =
      vtkSmartPointer<vtkIdFilter>::New();
  idFilter->SetInputConnection(sphereSource->GetOutputPort());
  idFilter->Update();

  // Create a plane to clip with
  vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(0, 0, 0);
  plane->SetNormal(1, 1, 1);

  // Convert the DataSet to a GenericDataSet
  vtkSmartPointer<vtkBridgeDataSet> bridgeDataSet = vtkSmartPointer<vtkBridgeDataSet>::New();
  bridgeDataSet->SetDataSet(idFilter->GetOutput());

  vtkSmartPointer<vtkGenericClip> clipper =
      vtkSmartPointer<vtkGenericClip>::New();
  clipper->SetClipFunction(plane);
  clipper->SetInputData(bridgeDataSet);
  clipper->Update();

  // Get the clipped cell ids
  vtkUnstructuredGrid* clipped = clipper->GetOutput();
  vtkIdTypeArray* originalIds = dynamic_cast<vtkIdTypeArray*>(clipped->GetCellData()->GetArray("vtkIdFilter_Ids"));
  for(vtkIdType i = 0; i < originalIds->GetNumberOfTuples(); i++)
  {
    std::cout << "new id " << i << ", original id " << originalIds->GetValue(i) << std::endl;
  }

  // Create a mapper and actor for clipped points
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(clipper->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a mapper and actor for clipping function
  vtkSmartPointer<vtkSampleFunction> sample =
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(20,20,20);
  sample->SetImplicitFunction(plane);
  double value = 10.0;
  double xmin = -value, xmax = value,
    ymin = -value, ymax = value,
    zmin = -value, zmax = value;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);

  // Create the 0 isosurface
  vtkSmartPointer<vtkContourFilter> contours =
    vtkSmartPointer<vtkContourFilter>::New();
  contours->SetInputConnection(sample->GetOutputPort());
  contours->GenerateValues(1, 1, 1);

  // Map the contours to graphical primitives
  vtkSmartPointer<vtkPolyDataMapper> contourMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contours->GetOutputPort());
  contourMapper->SetScalarRange(0.0, 1.2);

  // Create an actor for the sphere
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(contourMapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->AddActor(sphereActor);
  renderer->SetBackground(namedColors->GetColor3d("Burlywood").GetData());
  renderer->UseHiddenLineRemovalOn();
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
