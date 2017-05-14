[VTKExamples](/index/)/[CSharp](/CSharp)/SimpleOperations/RandomSequence

### Description
This is the "new" (December, 2009) VTK way to produce random numbers. It is actually a random sequence generator.

**RandomSequence.cs**
```csharp
using System;
using System.Diagnostics;
using Kitware.VTK;

void RandomSequence() {
   //Create a random sequence generator.
   vtkMinimalStandardRandomSequence sequence = 
      vtkMinimalStandardRandomSequence.New();

   // initialize the sequence
   sequence.SetSeed((int)(DateTime.Now.Ticks & 0x0000FFFF));
   //Get 3 random numbers.
   double x = sequence.GetValue();
   sequence.Next();
   double y = sequence.GetValue();
   sequence.Next();
   double z = sequence.GetValue();

   // You can also use sequence.GetRangeValue(-1.0, 1.0); 
   // to set a range on the random values.

   // Output the resulting random numbers
   Console.WriteLine("x: " + x + " y: " + y + " z: " + z);
}
```
