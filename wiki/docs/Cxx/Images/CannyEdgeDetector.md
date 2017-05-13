[VTKExamples](/home/)/[Cxx](/Cxx)/Images/CannyEdgeDetector

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestCannyEdgeDetector.png?raw=true" width="256" />

**CannyEdgeDetector.cxx**
```c++
#include <vtkVersion.h>
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
#if VTK_MAJOR_VERSION <= 5
  imageActor->SetInput(imageIn->GetOutput());
#else
  imageActor->SetInputData(imageIn->GetOutput());
#endif
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
#if VTK_MAJOR_VERSION <= 5
  nonMax->SetMagnitudeInput(imgMagnitude->GetOutput());
  nonMax->SetVectorInput(imgGradient->GetOutput());
#else
  imgMagnitude->Update();
  nonMax->SetMagnitudeInputData(imgMagnitude->GetOutput());
  imgGradient->Update();
  nonMax->SetVectorInputData(imgGradient->GetOutput());
#endif
  nonMax->SetDimensionality(2);

  vtkSmartPointer<vtkImageConstantPad> pad =
    vtkSmartPointer<vtkImageConstantPad>::New();
  pad->SetInputConnection(imgGradient->GetOutputPort());
  pad->SetOutputNumberOfScalarComponents(3);
  pad->SetConstant(0);

  vtkSmartPointer<vtkImageToStructuredPoints> i2sp1 =
    vtkSmartPointer<vtkImageToStructuredPoints>::New();
  i2sp1->SetInputConnection(nonMax->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  i2sp1->SetVectorInput(pad->GetOutput());
#else
  pad->Update();
 i2sp1->SetVectorInputData(pad->GetOutput());
#endif

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
#if VTK_MAJOR_VERSION <= 5
  i2sp->SetVectorInput(pad->GetOutput());
#else
  pad->Update();
  i2sp->SetVectorInputData(pad->GetOutput());
#endif

  // Subpixel them
  vtkSmartPointer<vtkSubPixelPositionEdgels> spe =
    vtkSmartPointer<vtkSubPixelPositionEdgels>::New();
  spe->SetInputConnection(gf->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  spe->SetGradMaps(i2sp->GetStructuredPointsOutput());
#else
  i2sp->Update();
  spe->SetGradMapsData(i2sp->GetStructuredPointsOutput());
#endif

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
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CannyEdgeDetector)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CannyEdgeDetector MACOSX_BUNDLE CannyEdgeDetector.cxx)
 
target_link_libraries(CannyEdgeDetector ${VTK_LIBRARIES})
```

**Download and Build CannyEdgeDetector**

Click [here to download CannyEdgeDetector](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CannyEdgeDetector.tar) and its *CMakeLists.txt* file.
Once the *tarball CannyEdgeDetector.tar* has been downloaded and extracted,
```
cd CannyEdgeDetector/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./CannyEdgeDetector
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

