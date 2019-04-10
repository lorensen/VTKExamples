// This example was derived a python script created by Andrew E. Slaughter
#include <vtkSmartPointer.h>

#include <vtkCompositeDataGeometryFilter.h>
#include <vtkExodusIIReader.h>
#include <vtkGaussianKernel.h>
#include <vtkInterpolateDataSetAttributes.h>
#include <vtkPointInterpolator.h>
#include <vtkStaticPointLocator.h>

#include <vtkNamedColors.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRenderer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkMultiBlockDataSet.h>

int main (int argc, char *argv[])
{
  std::string variable = "u";
  double range[2] = {0, 10};

  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " coarseMesh fineMesh" << std::endl;
    return EXIT_FAILURE;
  }
  std::string file0 = argv[1];
  std::string file1 = argv[2];

  ///////////////////////////////////////////////////////////////////////////
  // FILE 0: COARSE MESH WITH SOLUTION 0
    vtkSmartPointer<vtkExodusIIReader> coarseReader =
      vtkSmartPointer<vtkExodusIIReader>::New();
    coarseReader->SetFileName(file0.c_str());
    coarseReader->UpdateInformation();
    coarseReader->SetTimeStep(0);
    coarseReader->SetAllArrayStatus(vtkExodusIIReader::NODAL, 1);
    coarseReader->Update();

    vtkSmartPointer<vtkCompositeDataGeometryFilter> coarseGeometry =
      vtkSmartPointer<vtkCompositeDataGeometryFilter>::New();
    coarseGeometry->SetInputConnection(0, coarseReader->GetOutputPort(0));
    coarseGeometry->Update();

   vtkSmartPointer<vtkPolyDataMapper> coarseMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    coarseMapper->SetInputConnection(coarseGeometry->GetOutputPort());
    coarseMapper->SelectColorArray(variable.c_str());
    coarseMapper->SetScalarModeToUsePointFieldData();
    coarseMapper->InterpolateScalarsBeforeMappingOn();
    coarseMapper->SetScalarRange(range);

    vtkSmartPointer<vtkActor> coarseActor =
      vtkSmartPointer<vtkActor>::New();
    coarseActor->SetMapper(coarseMapper);
    coarseActor->GetProperty()->SetEdgeVisibility(true);

    vtkSmartPointer<vtkRenderer> coarseRenderer =
      vtkSmartPointer<vtkRenderer>::New();
    coarseRenderer->AddViewProp(coarseActor);

/////////////////////////////////////////////////////////////////////
// FILE 1: FINE MESH WITH SOLUTION 1

    vtkSmartPointer<vtkExodusIIReader> fineReader =
      vtkSmartPointer<vtkExodusIIReader>::New();
    fineReader->SetFileName(file1.c_str());
    fineReader->UpdateInformation();
    fineReader->SetTimeStep(0);
    fineReader->SetAllArrayStatus(vtkExodusIIReader::NODAL, 1);
    fineReader->Update();

    vtkSmartPointer<vtkCompositeDataGeometryFilter> fineGeometry =
      vtkSmartPointer<vtkCompositeDataGeometryFilter>::New();
    fineGeometry->SetInputConnection(0, fineReader->GetOutputPort(0));
    fineGeometry->Update();
    fineGeometry->GetOutput()->GetPointData()->SetActiveScalars(variable.c_str());

    vtkSmartPointer<vtkPolyDataMapper> fineGeometryMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    fineGeometryMapper->SetInputConnection(fineGeometry->GetOutputPort());
    fineGeometryMapper->SelectColorArray(variable.c_str());
    fineGeometryMapper->SetScalarModeToUsePointFieldData();
    fineGeometryMapper->InterpolateScalarsBeforeMappingOn();
    fineGeometryMapper->SetScalarRange(range);

    vtkSmartPointer<vtkActor> fineGeometryActor =
      vtkSmartPointer<vtkActor>::New();
    fineGeometryActor->SetMapper(fineGeometryMapper);
    fineGeometryActor->GetProperty()->SetEdgeVisibility(true);

    vtkSmartPointer<vtkRenderer> fineGeometryRenderer =
      vtkSmartPointer<vtkRenderer>::New();
    fineGeometryRenderer->AddViewProp(fineGeometryActor);

//////////////////////////////////////////////////////////////////////
// PROJECT SOLUTION FROM FILE 0 to GRID FROM FILE 1

    // Build the structure to interpolate onto
    vtkSmartPointer<vtkUnstructuredGrid> coarseInterpolatedGrid = // output to be interpolated on to
      vtkSmartPointer<vtkUnstructuredGrid>::New();

    vtkMultiBlockDataSet *coarseMultiBlock =
      dynamic_cast<vtkMultiBlockDataSet *>(coarseReader->GetOutput()->GetBlock(0));
    coarseInterpolatedGrid->DeepCopy(dynamic_cast<vtkUnstructuredGrid*>(coarseMultiBlock->GetBlock(0)));

    vtkSmartPointer<vtkStaticPointLocator> locator =
      vtkSmartPointer<vtkStaticPointLocator>::New();
    locator->SetDataSet(fineGeometry->GetOutput());
    locator->BuildLocator();

    vtkSmartPointer<vtkGaussianKernel> kernel =
      vtkSmartPointer<vtkGaussianKernel>::New();
    kernel->SetSharpness(4);
    kernel->SetKernelFootprintToNClosest();
    kernel->SetNumberOfPoints(10);
    kernel->SetSharpness(4.0);

    // Probe the fine geometry with the course geometry.
    // NOTE: The point arrays will not be interpolated unless PassPointArrays is off.
    vtkSmartPointer<vtkPointInterpolator> coarseInterpolator =
      vtkSmartPointer<vtkPointInterpolator>::New();
    coarseInterpolator->SetSourceData(fineGeometry->GetOutput()); // Pc data set to be probed by input points P
    coarseInterpolator->SetInputData(coarseGeometry->GetOutput());
    coarseInterpolator->SetKernel(kernel);
    coarseInterpolator->SetLocator(locator);
    coarseInterpolator->SetNullPointsStrategyToClosestPoint();
    coarseInterpolator->PassPointArraysOff();
    coarseInterpolator->Update();

    vtkSmartPointer<vtkDataSetMapper> coarseInterpolatorMapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
    coarseInterpolatorMapper->SetInputConnection(coarseInterpolator->GetOutputPort());
    coarseInterpolatorMapper->SelectColorArray(variable.c_str());
    coarseInterpolatorMapper->SetScalarModeToUsePointFieldData();
    coarseInterpolatorMapper->InterpolateScalarsBeforeMappingOn();
    coarseInterpolatorMapper->SetScalarRange(range);

    vtkSmartPointer<vtkActor> coarseInterpolatorActor =
      vtkSmartPointer<vtkActor>::New();
    coarseInterpolatorActor->SetMapper(coarseInterpolatorMapper);
    coarseInterpolatorActor->GetProperty()->SetEdgeVisibility(true);

    vtkSmartPointer<vtkRenderer> coarseInterpolatorRenderer =
      vtkSmartPointer<vtkRenderer>::New();
    coarseInterpolatorRenderer->AddActor(coarseInterpolatorActor);

    // Set the active scalar for the two inputs.
    // NOTE: InterpolateDataSetAttibutes does not interpolate field data.
    // To interpolate field data it must be added as the active scalar 
    coarseInterpolatedGrid->GetPointData()->SetActiveScalars(variable.c_str());
    coarseInterpolator->GetOutput()->GetPointData()->SetActiveScalars(variable.c_str());

    vtkSmartPointer<vtkInterpolateDataSetAttributes> coarseInterpolateAttributes =
      vtkSmartPointer<vtkInterpolateDataSetAttributes>::New();
    coarseInterpolateAttributes->AddInputData(0, coarseInterpolatedGrid);
    coarseInterpolateAttributes->AddInputData(0, coarseInterpolator->GetOutput());
    coarseInterpolateAttributes->SetT(0.5);
    coarseInterpolateAttributes->Update();

    vtkSmartPointer<vtkDataSetMapper> coarseInterpolateAttibutesMapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
    coarseInterpolateAttibutesMapper->SetInputConnection(coarseInterpolateAttributes->GetOutputPort());
    coarseInterpolateAttibutesMapper->SelectColorArray(variable.c_str());
    coarseInterpolateAttibutesMapper->SetScalarModeToUsePointFieldData();
    coarseInterpolateAttibutesMapper->InterpolateScalarsBeforeMappingOn();
    coarseInterpolateAttibutesMapper->SetScalarRange(range);

    vtkSmartPointer<vtkActor> coarseInterpolateAttributesActor =
      vtkSmartPointer<vtkActor>::New();
    coarseInterpolateAttributesActor->SetMapper(coarseInterpolateAttibutesMapper);
    coarseInterpolateAttributesActor->GetProperty()->SetEdgeVisibility(true);

    vtkSmartPointer<vtkRenderer> coarseInterpolateAttributesRenderer =
      vtkSmartPointer<vtkRenderer>::New();
    coarseInterpolateAttributesRenderer->AddActor(coarseInterpolateAttributesActor);

/////////////////////////
//  Window and Interactor

    vtkSmartPointer<vtkRenderWindow> window =
      vtkSmartPointer<vtkRenderWindow>::New();

    // Use the same camera for each renderer
    fineGeometryRenderer->SetActiveCamera(coarseRenderer->GetActiveCamera());
    coarseInterpolatorRenderer->SetActiveCamera(coarseRenderer->GetActiveCamera());
    coarseInterpolateAttributesRenderer->SetActiveCamera(coarseRenderer->GetActiveCamera());

    // Set each renderer color
    vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();
    coarseRenderer->SetBackground(
      colors->GetColor3d("Gainsboro").GetData());
    coarseInterpolatorRenderer->SetBackground(
      colors->GetColor3d("LightGrey").GetData());
    coarseInterpolateAttributesRenderer->SetBackground(
      colors->GetColor3d("Silver").GetData());
    fineGeometryRenderer->SetBackground(
      colors->GetColor3d("DarkGray").GetData());

    // Set the viewport for each renderer
    coarseRenderer->SetViewport(0, 0, 0.25, 1);
    coarseInterpolatorRenderer->SetViewport(0.25, 0, 0.5, 1);
    coarseInterpolateAttributesRenderer->SetViewport(0.5, 0, 0.75, 1);
    fineGeometryRenderer->SetViewport(0.75, 0, 1, 1);

    // Add the renderers
    window->AddRenderer(coarseRenderer);                      // low res
    window->AddRenderer(coarseInterpolatorRenderer);          // interpolated geometry
    window->AddRenderer(coarseInterpolateAttributesRenderer); // interpolated attributes
    window->AddRenderer(fineGeometryRenderer);                // hi res with point data

    // The size the window to hold 4 viewports of width 320
    window->SetSize(1280, 320);

    // Create the interactor
    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);
    window->Render();
    interactor->Initialize();

    // Reset the camera to a default view, shared by all
    coarseRenderer->ResetCamera();
    interactor->Start();

    return EXIT_SUCCESS;
}
