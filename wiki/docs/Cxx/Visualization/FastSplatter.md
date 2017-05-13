[VTKExamples](Home)/[Cxx](Cxx)/Visualization/FastSplatter

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestFastSplatter.png" width="256" />

**FastSplatter.cxx**
```c++
#include <vtkVersion.h>
#include "vtkImageData.h"
#include "vtkImageShiftScale.h"
#include "vtkFastSplatter.h"
#include "vtkImageViewer2.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"

#include <cmath>

const int SPLAT_IMAGE_SIZE = 100;

int main(int, char *[])
{
  // For the purposes of this example we'll build the splat image by
  // hand.

  vtkSmartPointer<vtkImageData> splatImage =
    vtkSmartPointer<vtkImageData>::New();
  splatImage->SetDimensions(SPLAT_IMAGE_SIZE, SPLAT_IMAGE_SIZE, 1);
#if VTK_MAJOR_VERSION <= 5
  splatImage->SetScalarTypeToFloat();
  splatImage->SetNumberOfScalarComponents(1);
  splatImage->AllocateScalars();
#else
  splatImage->AllocateScalars(VTK_FLOAT,1);
#endif
  for (int i = 0; i < SPLAT_IMAGE_SIZE; ++i)
  {
    for (int j = 0; j < SPLAT_IMAGE_SIZE; ++j)
    {
      double xCoord = 1 - fabs(  (i - SPLAT_IMAGE_SIZE/2)
                               / (SPLAT_IMAGE_SIZE/2.0) );
      double yCoord = 1 - fabs(  (j - SPLAT_IMAGE_SIZE/2)
                               / (SPLAT_IMAGE_SIZE/2.0) );

      splatImage->SetScalarComponentFromDouble(i, j, 0, 0,
                                               xCoord * yCoord );
    }
  }

  vtkSmartPointer<vtkPolyData> splatPoints =
    vtkSmartPointer<vtkPolyData>::New();
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  points->SetNumberOfPoints( 5 );
  double point[3];

  point[0] = 0;
  point[1] = 0;
  point[2] = 0;
  points->SetPoint( 0, point );

  point[0] = 1;
  point[1] = 1;
  point[2] = 0;
  points->SetPoint( 1, point );

  point[0] = -1;
  point[1] = 1;
  point[2] = 0;
  points->SetPoint( 2, point );

  point[0] = 1;
  point[1] = -1;
  point[2] = 0;
  points->SetPoint( 3, point );

  point[0] = -1;
  point[1] = -1;
  point[2] = 0;
  points->SetPoint( 4, point );

  splatPoints->SetPoints(points);

  vtkSmartPointer<vtkFastSplatter> splatter =
    vtkSmartPointer<vtkFastSplatter>::New();
#if VTK_MAJOR_VERSION <= 5
  splatter->SetInput( splatPoints );
  splatter->SetInput(1, splatImage );
#else
  splatter->SetInputData(splatPoints );
  splatter->SetInputData(1, splatImage );
#endif
  splatter->SetOutputDimensions( 2*SPLAT_IMAGE_SIZE,
                                 2*SPLAT_IMAGE_SIZE,
                                 1 );

  // The image viewers and writers are only happy with unsigned char
  // images.  This will convert the floats into that format.
  vtkSmartPointer<vtkImageShiftScale> resultScale =
    vtkSmartPointer<vtkImageShiftScale>::New();
  resultScale->SetOutputScalarTypeToUnsignedChar();
  resultScale->SetShift(0);
  resultScale->SetScale(255);
  resultScale->SetInputConnection( splatter->GetOutputPort() );

  splatter->Update();
  resultScale->Update();

  // Set up a viewer for the image.  vtkImageViewer and
  // vtkImageViewer2 are convenient wrappers around vtkActor2D,
  // vtkImageMapper, vtkRenderer, and vtkRenderWindow.  All you need
  // to supply is the interactor and hooray, Bob's your uncle.
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection( resultScale->GetOutputPort() );
  imageViewer->SetColorLevel(127);
  imageViewer->SetColorWindow(255);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->SetupInteractor(iren);

  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();

  imageViewer->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FastSplatter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FastSplatter MACOSX_BUNDLE FastSplatter.cxx)
 
target_link_libraries(FastSplatter ${VTK_LIBRARIES})
```

**Download and Build FastSplatter**

Click [here to download FastSplatter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FastSplatter.tar) and its *CMakeLists.txt* file.
Once the *tarball FastSplatter.tar* has been downloaded and extracted,
```
cd FastSplatter/build 
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
./FastSplatter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

