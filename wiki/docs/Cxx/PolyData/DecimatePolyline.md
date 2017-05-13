[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/DecimatePolyline

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestDecimatePolyline.png?raw=true" width="256" />

### Description
This example shows how to [(signal processing)|decimate]]([wikipedia:Decimation) a polyline.

**DecimatePolyline.cxx**
```c++
#include <vtkVersion.h>
#include <vtkDecimatePolylineFilter.h>
#include <vtkMath.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>

#include <vtkSmartPointer.h>

int main(int, char *[])
{
  const unsigned int numberofpoints = 100;

  vtkPolyData* circle = vtkPolyData::New();
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
  vtkIdType* lineIndices = new vtkIdType[numberofpoints+1];

  for( unsigned int i = 0; i < numberofpoints; i++ )
  {
    const double angle = 2.0 * vtkMath::Pi() * static_cast< double >( i ) /
      static_cast< double >( numberofpoints );
    points->InsertPoint( static_cast< vtkIdType >( i ),
                         cos( angle ),
                         sin( angle ),
                         0. );
    lineIndices[i] = static_cast< vtkIdType >( i );
  }
  lineIndices[numberofpoints] = 0;
  lines->InsertNextCell( numberofpoints+1, lineIndices );
  delete[] lineIndices;

  circle->SetPoints( points );
  circle->SetLines( lines );

  vtkSmartPointer<vtkPolyDataMapper> c_mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  c_mapper->SetInput( circle );
#else
  c_mapper->SetInputData( circle );
#endif

  vtkSmartPointer<vtkActor> c_actor =
    vtkSmartPointer<vtkActor>::New();
  c_actor->SetMapper( c_mapper );

  vtkSmartPointer<vtkDecimatePolylineFilter> decimate =
    vtkSmartPointer<vtkDecimatePolylineFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  decimate->SetInput( circle );
#else
  decimate->SetInputData( circle );
#endif
  decimate->SetTargetReduction( 0.95 );
  decimate->Update();

  vtkSmartPointer<vtkPolyDataMapper> d_mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  d_mapper->SetInputConnection( decimate->GetOutputPort() );

  vtkSmartPointer<vtkActor> d_actor =
    vtkSmartPointer<vtkActor>::New();
  d_actor->SetMapper( d_mapper );
  d_actor->GetProperty()->SetColor( 1., 0. ,0. );

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  ren->AddActor( c_actor );
  ren->AddActor( d_actor );

  vtkSmartPointer<vtkRenderWindow> renwin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer( ren );

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow( renwin );

  renwin->Render();

  iren->Start();

  circle->Delete();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DecimatePolyline)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DecimatePolyline MACOSX_BUNDLE DecimatePolyline.cxx)
 
target_link_libraries(DecimatePolyline ${VTK_LIBRARIES})
```

**Download and Build DecimatePolyline**

Click [here to download DecimatePolyline](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DecimatePolyline.tar) and its *CMakeLists.txt* file.
Once the *tarball DecimatePolyline.tar* has been downloaded and extracted,
```
cd DecimatePolyline/build 
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
./DecimatePolyline
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

