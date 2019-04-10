/*
Modified from VTK/Filters/Texture/Testing/Python/textureThreshold.py.

Demonstrating texture thresholding applied to scalar data from a simulation of
fluid flow->
    There are three planes cutting the blunt fin with different thresholds set.
     From the left, the scalar threshold is set so that:
       1) Only data with a scalar value greater than or equal to 1.5 is shown.
       2) Only data with a scalar value less than or equal to 1.5 is shown.
       3) Only data with a scalar value between 1.5 and 1.8 inclusive is
shown.
*/

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkStructuredPointsReader.h>
#include <vtkTexture.h>
#include <vtkThresholdTextureCoords.h>

#include <array>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cout << "Usage: " << argv[0] << " filename1 filename2 filename3"
              << std::endl;
    std::cout << "where: filename1 is bluntfinxyz.bin,\n"
              << "       filename2 is bluntfinq.bin and\n"
              << "       filename3 is texThres2.vtk." << std::endl;
    return EXIT_FAILURE;
  }

  std::string dataFn1 = argv[1];
  std::string dataFn2 = argv[2];
  std::string textureFn = argv[3];

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Read the data.
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->SetXYZFileName(dataFn1.c_str());
  pl3d->SetQFileName(dataFn2.c_str());
  pl3d->SetScalarFunctionNumber(100); // Density
  pl3d->SetVectorFunctionNumber(202); // Momentum
  pl3d->Update();

  vtkStructuredGrid* output =
    dynamic_cast<vtkStructuredGrid*>(pl3d->GetOutput()->GetBlock(0));

  // Make the wall (floor).
  vtkSmartPointer<vtkStructuredGridGeometryFilter> wall =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  wall->SetInputData(output);
  wall->SetExtent(0, 100, 0, 0, 0, 100);
  vtkSmartPointer<vtkPolyDataMapper> wallMap =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  wallMap->SetInputConnection(wall->GetOutputPort());
  wallMap->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> wallActor = vtkSmartPointer<vtkActor>::New();
  wallActor->SetMapper(wallMap);
  wallActor->GetProperty()->SetColor(colors->GetColor3d("PeachPuff").GetData());

  // Make the fin (rear wall).
  vtkSmartPointer<vtkStructuredGridGeometryFilter> fin =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  fin->SetInputData(output);
  fin->SetExtent(0, 100, 0, 100, 0, 0);
  vtkSmartPointer<vtkPolyDataMapper> finMap =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  finMap->SetInputConnection(fin->GetOutputPort());
  finMap->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> finActor = vtkSmartPointer<vtkActor>::New();
  finActor->SetMapper(finMap);
  finActor->GetProperty()->SetColor(
    colors->GetColor3d("DarkSlateGray").GetData());

  // Get the texture.
  vtkSmartPointer<vtkStructuredPointsReader> tmap =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  tmap->SetFileName(textureFn.c_str());
  vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(tmap->GetOutputPort());
  texture->InterpolateOff();
  texture->RepeatOff();

  // Create the rendering window, renderer, and interactive renderer.
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Make the planes to threshold and texture.
  std::vector<vtkSmartPointer<vtkStructuredGridGeometryFilter>> plane;
  std::vector<vtkSmartPointer<vtkThresholdTextureCoords>> thresh;
  std::vector<vtkSmartPointer<vtkDataSetMapper>> planeMap;
  std::vector<vtkSmartPointer<vtkActor>> planeActor;
  // Define the extents of planes that we will use.
  std::vector<std::array<int, 6>> planeExtents{{10, 10, 0, 100, 0, 100},
                                               {30, 30, 0, 100, 0, 100},
                                               {35, 35, 0, 100, 0, 100}};
  // Now set up the pipeline.
  for (unsigned int i = 0; i < planeExtents.size(); ++i)
  {
    plane.push_back(vtkSmartPointer<vtkStructuredGridGeometryFilter>::New());
    plane[i]->SetInputData(output);
    plane[i]->SetExtent(planeExtents[i].data());
    thresh.push_back(vtkSmartPointer<vtkThresholdTextureCoords>::New());
    thresh[i]->SetInputConnection(plane[i]->GetOutputPort());
    thresh[i]->SetInputConnection(plane[i]->GetOutputPort());
    // If you want an image similar to Fig 9-43(a) in the VTK textbook, set
    // thresh[i]->ThresholdByUpper(1.5); for all planes.
    switch (i)
    {
      case 0:
      default:
        thresh[i]->ThresholdByUpper(1.5);
        break;
      case 1:
        thresh[i]->ThresholdByLower(1.5);
        break;
      case 2:
        thresh[i]->ThresholdBetween(1.5, 1.8);
        break;
    }
    planeMap.push_back(vtkSmartPointer<vtkDataSetMapper>::New());
    planeMap[i]->SetInputConnection(thresh[i]->GetOutputPort());
    planeMap[i]->SetScalarRange(output->GetScalarRange());
    planeActor.push_back(vtkSmartPointer<vtkActor>::New());
    planeActor[i]->SetMapper(planeMap[i]);
    planeActor[i]->SetTexture(texture);
    // The slight transparency gives a nice effect.
    planeActor[i]->GetProperty()->SetOpacity(0.999);
    ren->AddActor(planeActor[i]);
  }
  // Get an outline of the data set for context.
  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputData(output);
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());
  outlineActor->SetMapper(outlineMapper);

  // Add the remaining actors to the renderer, set the background and size.
  ren->AddActor(outlineActor);
  ren->AddActor(wallActor);
  ren->AddActor(finActor);
  ren->SetBackground(colors->GetColor3d("MistyRose").GetData());
  renWin->SetSize(512, 512);
  vtkSmartPointer<vtkCamera> cam = vtkSmartPointer<vtkCamera>::New();
  cam->SetClippingRange(1.51176, 75.5879);
  cam->SetFocalPoint(2.33749, 2.96739, 3.61023);
  cam->SetPosition(10.8787, 5.27346, 15.8687);
  cam->SetViewAngle(30);
  cam->SetViewUp(-0.0610856, 0.987798, -0.143262);
  ren->SetActiveCamera(cam);

  renWin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
