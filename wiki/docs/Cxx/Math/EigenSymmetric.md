[VTKExamples](/home/)/[Cxx](/Cxx)/Math/EigenSymmetric

### Description
At the moment, this is a pretty messy process, so here are some helper functions that will hopefully eventually be wrapped into a class/interface.

**EigenSymmetric.cxx**
```c++
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
// Create this matrix
// 1 2 3
// 2 5 9
// 3 9 8

  double **a = create_matrix<double> ( 3,3 );
  a[0][0] = 1; a[0][1] = 2;  a[0][2] = 3;
  a[1][0] = 2; a[1][1] = 5;  a[1][2] = 9;
  a[2][0] = 3; a[2][1] = 9;  a[2][2] = 8;

  //create a matrix for the eigenvectors to be stored in
  double **w = create_matrix<double> ( 3,3 );

  //create a vector for the eigenvalues to be stored in
  double v[3];

  //compute the eigenvalues/vectors
  vtkMath::Jacobi ( a,v,w );

  //output eigen values
  std::cout << "Eigen values (decreasing order): " << std::endl;
  for ( int i=0; i<3; i++ )
  {
    std::cout << v[i] << " ";
  }

  //output eigenvectors
  std::cout << "Eigen vectors (same order as eigen values): " << std::endl;
  for ( int i=0; i<3; i++ )
  {
    //the columns of w are the eigenvectors
    std::cout << "Eigen vector " << i << " : " << w[0][i] << " " << w[1][i] << " " << w[2][i] << std::endl;
  }

  //clean up
  free_matrix ( w );
  free_matrix ( a );

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(EigenSymmetric)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(EigenSymmetric MACOSX_BUNDLE EigenSymmetric.cxx)
 
target_link_libraries(EigenSymmetric ${VTK_LIBRARIES})
```

**Download and Build EigenSymmetric**

Click [here to download EigenSymmetric](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/EigenSymmetric.tar) and its *CMakeLists.txt* file.
Once the *tarball EigenSymmetric.tar* has been downloaded and extracted,
```
cd EigenSymmetric/build 
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
./EigenSymmetric
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

