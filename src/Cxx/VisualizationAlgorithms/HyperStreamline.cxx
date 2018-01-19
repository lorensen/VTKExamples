#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkHyperStreamline.h>
#include <vtkImageData.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkLogLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPointLoad.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main (int, char *[])
{
// Create the RenderWindow, Renderer and interactive renderer
//
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetMultiSamples(0);
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

//set VTK_INTEGRATE_BOTH_DIRECTIONS 2

//
// generate tensors
  vtkSmartPointer<vtkPointLoad> ptLoad =
    vtkSmartPointer<vtkPointLoad>::New();
  ptLoad->SetLoadValue(100.0);
  ptLoad->SetSampleDimensions(20, 20, 20);
  ptLoad->ComputeEffectiveStressOn();
  ptLoad->SetModelBounds(-10, 10, -10, 10, -10, 10);
  ptLoad->Update();

// Generate hyperstreamlines
  vtkSmartPointer<vtkHyperStreamline> s1 =
    vtkSmartPointer<vtkHyperStreamline>::New();
  s1->SetInputData(ptLoad->GetOutput());
  s1->SetStartPosition(9, 9, -9);
  s1->IntegrateMinorEigenvector();
  s1->SetMaximumPropagationDistance(18.0);
  s1->SetIntegrationStepLength(0.1);
  s1->SetStepLength(0.01);
  s1->SetRadius(0.25);
  s1->SetNumberOfSides(18);
  s1->SetIntegrationDirectionToIntegrateBothDirections();
  s1->Update();

// Map hyperstreamlines
  vtkSmartPointer<vtkLogLookupTable> lut =
    vtkSmartPointer<vtkLogLookupTable>::New();
  lut->SetHueRange(.6667, 0.0);

  vtkSmartPointer<vtkPolyDataMapper> s1Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  s1Mapper->SetInputConnection(s1->GetOutputPort());
  s1Mapper->SetLookupTable(lut);
  s1Mapper->SetScalarRange(ptLoad->GetOutput()->GetScalarRange());

  vtkSmartPointer<vtkActor> s1Actor =
    vtkSmartPointer<vtkActor>::New();
  s1Actor->SetMapper(s1Mapper);

  vtkSmartPointer<vtkHyperStreamline> s2 =
    vtkSmartPointer<vtkHyperStreamline>::New();
  s2->SetInputData(ptLoad->GetOutput());
  s2->SetStartPosition(-9, -9, -9);
  s2->IntegrateMinorEigenvector();
  s2->SetMaximumPropagationDistance(18.0);
  s2->SetIntegrationStepLength(0.1);
  s2->SetStepLength(0.01);
  s2->SetRadius(0.25);
  s2->SetNumberOfSides(18);
  s2->SetIntegrationDirectionToIntegrateBothDirections();
  s2->Update();

  vtkSmartPointer<vtkPolyDataMapper> s2Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  s2Mapper->SetInputConnection(s2->GetOutputPort());
  s2Mapper->SetLookupTable(lut);
  s2Mapper->SetScalarRange(ptLoad->GetOutput()->GetScalarRange());

  vtkSmartPointer<vtkActor> s2Actor =
    vtkSmartPointer<vtkActor>::New();
  s2Actor->SetMapper(s2Mapper);

  vtkSmartPointer<vtkHyperStreamline> s3 =
    vtkSmartPointer<vtkHyperStreamline>::New();
  s3->SetInputData(ptLoad->GetOutput());
  s3->SetStartPosition(9, -9, -9);
  s3->IntegrateMinorEigenvector();
  s3->SetMaximumPropagationDistance(18.0);
  s3->SetIntegrationStepLength(0.1);
  s3->SetStepLength(0.01);
  s3->SetRadius(0.25);
  s3->SetNumberOfSides(18);
  s3->SetIntegrationDirectionToIntegrateBothDirections();
  s3->Update();

  vtkSmartPointer<vtkPolyDataMapper> s3Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  s3Mapper->SetInputConnection(s3->GetOutputPort());
  s3Mapper->SetLookupTable(lut);
  s3Mapper->SetScalarRange(ptLoad->GetOutput()->GetScalarRange());

  vtkSmartPointer<vtkActor> s3Actor =
    vtkSmartPointer<vtkActor>::New();
  s3Actor->SetMapper(s3Mapper);

  vtkSmartPointer<vtkHyperStreamline> s4 =
    vtkSmartPointer<vtkHyperStreamline>::New();
  s4->SetInputData(ptLoad->GetOutput());
  s4->SetStartPosition(-9, 9, -9);
  s4->IntegrateMinorEigenvector();
  s4->SetMaximumPropagationDistance(18.0);
  s4->SetIntegrationStepLength(0.1);
  s4->SetStepLength(0.01);
  s4->SetRadius(0.25);
  s4->SetNumberOfSides(18);
  s4->SetIntegrationDirectionToIntegrateBothDirections();
  s4->Update();

  vtkSmartPointer<vtkPolyDataMapper> s4Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  s4Mapper->SetInputConnection(s4->GetOutputPort());
  s4Mapper->SetLookupTable(lut);
  s4Mapper->SetScalarRange(ptLoad->GetOutput()->GetScalarRange());

  vtkSmartPointer<vtkActor> s4Actor =
    vtkSmartPointer<vtkActor>::New();
  s4Actor->SetMapper(s4Mapper);

// plane for context
//
  vtkSmartPointer<vtkImageDataGeometryFilter> g =
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  g->SetInputData(ptLoad->GetOutput());
  g->SetExtent(0, 100, 0, 100, 0, 0);
  g->Update(); //for scalar range

  vtkSmartPointer<vtkPolyDataMapper> gm =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  gm->SetInputConnection(g->GetOutputPort());
  gm->SetScalarRange(g->GetOutput()->GetScalarRange());

  vtkSmartPointer<vtkActor> ga =
    vtkSmartPointer<vtkActor>::New();
  ga->SetMapper(gm);

// Create outline around data
//
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputData(ptLoad->GetOutput());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

// Create cone indicating application of load
//
  vtkSmartPointer<vtkConeSource> coneSrc =
    vtkSmartPointer<vtkConeSource>::New();
  coneSrc->SetRadius(.5);
  coneSrc->SetHeight(2);

  vtkSmartPointer<vtkPolyDataMapper> coneMap =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMap->SetInputConnection(coneSrc->GetOutputPort());

  vtkSmartPointer<vtkActor> coneActor =
    vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMap);
  coneActor->SetPosition(0, 0, 11);
  coneActor->RotateY(90);
  coneActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  camera->SetFocalPoint(0.113766, -1.13665, -1.01919);
  camera->SetPosition(-29.4886, -63.1488, 26.5807);
  camera->SetViewAngle(24.4617);
  camera->SetViewUp(0.17138, 0.331163, 0.927879);
  camera->SetClippingRange(1, 100);

  ren1->AddActor(s1Actor);
  ren1->AddActor(s2Actor);
  ren1->AddActor(s3Actor);
  ren1->AddActor(s4Actor);
  ren1->AddActor(outlineActor);
  ren1->AddActor(coneActor);
  ren1->AddActor(ga);
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  ren1->SetActiveCamera(camera);

  renWin->SetSize(640, 480);
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
