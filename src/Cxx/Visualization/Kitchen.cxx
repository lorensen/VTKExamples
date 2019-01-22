#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLineSource.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkStreamTracer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkStructuredGridReader.h>

#include <array>

int main( int argc, char *argv[] )
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " kitchen.vtk" << std::endl;
    return EXIT_FAILURE;
  }
  double range[2];
  double maxVelocity = 0.0, maxTime = 0.0;
  
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the furniture colors.
  std::array<unsigned char , 4> furnColor{{204, 204, 153, 255}};
    colors->SetColor("Furniture", furnColor.data());

  vtkSmartPointer<vtkRenderer> aren =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(aren);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
//
// Read data
//
  vtkSmartPointer<vtkStructuredGridReader> reader =
    vtkSmartPointer<vtkStructuredGridReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update(); //force a read to occur
  reader->GetOutput()->GetLength();

  if ( reader->GetOutput()->GetPointData()->GetScalars() )
  {
    reader->GetOutput()->GetPointData()->GetScalars()->GetRange(range);
  }
  if ( reader->GetOutput()->GetPointData()->GetVectors() )
  {
    maxVelocity = reader->GetOutput()->GetPointData()->GetVectors()->GetMaxNorm();
    maxTime = 4.0*reader->GetOutput()->GetLength()/maxVelocity ;
  }
//
// Outline around data
//
  vtkSmartPointer<vtkStructuredGridOutlineFilter> outlineF =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outlineF->SetInputConnection(reader->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outlineF->GetOutputPort());
  vtkSmartPointer<vtkActor> outline =
    vtkSmartPointer<vtkActor>::New();
  outline->SetMapper(outlineMapper);
  outline->GetProperty()->SetColor(colors->GetColor3d("LampBlack").GetData());
//
// Set up shaded surfaces (i.e., supporting geometry)
//
  vtkSmartPointer<vtkStructuredGridGeometryFilter> doorGeom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  doorGeom->SetInputConnection(reader->GetOutputPort());
  doorGeom->SetExtent(27,27,14,18,0,11);
  vtkSmartPointer<vtkPolyDataMapper> mapDoor =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapDoor->SetInputConnection(doorGeom->GetOutputPort());
  mapDoor->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> door =
    vtkSmartPointer<vtkActor>::New();
  door->SetMapper(mapDoor);
  door->GetProperty()->SetColor(colors->GetColor3d("Burlywood").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> window1Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  window1Geom->SetInputConnection(reader->GetOutputPort());
  window1Geom->SetExtent(0,0,9,18,6,12);
  vtkSmartPointer<vtkPolyDataMapper> mapWindow1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapWindow1->SetInputConnection(window1Geom->GetOutputPort());
  mapWindow1->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> window1 =
    vtkSmartPointer<vtkActor>::New();
  window1->SetMapper(mapWindow1);
  window1->GetProperty()->SetColor(colors->GetColor3d("SkyBlue").GetData());
  window1->GetProperty()->SetOpacity(.6);

  vtkSmartPointer<vtkStructuredGridGeometryFilter> window2Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  window2Geom->SetInputConnection(reader->GetOutputPort());
  window2Geom->SetExtent(5,12,23,23,6,12);
  vtkSmartPointer<vtkPolyDataMapper> mapWindow2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapWindow2->SetInputConnection(window2Geom->GetOutputPort());
  mapWindow2->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> window2 =
    vtkSmartPointer<vtkActor>::New();
  window2->SetMapper(mapWindow2);
  window2->GetProperty()->SetColor(colors->GetColor3d("SkyBlue").GetData());
  window2->GetProperty()->SetOpacity(.6);

  vtkSmartPointer<vtkStructuredGridGeometryFilter> klower1Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  klower1Geom->SetInputConnection(reader->GetOutputPort());
  klower1Geom->SetExtent(17,17,0,11,0,6);
  vtkSmartPointer<vtkPolyDataMapper> mapKlower1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapKlower1->SetInputConnection(klower1Geom->GetOutputPort());
  mapKlower1->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> klower1 =
    vtkSmartPointer<vtkActor>::New();
  klower1->SetMapper(mapKlower1);
  klower1->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> klower2Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  klower2Geom->SetInputConnection(reader->GetOutputPort());
  klower2Geom->SetExtent(19,19,0,11,0,6);
  vtkSmartPointer<vtkPolyDataMapper> mapKlower2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapKlower2->SetInputConnection(klower2Geom->GetOutputPort());
  mapKlower2->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> klower2 =
    vtkSmartPointer<vtkActor>::New();
  klower2->SetMapper(mapKlower2);
  klower2->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> klower3Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  klower3Geom->SetInputConnection(reader->GetOutputPort());
  klower3Geom->SetExtent(17,19,0,0,0,6);
  vtkSmartPointer<vtkPolyDataMapper> mapKlower3 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapKlower3->SetInputConnection(klower3Geom->GetOutputPort());
  mapKlower3->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> klower3 =
    vtkSmartPointer<vtkActor>::New();
  klower3->SetMapper(mapKlower3);
  klower3->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> klower4Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  klower4Geom->SetInputConnection(reader->GetOutputPort());
  klower4Geom->SetExtent(17,19,11,11,0,6);
  vtkSmartPointer<vtkPolyDataMapper> mapKlower4 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapKlower4->SetInputConnection(klower4Geom->GetOutputPort());
  mapKlower4->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> klower4 =
    vtkSmartPointer<vtkActor>::New();
  klower4->SetMapper(mapKlower4);
  klower4->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> klower5Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  klower5Geom->SetInputConnection(reader->GetOutputPort());
  klower5Geom->SetExtent(17,19,0,11,0,0);
  vtkSmartPointer<vtkPolyDataMapper> mapKlower5 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapKlower5->SetInputConnection(klower5Geom->GetOutputPort());
  mapKlower5->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> klower5 =
    vtkSmartPointer<vtkActor>::New();
  klower5->SetMapper(mapKlower5);
  klower5->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> klower6Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  klower6Geom->SetInputConnection(reader->GetOutputPort());
  klower6Geom->SetExtent(17,19,0,7,6,6);
  vtkSmartPointer<vtkPolyDataMapper> mapKlower6 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapKlower6->SetInputConnection(klower6Geom->GetOutputPort());
  mapKlower6->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> klower6 =
    vtkSmartPointer<vtkActor>::New();
  klower6->SetMapper(mapKlower6);
  klower6->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> klower7Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  klower7Geom->SetInputConnection(reader->GetOutputPort());
  klower7Geom->SetExtent(17,19,9,11,6,6);
  vtkSmartPointer<vtkPolyDataMapper> mapKlower7 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapKlower7->SetInputConnection(klower7Geom->GetOutputPort());
  mapKlower7->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> klower7 =
    vtkSmartPointer<vtkActor>::New();
  klower7->SetMapper(mapKlower7);
  klower7->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> hood1Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  hood1Geom->SetInputConnection(reader->GetOutputPort());
  hood1Geom->SetExtent(17,17,0,11,11,16);
  vtkSmartPointer<vtkPolyDataMapper> mapHood1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapHood1->SetInputConnection(hood1Geom->GetOutputPort());
  mapHood1->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> hood1 =
    vtkSmartPointer<vtkActor>::New();
  hood1->SetMapper(mapHood1);
  hood1->GetProperty()->SetColor(colors->GetColor3d("Silver").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> hood2Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  hood2Geom->SetInputConnection(reader->GetOutputPort());
  hood2Geom->SetExtent(19,19,0,11,11,16);
  vtkSmartPointer<vtkPolyDataMapper> mapHood2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapHood2->SetInputConnection(hood2Geom->GetOutputPort());
  mapHood2->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> hood2 =
    vtkSmartPointer<vtkActor>::New();
  hood2->SetMapper(mapHood2);
  hood2->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> hood3Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  hood3Geom->SetInputConnection(reader->GetOutputPort());
  hood3Geom->SetExtent(17,19,0,0,11,16);
  vtkSmartPointer<vtkPolyDataMapper> mapHood3 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapHood3->SetInputConnection(hood3Geom->GetOutputPort());
  mapHood3->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> hood3 =
    vtkSmartPointer<vtkActor>::New();
  hood3->SetMapper(mapHood3);
  hood3->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> hood4Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  hood4Geom->SetInputConnection(reader->GetOutputPort());
  hood4Geom->SetExtent(17,19,11,11,11,16);
  vtkSmartPointer<vtkPolyDataMapper> mapHood4 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapHood4->SetInputConnection(hood4Geom->GetOutputPort());
  mapHood4->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> hood4 =
    vtkSmartPointer<vtkActor>::New();
  hood4->SetMapper(mapHood4);
  hood4->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> hood6Geom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  hood6Geom->SetInputConnection(reader->GetOutputPort());
  hood6Geom->SetExtent(17,19,0,11,16,16);
  vtkSmartPointer<vtkPolyDataMapper> mapHood6 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapHood6->SetInputConnection(hood6Geom->GetOutputPort());
  mapHood6->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> hood6 =
    vtkSmartPointer<vtkActor>::New();
  hood6->SetMapper(mapHood6);
  hood6->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> cookingPlateGeom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  cookingPlateGeom->SetInputConnection(reader->GetOutputPort());
  cookingPlateGeom->SetExtent(17,19,7,9,6,6);
  vtkSmartPointer<vtkPolyDataMapper> mapCookingPlate =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapCookingPlate->SetInputConnection(cookingPlateGeom->GetOutputPort());
  mapCookingPlate->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> cookingPlate =
    vtkSmartPointer<vtkActor>::New();
  cookingPlate->SetMapper(mapCookingPlate);
  cookingPlate->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> filterGeom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  filterGeom->SetInputConnection(reader->GetOutputPort());
  filterGeom->SetExtent(17,19,7,9,11,11);
  vtkSmartPointer<vtkPolyDataMapper> mapFilter =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapFilter->SetInputConnection(filterGeom->GetOutputPort());
  mapFilter->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> filter =
    vtkSmartPointer<vtkActor>::New();
  filter->SetMapper(mapFilter);
  filter->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());
//
// regular streamlines
//
  vtkSmartPointer<vtkLineSource> line =
    vtkSmartPointer<vtkLineSource>::New();
  line->SetResolution(39);
  line->SetPoint1(0.08, 2.50, 0.71);
  line->SetPoint2(0.08, 4.50, 0.71);
  vtkSmartPointer<vtkPolyDataMapper> rakeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  rakeMapper->SetInputConnection(line->GetOutputPort());
  vtkSmartPointer<vtkActor> rake =
    vtkSmartPointer<vtkActor>::New();
  rake->SetMapper(rakeMapper);

  vtkSmartPointer<vtkStreamTracer> streamers =
    vtkSmartPointer<vtkStreamTracer>::New();
  //streamers->DebugOn();
  streamers->SetInputConnection(reader->GetOutputPort());
  streamers->SetSourceConnection(line->GetOutputPort());
  streamers->SetMaximumPropagation(maxTime);
  streamers->SetInitialIntegrationStep(.5);
  streamers->SetMinimumIntegrationStep(.1);
  streamers->SetIntegratorType(2);
  streamers->Update();

  vtkSmartPointer<vtkPolyDataMapper> streamersMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  streamersMapper->SetInputConnection(streamers->GetOutputPort());
  streamersMapper->SetScalarRange(range);

  vtkSmartPointer<vtkActor> lines =
    vtkSmartPointer<vtkActor>::New();
  lines->SetMapper(streamersMapper);
  lines->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

  aren->TwoSidedLightingOn();

  aren->AddActor(outline);
  aren->AddActor(door);
  aren->AddActor(window1);
  aren->AddActor(window2);
  aren->AddActor(klower1);
  aren->AddActor(klower2);
  aren->AddActor(klower3);
  aren->AddActor(klower4);
  aren->AddActor(klower5);
  aren->AddActor(klower6);
  aren->AddActor(klower7);
  aren->AddActor(hood1);
  aren->AddActor(hood2);
  aren->AddActor(hood3);
  aren->AddActor(hood4);
  aren->AddActor(hood6);
  aren->AddActor(cookingPlate);
  aren->AddActor(filter);
  aren->AddActor(lines);
  aren->AddActor(rake);

  aren->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkCamera> aCamera =
    vtkSmartPointer<vtkCamera>::New();
  aren->SetActiveCamera(aCamera);
  aren->ResetCamera();

  aCamera->SetFocalPoint(3.505, 2.505, 1.255);
  aCamera->SetPosition(3.505, 24.6196, 1.255);
  aCamera->SetViewUp(0,0,1);
  aCamera->Azimuth(60);
  aCamera->Elevation(30);
  aCamera->Dolly(1.5);
  aren->ResetCameraClippingRange();

  renWin->SetSize(640, 512);
  renWin->Render();

  // interact with data
  iren->Start();

  return EXIT_SUCCESS;
}
