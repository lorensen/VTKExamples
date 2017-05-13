[VTKExamples](Home)/[Cxx](Cxx)/Images/ImageContinuousDilate3D

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Images/TestImageContinuousDilate3D.png" width="256" />

**ImageContinuousDilate3D.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkImageData.h>
#include <vtkImageContinuousDilate3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkPNGReader.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();

  if(argc < 2)
  {
    // Create an image
    vtkSmartPointer<vtkImageCanvasSource2D> source =
      vtkSmartPointer<vtkImageCanvasSource2D>::New();
    source->SetScalarTypeToUnsignedChar();
    source->SetExtent(0, 200, 0, 200, 0, 0);
    source->SetDrawColor(0,0,0);
    source->FillBox(0,200,0,200);
    source->SetDrawColor(255,0,0);
    source->FillBox(100,150,100,150);
    source->Update();
    image->ShallowCopy(source->GetOutput());
  }
  else
  {
    vtkSmartPointer<vtkPNGReader> reader =
      vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    image->ShallowCopy(reader->GetOutput());
  }

  vtkSmartPointer<vtkImageContinuousDilate3D> dilateFilter =
    vtkSmartPointer<vtkImageContinuousDilate3D>::New();
#if VTK_MAJOR_VERSION <= 5
  dilateFilter->SetInputConnection(image->GetProducerPort());
#else
  dilateFilter->SetInputData(image);
#endif
  dilateFilter->SetKernelSize(10,10,1);
  dilateFilter->Update();

  vtkSmartPointer<vtkDataSetMapper> originalMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  originalMapper->SetInputConnection(image->GetProducerPort());
#else
  originalMapper->SetInputData(image);
#endif
  originalMapper->Update();

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);

  vtkSmartPointer<vtkDataSetMapper> dilatedMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  dilatedMapper->SetInputConnection(dilateFilter->GetOutputPort());
  dilatedMapper->Update();

  vtkSmartPointer<vtkActor> dilatedActor =
    vtkSmartPointer<vtkActor>::New();
  dilatedActor->SetMapper(dilatedMapper);

  // Visualize
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  leftRenderer->AddActor(originalActor);
  rightRenderer->AddActor(dilatedActor);

  leftRenderer->ResetCamera();
  rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageContinuousDilate3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageContinuousDilate3D MACOSX_BUNDLE ImageContinuousDilate3D.cxx)
 
target_link_libraries(ImageContinuousDilate3D ${VTK_LIBRARIES})
```

**Download and Build ImageContinuousDilate3D**

Click [here to download ImageContinuousDilate3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageContinuousDilate3D.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageContinuousDilate3D.tar* has been downloaded and extracted,
```
cd ImageContinuousDilate3D/build 
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
./ImageContinuousDilate3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

