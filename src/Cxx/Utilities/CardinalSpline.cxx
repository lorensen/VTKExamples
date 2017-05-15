#include <vtkSmartPointer.h>
#include <vtkCardinalSpline.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
  // Create a scalar array.  The array could be associated with the scalars of a vtkDataSet
  vtkSmartPointer<vtkFloatArray> distances =
      vtkSmartPointer<vtkFloatArray>::New();
  distances->SetNumberOfComponents(1);
  distances->SetName("Distances");
  distances->InsertNextValue(100.0);
  distances->InsertNextValue(300.0);

  // Create a cardinal spline to show how to linearly interpolate between two scalar values
  vtkSmartPointer<vtkCardinalSpline> spline =
      vtkSmartPointer<vtkCardinalSpline>::New();
  spline->ClosedOff();

  // Set the left and right second derivatives to 0 corresponding to linear interpolation
  spline->SetLeftConstraint(2);
  spline->SetLeftValue(0);
  spline->SetRightConstraint(2);
  spline->SetRightValue(0);
  double* r = distances->GetRange();
  double xmin = r[0];
  double xmax = r[1];
  double length = xmax-xmin;
  for( vtkIdType i = 0; i < distances->GetNumberOfTuples(); ++i )
  {
    double x = distances->GetTuple1(i);
    double t = (x - xmin)/length;
    spline->AddPoint( t, x );
  }

  // Evaluate every 50 distance units along the line
  std::cout << "Spline interpolation:" << std::endl;
  double dt = .25;
  for( double t = dt ; t <= 1. - dt; t += dt )
  {
    std::cout << "t: " << t << " value = " << spline->Evaluate(t) << std::endl;
  }

  return EXIT_SUCCESS;
}
