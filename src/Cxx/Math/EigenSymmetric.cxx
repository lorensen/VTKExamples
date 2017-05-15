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
