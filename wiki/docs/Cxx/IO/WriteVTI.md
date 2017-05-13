[VTKExamples](/home/)/[Cxx](/Cxx)/IO/WriteVTI

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestWriteVTI.png?raw=true" width="256" />

**WriteVTI.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkXMLImageDataReader.h>
#include <vtkImageData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cout << "Required arguments: filename.vti" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];

  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();
  imageData->SetDimensions(3,4,5);
#if VTK_MAJOR_VERSION <= 5
  imageData->SetNumberOfScalarComponents(1);
  imageData->SetScalarTypeToDouble();
#else
  imageData->AllocateScalars(VTK_DOUBLE, 1);
#endif
  int* dims = imageData->GetDimensions();

  // Fill every entry of the image data with "2.0"
  for (int z = 0; z < dims[2]; z++)
  {
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
        pixel[0] = 2.0;
      }
    }
  }

  vtkSmartPointer<vtkXMLImageDataWriter> writer =
    vtkSmartPointer<vtkXMLImageDataWriter>::New();
  writer->SetFileName(filename.c_str());
#if VTK_MAJOR_VERSION <= 5
  writer->SetInputConnection(imageData->GetProducerPort());
#else
  writer->SetInputData(imageData);
#endif
  writer->Write();

  // Read the file (to test that it was written correctly)
  vtkSmartPointer<vtkXMLImageDataReader> reader =
    vtkSmartPointer<vtkXMLImageDataReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  // Convert the image to a polydata
  vtkSmartPointer<vtkImageDataGeometryFilter> imageDataGeometryFilter =
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  imageDataGeometryFilter->SetInputConnection(reader->GetOutputPort());
  imageDataGeometryFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(imageDataGeometryFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(3);

  // Setup rendering
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1);
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(WriteVTI)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WriteVTI MACOSX_BUNDLE WriteVTI.cxx)
 
target_link_libraries(WriteVTI ${VTK_LIBRARIES})
```

**Download and Build WriteVTI**

Click [here to download WriteVTI](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WriteVTI.tar) and its *CMakeLists.txt* file.
Once the *tarball WriteVTI.tar* has been downloaded and extracted,
```
cd WriteVTI/build 
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
./WriteVTI
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

