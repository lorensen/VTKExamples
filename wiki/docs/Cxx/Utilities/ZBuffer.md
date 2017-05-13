[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/ZBuffer

**ZBuffer.cxx**
```c++
// This demo creates depth map for a polydata instance by extracting
// exact ZBuffer values.
#include <vtkSmartPointer.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkBMPWriter.h>
#include <vtkWindowToImageFilter.h>
#include <vtkImageShiftScale.h>

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
      std::cout << "Usage: " << argv[0]
                << " input(.vtp) output(.bmp)"
                << std::endl;
      return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkXMLPolyDataReader> fileReader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  vtkSmartPointer<vtkWindowToImageFilter> filter =
    vtkSmartPointer<vtkWindowToImageFilter>::New();
  vtkSmartPointer<vtkBMPWriter> imageWriter =
    vtkSmartPointer<vtkBMPWriter>::New();
  vtkSmartPointer<vtkImageShiftScale> scale =
    vtkSmartPointer<vtkImageShiftScale>::New();

  // Read .vtp file
  fileReader->SetFileName(argv[1]);

  //Build visualization enviroment
  mapper->SetInputConnection(fileReader->GetOutputPort());
  actor->SetMapper(mapper);
  renderer->AddActor(actor);
  renWin->AddRenderer(renderer);
  interactor->SetRenderWindow(renWin);
  renWin->Render();

  // Create Depth Map
  filter->SetInput(renWin);
  filter->SetMagnification(1);
  filter->SetInputBufferTypeToZBuffer();        //Extract z buffer value

  scale->SetOutputScalarTypeToUnsignedChar();
  scale->SetInputConnection(filter->GetOutputPort());
  scale->SetShift(0);
  scale->SetScale(-255);

  // Write depth map as a .bmp image
  imageWriter->SetFileName(argv[2]);
  imageWriter->SetInputConnection(scale->GetOutputPort());
  imageWriter->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ZBuffer)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ZBuffer MACOSX_BUNDLE ZBuffer.cxx)
 
target_link_libraries(ZBuffer ${VTK_LIBRARIES})
```

**Download and Build ZBuffer**

Click [here to download ZBuffer](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ZBuffer.tar) and its *CMakeLists.txt* file.
Once the *tarball ZBuffer.tar* has been downloaded and extracted,
```
cd ZBuffer/build 
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
./ZBuffer
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

