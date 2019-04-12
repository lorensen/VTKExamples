#include <vtkStreamTracer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLookupTable.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkTubeFilter.h>

#include <vtkNamedColors.h>

//// LOx post CFD case study

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " postxyz.bin postq.bin" << std::endl;
    return EXIT_FAILURE;
  }
// read data
//
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->AutoDetectFormatOn();
  pl3d->SetXYZFileName(argv[1]);
  pl3d->SetQFileName(argv[2]);
  pl3d->SetScalarFunctionNumber(153);
  pl3d->SetVectorFunctionNumber(200);
  pl3d->Update();

  vtkStructuredGrid *sg =
    dynamic_cast<vtkStructuredGrid*>(pl3d->GetOutput()->GetBlock(0));

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

//blue to red lut
//
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetHueRange(0.667, 0.0);

// computational planes
  vtkSmartPointer<vtkStructuredGridGeometryFilter> floorComp =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  floorComp->SetExtent(0, 37, 0, 75, 0, 0);
  floorComp->SetInputData(sg);
  floorComp->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> floorMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  floorMapper->SetInputConnection(floorComp->GetOutputPort());
  floorMapper->ScalarVisibilityOff();
  floorMapper->SetLookupTable(lut);
  
  vtkSmartPointer<vtkActor> floorActor =
    vtkSmartPointer<vtkActor>::New();
  floorActor->SetMapper(floorMapper);
  floorActor->GetProperty()->SetRepresentationToWireframe();
  floorActor->GetProperty()->SetColor(colors->GetColor3d("Beige").GetData());
  floorActor->GetProperty()->SetLineWidth(2);

  vtkSmartPointer<vtkStructuredGridGeometryFilter> subFloorComp =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();

  subFloorComp->SetExtent(0, 37, 0, 15, 22, 22);
  subFloorComp->SetInputData(sg);

  vtkSmartPointer<vtkPolyDataMapper> subFloorMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  subFloorMapper->SetInputConnection(subFloorComp->GetOutputPort());
  subFloorMapper->SetLookupTable(lut);
  subFloorMapper->SetScalarRange(sg->GetScalarRange());

  vtkSmartPointer<vtkActor> subFloorActor =
    vtkSmartPointer<vtkActor>::New();

  subFloorActor->SetMapper(subFloorMapper);

  vtkSmartPointer<vtkStructuredGridGeometryFilter> subFloor2Comp =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  subFloor2Comp->SetExtent(0, 37, 60, 75, 22, 22);
  subFloor2Comp->SetInputData(sg);
  
  vtkSmartPointer<vtkPolyDataMapper> subFloor2Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  subFloor2Mapper->SetInputConnection(subFloor2Comp->GetOutputPort());
  subFloor2Mapper->SetLookupTable(lut);
  subFloor2Mapper->SetScalarRange(sg->GetScalarRange());

  vtkSmartPointer<vtkActor> subFloor2Actor =
    vtkSmartPointer<vtkActor>::New();

  subFloor2Actor->SetMapper(subFloor2Mapper);

  vtkSmartPointer<vtkStructuredGridGeometryFilter> postComp =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();

  postComp->SetExtent(10, 10, 0, 75, 0, 37);
  postComp->SetInputData(sg);

  vtkSmartPointer<vtkPolyDataMapper> postMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  postMapper->SetInputConnection(postComp->GetOutputPort());
  postMapper->SetLookupTable(lut);
  postMapper->SetScalarRange(sg->GetScalarRange());

  vtkSmartPointer<vtkActor> postActor =
    vtkSmartPointer<vtkActor>::New();
  postActor->SetMapper(postMapper);
  postActor->GetProperty()->SetColor(colors->GetColor3d("Beige").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> fanComp =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  fanComp->SetExtent(0, 37, 38, 38, 0, 37);
  fanComp->SetInputData(sg);

  vtkSmartPointer<vtkPolyDataMapper> fanMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  fanMapper->SetInputConnection(fanComp->GetOutputPort());
  fanMapper->SetLookupTable(lut);
  fanMapper->SetScalarRange(sg->GetScalarRange());
  
  vtkSmartPointer<vtkActor> fanActor =
    vtkSmartPointer<vtkActor>::New();

  fanActor->SetMapper(fanMapper);
  fanActor->GetProperty()->SetColor(colors->GetColor3d("Beige").GetData());

// streamers
//
// spherical seed points
  vtkSmartPointer<vtkPointSource> rake =
    vtkSmartPointer<vtkPointSource>::New();
  rake->SetCenter(-0.74, 0, 0.3);
  rake->SetNumberOfPoints(10);

// a line of seed points
  vtkSmartPointer<vtkStructuredGridGeometryFilter> seedsComp =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  seedsComp->SetExtent(10, 10, 37, 39, 1, 27);
  seedsComp->SetInputData(sg);
  
  vtkSmartPointer<vtkStreamTracer> streamers =
    vtkSmartPointer<vtkStreamTracer>::New();
  streamers->SetInputConnection(pl3d->GetOutputPort());

// streamers SetSource [rake GetOutput]
  streamers->SetSourceConnection(seedsComp->GetOutputPort());
  streamers->SetMaximumPropagation(250);
  streamers->SetInitialIntegrationStep(.2);
  streamers->SetMinimumIntegrationStep(.01);
  streamers->SetIntegratorType(2);
  streamers->Update();

  vtkSmartPointer<vtkTubeFilter> tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection(streamers->GetOutputPort());
  tubes->SetNumberOfSides(8);
  tubes->SetRadius(.08);
  tubes->SetVaryRadius(0);

  vtkSmartPointer<vtkPolyDataMapper> mapTubes =
    vtkSmartPointer<vtkPolyDataMapper>::New();

  mapTubes->SetInputConnection(tubes->GetOutputPort());
  mapTubes->SetScalarRange(sg->GetScalarRange());

  vtkSmartPointer<vtkActor> tubesActor =
    vtkSmartPointer<vtkActor>::New();
  tubesActor->SetMapper(mapTubes);

// outline
  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputData(sg);

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Beige").GetData());


// Create graphics stuff
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(outlineActor);
  ren1->AddActor(floorActor);
//  ren1->AddActor(subFloorActor);
//  ren1->AddActor(subFloor2Actor);
  ren1->AddActor(postActor);
//  ren1->AddActor(fanActor);
  ren1->AddActor(tubesActor);

  vtkSmartPointer<vtkCamera> aCam =
    vtkSmartPointer<vtkCamera>::New();
  aCam->SetFocalPoint(2.47736, -0.150024, 2.42361);
  aCam->SetPosition(1.57547, -13.4601, 5.47872);
  aCam->SetViewUp(0.00197003, 0.223588, 0.974682);
//  aCam->Dolly(4.0);
  aCam->SetClippingRange(1, 100);

  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  ren1->SetActiveCamera(aCam);
  renWin->SetSize(640, 480);

  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
