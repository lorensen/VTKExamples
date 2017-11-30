/*
 * Visualization of gradient information.
 *
 */

#include <vtkImageCast.h>
#include <vtkImageConstantPad.h>
#include <vtkImageEuclideanToPolar.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageGradient.h>
#include <vtkImageHSVToRGB.h>
#include <vtkImageMagnify.h>
#include <vtkImageViewer.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " fileName" << std::endl;
    std::cout << "where: fileName is FullHead.mhd." << std::endl;
    std::cout << "Note: The file FullHead.raw.gz must also be present in the "
                 "same folder."
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argv[1];

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Read the CT data of the human head.
  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName(fileName.c_str());
  reader->Update();

  vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
  cast->SetInputConnection(reader->GetOutputPort());
  cast->SetOutputScalarTypeToFloat();

  // Magnify the image.
  vtkSmartPointer<vtkImageMagnify> magnify =
    vtkSmartPointer<vtkImageMagnify>::New();
  magnify->SetInputConnection(cast->GetOutputPort());
  magnify->SetMagnificationFactors(2, 2, 1);
  magnify->InterpolateOn();

  // Smooth the data.
  // Remove high frequency artifacts due to linear interpolation.
  vtkSmartPointer<vtkImageGaussianSmooth> smooth =
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  smooth->SetInputConnection(magnify->GetOutputPort());
  smooth->SetDimensionality(2);
  smooth->SetStandardDeviations(1.5, 1.5, 0.0);
  smooth->SetRadiusFactors(2.01, 2.01, 0.0);

  // Compute the 2D gradient.
  vtkSmartPointer<vtkImageGradient> gradient =
    vtkSmartPointer<vtkImageGradient>::New();
  gradient->SetInputConnection(smooth->GetOutputPort());
  gradient->SetDimensionality(2);

  // Convert the data to polar coordinates.
  // The image magnitude is mapped into saturation value,
  //  whilst the gradient direction is mapped into hue value.
  vtkSmartPointer<vtkImageEuclideanToPolar> polar =
    vtkSmartPointer<vtkImageEuclideanToPolar>::New();
  polar->SetInputConnection(gradient->GetOutputPort());
  polar->SetThetaMaximum(255.0);

  // Add a third component to the data.
  // This is needed since the gradient filter only generates two components,
  //  and we need three components to represent color.
  vtkSmartPointer<vtkImageConstantPad> pad =
    vtkSmartPointer<vtkImageConstantPad>::New();
  pad->SetInputConnection(polar->GetOutputPort());
  pad->SetOutputNumberOfScalarComponents(3);
  pad->SetConstant(200.0);

  // At this point we have Hue, Value, Saturation.
  // Permute components so saturation will be constant.
  // Re-arrange components into HSV order.
  vtkSmartPointer<vtkImageExtractComponents> permute =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  permute->SetInputConnection(pad->GetOutputPort());
  permute->SetComponents(0, 2, 1);

  // Convert back into RGB values.
  vtkSmartPointer<vtkImageHSVToRGB> rgb =
    vtkSmartPointer<vtkImageHSVToRGB>::New();
  rgb->SetInputConnection(permute->GetOutputPort());
  rgb->SetMaximum(255.0);

  // Set up a viewer for the image.
  // Note that vtkImageViewer and vtkImageViewer2 are convenience wrappers
  // around
  // vtkActor2D, vtkImageMapper, vtkRenderer, and vtkRenderWindow.
  // So all that needs to be supplied is the interactor.
  vtkSmartPointer<vtkImageViewer> viewer =
    vtkSmartPointer<vtkImageViewer>::New();
  viewer->SetInputConnection(rgb->GetOutputPort());
  viewer->SetZSlice(22);
  viewer->SetColorWindow(255.0);
  viewer->SetColorLevel(127.0);
  viewer->GetRenderWindow()->SetSize(512, 512);
  viewer->GetRenderer()->SetBackground(colors->GetColor3d("Silver").GetData());

  // Create the RenderWindowInteractor.
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(iren);
  viewer->Render();

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
