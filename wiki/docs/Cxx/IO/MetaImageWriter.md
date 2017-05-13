[VTKExamples](Home)/[Cxx](Cxx)/IO/MetaImageWriter

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/IO/TestMetaImageWriter.png" width="256" />

**MetaImageWriter.cxx**
```c++
// some standard vtk headers
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

// headers needed for this example
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCast.h>
#include <vtkMetaImageWriter.h>
#include <vtkMetaImageReader.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
   // adapt path !
   std::string filePath = "julia_mha.mhd";
   std::string filePathRaw = "julia_mha.raw";
   // Create an image
   vtkSmartPointer<vtkImageMandelbrotSource> source =
      vtkSmartPointer<vtkImageMandelbrotSource>::New();

   vtkSmartPointer<vtkImageCast> castFilter = 
      vtkSmartPointer<vtkImageCast>::New();
   castFilter->SetOutputScalarTypeToUnsignedChar();
   castFilter->SetInputConnection(source->GetOutputPort());
   castFilter->Update();

   vtkSmartPointer<vtkMetaImageWriter> writer =
      vtkSmartPointer<vtkMetaImageWriter>::New();
   writer->SetInputConnection(castFilter->GetOutputPort());
   writer->SetFileName(filePath.c_str());
   writer->SetRAWFileName(filePathRaw.c_str());
   writer->Write();

   // Read and display file for verification that it was written correctly
   vtkSmartPointer<vtkMetaImageReader> reader = 
      vtkSmartPointer<vtkMetaImageReader>::New();
   reader->SetFileName(filePath.c_str());
   reader->Update();

   vtkSmartPointer<vtkImageActor> actor =
      vtkSmartPointer<vtkImageActor>::New();
   actor->GetMapper()->SetInputConnection(reader->GetOutputPort());

   vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
   vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
   renderWindow->AddRenderer(renderer);
   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
   renderWindowInteractor->SetRenderWindow(renderWindow);

   renderer->AddActor(actor);
   renderer->SetBackground(.2, .3, .4);

   renderWindow->Render();
   renderWindowInteractor->Start();

   return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MetaImageWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MetaImageWriter MACOSX_BUNDLE MetaImageWriter.cxx)
 
target_link_libraries(MetaImageWriter ${VTK_LIBRARIES})
```

**Download and Build MetaImageWriter**

Click [here to download MetaImageWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MetaImageWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball MetaImageWriter.tar* has been downloaded and extracted,
```
cd MetaImageWriter/build 
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
./MetaImageWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

