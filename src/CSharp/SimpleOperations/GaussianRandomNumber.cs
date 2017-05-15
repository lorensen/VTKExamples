using System;
using System.Diagnostics;
using Kitware.VTK;

void GaussianRandomNumber() {
   // Set the number of random numbers we wish to produce to 3.
   uint numRand = 3;
   // Without this line, the random numbers will be the same every iteration.
   vtkMath.RandomSeed((int)( DateTime.Now.Ticks & 0x0000FFFF ));

   // Generate numRand random numbers from a Gaussian distribution with mean 0.0 and standard deviation 2.0
   for(uint i = 0; i < numRand; i++) {
      double a = vtkMath.Gaussian(0.0, 2.0);
      Console.WriteLine(a);
   }
}
