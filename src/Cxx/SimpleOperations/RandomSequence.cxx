#include <vtkMinimalStandardRandomSequence.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  //Create a random sequence generator.
  vtkSmartPointer<vtkMinimalStandardRandomSequence> sequence = 
      vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();

  // initialize the sequence
  sequence->SetSeed(1);

  //Get 3 random numbers.
  double x = sequence->GetValue();
  sequence->Next();
  double y = sequence->GetValue();
  sequence->Next();
  double z = sequence->GetValue();
  
  // You can also use seq->GetRangeValue(-1.0,1.0); 
  //to set a range on the random values.

  //Output the resulting random numbersl
  std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
  
  return EXIT_SUCCESS;
}
