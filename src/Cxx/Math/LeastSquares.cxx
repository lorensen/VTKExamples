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
