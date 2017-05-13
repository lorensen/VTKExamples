[VTKExamples](/home/)/[Cxx](/Cxx)/ImageData/ImageTranslateExtent

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/ImageData/TestImageTranslateExtent.png?raw=true" width="256" />

### Description
If you are looking to change the extent to change the "origin" of the image from the corner to the center, see vtkImageChangeInformation (http://www.vtk.org/Wiki/VTK/Examples/Cxx/Images/CenterAnImage).

Currently this method changes the extent (shown by the terminal output in the example), but does not change where the corner of the image is displayed relative to the sphere at (0,0,0).

**ImageTranslateExtent.cxx**
```c++
#include <vtkVersion.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkImageTranslateExtent.h>

static void CreateColorImage(vtkImageData* const);

int main(int, char *[])
{
  vtkSmartPointer<vtkImageData> colorImage = vtkSmartPointer<vtkImageData>::New();
  CreateColorImage(colorImage); // This image has (0,0) at the bottom left corner

  int extent[6];
  colorImage->GetExtent(extent);
  std::cout << "Old extent: " << extent[0] << " " << extent[1] << " " << extent[2] << " " << extent[3] << " " << extent[4] << " " << extent[5] << std::endl;

  // This moves the (0,0) position in the image to the center of the image
//  int extent[6];
//  colorImage->GetExtent(extent);
//  colorImage->SetExtent(extent[0] - (extent[1] - extent[0])/2, extent[0] + (extent[1] - extent[0])/2,
//                        extent[2] - (extent[3] - extent[2])/2, extent[2] + (extent[3] - extent[2])/2,
//                        extent[4] - (extent[5] - extent[4])/2, extent[4] + (extent[5] - extent[4])/2);

  int dimensions[3];
  colorImage->GetDimensions(dimensions);

  vtkSmartPointer<vtkImageTranslateExtent> translateExtent =
    vtkSmartPointer<vtkImageTranslateExtent>::New();
  translateExtent->SetTranslation(-dimensions[0]/2,-dimensions[1]/2,0);
#if VTK_MAJOR_VERSION <= 5
  translateExtent->SetInput(colorImage);
#else
  translateExtent->SetInputData(colorImage);
#endif
  translateExtent->Update();
  colorImage->DeepCopy(translateExtent->GetOutput());

  colorImage->GetExtent(extent);
  std::cout << "New extent: " << extent[0] << " " << extent[1] << " " << extent[2] << " " << extent[3] << " " << extent[4] << " " << extent[5] << std::endl;

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(1.0);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  imageSliceMapper->SetInput(colorImage);
#else
  imageSliceMapper->SetInputData(colorImage);
#endif
  vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice->SetMapper(imageSliceMapper);
  imageSlice->SetPosition(0,0,0);

  // Setup renderers
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(imageSlice);
  renderer->AddViewProp(sphereActor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(300, 300);
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

void CreateColorImage(vtkImageData* const image)
{
  image->SetDimensions(10, 10, 1);

#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(3);
  image->SetScalarTypeToUnsignedChar();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);
#endif

  for(unsigned int x = 0; x < 10; x++)
  {
    for(unsigned int y = 0; y < 10; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 255;
      pixel[1] = 0;
      pixel[2] = 255;
    }
  }
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageTranslateExtent)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageTranslateExtent MACOSX_BUNDLE ImageTranslateExtent.cxx)
 
target_link_libraries(ImageTranslateExtent ${VTK_LIBRARIES})
```

**Download and Build ImageTranslateExtent**

Click [here to download ImageTranslateExtent](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageTranslateExtent.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageTranslateExtent.tar* has been downloaded and extracted,
```
cd ImageTranslateExtent/build 
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
./ImageTranslateExtent
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

