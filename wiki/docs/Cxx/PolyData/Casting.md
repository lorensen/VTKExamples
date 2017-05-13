[VTKExamples](Home)/[Cxx](Cxx)/PolyData/Casting

### Description
This example creates a polydata object with 3 points and attaches a distance value to each point. To retrieve the array from the polydata, we have to use a SafeDownCast to the type that we want. This is necessary because to keep things as general as possible the polydata will return an abstract array class.

**Casting.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>

int main(int, char *[])
{
  // Create points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  unsigned int numberOfPoints = 3;
  points->InsertNextPoint ( 0.0, 0.0, 0.0 );
  points->InsertNextPoint ( 1.0, 0.0, 0.0 );
  points->InsertNextPoint ( 0.0, 1.0, 0.0 );

  // Add the points to a polydata
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints ( points );

  // Add distances to each point
  vtkSmartPointer<vtkDoubleArray> distances =
    vtkSmartPointer<vtkDoubleArray>::New();
  distances->SetNumberOfComponents(1);
  distances->SetName("Distances");

  distances->InsertNextValue(1.1);
  distances->InsertNextValue(2.2);
  distances->InsertNextValue(3.3);

  polydata->GetPointData()->AddArray ( distances );

  // Get the distances from the polydata
  vtkDoubleArray* array = vtkDoubleArray::SafeDownCast ( polydata->GetPointData()->GetArray ( "Distances" ) );

  if ( array )
  {
    for ( unsigned int i = 0; i < numberOfPoints; i++ )
    {
      double dist;
      dist = array->GetValue ( i );
      std::cout << "Distance: " << dist << std::endl;
    }
  }

  // Cast the double distances to ints
  vtkDoubleArray* doubleDistances = vtkDoubleArray::SafeDownCast(
                   polydata->GetPointData()->GetArray("Distances"));
  vtkIntArray* intDistances = vtkIntArray::SafeDownCast(doubleDistances);

  if(intDistances)
  {
    for(unsigned int i = 0; i < numberOfPoints; i++)
    {
      int dist;
      dist = intDistances->GetValue ( i );
      std::cout << "Distance: " << dist << std::endl;
    }
  }
  else
  {
    std::cout << "invalid cast." << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Casting)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Casting MACOSX_BUNDLE Casting.cxx)
 
target_link_libraries(Casting ${VTK_LIBRARIES})
```

**Download and Build Casting**

Click [here to download Casting](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Casting.tar) and its *CMakeLists.txt* file.
Once the *tarball Casting.tar* has been downloaded and extracted,
```
cd Casting/build 
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
./Casting
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

