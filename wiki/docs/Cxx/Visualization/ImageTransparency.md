[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/ImageTransparency

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestImageTransparency.png?raw=true" width="256" />

### Description
:''See also: [and [[../../Images/ImageStencil]]([../../Images/Transparency]])''

**ImageTransparency.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToColors.h>
#include <vtkJPEGReader.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

static void CreateImage(vtkSmartPointer<vtkImageData> image);

int main(int, char*[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  CreateImage(image);

  // Create actor
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  imageActor->SetInput(image);
#else
  imageActor->GetMapper()->SetInputData(image);
#endif

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageActor);
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CreateImage(vtkSmartPointer<vtkImageData> image)
{
  // Specify the size of the image data
  image->SetDimensions(10,10,1);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(4);
  image->SetScalarTypeToUnsignedChar();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,4);
#endif
  int* dims = image->GetDimensions();
  // int dims[3]; // can't do this

  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  // Fill every entry of the image with "2"
  for (int y = 0; y < dims[1]; y++)
  {
    for (int x = 0; x < dims[0]; x++)
    {

      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 255;
      pixel[1] = 255;
      pixel[2] = 255;
      if(x<5)
      {
        pixel[3] = 0;
      }
      else
      {
        pixel[3] = 255;
      }
    }
  }

}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageTransparency)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageTransparency MACOSX_BUNDLE ImageTransparency.cxx)
 
target_link_libraries(ImageTransparency ${VTK_LIBRARIES})
```

**Download and Build ImageTransparency**

Click [here to download ImageTransparency](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageTransparency.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageTransparency.tar* has been downloaded and extracted,
```
cd ImageTransparency/build 
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
./ImageTransparency
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

