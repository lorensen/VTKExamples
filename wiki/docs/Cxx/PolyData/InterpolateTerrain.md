[VTKExamples](Home)/[Cxx](Cxx)/PolyData/InterpolateTerrain

### Description
This example samples a "terrain map" using two approaches.

# Creates an image from the x,y points of the terrian and then uses vtkProbeFilter to interpolate the heights.
# Uses vtkCellLocator to directly interpolate the terrain polydata.

Note that the results differ when the point is not one of the original terrain points. This is because the image has quadrilateral elements and the polydata has triangles. As the resolution of the grid increases, the two results converge.

**InterpolateTerrain.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkTriangle.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkLine.h>
#include <vtkImageData.h>
#include <vtkProbeFilter.h>
#include <vtkDelaunay2D.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkDoubleArray.h>
#include <vtkMath.h>
#include <vtkCellLocator.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->SetExtent(0, 9, 0, 9, 0, 0);
#if VTK_MAJOR_VERSION <= 5
  image->SetScalarTypeToDouble();
  image->SetNumberOfScalarComponents(1);
#else
  image->AllocateScalars(VTK_DOUBLE,1);
#endif
  //Create a random set of heights on a grid. This is often called a
  //"terrain map"
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  unsigned int GridSize = 10;
  for ( unsigned int x = 0; x < GridSize; x++ )
  {
    for ( unsigned int y = 0; y < GridSize; y++ )
    {
      double val = vtkMath::Random(-1.0, 1.0);
      points->InsertNextPoint ( x, y, val);
      image->SetScalarComponentFromDouble(x,y,0,0,val);
    }
  }

  //add the grid points to a polydata object
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints ( points );

  //triangulate the grid points
  vtkSmartPointer<vtkDelaunay2D> delaunay =
    vtkSmartPointer<vtkDelaunay2D>::New();
#if VTK_MAJOR_VERSION <= 5
  delaunay->SetInput ( polydata );
#else
  delaunay->SetInputData ( polydata );
#endif
  delaunay->Update();

  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName ( "surface.vtp" );
  writer->SetInputConnection ( delaunay->GetOutputPort() );
  writer->Write();

  // Add some points to interpolate
  vtkSmartPointer<vtkPoints> probePoints =
    vtkSmartPointer<vtkPoints>::New();
  probePoints->InsertNextPoint(5.2, 3.2, 0);
  probePoints->InsertNextPoint(5.0, 3.0, 0);
  probePoints->InsertNextPoint(0.0, 0.0, 0);

  vtkSmartPointer<vtkPolyData> probePolyData =
    vtkSmartPointer<vtkPolyData>::New();
  probePolyData->SetPoints(probePoints);

  vtkSmartPointer<vtkProbeFilter> probe =
    vtkSmartPointer<vtkProbeFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  probe->SetSource(image);
  probe->SetInput(probePolyData);
#else
  probe->SetSourceData(image);
  probe->SetInputData(probePolyData);
#endif
  probe->Update();

  vtkDataArray* data = probe->GetOutput()->GetPointData()->GetScalars();
  vtkDoubleArray* doubleData = vtkDoubleArray::SafeDownCast (data);

  for(int i = 0; i < doubleData->GetNumberOfTuples(); i++)
  {
    double val = doubleData->GetValue(i);
    cout << "Interpolation using ProbeFilter ";
    cout << "doubleData->GetValue(" << i << "): " << val << endl;
  }

  // Now find the elevation with a CellLocator
  vtkSmartPointer<vtkCellLocator> cellLocator =
    vtkSmartPointer<vtkCellLocator>::New();
  cellLocator->SetDataSet(delaunay->GetOutput());
  cellLocator->BuildLocator();

  for(int i = 0; i < doubleData->GetNumberOfTuples(); i++)
  {
    int subId;
    double t, xyz[3], pcoords[3];
    double rayStart[3], rayEnd[3];
    probePoints->GetPoint(i, rayStart);
    rayStart[2] += 1000.0;
    probePoints->GetPoint(i, rayEnd);
    rayEnd[2] -= 1000.0;

    if (cellLocator->IntersectWithLine(
          rayStart,
          rayEnd,
          0.0001,
          t,
          xyz,
          pcoords,
          subId))
    {
      cout << "Interpolation using CellLocator ";
      cout << "Elevation at " << rayStart[0] << ", " << rayStart[1] << " is " << xyz[2] << endl;
    }
  }
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(InterpolateTerrain)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(InterpolateTerrain MACOSX_BUNDLE InterpolateTerrain.cxx)
 
target_link_libraries(InterpolateTerrain ${VTK_LIBRARIES})
```

**Download and Build InterpolateTerrain**

Click [here to download InterpolateTerrain](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/InterpolateTerrain.tar) and its *CMakeLists.txt* file.
Once the *tarball InterpolateTerrain.tar* has been downloaded and extracted,
```
cd InterpolateTerrain/build 
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
./InterpolateTerrain
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

