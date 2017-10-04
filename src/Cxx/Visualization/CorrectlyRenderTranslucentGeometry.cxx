#include <vtkSmartPointer.h>
#include <vtkDepthSortPolyData.h>

#include <vtkSphereSource.h>
#include <vtkAppendPolyData.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTimerLog.h>
#include <vtkTransform.h>

/**
 * Generate a bunch of overlapping spheres within one poly data set:
 * one big sphere evenly surrounded by four small spheres that intersect the
 * centered sphere.
 * @param theta sphere sampling resolution (THETA)
 * @param phi sphere sampling resolution (PHI)
 * @return the set of spheres within one logical poly data set
 **/
vtkSmartPointer<vtkAppendPolyData> GenerateOverlappingBunchOfSpheres(int theta,
                                                                     int phi)
{
  vtkSmartPointer<vtkAppendPolyData> appendData =
    vtkSmartPointer<vtkAppendPolyData>::New();

  for (int i = 0; i < 5; i++)
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(theta);
    sphereSource->SetPhiResolution(phi);
    sphereSource->SetRadius(0.5); // all spheres except the center
                                  // one should have radius = 0.5
    switch (i)
    {
      case 0:
        sphereSource->SetRadius(1);
        sphereSource->SetCenter(0, 0, 0); break;
      case 1:
        sphereSource->SetCenter(1, 0, 0); break;
      case 2:
        sphereSource->SetCenter(-1, 0, 0); break;
      case 3:
        sphereSource->SetCenter(0, 1, 0); break;
      case 4:
        sphereSource->SetCenter(0, -1, 0); break;
    }
    sphereSource->Update();
    appendData->AddInputConnection(sphereSource->GetOutputPort());
  }

  return appendData;
}

/**
 * Setup the rendering environment for depth peeling (general depth peeling
 * support is requested).
 * @see IsDepthPeelingSupported()
 * @param renderWindow a valid openGL-supporting render window
 * @param renderer a valid renderer instance
 * @param maxNoOfPeels maximum number of depth peels (multi-pass rendering)
 * @param occulusionRation the occlusion ration (0.0 means a perfect image,
 * >0.0 means a non-perfect image which in general results in faster rendering)
 * @return TRUE if depth peeling could be set up
 */
bool SetupEnvironmentForDepthPeeling(
  vtkSmartPointer<vtkRenderWindow> renderWindow,
  vtkSmartPointer<vtkRenderer> renderer, int maxNoOfPeels,
  double occlusionRatio)
{
  if (!renderWindow || !renderer)
    return false;

  // 1. Use a render window with alpha bits (as initial value is 0 (false)):
  renderWindow->SetAlphaBitPlanes(true);

  // 2. Force to not pick a framebuffer with a multisample buffer
  // (as initial value is 8):
  renderWindow->SetMultiSamples(0);

  // 3. Choose to use depth peeling (if supported) (initial value is 0 (false)):
  renderer->SetUseDepthPeeling(true);

  // 4. Set depth peeling parameters
  // - Set the maximum number of rendering passes (initial value is 4):
  renderer->SetMaximumNumberOfPeels(maxNoOfPeels);
  // - Set the occlusion ratio (initial value is 0.0, exact image):
  renderer->SetOcclusionRatio(occlusionRatio);

  return true;
}

/**
 * Find out whether this box supports depth peeling. Depth peeling requires
 * a variety of openGL extensions and appropriate drivers.
 * @param renderWindow a valid openGL-supporting render window
 * @param renderer a valid renderer instance
 * @param doItOffscreen do the test off screen which means that nothing is
 * rendered to screen (this requires the box to support off screen rendering)
 * @return TRUE if depth peeling is supported, FALSE otherwise (which means
 * that another strategy must be used for correct rendering of translucent
 * geometry, e.g. CPU-based depth sorting)
 */
bool IsDepthPeelingSupported(vtkSmartPointer<vtkRenderWindow> renderWindow,
                             vtkSmartPointer<vtkRenderer> renderer,
                             bool doItOffScreen)
{
  if (!renderWindow || !renderer)
  {
    return false;
  }

  bool success = true;

  // Save original renderer / render window state
  bool origOffScreenRendering = renderWindow->GetOffScreenRendering() == 1;
  bool origAlphaBitPlanes = renderWindow->GetAlphaBitPlanes() == 1;
  int origMultiSamples = renderWindow->GetMultiSamples();
  bool origUseDepthPeeling = renderer->GetUseDepthPeeling() == 1;
  int origMaxPeels = renderer->GetMaximumNumberOfPeels();
  double origOcclusionRatio = renderer->GetOcclusionRatio();

  // Activate off screen rendering on demand
  renderWindow->SetOffScreenRendering(doItOffScreen);

  // Setup environment for depth peeling (with some default parametrization)
  success = success && SetupEnvironmentForDepthPeeling(renderWindow, renderer,
                                                       100, 0.1);

  // Do a test render
  renderWindow->Render();

  // Check whether depth peeling was used
  success = success && renderer->GetLastRenderingUsedDepthPeeling();

  // recover original state
  renderWindow->SetOffScreenRendering(origOffScreenRendering);
  renderWindow->SetAlphaBitPlanes(origAlphaBitPlanes);
  renderWindow->SetMultiSamples(origMultiSamples);
  renderer->SetUseDepthPeeling(origUseDepthPeeling);
  renderer->SetMaximumNumberOfPeels(origMaxPeels);
  renderer->SetOcclusionRatio(origOcclusionRatio);

  return success;
}

/**
 * Example application demonstrating correct rendering of translucent geometry.
 * It will automatically detect whether depth peeling is supported by the
 * hardware and software, and will apply depth peeling if possible. Otherwise
 * a fallback strategy is used: depth sorting on the CPU.
 * <br>Usage:
 * [ProgramName] Theta Phi MaximumPeels OcclusionRatio ForceDepthSortingFlag
 * DoNotUseAnyDepthRelatedAlgorithmFlag
 * <br>
 * Theta ... spheres' THETA resolution <br>
 * Phi ... spheres' PHI resolution <br>
 * MaximumPeels ... maximum number of depth peels (multi-pass rendering) for
 * depth peeling mode <br>
 * OcclusionRatio ... occlusion ratio for depth peeling mode (0.0 for a
 * perfect rendered image, >0.0 for a non-perfect image which is expected to
 * be slower) <br>
 * ForceDepthSortingFlag ... force depth sorting even if depth peeling is
 * supported <br>
 * DoNotUseAnyDepthRelatedAlgorithmFlag ... neither use depth peeling nor
 * depth sorting - just render as usual
 */
int main (int argc, char *argv[])
{
  if (argc != 7)
  {
    cerr << "Usage: " << argv[0] << " Theta Phi MaximumPeels " <<
      "OcclusionRatio ForceDepthSortingFlag " <<
      "DoNotUseAnyDepthRelatedAlgorithmFlag" << std::endl;
    return EXIT_FAILURE;
  }

  int theta = atoi(argv[1]);
  int phi = atoi(argv[2]);
  int maxPeels = atoi(argv[3]);
  double occulusionRatio = atof(argv[4]);
  bool forceDepthSort =  atoi(argv[5]) == 1;
  bool withoutAnyDepthThings = atoi(argv[6]) == 1;

  // Generate a translucent sphere poly data set that partially overlaps:
  vtkSmartPointer<vtkAppendPolyData> translucentGeometry =
    GenerateOverlappingBunchOfSpheres(theta, phi);

  // generate a basic Mapper and Actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(translucentGeometry->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetOpacity(0.5); // translucent !!!
  actor->GetProperty()->SetColor(1, 0, 0);
  actor->RotateX(-72); // put the objects in a position where it is easy to see
                       // different overlapping regions

  // Create the RenderWindow, Renderer and RenderWindowInteractor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 400);
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer, set the background and size
  renderer->AddActor(actor);
  renderer->SetBackground(1, 1, 1);

  // Setup view geometry
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(2.2); // so the object is larger
  renderWindow->Render();

  // Answer the key question: Does this box support GPU Depth Peeling?
  bool useDepthPeeling = IsDepthPeelingSupported(renderWindow, renderer, true);
  std::cout << "DEPTH PEELING SUPPORT: " << (useDepthPeeling ? "YES" : "NO") << std::endl;

  int success = EXIT_SUCCESS;

  // Use depth peeling if available and not explicitly prohibited, otherwise we
  // use manual depth sorting
  std::cout << std::endl << "CHOSEN MODE: ";
  if (useDepthPeeling && !forceDepthSort && !withoutAnyDepthThings) // GPU
  {
    std::cout << "*** DEPTH PEELING ***" << std::endl;
    // Setup GPU depth peeling with configured parameters
    success = !SetupEnvironmentForDepthPeeling(renderWindow, renderer,
                                               maxPeels, occulusionRatio);
  }
  else if (!withoutAnyDepthThings) // CPU
  {
    std::cout << "*** DEPTH SORTING ***" << std::endl;
    // Setup CPU depth sorting filter
    vtkSmartPointer<vtkDepthSortPolyData> depthSort =
      vtkSmartPointer<vtkDepthSortPolyData>::New();
    depthSort->SetInputConnection(translucentGeometry->GetOutputPort());
    depthSort->SetDirectionToBackToFront();
    depthSort->SetVector(1, 1, 1);
    depthSort->SetCamera(renderer->GetActiveCamera());
    depthSort->SortScalarsOff(); // do not really need this here
    // Bring it to the mapper's input
    mapper->SetInputConnection(depthSort->GetOutputPort());
    depthSort->Update();
  }
  else
  {
    std::cout << "*** NEITHER DEPTH PEELING NOR DEPTH SORTING ***" << std::endl;
  }

  // Initialize interaction
  renderWindowInteractor->Initialize();

  // Check the average frame rate when rotating the actor
  int endCount = 100;
  vtkSmartPointer<vtkTimerLog> clock =
    vtkSmartPointer<vtkTimerLog>::New();
  // Set a user transform for successively rotating the camera position
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Identity();
  transform->RotateY(2.0); // rotate 2 degrees around Y-axis at each iteration
  vtkSmartPointer<vtkCamera> camera = renderer->GetActiveCamera();
  double camPos[3]; // camera position
  // Start test
  clock->StartTimer();
  for (int i = 0; i < endCount; i++)
  {
    camera->GetPosition(camPos);
    transform->TransformPoint(camPos, camPos);
    camera->SetPosition(camPos);
    renderWindow->Render();
  }
  clock->StopTimer();
  double frameRate = (double)endCount / clock->GetElapsedTime();
  std::cout << "AVERAGE FRAME RATE: " << frameRate << " fps" << std::endl;

  // Start interaction
  renderWindowInteractor->Start();


  return success;
}
