[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/RenderLargeImage

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestRenderLargeImage.png?raw=true" width="256" />

### Description
This example renders a high resolution image. The image can be much larger than the window on the screen. It is useful if you need an image for a large poster, or you can down sample the image to produce a high quality anti-aliased image.

The example takes up to three arguments. The first, an input polydata, is required, as is the second, a .png file to hold the high res image. An optional third argument specifies the magnification of the high res image (default 4).

**RenderLargeImage.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkImageViewer.h>
#include <vtkPNGWriter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderLargeImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkXMLPolyDataReader.h>

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0]
              << " Input(.vtp) Output(.png) [Magnification]"
              << std::endl;
    return EXIT_FAILURE;
  }
  int magnification = 4;
  if (argc == 4)
  {
    magnification = atoi(argv[3]);
  }

  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<  vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->AddRenderer(renderer);

  renderer->AddActor(actor);

  // Let the renderer compute good position and focal point
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Dolly(1.4);
  renderer->ResetCameraClippingRange();
  renderer->SetBackground(.3, .4, .5);

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  std::cout << "Interact with image to get desired view and then press 'e'"
            << std::endl;
  interactor->Start();
  std::cout << "Generating large image size: "
            << renderWindow->GetSize()[0] * magnification << " by "
            << renderWindow->GetSize()[1] * magnification
            << std::endl;


  vtkSmartPointer<vtkRenderLargeImage> renderLarge =
    vtkSmartPointer<vtkRenderLargeImage>::New();
  renderLarge->SetInput(renderer);
  renderLarge->SetMagnification(magnification);

  std::cout << "Saving image in " << argv[2] << std::endl;
  vtkSmartPointer<vtkPNGWriter> writer =
    vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName(argv[2]);
  writer->SetInputConnection(renderLarge->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RenderLargeImage)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RenderLargeImage MACOSX_BUNDLE RenderLargeImage.cxx)
 
target_link_libraries(RenderLargeImage ${VTK_LIBRARIES})
```

**Download and Build RenderLargeImage**

Click [here to download RenderLargeImage](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RenderLargeImage.tar) and its *CMakeLists.txt* file.
Once the *tarball RenderLargeImage.tar* has been downloaded and extracted,
```
cd RenderLargeImage/build 
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
./RenderLargeImage
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

