#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkFlyingEdges3D.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageThreshold.h>
#include <vtkLookupTable.h>
#include <vtkMarchingCubes.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStripper.h>
#include <vtkWindowedSincPolyDataFilter.h>

#include <array>
#include <map>
#include <vector>

namespace {
void CreateFrogLut(vtkLookupTable* colorLut);
void CreateFrogSkinActor(std::string fileName, vtkActor* actor,
                         bool const& useMarchingCubes);
void CreateFrogActor(std::string fileName, int tissue, vtkActor* actor,
                     bool const& useMarchingCubes);
} // namespace

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cout << "Display all frog parts and translucent skin." << std::endl;
    std::cout << "Usage: " << argv[0]
              << " filename1 filename2 [noSkin] [noSkeleton] [useMarchingCubes]"
              << std::endl;
    std::cout << "where: filename1 is frog.mhd," << std::endl;
    std::cout << "       filename2 is frogtissue.mhd" << std::endl;
    std::cout << "       noSkin = 0|1" << std::endl;
    std::cout << "       noSkeleton = 0|1" << std::endl;
    std::cout << "       useMarchingCubes = 0|1" << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "Frog, using vtkFlyingEdges3D: frog.mhd frogtissue.mhd"
              << std::endl;
    std::cout
        << "Frog, using vtkMarchingCubes: frog.mhd frogtissue.mhd, 0, 0, 1"
        << std::endl;
    std::cout
        << "Frog with no skin, the parameters are: frog.mhd frogtissue.mhd 1"
        << std::endl;
    std::cout << "Frog with no skin or skeleton, the parameters are: frog.mhd "
                 "frogtissue.mhd 1 1"
              << std::endl;
    return EXIT_FAILURE;
  }
  std::string frogSkin = argv[1];
  std::string frogTissues = argv[2];
  auto noSkin = false;
  auto noSkeleton = false;
  auto useMarchingCubes = false;
  if (argc > 3)
  {
    if (atoi(argv[3]) != 0)
    {
      noSkin = true;
    }
  }
  if (argc > 4)
  {
    if (atoi(argv[4]) != 0)
    {
      noSkeleton = true;
    }
  }
  if (argc > 5)
  {
    if (atoi(argv[5]) != 0)
    {
      useMarchingCubes = true;
    }
  }

  if (useMarchingCubes)
  {
    std::cout << "Using vtkMarchingCubes." << std::endl;
  }
  else
  {
    std::cout << "Using vtkFlyingEdges3D." << std::endl;
  }

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkLookupTable> colorLut;
  colorLut->SetNumberOfColors(17);
  colorLut->SetTableRange(0, 16);
  colorLut->Build();
  CreateFrogLut(colorLut);

  // Setup render window, renderer, and interactor.
  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);
  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);

  if (!noSkin)
  {
    // The skin.
    vtkNew<vtkActor> skinActor;
    skinActor->GetProperty()->SetColor(
        colors->GetColor3d("LimeGreen").GetData());
    skinActor->GetProperty()->SetOpacity(0.4);
    CreateFrogSkinActor(frogSkin, skinActor, useMarchingCubes);
    renderer->AddActor(skinActor);
    std::cout << "Tissue: skin" << std::endl;
  }

  // Now for the tissues.
  // Use this to ensure that the tissues are selected in this order.
  std::array<std::string, 15> tissues = {
      {"blood", "brain", "duodenum", "eyeRetina", "eyeWhite", "heart", "ileum",
       "kidney", "intestine", "liver", "lung", "nerve", "skeleton", "spleen",
       "stomach"}};

  auto tissueNumber = 0;
  for (auto tissue : tissues)
  {
    tissueNumber++;
    if (noSkeleton)
    {
      if (tissue == "skeleton")
      {
        continue;
      }
    }
    vtkNew<vtkActor> actor;
    actor->GetProperty()->SetDiffuseColor(
        colorLut->GetTableValue(tissueNumber));
    actor->GetProperty()->SetSpecular(.5);
    actor->GetProperty()->SetSpecularPower(10);
    CreateFrogActor(frogTissues, tissueNumber, actor, useMarchingCubes);
    renderer->AddActor(actor);
    std::cout << "Tissue: " << tissue << ", Label: " << tissueNumber
              << std::endl;
  }

  renderer->GetActiveCamera()->SetViewUp(0, 0, -1);
  renderer->GetActiveCamera()->SetPosition(0, -1, 0);

  renderer->GetActiveCamera()->Azimuth(210);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCamera();
  renderer->ResetCameraClippingRange();
  renderer->GetActiveCamera()->Dolly(1.5);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  renderWindow->SetSize(640, 480);
  renderWindow->SetWindowName("Frog");
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace {

void CreateFrogLut(vtkLookupTable* colorLut)
{
  vtkNew<vtkNamedColors> colors;
  colorLut->SetTableValue(0, colors->GetColor4d("black").GetData());
  colorLut->SetTableValue(1,
                          colors->GetColor4d("salmon").GetData()); // blood
  colorLut->SetTableValue(2,
                          colors->GetColor4d("beige").GetData()); // brain
  colorLut->SetTableValue(3,
                          colors->GetColor4d("orange").GetData()); // duodenum
  colorLut->SetTableValue(4,
                          colors->GetColor4d("misty_rose").GetData()); // retina
  colorLut->SetTableValue(5,
                          colors->GetColor4d("white").GetData()); // eye_white
  colorLut->SetTableValue(6,
                          colors->GetColor4d("tomato").GetData()); // heart
  colorLut->SetTableValue(7,
                          colors->GetColor4d("raspberry").GetData()); // ileum
  colorLut->SetTableValue(8,
                          colors->GetColor4d("banana").GetData()); // kidney
  colorLut->SetTableValue(9,
                          colors->GetColor4d("peru").GetData()); // l_intestine
  colorLut->SetTableValue(10,
                          colors->GetColor4d("pink").GetData()); // liver
  colorLut->SetTableValue(11,
                          colors->GetColor4d("powder_blue").GetData()); // lung
  colorLut->SetTableValue(12,
                          colors->GetColor4d("carrot").GetData()); // nerve
  colorLut->SetTableValue(13,
                          colors->GetColor4d("wheat").GetData()); // skeleton
  colorLut->SetTableValue(14,
                          colors->GetColor4d("violet").GetData()); // spleen
  colorLut->SetTableValue(15,
                          colors->GetColor4d("plum").GetData()); // stomach
}

void CreateFrogSkinActor(std::string fileName, vtkActor* actor,
                         bool const& useMarchingCubes)
{
  vtkNew<vtkMetaImageReader> reader;
  reader->SetFileName(fileName.c_str());
  reader->Update();

  double isoValue = 20.5;
  vtkNew<vtkMarchingCubes> mcubes;
  vtkNew<vtkFlyingEdges3D> flyingEdges;
  vtkNew<vtkWindowedSincPolyDataFilter> smoother;
  if (useMarchingCubes)
  {
    mcubes->SetInputConnection(reader->GetOutputPort());
    mcubes->ComputeScalarsOff();
    mcubes->ComputeGradientsOff();
    mcubes->ComputeNormalsOff();
    mcubes->SetValue(0, isoValue);
    smoother->SetInputConnection(mcubes->GetOutputPort());
  }
  else
  {
    flyingEdges->SetInputConnection(reader->GetOutputPort());
    flyingEdges->ComputeScalarsOff();
    flyingEdges->ComputeGradientsOff();
    flyingEdges->ComputeNormalsOff();
    flyingEdges->SetValue(0, isoValue);
    smoother->SetInputConnection(flyingEdges->GetOutputPort());
  }

  int smoothingIterations = 5;
  double passBand = 0.001;
  double featureAngle = 60.0;
  smoother->SetNumberOfIterations(smoothingIterations);
  smoother->BoundarySmoothingOff();
  smoother->FeatureEdgeSmoothingOff();
  smoother->SetFeatureAngle(featureAngle);
  smoother->SetPassBand(passBand);
  smoother->NonManifoldSmoothingOn();
  smoother->NormalizeCoordinatesOn();
  smoother->Update();

  vtkNew<vtkPolyDataNormals> normals;
  normals->SetInputConnection(smoother->GetOutputPort());
  normals->SetFeatureAngle(featureAngle);

  vtkNew<vtkStripper> stripper;
  stripper->SetInputConnection(normals->GetOutputPort());

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(stripper->GetOutputPort());

  actor->SetMapper(mapper);
  return;
}

void CreateFrogActor(std::string fileName, int tissue, vtkActor* actor,
                     bool const& useMarchingCubes)
{
  vtkNew<vtkMetaImageReader> reader;
  reader->SetFileName(fileName.c_str());
  reader->Update();

  vtkNew<vtkImageThreshold> selectTissue;
  selectTissue->ThresholdBetween(tissue, tissue);
  selectTissue->SetInValue(255);
  selectTissue->SetOutValue(0);
  selectTissue->SetInputConnection(reader->GetOutputPort());

  int gaussianRadius = 1;
  double gaussianStandardDeviation = 2.0;
  vtkNew<vtkImageGaussianSmooth> gaussian;
  gaussian->SetStandardDeviations(gaussianStandardDeviation,
                                  gaussianStandardDeviation,
                                  gaussianStandardDeviation);
  gaussian->SetRadiusFactors(gaussianRadius, gaussianRadius, gaussianRadius);
  gaussian->SetInputConnection(selectTissue->GetOutputPort());

  double isoValue = 127.5;
  vtkNew<vtkMarchingCubes> mcubes;
  vtkNew<vtkFlyingEdges3D> flyingEdges;
  vtkNew<vtkWindowedSincPolyDataFilter> smoother;
  if (useMarchingCubes)
  {
    mcubes->SetInputConnection(gaussian->GetOutputPort());
    mcubes->ComputeScalarsOff();
    mcubes->ComputeGradientsOff();
    mcubes->ComputeNormalsOff();
    mcubes->SetValue(0, isoValue);
    smoother->SetInputConnection(mcubes->GetOutputPort());
  }
  else
  {
    flyingEdges->SetInputConnection(gaussian->GetOutputPort());
    flyingEdges->ComputeScalarsOff();
    flyingEdges->ComputeGradientsOff();
    flyingEdges->ComputeNormalsOff();
    flyingEdges->SetValue(0, isoValue);
    smoother->SetInputConnection(flyingEdges->GetOutputPort());
  }

  int smoothingIterations = 5;
  double passBand = 0.001;
  double featureAngle = 60.0;
  smoother->SetNumberOfIterations(smoothingIterations);
  smoother->BoundarySmoothingOff();
  smoother->FeatureEdgeSmoothingOff();
  smoother->SetFeatureAngle(featureAngle);
  smoother->SetPassBand(passBand);
  smoother->NonManifoldSmoothingOn();
  smoother->NormalizeCoordinatesOn();
  smoother->Update();

  vtkNew<vtkPolyDataNormals> normals;
  normals->SetInputConnection(smoother->GetOutputPort());
  normals->SetFeatureAngle(featureAngle);

  vtkNew<vtkStripper> stripper;
  stripper->SetInputConnection(normals->GetOutputPort());

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(stripper->GetOutputPort());

  actor->SetMapper(mapper);
  return;
}

} // namespace
