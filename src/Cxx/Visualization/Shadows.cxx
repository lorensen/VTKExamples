// The scene consists of
// * 4 actors: a rectangle, a box, a cone and a sphere. The box, the cone and
// the sphere are above the rectangle.
// * 2 spotlights: one in the direction of the box, another one in the
// direction of the sphere. Both lights are above the box, the cone and
// the sphere.
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>

#include <vtkOpenGLRenderer.h>

#include <vtkLightActor.h>
#include <vtkFrameBufferObject.h>
#include <vtkImageSinusoidSource.h>
#include <vtkImageData.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkLookupTable.h>
#include <vtkCamera.h>
#include <vtkCameraPass.h>
#include <vtkLightsPass.h>
#include <vtkSequencePass.h>
#include <vtkOpaquePass.h>
#include <vtkDepthPeelingPass.h>
#include <vtkTranslucentPass.h>
#include <vtkVolumetricPass.h>
#include <vtkOverlayPass.h>
#include <vtkRenderPassCollection.h>
#include <vtkShadowMapBakerPass.h>
#include <vtkShadowMapPass.h>
#include <vtkConeSource.h>
#include <vtkPlaneSource.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkInformation.h>
#include <vtkProperty.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>
#include <assert.h>
#include <vtkMath.h>
#include <vtkFrustumSource.h>
#include <vtkPlanes.h>
#include <vtkActorCollection.h>
#include <vtkPolyDataNormals.h>
#include <vtkPointData.h>


// For each spotlight, add a light frustum wireframe representation and a cone
// wireframe representation, colored with the light color.
void AddLightActors(vtkRenderer *r);

int main(int, char*[])
{
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(400,400);
  renderWindow->SetMultiSamples(0);

  renderWindow->SetAlphaBitPlanes(1);
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkOpenGLRenderer> renderer =
    vtkSmartPointer<vtkOpenGLRenderer>::New();
  renderWindow->AddRenderer(renderer);

  bool supported = vtkFrameBufferObject::IsSupported(renderWindow); // adapted from line 182 of vtkShadowMapPass.cxx

  if(!supported)
  {
    std::cerr << "Shadow rendering is not supported by the current video"
              << " driver!" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkCameraPass> cameraP =
    vtkSmartPointer<vtkCameraPass>::New();

  vtkSmartPointer<vtkOpaquePass> opaque =
    vtkSmartPointer<vtkOpaquePass>::New();

  vtkSmartPointer<vtkDepthPeelingPass> peeling =
    vtkSmartPointer<vtkDepthPeelingPass>::New();
  peeling->SetMaximumNumberOfPeels(200);
  peeling->SetOcclusionRatio(0.1);

  vtkSmartPointer<vtkTranslucentPass> translucent =
    vtkSmartPointer<vtkTranslucentPass>::New();
  peeling->SetTranslucentPass(translucent);

  vtkSmartPointer<vtkVolumetricPass> volume =
    vtkSmartPointer<vtkVolumetricPass>::New();
  vtkSmartPointer<vtkOverlayPass> overlay =
    vtkSmartPointer<vtkOverlayPass>::New();

  vtkSmartPointer<vtkLightsPass> lights =
    vtkSmartPointer<vtkLightsPass>::New();

  vtkSmartPointer<vtkSequencePass> opaqueSequence =
    vtkSmartPointer<vtkSequencePass>::New();

  vtkSmartPointer<vtkRenderPassCollection> passes2 =
    vtkSmartPointer<vtkRenderPassCollection>::New();
  passes2->AddItem(lights);
  passes2->AddItem(opaque);
  opaqueSequence->SetPasses(passes2);

  vtkSmartPointer<vtkCameraPass> opaqueCameraPass =
    vtkSmartPointer<vtkCameraPass>::New();
  opaqueCameraPass->SetDelegatePass(opaqueSequence);

  vtkSmartPointer<vtkShadowMapBakerPass> shadowsBaker =
    vtkSmartPointer<vtkShadowMapBakerPass>::New();
  shadowsBaker->SetOpaquePass(opaqueCameraPass);
  shadowsBaker->SetResolution(1024);
  // To cancel self-shadowing.
  shadowsBaker->SetPolygonOffsetFactor(3.1f);
  shadowsBaker->SetPolygonOffsetUnits(10.0f);

  vtkSmartPointer<vtkShadowMapPass> shadows =
    vtkSmartPointer<vtkShadowMapPass>::New();
  shadows->SetShadowMapBakerPass(shadowsBaker);
  shadows->SetOpaquePass(opaqueSequence);

  vtkSmartPointer<vtkSequencePass> seq =
    vtkSmartPointer<vtkSequencePass>::New();
  vtkSmartPointer<vtkRenderPassCollection> passes =
    vtkSmartPointer<vtkRenderPassCollection>::New();
  passes->AddItem(shadowsBaker);
  passes->AddItem(shadows);
  passes->AddItem(lights);
  passes->AddItem(peeling);
  passes->AddItem(volume);
  passes->AddItem(overlay);
  seq->SetPasses(passes);
  cameraP->SetDelegatePass(seq);

  renderer->SetPass(cameraP);

  vtkSmartPointer<vtkPlaneSource> rectangleSource =
    vtkSmartPointer<vtkPlaneSource>::New();
  rectangleSource->SetOrigin(-5.0,0.0,5.0);
  rectangleSource->SetPoint1(5.0,0.0,5.0);
  rectangleSource->SetPoint2(-5.0,0.0,-5.0);
  rectangleSource->SetResolution(100,100);

  vtkSmartPointer<vtkPolyDataMapper> rectangleMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  rectangleMapper->SetInputConnection(rectangleSource->GetOutputPort());

  rectangleMapper->SetScalarVisibility(0);

  vtkSmartPointer<vtkActor> rectangleActor =
    vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkInformation> rectangleKeyProperties =
    vtkSmartPointer<vtkInformation>::New();
  rectangleKeyProperties->Set(vtkShadowMapBakerPass::OCCLUDER(),0); // dummy val.
  rectangleKeyProperties->Set(vtkShadowMapBakerPass::RECEIVER(),0); // dummy val.
  rectangleActor->SetPropertyKeys(rectangleKeyProperties);

  rectangleActor->SetMapper(rectangleMapper);
  rectangleActor->SetVisibility(1);
  rectangleActor->GetProperty()->SetColor(1.0,1.0,1.0);

  vtkSmartPointer<vtkCubeSource> boxSource =
    vtkSmartPointer<vtkCubeSource>::New();
  boxSource->SetXLength(2.0);
  vtkSmartPointer<vtkPolyDataNormals> boxNormals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  boxNormals->SetInputConnection(boxSource->GetOutputPort());
  boxNormals->SetComputePointNormals(0);
  boxNormals->SetComputeCellNormals(1);
  boxNormals->Update();
  boxNormals->GetOutput()->GetPointData()->SetNormals(0);

  vtkSmartPointer<vtkPolyDataMapper> boxMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  boxMapper->SetInputConnection(boxNormals->GetOutputPort());
  boxMapper->SetScalarVisibility(0);

  vtkSmartPointer<vtkActor> boxActor =
    vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkInformation> boxKeyProperties =
    vtkSmartPointer<vtkInformation>::New();
  boxKeyProperties->Set(vtkShadowMapBakerPass::OCCLUDER(),0); // dummy val.
  boxKeyProperties->Set(vtkShadowMapBakerPass::RECEIVER(),0); // dummy val.
  boxActor->SetPropertyKeys(boxKeyProperties);

  boxActor->SetMapper(boxMapper);
  boxActor->SetVisibility(1);
  boxActor->SetPosition(-2.0,2.0,0.0);
  boxActor->GetProperty()->SetColor(1.0,0.0,0.0);

  vtkSmartPointer<vtkConeSource> coneSource =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->SetResolution(24);
  coneSource->SetDirection(1.0,1.0,1.0);
  vtkSmartPointer<vtkPolyDataMapper> coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(coneSource->GetOutputPort());
  coneMapper->SetScalarVisibility(0);

  vtkSmartPointer<vtkActor> coneActor =
    vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkInformation> coneKeyProperties=
    vtkSmartPointer<vtkInformation>::New();
  coneKeyProperties->Set(vtkShadowMapBakerPass::OCCLUDER(),0); // dummy val.
  coneKeyProperties->Set(vtkShadowMapBakerPass::RECEIVER(),0); // dummy val.
  coneActor->SetPropertyKeys(coneKeyProperties);

  coneActor->SetMapper(coneMapper);
  coneActor->SetVisibility(1);
  coneActor->SetPosition(0.0,1.0,1.0);
  coneActor->GetProperty()->SetColor(0.0,0.0,1.0);
//  coneActor->GetProperty()->SetLighting(false);

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetThetaResolution(32);
  sphereSource->SetPhiResolution(32);
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  sphereMapper->SetScalarVisibility(0);

  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkInformation> sphereKeyProperties =
    vtkSmartPointer<vtkInformation>::New();
  sphereKeyProperties->Set(vtkShadowMapBakerPass::OCCLUDER(),0); // dummy val.
  sphereKeyProperties->Set(vtkShadowMapBakerPass::RECEIVER(),0); // dummy val.
  sphereActor->SetPropertyKeys(sphereKeyProperties);
  sphereActor->SetMapper(sphereMapper);

  sphereActor->SetVisibility(1);
  sphereActor->SetPosition(2.0,2.0,-1.0);
  sphereActor->GetProperty()->SetColor(1.0,1.0,0.0);

  renderer->AddViewProp(rectangleActor);
  renderer->AddViewProp(boxActor);
  renderer->AddViewProp(coneActor);
  renderer->AddViewProp(sphereActor);

  // Spotlights.

  // lighting the box.
  vtkSmartPointer<vtkLight> l1 =
    vtkSmartPointer<vtkLight>::New();
  l1->SetPosition(-4.0,4.0,-1.0);
  l1->SetFocalPoint(boxActor->GetPosition());
  l1->SetColor(1.0,1.0,1.0);
  l1->SetPositional(1);
  renderer->AddLight(l1);
  l1->SetSwitch(1);

  // lighting the sphere
  vtkSmartPointer<vtkLight> l2 =
    vtkSmartPointer<vtkLight>::New();
  l2->SetPosition(4.0,5.0,1.0);
  l2->SetFocalPoint(sphereActor->GetPosition());
  l2->SetColor(1.0,0.0,1.0);
//  l2->SetColor(1.0,1.0,1.0);
  l2->SetPositional(1);
  renderer->AddLight(l2);
  l2->SetSwitch(1);

  AddLightActors(renderer);

  renderer->SetBackground(0.66,0.66,0.66);
  renderer->SetBackground2(157.0/255.0*0.66,186/255.0*0.66,192.0/255.0*0.66);
  renderer->SetGradientBackground(true);

  renderWindow->Render();
  if(peeling->GetLastRenderingUsedDepthPeeling())
  {
    std::cout << "depth peeling was used" << std::endl;
  }
  else
  {
    std::cout << "depth peeling was not used (alpha blending instead)" << std::endl;
  }

  renderer->ResetCamera();
  vtkSmartPointer<vtkCamera> camera = renderer->GetActiveCamera();
  camera->Azimuth(40.0);
  camera->Elevation(10.0);

  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}

// For each spotlight, add a light frustum wireframe representation and a cone
// wireframe representation, colored with the light color.
void AddLightActors(vtkRenderer *r)
{
  assert("pre: r_exists" && r!=0);

  vtkLightCollection *lights=r->GetLights();

  lights->InitTraversal();
  vtkLight *l=lights->GetNextItem();
  while(l!=0)
  {
    double angle=l->GetConeAngle();
    if(l->LightTypeIsSceneLight() && l->GetPositional()
       && angle<180.0) // spotlight
    {
      vtkSmartPointer<vtkLightActor> la=
        vtkSmartPointer<vtkLightActor>::New();
      la->SetLight(l);
      r->AddViewProp(la);
    }
    l=lights->GetNextItem();
  }
}
