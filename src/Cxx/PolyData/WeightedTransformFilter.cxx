#include <vtkSphereSource.h>
#include <vtkTransformFilter.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTransform.h>
#include <vtkWeightedTransformFilter.h>

int main(int, char *[])
{
  // Use a sphere as a basis of the shape
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetPhiResolution(40);
  sphere->SetThetaResolution(40);
  sphere->Update();

  vtkPolyData* sphereData = sphere->GetOutput();

  // Create a data array to hold the weighting coefficients
  vtkSmartPointer<vtkFloatArray> tfarray =
    vtkSmartPointer<vtkFloatArray>::New();
  vtkIdType npoints = sphereData->GetNumberOfPoints();
  tfarray->SetNumberOfComponents(2);
  tfarray->SetNumberOfTuples(npoints);

  // Parameterize the sphere along the z axis, and fill the weights
  // with (1.0-a, a) to linearly interpolate across the shape
  for(int i = 0; i < npoints; i++)
  {
    double pt[3];
    sphereData->GetPoint(i, pt);
//    double x = pt[0];
//    double y = pt[1];
    double z = pt[2];

    double zn = z + 0.5;
    double zn1 = 1.0 - zn;
    if(zn > 1.0)
    {
      zn = 1.0;
    }
    if(zn1 < 0.0)
    {
      zn1 = 0.0;
    }

    tfarray->SetComponent(i, 0, zn1);
    tfarray->SetComponent(i, 1, zn);
  }

  // Create field data to hold the array, and bind it to the sphere
//  vtkSmartPointer<vtkFieldData> fd =
//    vtkSmartPointer<vtkFieldData>::New();
  tfarray->SetName("weights");
  sphereData->GetPointData()->AddArray(tfarray);

  // Use an ordinary transform to stretch the shape
  vtkSmartPointer<vtkTransform> stretch =
    vtkSmartPointer<vtkTransform>::New();
  stretch->Scale(1, 1, 3.2);

  vtkSmartPointer<vtkTransformFilter> stretchFilter =
    vtkSmartPointer<vtkTransformFilter>::New();
  stretchFilter->SetInputData(sphereData);
  stretchFilter->SetTransform(stretch);

  // Now, for the weighted transform stuff
  vtkSmartPointer<vtkWeightedTransformFilter> weightedTrans =
    vtkSmartPointer<vtkWeightedTransformFilter>::New();

  // Create two transforms to interpolate between
  vtkSmartPointer<vtkTransform> identity =
    vtkSmartPointer<vtkTransform>::New();
  identity->Identity();

  vtkSmartPointer<vtkTransform> rotated =
    vtkSmartPointer<vtkTransform>::New();
  double rotatedAngle = 45;
  rotated->RotateX(rotatedAngle);

  weightedTrans->SetNumberOfTransforms(2);
  weightedTrans->SetTransform(identity, 0);
  weightedTrans->SetTransform(rotated, 1);
  // which data array should the filter use ?
  weightedTrans->SetWeightArray("weights");

  weightedTrans->SetInputConnection(stretchFilter->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> weightedTransMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  weightedTransMapper->SetInputConnection(weightedTrans->GetOutputPort());
  vtkSmartPointer<vtkActor> weightedTransActor =
    vtkSmartPointer<vtkActor>::New();
  weightedTransActor->SetMapper(weightedTransMapper);
  weightedTransActor->GetProperty()->SetDiffuseColor(0.8, 0.8, 0.1);
  weightedTransActor->GetProperty()->SetRepresentationToSurface();

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->AddActor(weightedTransActor);
  renderer->SetBackground(0.1, 0.2, 0.5);
  renderWindow->SetSize(300, 300);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(90);
  renderer->GetActiveCamera()->Dolly(1);

  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
