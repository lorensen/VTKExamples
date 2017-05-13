[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageAnisotropicDiffusion2D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageAnisotropicDiffusion2D.png?raw=true" width="256" />

**ImageAnisotropicDiffusion2D.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkCamera.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkImageAnisotropicDiffusion2D.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char *argv[])
{
   // Handle the arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " filename.png [iterations(10)] [threshold(20)]" << std::endl;
    return EXIT_FAILURE;
  }
  int iterations = 10;
  if (argc >= 3)
  {
    iterations = atoi(argv[2]);
  }
  float threshold = 20;
  if (argc >= 4)
  {
    threshold = atoi(argv[3]);
  }
  // Read the image
  vtkSmartPointer<vtkJPEGReader> reader =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageAnisotropicDiffusion2D> diffusion =
    vtkSmartPointer<vtkImageAnisotropicDiffusion2D>::New();
  diffusion->SetInputConnection(reader->GetOutputPort());
  diffusion->SetNumberOfIterations(iterations);
  diffusion->SetDiffusionThreshold(threshold);
  diffusion->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  // Create an actor
  vtkSmartPointer<vtkImageActor> diffusionActor =
    vtkSmartPointer<vtkImageActor>::New();
  diffusionActor->GetMapper()->SetInputConnection(diffusion->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->AddActor(originalActor);
  leftRenderer->SetActiveCamera(camera);
  leftRenderer->ResetCamera();

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->AddActor(diffusionActor);
  rightRenderer->SetActiveCamera(camera);

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600,300);
  renderWindow->AddRenderer(leftRenderer);
  renderWindow->AddRenderer(rightRenderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageAnisotropicDiffusion2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageAnisotropicDiffusion2D MACOSX_BUNDLE ImageAnisotropicDiffusion2D.cxx)
 
target_link_libraries(ImageAnisotropicDiffusion2D ${VTK_LIBRARIES})
```

**Download and Build ImageAnisotropicDiffusion2D**

Click [here to download ImageAnisotropicDiffusion2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageAnisotropicDiffusion2D.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageAnisotropicDiffusion2D.tar* has been downloaded and extracted,
```
cd ImageAnisotropicDiffusion2D/build 
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
./ImageAnisotropicDiffusion2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

