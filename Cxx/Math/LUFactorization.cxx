#include <vtkMath.h>

template<class TReal>
TReal **create_matrix ( long nrow, long ncol ) {
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

void OutputMatrix(double** a)
{
  std::cout << "[ " << a[0][0] << " " << a[0][1] << std::endl;
  std::cout << "  " << a[1][0] << " " << a[1][1] << " ]" << std::endl;
}

int main(int, char *[] )
{
  // Create and populate matrix
  int n = 2;
  double **a = create_matrix<double> (n, n);
  a[0][0] = 4; a[0][1] = 3;
  a[1][0] = 6; a[1][1] = 3;

  //[4 3; 6 3] should decompose to [1 0; 1.5 1] * [4 3; 0 -1.5]

  std::cout << "a"<< std::endl;
  OutputMatrix(a);

  // These values do not seem to change the result?
  int pivotIndices[2] = {0, 0};

  //Decompose matrix A into LU form
  vtkMath::LUFactorLinearSystem(a, pivotIndices, n);

  std::cout << "A decomposed into (unit lower triangular) L and U:"<< std::endl;
  OutputMatrix(a);

  /* The resulting matrix,
   [6       3]
   [.66667  1]
   is a superposition of L and U, with L being a unit lower triangular matrix.
   That is, ones on the diagonal, zeros in the upper right triangle, and values in the lower left triangle.

  The diagonal of the resulting A is the diagonal of U. The upper right triangle of A is the upper right triangle of U.
  The lower left triangle of A is the lower left triangle of L (and remember, the diagonal of L is all 1's).
  */

  /*
  To show that the resulting interpretation of the output matrix A is correct, we form the matrices following the description above
  and show that they multiply to the original A matrix.
  octave:9> [1 0; .666667 1] * [6 3; 0 1]
  ans =

   6.0000   3.0000
   4.0000   3.0000
  */

  return EXIT_SUCCESS;
}
