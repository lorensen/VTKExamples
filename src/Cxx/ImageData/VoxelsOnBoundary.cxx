#include <string>
#include <vector>
#include <iostream>

#include <vtkSmartPointer.h>
#include <vtkMultiThreshold.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkUnstructuredGrid.h>
#include <vtkMetaImageReader.h>
#include <vtkImageDataToPointSet.h>
#include <vtkPlane.h>
#include <vtkImageShrink3D.h>
#include <vtkImageData.h>
#include <vtkPointSet.h>

#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>

int main (int argc, char *argv[])
{
  auto reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName (argv[1]);
  reader->Update();

  auto shrink =
    vtkSmartPointer<vtkImageShrink3D>::New();
  shrink->SetShrinkFactors(4, 4, 4);
  shrink->SetInputConnection(reader->GetOutputPort());
  shrink->Update();

  // Create a PointSet from the ImageData
  auto imageDataToPointSet =
    vtkSmartPointer<vtkImageDataToPointSet>::New();
  imageDataToPointSet->SetInputConnection(reader->GetOutputPort());
  imageDataToPointSet->SetInputConnection(shrink->GetOutputPort());
  imageDataToPointSet->Update();

  // Extract voxels on the border between the inside and outside.
  auto threshold =
    vtkSmartPointer<vtkMultiThreshold>::New();
  // Inside points have one or more points above the isosurface
  int insideId = threshold->AddIntervalSet(
    501, 20000,
    vtkMultiThreshold::CLOSED, vtkMultiThreshold::CLOSED,
    vtkDataObject::FIELD_ASSOCIATION_POINTS, "ImageScalars",
    0, 0);
  // Border points have points that straddle the boundary
  int borderId = threshold->AddIntervalSet(
    499.9999, 501.0000,
    vtkMultiThreshold::OPEN, vtkMultiThreshold::OPEN,
    vtkDataObject::FIELD_ASSOCIATION_POINTS, "ImageScalars",
    0, 0);

  threshold->SetInputData(imageDataToPointSet->GetOutput());

  // Select the intervals to be output
  threshold->OutputSet(insideId);
  threshold->OutputSet(borderId);
  threshold->Update();

  // Visualize
  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d outsideColor    = colors->GetColor3d("Crimson");
  vtkColor3d insideColor     = colors->GetColor3d("Banana");
  vtkColor3d borderColor     = colors->GetColor3d("Mint");
  vtkColor3d surfaceColor    = colors->GetColor3d("Peacock");
  vtkColor3d backgroundColor = colors->GetColor3d("Silver");

  auto plane =
    vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(dynamic_cast<vtkUnstructuredGrid*>(vtkMultiBlockDataSet::SafeDownCast(threshold->GetOutput()->GetBlock(insideId))->GetBlock(0))->GetCenter());
  plane->SetNormal(1.0, -1.0, -1.0);

  // Inside
  auto insideMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  insideMapper->SetInputData(
    dynamic_cast<vtkUnstructuredGrid*>(vtkMultiBlockDataSet::SafeDownCast(threshold->GetOutput()->GetBlock(insideId))->GetBlock(0)));
  insideMapper->ScalarVisibilityOff();

  auto insideActor =
    vtkSmartPointer<vtkActor>::New();
  insideActor->SetMapper(insideMapper);
  insideActor->GetProperty()->SetDiffuseColor(insideColor.GetData());
  insideActor->GetProperty()->SetSpecular(.6);
  insideActor->GetProperty()->SetSpecularPower(30);
  insideActor->GetProperty()->EdgeVisibilityOn();

  // Border
  auto borderMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  borderMapper->SetInputData(
    dynamic_cast<vtkUnstructuredGrid*>(vtkMultiBlockDataSet::SafeDownCast(threshold->GetOutput()->GetBlock(borderId))->GetBlock(0)));
  borderMapper->ScalarVisibilityOff();

  auto borderActor =
    vtkSmartPointer<vtkActor>::New();
  borderActor->SetMapper(borderMapper);
  borderActor->GetProperty()->SetDiffuseColor(borderColor.GetData());
  borderActor->GetProperty()->SetSpecular(.6);
  borderActor->GetProperty()->SetSpecularPower(30);
  borderActor->GetProperty()->EdgeVisibilityOn();

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->SetBackground(backgroundColor.GetData());
  renderer->UseHiddenLineRemovalOn();

  renderer->AddActor(insideActor);
  renderer->AddActor(borderActor);

  renderWindow->SetWindowName("CellsOnBoundary");
  renderWindow->Render();

  // Setup a good view
  renderer->GetActiveCamera()->SetViewUp (0, 0, -1);
  renderer->GetActiveCamera()->SetPosition (0, -1, 0);
  renderer->GetActiveCamera()->SetFocalPoint (0, 0, 0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Elevation(30.0);
  renderer->ResetCamera ();
  renderer->GetActiveCamera()->Dolly(1.5);

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

