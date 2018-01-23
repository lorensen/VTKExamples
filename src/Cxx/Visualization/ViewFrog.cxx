#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageThreshold.h>
#include <vtkLookupTable.h>
#include <vtkMarchingCubes.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStripper.h>
#include <vtkWindowedSincPolyDataFilter.h>

#include <map>

namespace
{
void CreateFrogLut(vtkSmartPointer<vtkLookupTable> &colorLut);
void CreateFrogActor(std::string fileName,
                     int tissue,
                     vtkSmartPointer<vtkActor> &actor);
void CreateTissueMap(std::map<std::string, int> &tissueMap);
}
int main (int argc, char *argv[])
{
  std::map<std::string, int> tissueMap;
  CreateTissueMap(tissueMap);

  vtkSmartPointer<vtkLookupTable> colorLut =
    vtkSmartPointer<vtkLookupTable>::New();
  colorLut->SetNumberOfColors(17);
  colorLut->SetTableRange(0, 16);
  colorLut->Build();

  CreateFrogLut(colorLut);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  for (int i = 2; i < argc; ++i)
  {
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->GetProperty()->SetDiffuseColor(
    colorLut->GetTableValue(tissueMap[argv[i]]));
  actor->GetProperty()->SetSpecular(.5);
  actor->GetProperty()->SetSpecularPower(10);
  CreateFrogActor(argv[1], tissueMap[argv[i]], actor);
  renderer->AddActor(actor);
  std::cout << "Tissue: " << argv[i]
            << ", Label: " << tissueMap[argv[i]] << std::endl;
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
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace
{
void CreateTissueMap(std::map<std::string, int> &tissueMap)
{
  tissueMap["blood"] = 1;
  tissueMap["brain"] = 2;
  tissueMap["duodenum"] = 3;
  tissueMap["eyeRetina"] = 4;
  tissueMap["eyeWhite"] = 5;
  tissueMap["heart"] = 6;
  tissueMap["ileum"] = 7;
  tissueMap["kidney"] = 8;
  tissueMap["intestine"] = 9;
  tissueMap["liver"] = 10;
  tissueMap["lung"] = 11;
  tissueMap["nerve"] = 12;
  tissueMap["skeleton"] = 13;
  tissueMap["spleen"] = 14;
  tissueMap["stomach"] = 15;
  return;
}
void CreateFrogActor(std::string fileName,
                     int tissue,
                     vtkSmartPointer<vtkActor> &actor)
{
  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName(fileName.c_str());
  reader->Update();

  vtkSmartPointer<vtkImageThreshold> selectTissue =
    vtkSmartPointer<vtkImageThreshold>::New();
  selectTissue->ThresholdBetween(tissue, tissue);
  selectTissue->SetInValue(255);
  selectTissue->SetOutValue(0);
  selectTissue->SetInputConnection(reader->GetOutputPort());

  int gaussianRadius = 1;
  double gaussianStandardDeviation = 2.0;
  vtkSmartPointer<vtkImageGaussianSmooth> gaussian =
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  gaussian->SetStandardDeviations (gaussianStandardDeviation,
                                   gaussianStandardDeviation,
                                   gaussianStandardDeviation);
  gaussian->SetRadiusFactors (gaussianRadius,
                              gaussianRadius,
                              gaussianRadius);
  gaussian->SetInputConnection(selectTissue->GetOutputPort());

  double isoValue = 127.5;
  vtkSmartPointer<vtkMarchingCubes> mcubes =
    vtkSmartPointer<vtkMarchingCubes>::New();
  mcubes->SetInputConnection(gaussian->GetOutputPort());
  mcubes->ComputeScalarsOff();
  mcubes->ComputeGradientsOff();
  mcubes->ComputeNormalsOff();
  mcubes->SetValue(0, isoValue);

  int smoothingIterations = 5;
  double passBand = 0.001;
  double featureAngle = 60.0;
  vtkSmartPointer<vtkWindowedSincPolyDataFilter> smoother =
    vtkSmartPointer<vtkWindowedSincPolyDataFilter>::New();
  smoother->SetInputConnection(mcubes->GetOutputPort());
  smoother->SetNumberOfIterations(smoothingIterations);
  smoother->BoundarySmoothingOff();
  smoother->FeatureEdgeSmoothingOff();
  smoother->SetFeatureAngle(featureAngle);
  smoother->SetPassBand(passBand);
  smoother->NonManifoldSmoothingOn();
  smoother->NormalizeCoordinatesOn();
  smoother->Update();

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(smoother->GetOutputPort());
  normals->SetFeatureAngle(featureAngle);

  vtkSmartPointer<vtkStripper> stripper =
    vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputConnection(normals->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(stripper->GetOutputPort());

  actor->SetMapper(mapper);
  return;
}

void CreateFrogLut(vtkSmartPointer<vtkLookupTable> &colorLut)
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  colorLut->SetTableValue(0,
                          0, 0, 0, 0);
  colorLut->SetTableValue(1,
                          colors->GetColor4d("salmon").GetData()); //blood
  colorLut->SetTableValue(2,
                          colors->GetColor4d("beige").GetData()); //brain
  colorLut->SetTableValue(3,
                          colors->GetColor4d("orange").GetData()); //duodenum
  colorLut->SetTableValue(4,
                          colors->GetColor4d("misty_rose").GetData()); //eye_retina
  colorLut->SetTableValue(5,
                          colors->GetColor4d("white").GetData()); //eye_white
  colorLut->SetTableValue(6,
                          colors->GetColor4d("tomato").GetData()); //heart
  colorLut->SetTableValue(7,
                          colors->GetColor4d("raspberry").GetData()); //ileum
  colorLut->SetTableValue(8,
                          colors->GetColor4d("banana").GetData()); //kidney
  colorLut->SetTableValue(9,
                          colors->GetColor4d("peru").GetData()); //l_intestine
  colorLut->SetTableValue(10,
                          colors->GetColor4d("pink").GetData()); //liver
  colorLut->SetTableValue(11,
                          colors->GetColor4d("powder_blue").GetData()); //lung
  colorLut->SetTableValue(12,
                          colors->GetColor4d("carrot").GetData()); //nerve
  colorLut->SetTableValue(13,
                          colors->GetColor4d("wheat").GetData()); //skeleton
  colorLut->SetTableValue(14,
                          colors->GetColor4d("violet").GetData()); //spleen
  colorLut->SetTableValue(15,
                          colors->GetColor4d("plum").GetData()); //stomach
}
}
