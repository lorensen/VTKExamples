[VTKExamples](Home)/[Cxx](Cxx)/Images/ImageStencil

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Images/TestImageStencil.png" width="256" />

### Description
This example creates a red image and a green image. It creates a mask that is half on and half off. It then combines the images according to the mask using an ImageStencil.

:''See also: [and [[../Transparency]]([../../Visualization/ImageTransparency]])''

**ImageStencil.cxx**
```c++
#include <vtkVersion.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageStencil.h>
#include <vtkImageStencilData.h>
#include <vtkImageToImageStencil.h>
#include <vtkJPEGReader.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

static void CreateColorImage(vtkImageData*, unsigned int channel);
static void CreateMask(vtkImageData*);

int main(int, char *[])
{
  vtkSmartPointer<vtkImageData> image1 = vtkSmartPointer<vtkImageData>::New();
  CreateColorImage(image1, 0); // Create a red image

  vtkSmartPointer<vtkImageData> image2 = vtkSmartPointer<vtkImageData>::New();
  CreateColorImage(image2, 1); // Create a green image

  vtkSmartPointer<vtkImageData> mask = vtkSmartPointer<vtkImageData>::New();
  CreateMask(mask);

  //vtkSmartPointer<vtkImageStencilData> stencilData = vtkSmartPointer<vtkImageStencilData>::New();
  vtkSmartPointer<vtkImageToImageStencil> imageToImageStencil = vtkSmartPointer<vtkImageToImageStencil>::New();
#if VTK_MAJOR_VERSION <= 5
  imageToImageStencil->SetInputConnection(mask->GetProducerPort());
#else
  imageToImageStencil->SetInputData(mask);
#endif
  imageToImageStencil->ThresholdByUpper(122);

  vtkSmartPointer<vtkImageStencil> stencil = vtkSmartPointer<vtkImageStencil>::New();
  stencil->SetInputConnection(2, imageToImageStencil->GetOutputPort());
  stencil->ReverseStencilOn();
#if VTK_MAJOR_VERSION <= 5
  stencil->SetBackgroundInput(image2);
  stencil->SetInputConnection(image1->GetProducerPort());
#else
  stencil->SetBackgroundInputData(image2);
  stencil->SetInputData(image1);
#endif
  stencil->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(stencil->GetOutputPort());

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}


void CreateColorImage(vtkImageData* image, const unsigned int channel)
{
  unsigned int dim = 20;

  image->SetDimensions(dim, dim, 1);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(3);
  image->SetScalarTypeToUnsignedChar();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);
#endif
  for(unsigned int x = 0; x < dim; x++)
  {
    for(unsigned int y = 0; y < dim; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 0;
      pixel[1] = 0;
      pixel[2] = 0;

      pixel[channel] = 255;
    }
  }

  image->Modified();
}

static void CreateMask(vtkImageData* image)
{
  unsigned int dim = 20;

  image->SetDimensions(dim, dim, 1);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(1);
  image->SetScalarTypeToUnsignedChar();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
#endif
  for(unsigned int x = 0; x < dim; x++)
  {
    for(unsigned int y = 0; y < dim; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      if(x < dim/2)
      {
        pixel[0] = 0;
      }
      else
      {
        pixel[0] = 255;
      }
    }
  }

  image->Modified();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageStencil)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageStencil MACOSX_BUNDLE ImageStencil.cxx)
 
target_link_libraries(ImageStencil ${VTK_LIBRARIES})
```

**Download and Build ImageStencil**

Click [here to download ImageStencil](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageStencil.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageStencil.tar* has been downloaded and extracted,
```
cd ImageStencil/build 
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
./ImageStencil
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

