[VTKExamples](Home)/[Cxx](Cxx)/Images/ImageShiftScale

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Images/TestImageShiftScale.png" width="256" />

**ImageShiftScale.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageShiftScale.h>
#include <vtkImageEllipsoidSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageProperty.h>
#include <vtkPNGWriter.h>

static void CreateImage(vtkImageData*);

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
  CreateImage(image);

  vtkSmartPointer<vtkImageShiftScale> shiftScaleFilter =
    vtkSmartPointer<vtkImageShiftScale>::New();
  shiftScaleFilter->SetOutputScalarTypeToUnsignedChar();
#if VTK_MAJOR_VERSION <= 5
  shiftScaleFilter->SetInputConnection(image->GetProducerPort());
#else
  shiftScaleFilter->SetInputData(image);
#endif
  shiftScaleFilter->SetShift(100);
  shiftScaleFilter->SetScale(1);
  shiftScaleFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageSliceMapper> originalSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  originalSliceMapper->SetInputConnection(image->GetProducerPort());
#else
  originalSliceMapper->SetInputData(image);
#endif

  vtkSmartPointer<vtkImageSlice> originalSlice = vtkSmartPointer<vtkImageSlice>::New();
  originalSlice->SetMapper(originalSliceMapper);
  originalSlice->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkImageSliceMapper> shiftScaleMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
  shiftScaleMapper->SetInputConnection(shiftScaleFilter->GetOutputPort());

  vtkSmartPointer<vtkImageSlice> shiftScaleSlice = vtkSmartPointer<vtkImageSlice>::New();
  shiftScaleSlice->SetMapper(shiftScaleMapper);
  shiftScaleSlice->GetProperty()->SetInterpolationTypeToNearest();

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double shiftScaleViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddViewProp(originalSlice);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> shiftScaleRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  shiftScaleRenderer->SetViewport(shiftScaleViewport);
  shiftScaleRenderer->AddViewProp(shiftScaleSlice);
  shiftScaleRenderer->ResetCamera();
  shiftScaleRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(shiftScaleRenderer);

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


void CreateImage(vtkImageData* image)
{
  unsigned int dim = 20;

  image->SetDimensions(dim, dim, 1);

#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(1);
  image->SetScalarTypeToUnsignedChar();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,1);
#endif
  for(unsigned int x = 0; x < dim; x++)
  {
    for(unsigned int y = 0; y < dim; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      if(x < dim/2)
      {
	pixel[0] = 50;
      }
      else
      {
	pixel[0] = 150;
      }
    }
  }

  image->Modified();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageShiftScale)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageShiftScale MACOSX_BUNDLE ImageShiftScale.cxx)
 
target_link_libraries(ImageShiftScale ${VTK_LIBRARIES})
```

**Download and Build ImageShiftScale**

Click [here to download ImageShiftScale](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageShiftScale.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageShiftScale.tar* has been downloaded and extracted,
```
cd ImageShiftScale/build 
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
./ImageShiftScale
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

