[VTKExamples](/index/)/[Cxx](/Cxx)/IO/ParticleReader

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestParticleReader.png?raw=true" width="256" />

### Description
This example reads ascii files where each line consists of points with its position (x,y,z) and (optionally) <u>one</u> scalar
or binary files in RAW 3d file format.

**ParticleReader.cxx**
```c++
//
// This example reads ascii files where each line consists of points with its position (x,y,z) 
// and (optionally) one scalar or binary files in RAW 3d file format.
//
// some standard vtk headers
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkProperty.h>

// headers needed for this example
#include <vtkParticleReader.h>
#include <vtkPolyDataMapper.h>


// needed to easily convert int to std::string
int main(int argc, char* argv[])
{
   // Verify input arguments
   if ( argc != 2 )
   {
      std::cout << "Usage: " << argv[0]
      << " Filename(.raw)" << std::endl;
      return EXIT_FAILURE;
   }

   std::string filePath = argv[1];
   // Particles.raw supplied by VTK is big endian encoded
   //std::string filePath = "C:\\VTK\\vtkdata-5.8.0\\Data\\Particles.raw";
   // Read the file
   vtkSmartPointer<vtkParticleReader> reader =
      vtkSmartPointer<vtkParticleReader>::New();

   reader->SetFileName ( filePath.c_str() );
   // if nothing gets displayed or totally wrong, swap the endianness
   reader->SetDataByteOrderToBigEndian();
   reader->Update();

   // Visualize
   vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
   mapper->SetInputConnection(reader->GetOutputPort());
   std::cout << "number of pieces: " << mapper->GetNumberOfPieces() << std::endl;
   mapper->SetScalarRange(4, 9);

   vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();

   actor->SetMapper(mapper);
   actor->GetProperty()->SetPointSize(4);

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
 
PROJECT(ParticleReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ParticleReader MACOSX_BUNDLE ParticleReader.cxx)
 
target_link_libraries(ParticleReader ${VTK_LIBRARIES})
```

**Download and Build ParticleReader**

Click [here to download ParticleReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ParticleReader.tar) and its *CMakeLists.txt* file.
Once the *tarball ParticleReader.tar* has been downloaded and extracted,
```
cd ParticleReader/build 
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
./ParticleReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

