#include <vtkMath.h>
#include <time.h>

int main(int, char *[])
{
  //The number of random numbers we wish to produce
  unsigned int numRand = 3;

  //without this line, the random numbers will be the same every iteration
  vtkMath::RandomSeed(time(NULL));

  //Generate numRand random numbers from a Gaussian distribution with mean 0.0 and standard deviation 2.0
  for(unsigned int i = 0; i < numRand; i++)
  {
    double a = vtkMath::Gaussian(0.0,2.0);
    std::cout << a << std::endl;
  }

  return EXIT_SUCCESS;
}
