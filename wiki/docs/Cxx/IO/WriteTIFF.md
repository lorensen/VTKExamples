[VTKExamples](/home/)/[Cxx](/Cxx)/IO/WriteTIFF

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestWriteTIFF.png?raw=true" width="256" />

**WriteTIFF.cxx**
```c++
#include <vtkImageData.h>
#include <vtkInteractorStyleImage.h>
#include <vtkTIFFWriter.h>
#include <vtkSmartPointer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkTIFFReader.h>

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Required parameters: OutputFilename.tif" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];

  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetExtent(0,9,0,9,0,0);
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetDrawColor(0, 0, 0, 0);
  imageSource->FillBox(0,9,0,9);
  imageSource->SetDrawColor(255, 0, 0, 0);
  imageSource->FillBox(5,7,5,7);
  imageSource->Update();

  vtkSmartPointer<vtkTIFFWriter> tiffWriter =
    vtkSmartPointer<vtkTIFFWriter>::New();
  tiffWriter->SetFileName(filename.c_str());
  tiffWriter->SetInputConnection(imageSource->GetOutputPort());
  tiffWriter->Write();

  // Read and display for verification
  vtkSmartPointer<vtkTIFFReader> reader =
    vtkSmartPointer<vtkTIFFReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

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
 
PROJECT(WriteTIFF)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WriteTIFF MACOSX_BUNDLE WriteTIFF.cxx)
 
target_link_libraries(WriteTIFF ${VTK_LIBRARIES})
```

**Download and Build WriteTIFF**

Click [here to download WriteTIFF](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WriteTIFF.tar) and its *CMakeLists.txt* file.
Once the *tarball WriteTIFF.tar* has been downloaded and extracted,
```
cd WriteTIFF/build 
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
./WriteTIFF
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

