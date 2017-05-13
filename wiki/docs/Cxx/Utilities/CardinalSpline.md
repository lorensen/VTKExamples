[VTKExamples](Home)/[Cxx](Cxx)/Utilities/CardinalSpline

### Description
This example takes two points that have associated scalar values and allows you to interpolate the value at any point on the line between them using cardinal spline interpolation.

**CardinalSpline.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCardinalSpline.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
  // Create a scalar array.  The array could be associated with the scalars of a vtkDataSet
  vtkSmartPointer<vtkFloatArray> distances =
      vtkSmartPointer<vtkFloatArray>::New();
  distances->SetNumberOfComponents(1);
  distances->SetName("Distances");
  distances->InsertNextValue(100.0);
  distances->InsertNextValue(300.0);

  // Create a cardinal spline to show how to linearly interpolate between two scalar values
  vtkSmartPointer<vtkCardinalSpline> spline =
      vtkSmartPointer<vtkCardinalSpline>::New();
  spline->ClosedOff();

  // Set the left and right second derivatives to 0 corresponding to linear interpolation
  spline->SetLeftConstraint(2);
  spline->SetLeftValue(0);
  spline->SetRightConstraint(2);
  spline->SetRightValue(0);
  double* r = distances->GetRange();
  double xmin = r[0];
  double xmax = r[1];
  double length = xmax-xmin;
  for( vtkIdType i = 0; i < distances->GetNumberOfTuples(); ++i )
  {
    double x = distances->GetTuple1(i);
    double t = (x - xmin)/length;
    spline->AddPoint( t, x );
  }

  // Evaluate every 50 distance units along the line
  std::cout << "Spline interpolation:" << std::endl;
  double dt = .25;
  for( double t = dt ; t <= 1. - dt; t += dt )
  {
    std::cout << "t: " << t << " value = " << spline->Evaluate(t) << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CardinalSpline)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CardinalSpline MACOSX_BUNDLE CardinalSpline.cxx)
 
target_link_libraries(CardinalSpline ${VTK_LIBRARIES})
```

**Download and Build CardinalSpline**

Click [here to download CardinalSpline](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CardinalSpline.tar) and its *CMakeLists.txt* file.
Once the *tarball CardinalSpline.tar* has been downloaded and extracted,
```
cd CardinalSpline/build 
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
./CardinalSpline
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

