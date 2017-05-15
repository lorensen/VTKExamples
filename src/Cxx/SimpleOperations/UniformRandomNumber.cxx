#include <vtkMath.h>
#include <time.h>

int main(int, char *[])
{
  // Set the number of random numbers we wish to produce to 3.
  unsigned int numRand = 3;

  // Without this line, the random numbers will be the same every iteration.
  vtkMath::RandomSeed(time(NULL));

  // Generate numRand random numbers from a uniform distribution between 0.0 and 2.0
  for(unsigned int i = 0; i < numRand; i++)
  {
    double a = vtkMath::Random(0.0,2.0);
    std::cout << a << std::endl;
  }

  return EXIT_SUCCESS;
}
