[VTKExamples](/home/)/[Cxx](/Cxx)/Images/Transparency

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestTransparency.png?raw=true" width="256" />

### Description
This example creates a half transparent, half green mask and overlays it on top of an input image.

:''See also: [and [[../ImageStencil]]([../../Visualization/ImageTransparency]])''

**Transparency.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>
#include <vtkImageMapper3D.h>
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkJPEGReader.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.jpg)" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkJPEGReader> reader =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkImageData* image = reader->GetOutput();

  // Create a mask - half of the image should be transparent and the other half opaque
  vtkSmartPointer<vtkImageData> maskImage =
    vtkSmartPointer<vtkImageData>::New();
  int extent[6];
  image->GetExtent(extent);
  maskImage->SetExtent(extent);
#if VTK_MAJOR_VERSION <= 5
  maskImage->SetNumberOfScalarComponents(1);
  maskImage->SetScalarTypeToDouble();
#else
  maskImage->AllocateScalars(VTK_DOUBLE,1);
#endif
  for (int y = extent[2]; y < extent[3]; y++)
  {
    for (int x = extent[0]; x < extent[1]; x++)
    {
      double* pixel = static_cast<double*>(maskImage->GetScalarPointer(x,y,0));
      if(y > (extent[3]-extent[2])/2.0)
      {
        pixel[0] = 0.0;
      }
      else
      {
        pixel[0] = 1.0;
      }
    }
  }

  vtkSmartPointer<vtkLookupTable> lookupTable =
    vtkSmartPointer<vtkLookupTable>::New();
  lookupTable->SetNumberOfTableValues(2);
  lookupTable->SetRange(0.0,1.0);
  lookupTable->SetTableValue( 0, 0.0, 0.0, 0.0, 0.0 ); //label 0 is transparent
  lookupTable->SetTableValue( 1, 0.0, 1.0, 0.0, 1.0 ); //label 1 is opaque and green
  lookupTable->Build();

  vtkSmartPointer<vtkImageMapToColors> mapTransparency =
    vtkSmartPointer<vtkImageMapToColors>::New();
  mapTransparency->SetLookupTable(lookupTable);
  mapTransparency->PassAlphaToOutputOn();
#if VTK_MAJOR_VERSION <= 5
  mapTransparency->SetInput(maskImage);
#else
  mapTransparency->SetInputData(maskImage);
#endif

  // Create actors
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  imageActor->SetInput(image);
#else
  imageActor->GetMapper()->SetInputData(image);
#endif

  vtkSmartPointer<vtkImageActor> maskActor =
    vtkSmartPointer<vtkImageActor>::New();
  maskActor->GetMapper()->SetInputConnection(
    mapTransparency->GetOutputPort());

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageActor);
  renderer->AddActor(maskActor);
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
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Transparency)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Transparency MACOSX_BUNDLE Transparency.cxx)
 
target_link_libraries(Transparency ${VTK_LIBRARIES})
```

**Download and Build Transparency**

Click [here to download Transparency](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Transparency.tar) and its *CMakeLists.txt* file.
Once the *tarball Transparency.tar* has been downloaded and extracted,
```
cd Transparency/build 
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
./Transparency
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

