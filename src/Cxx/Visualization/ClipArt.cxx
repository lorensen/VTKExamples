#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkClipPolyData.h>
#include <vtkDecimatePro.h>
#include <vtkImageConstantPad.h>
#include <vtkImageData.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageRGBToHSV.h>
#include <vtkImageSeedConnectivity.h>
#include <vtkImageShrink3D.h>
#include <vtkImageThreshold.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkTexture.h>
#include <vtkTextureMapToPlane.h>
#include <vtkTriangleFilter.h>

#include <vtkInformation.h>
#include <vtkStreamingDemandDrivenPipeline.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.jpg)" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkJPEGReader> imageIn =
    vtkSmartPointer<vtkJPEGReader>::New();
  imageIn->SetFileName(argv[1]);

  // Convert the image to hsv so that we can threshold on value
  vtkSmartPointer<vtkImageRGBToHSV> toHSV =
    vtkSmartPointer<vtkImageRGBToHSV>::New();
  toHSV->SetInputConnection(imageIn->GetOutputPort());

  // Just work with the value
  vtkSmartPointer<vtkImageExtractComponents> extractImage =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractImage->SetInputConnection(toHSV->GetOutputPort());
  extractImage->SetComponents(2);

  // Threshold to a black/white image
  vtkSmartPointer<vtkImageThreshold> threshold1 =
    vtkSmartPointer<vtkImageThreshold>::New();
  threshold1->SetInputConnection(extractImage->GetOutputPort());
  threshold1->ThresholdByUpper(230);
  threshold1->SetInValue(255);
  threshold1->SetOutValue(0);
  threshold1->Update();

  // Place a seed in each corner and label connected pixels with 255
  threshold1->UpdateInformation();

  int *extent = threshold1->GetOutputInformation(0)->Get(
    vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT());
  vtkSmartPointer<vtkImageSeedConnectivity> connect =
    vtkSmartPointer<vtkImageSeedConnectivity>::New();
  connect->SetInputConnection(threshold1->GetOutputPort());
  connect->SetInputConnectValue(255);
  connect->SetOutputConnectedValue(255);
  connect->SetOutputUnconnectedValue(0);
  connect->AddSeed(extent[0], extent[2]);
  connect->AddSeed(extent[1], extent[2]);
  connect->AddSeed(extent[1], extent[3]);
  connect->AddSeed(extent[0], extent[3]);

  // Smooth a little before clipping
  vtkSmartPointer<vtkImageGaussianSmooth> smooth =
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  smooth->SetDimensionality(2);
  smooth->SetStandardDeviation(1.0, 1.0);
  smooth->SetInputConnection(connect->GetOutputPort());

  vtkSmartPointer<vtkImageShrink3D> shrink =
    vtkSmartPointer<vtkImageShrink3D>::New();
  shrink->SetInputConnection(smooth->GetOutputPort());
  shrink->SetShrinkFactors(1, 1, 1);
  shrink->AveragingOn();

  // Convert the image to polydata
  vtkSmartPointer<vtkImageDataGeometryFilter> geometry =
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  geometry->SetInputConnection(shrink->GetOutputPort());

  // Create texture coordinates
  vtkSmartPointer<vtkTextureMapToPlane> geometryTexture =
    vtkSmartPointer<vtkTextureMapToPlane>::New();
  geometryTexture->SetInputConnection(geometry->GetOutputPort());
  geometryTexture->SetOrigin(0, 0, 0);
  geometryTexture->SetPoint1(extent[1], 0, 0);
  geometryTexture->SetPoint2(0, extent[3], 0);

  // Clip the geometry
  vtkSmartPointer<vtkClipPolyData> clip =
    vtkSmartPointer<vtkClipPolyData>::New();
  clip->SetInputConnection(geometryTexture->GetOutputPort());
  clip->SetValue(5.5);
  clip->GenerateClipScalarsOff();
  clip->InsideOutOff();
  clip->InsideOutOn();

  vtkSmartPointer<vtkTriangleFilter> triangles =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangles->SetInputConnection(clip->GetOutputPort());

  vtkSmartPointer<vtkDecimatePro> decimate =
    vtkSmartPointer<vtkDecimatePro>::New();
  decimate->SetInputConnection(triangles->GetOutputPort());
  decimate->BoundaryVertexDeletionOn();
  decimate->SetDegree(100);
  decimate->PreserveTopologyOn();
  decimate->SetTargetReduction(.99);

  vtkSmartPointer<vtkLinearExtrusionFilter> extrude =
    vtkSmartPointer<vtkLinearExtrusionFilter>::New();
  extrude->SetInputConnection(decimate->GetOutputPort());
  extrude->SetExtrusionTypeToNormalExtrusion();
  extrude->SetScaleFactor(-10);

  vtkSmartPointer<vtkPolyDataMapper> map =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  map->SetInputConnection(extrude->GetOutputPort());
  map->ScalarVisibilityOff();

  vtkSmartPointer<vtkTexture> imageTexture =
    vtkSmartPointer<vtkTexture>::New();
  imageTexture->InterpolateOn();
  imageTexture->SetInputConnection(imageIn->GetOutputPort());

  vtkSmartPointer<vtkActor> clipart =
    vtkSmartPointer<vtkActor>::New();
  clipart->SetMapper(map);
  clipart->SetTexture(imageTexture);

  // Create the RenderWindow, Renderer and Interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->AddActor(clipart);

  // Create a nice view
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.5);
  renderer->ResetCameraClippingRange();

  renderer->SetBackground(0.2, 0.3, 0.4);
  renderWindow->SetSize(320, 256);

  interactor->Initialize();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
