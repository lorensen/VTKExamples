#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkStructuredPoints.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPNGReader.h>
#include <vtkImageLuminance.h>
#include <vtkProperty.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageCast.h>
#include <vtkImageGradient.h>
#include <vtkImageMagnitude.h>
#include <vtkImageNonMaximumSuppression.h>
#include <vtkImageConstantPad.h>
#include <vtkImageToStructuredPoints.h>
#include <vtkLinkEdgels.h>
#include <vtkThreshold.h>
#include <vtkGeometryFilter.h>
#include <vtkSubPixelPositionEdgels.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "Required args: filename.png" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];



    // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double edgeViewport[4] = {0.5, 0.0, 1.0, 1.0};

  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  vtkSmartPointer<vtkRenderer> edgeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  edgeRenderer->SetViewport(edgeViewport);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600,300);
  renderWindow->SetMultiSamples(0);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(edgeRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkPNGReader> imageIn =
    vtkSmartPointer<vtkPNGReader>::New();
  imageIn->SetFileName(filename.c_str());
  imageIn->Update();

  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->SetInputData(imageIn->GetOutput());

  originalRenderer->AddActor(imageActor);

  vtkSmartPointer<vtkImageLuminance> il =
    vtkSmartPointer<vtkImageLuminance>::New();
  il->SetInputConnection(imageIn->GetOutputPort());

  vtkSmartPointer<vtkImageCast> ic =
    vtkSmartPointer<vtkImageCast>::New();
  ic->SetOutputScalarTypeToFloat();
  ic->SetInputConnection(il->GetOutputPort());

  // Smooth the image
  vtkSmartPointer<vtkImageGaussianSmooth> gs =
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  gs->SetInputConnection(ic->GetOutputPort());
  gs->SetDimensionality(2);
  gs->SetRadiusFactors(1, 1, 0);

  // Gradient the image
  vtkSmartPointer<vtkImageGradient> imgGradient =
    vtkSmartPointer<vtkImageGradient>::New();
  imgGradient->SetInputConnection(gs->GetOutputPort());
  imgGradient->SetDimensionality(2);

  vtkSmartPointer<vtkImageMagnitude> imgMagnitude =
    vtkSmartPointer<vtkImageMagnitude>::New();
  imgMagnitude->SetInputConnection(imgGradient->GetOutputPort());

  // Non maximum suppression
  vtkSmartPointer<vtkImageNonMaximumSuppression> nonMax =
    vtkSmartPointer<vtkImageNonMaximumSuppression>::New();
  imgMagnitude->Update();
  nonMax->SetMagnitudeInputData(imgMagnitude->GetOutput());
  imgGradient->Update();
  nonMax->SetVectorInputData(imgGradient->GetOutput());
  nonMax->SetDimensionality(2);

  vtkSmartPointer<vtkImageConstantPad> pad =
    vtkSmartPointer<vtkImageConstantPad>::New();
  pad->SetInputConnection(imgGradient->GetOutputPort());
  pad->SetOutputNumberOfScalarComponents(3);
  pad->SetConstant(0);

  vtkSmartPointer<vtkImageToStructuredPoints> i2sp1 =
    vtkSmartPointer<vtkImageToStructuredPoints>::New();
  i2sp1->SetInputConnection(nonMax->GetOutputPort());
  pad->Update();
  i2sp1->SetVectorInputData(pad->GetOutput());

  // Link edgles
  vtkSmartPointer<vtkLinkEdgels> imgLink =
    vtkSmartPointer<vtkLinkEdgels>::New();
  imgLink->SetInputConnection(i2sp1->GetOutputPort());
  imgLink->SetGradientThreshold(2);

  // Threshold links
  vtkSmartPointer<vtkThreshold> thresholdEdgels =
    vtkSmartPointer<vtkThreshold>::New();
  thresholdEdgels->SetInputConnection(imgLink->GetOutputPort());
  thresholdEdgels->ThresholdByUpper(10);
  thresholdEdgels->AllScalarsOff();

  vtkSmartPointer<vtkGeometryFilter> gf =
    vtkSmartPointer<vtkGeometryFilter>::New();
  gf->SetInputConnection(thresholdEdgels->GetOutputPort());

  vtkSmartPointer<vtkImageToStructuredPoints> i2sp =
    vtkSmartPointer<vtkImageToStructuredPoints>::New();
  i2sp->SetInputConnection(imgMagnitude->GetOutputPort());
  pad->Update();
  i2sp->SetVectorInputData(pad->GetOutput());

  // Subpixel them
  vtkSmartPointer<vtkSubPixelPositionEdgels> spe =
    vtkSmartPointer<vtkSubPixelPositionEdgels>::New();
  spe->SetInputConnection(gf->GetOutputPort());
  i2sp->Update();
  spe->SetGradMapsData(i2sp->GetStructuredPointsOutput());

  vtkSmartPointer<vtkStripper> strip =
    vtkSmartPointer<vtkStripper>::New();
  strip->SetInputConnection(spe->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> dsm =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  dsm->SetInputConnection(strip->GetOutputPort());
  dsm->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->SetMapper(dsm);
  planeActor->GetProperty()->SetAmbient(1.0);
  planeActor->GetProperty()->SetDiffuse(0.0);

  // Add the actors to the renderer, set the background and size
  edgeRenderer->AddActor(planeActor);

  // Render the image
  interactor->Initialize();
  renderWindow->Render();
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
