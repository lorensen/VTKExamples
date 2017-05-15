#include <vtkSmartPointer.h>
#include <vtkPiecewiseFunction.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPiecewiseFunction> piecewiseFunction = 
      vtkSmartPointer<vtkPiecewiseFunction>::New();
  piecewiseFunction->AddPoint(0.0, 0.0);
  piecewiseFunction->AddPoint(1.0, 2.0);
  
  double test = piecewiseFunction->GetValue(0.25);

  std::cout << "test: " << test << " (should be 0.5)" << std::endl;

  return EXIT_SUCCESS;
}
