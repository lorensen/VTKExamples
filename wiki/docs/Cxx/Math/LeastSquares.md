[VTKExamples](Home)/[Cxx](Cxx)/Math/LeastSquares

### Description
This example solves XM = Y (an interesting way to write Ax = b). 

In particular, we are trying to solve
<source lang="text">
[4]     [-2](1)
[2] M = [6](1)
[3]     [1](2)
</source>

It currently does not work.

**LeastSquares.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkMath.h>

  /* allocate memory for an nrow x ncol matrix */
  template<class TReal>
      TReal **create_matrix ( long nrow, long ncol )
  {
  typedef TReal* TRealPointer;
  TReal **m = new TRealPointer[nrow];

  TReal* block = ( TReal* ) calloc ( nrow*ncol, sizeof ( TReal ) );
  m[0] = block;
  for ( int row = 1; row < nrow; ++row )
  {
    m[ row ] = &block[ row * ncol ];
  }
  return m;
  }

  /* free a TReal matrix allocated with matrix() */
  template<class TReal>
      void free_matrix ( TReal **m )
  {
  free ( m[0] );
  delete[] m;
  }

int main(int, char *[])
{

  // Solve XM = Y;

  int numberOfSamples = 3;
  int numberOfVariables = 2;
  double **x = create_matrix<double> (numberOfSamples, numberOfVariables);
  x[0][0] = 1; x[0][1] = 4;
  x[1][0] = 1; x[1][1] = 2;
  x[2][0] = 2; x[2][1] = 3;

  double **m = create_matrix<double> ( numberOfVariables, 1 );

  double **y = create_matrix<double> ( numberOfSamples, 1 );
  y[0][0] = -2;
  y[1][0] = 6;
  y[2][0] = 1;

  vtkMath::SolveLeastSquares(numberOfSamples, x, numberOfVariables, y, 1, m);

  std::cout << "Solution is: " << m[0][0] << " " << m[1][0] << std::endl;

  // Solution should be [3; -1];
  free_matrix(x);
  free_matrix(m);
  free_matrix(y);

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LeastSquares)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LeastSquares MACOSX_BUNDLE LeastSquares.cxx)
 
target_link_libraries(LeastSquares ${VTK_LIBRARIES})
```

**Download and Build LeastSquares**

Click [here to download LeastSquares](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LeastSquares.tar) and its *CMakeLists.txt* file.
Once the *tarball LeastSquares.tar* has been downloaded and extracted,
```
cd LeastSquares/build 
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
./LeastSquares
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

