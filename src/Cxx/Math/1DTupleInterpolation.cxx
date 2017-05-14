//
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif
#include <ctime>
 
#include <vtkSmartPointer.h>
#include <vtkTupleInterpolator.h>
#include <vtkCardinalSpline.h>
#include <vtkKochanekSpline.h>
 
#define VERBOSE(x) \
{ \
  if (Verbose) \
  {\
    std::cout x; \
    std::cout.flush(); \
  }\
}
 
// verbose flag
bool Verbose = true;
// CSV output flag
bool CSVOutput = false;
 
/**
 * Print example usage information.
 **/
void PrintUsage(char *binname)
{
  std::string progname = "<binary-name>";
  if (binname)
    progname = std::string(binname);
  std::cout << "\n";
  std::cout << "   *** E X A M P L E   U S A G E ***\n";
  std::cout << "\n";
  std::cout << progname << " [options]\n";
  std::cout << "\n";
  std::cout << "  -h or --help ... print this short help\n";
  std::cout << "  -nv or --no-verbose ... no verbose messages to std::cout\n";
  std::cout << "  -co or --csv-output ... CSV (comma separated values) file outputs\n";
  std::cout << "\n";
  std::cout << "  NOTE: optional arguments are case-sensitive!\n";
  std::cout << "\n";
  std::cout << "  Author: ---\n";
  std::cout << "  Affiliation: ---\n";
  std::cout << "\n";
}
 
/** Runge function. **/
double FRunge(double x)
{
  return 1.0 / (1.0 + x * x);
}
 
/** Sine function. **/
double FSin(double x)
{
  return sin(x);
}
 
/** Execute a specific tuple interpolation method with pre-initialized tuple interpolator. **/
bool TestInterpolation(vtkSmartPointer<vtkTupleInterpolator> tupInt, double
    tolerance, const char *csvFileName, double (*mathFunc)(double), double *x,
    double *y, double N, double symmetricIntervalWidth)
{
  bool ok = true;
  std::ofstream csvint;
  if (CSVOutput)
  {
    csvint.open(csvFileName, std::ios::out);
    if (csvint.is_open())
      csvint << "x;y;e\n";
    else
      ok = false;
  }
  double yt[1];
  for (int i = 0; i < N; i++) // re-define supporting points
  {
    yt[0] = y[i];
    tupInt->AddTuple(x[i], yt);
  }
  // draw random samples from interval and test against mathFunc:
  for (int i = 0; i < 1000; i++)
  {
    double f = (double) (rand() % 100001) / 100000.;
    double xi = (f * 2.0 - 1.0) * symmetricIntervalWidth;
    double yi[1];
    tupInt->InterpolateTuple(xi, yi);
    double ei = std::abs(yi[0] - mathFunc(xi));
    // we have a tolerance within [-PI;+PI] - empirical!
    if (xi >= -symmetricIntervalWidth && xi <= symmetricIntervalWidth &&
        ei > tolerance)
      ok = false;
    if (CSVOutput && csvint.is_open())
      csvint << xi << ";" << yi[0] << ";" << ei << "\n";
  }
  if (CSVOutput && csvint.is_open())
    csvint.close();
  return ok;
}
 
/** \brief Demonstrate base functionality of VTK-based tuple interpolation (1D).
 * Demonstrate base functionality of VTK-based tuple interpolation (1D).
 *
 * Application result is 0 if SUCCESSFUL.
 *
 * Arguments: <br>
 * -h or --help ... print short help <br>
 * -nv or --no-verbose ... message output (verbose) <br>
 * -co or --csv-output ... CSV (comma separated values) file outputs <br>
 *
 * @author ---
 * @version 1.2
 */
int main(int argc, char *argv[])
{
  // arguments check
  for (int i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) == "-nv" || std::string(argv[i]) == "--no-verbose")
      Verbose = false;
    if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help")
    {
      if (argc > 0)
        PrintUsage(argv[0]);
      else
        PrintUsage(NULL);
      return EXIT_FAILURE;
    }
    if (std::string(argv[i]) == "-co" || std::string(argv[i]) == "--csv-output")
      CSVOutput = true;
  }
 
  VERBOSE(<< "\nDemonstrating VTK-based 1-tuple interpolation capabilities.\n")
  bool ok = true;
 
  VERBOSE(<< "  * Generate supporting points ... ")
  bool lok = true; // local OK
  // - SINE -
  const int N1 = 13;
  double *xs = new double[N1];
  double *ys = new double[N1];
  std::ofstream csv;
  if (CSVOutput)
  {
    csv.open("sine.csv", std::ios::out);
    if (csv.is_open())
      csv << "x;y\n";
    else
      lok = false;
  }
  // prepare the supporting points (sine):
  for (int i = 0; i < N1; i++)
  {
    xs[i] = -M_PI + (double) i / (double) (N1 - 1) * (2. * M_PI);
    ys[i] = FSin(xs[i]);
 
    if (CSVOutput && csv.is_open())
      csv << xs[i] << ";" << ys[i] << "\n";
  }
  if (CSVOutput && csv.is_open())
    csv.close();
  // - RUNGE -
  const int N2 = 10;
  double *xr = new double[N2];
  double *yr = new double[N2];
  if (CSVOutput)
  {
    csv.open("runge.csv", std::ios::out);
    if (csv.is_open())
      csv << "x;y\n";
    else
      lok = false;
  }
  // prepare the supporting points (sine):
  for (int i = 0; i < N2; i++)
  {
    xr[i] = -5.0 + (double) i / (double) (N2 - 1) * (2. * 5.0);
    yr[i] = FRunge(xr[i]);
 
    if (CSVOutput && csv.is_open())
      csv << xr[i] << ";" << yr[i] << "\n";
  }
  if (CSVOutput && csv.is_open())
    csv.close();
  ok = ok && lok;
  VERBOSE(<< (lok ? "OK" : "FAILURE") << "\n")
 
  VERBOSE(<< "  * Interpolation of sine using linear method ... ")
  // initialize the tuple interpolator (1D):
  vtkSmartPointer<vtkTupleInterpolator> tupInt = vtkSmartPointer<vtkTupleInterpolator>::New();
  tupInt->SetInterpolationTypeToLinear(); // linear
  tupInt->SetNumberOfComponents(1); // 1D (NOTE: set #components AFTER interpolation-type!)
  lok = TestInterpolation(tupInt, 0.04, "sin_linear_int.csv", FSin, xs, ys, N1, M_PI);
  ok = ok && lok;
  VERBOSE(<< (lok ? "OK" : "FAILURE") << "\n")
 
  VERBOSE(<< "  * Interpolation of sine using cardinal spline method (open interval) ... ")
  // initialize the tuple interpolator (1D):
  tupInt->SetInterpolationTypeToSpline(); // spline (implicit reset!)
  vtkSmartPointer<vtkCardinalSpline> cardSpline = vtkSmartPointer<vtkCardinalSpline>::New();
  cardSpline->SetClosed(false);
  tupInt->SetInterpolatingSpline(cardSpline);
  tupInt->SetNumberOfComponents(1); // 1D (NOTE: set #components AFTER interpolation-type!)
  lok = TestInterpolation(tupInt, 0.1, "sin_card_spline_open_int.csv", FSin, xs, ys, N1, M_PI);
  ok = ok && lok;
  VERBOSE(<< (lok ? "OK" : "FAILURE") << "\n")
 
  VERBOSE(<< "  * Interpolation of sine using cardinal spline method (closed interval) ... ")
  // initialize the tuple interpolator (1D):
  tupInt->Initialize(); // reset
  tupInt->SetInterpolationTypeToSpline(); // spline
  cardSpline->SetClosed(true);
  tupInt->SetInterpolatingSpline(cardSpline);
  tupInt->SetNumberOfComponents(1); // 1D (NOTE: set #components AFTER interpolation-type!)
  lok = TestInterpolation(tupInt, 0.05, "sin_card_spline_closed_int.csv", FSin, xs, ys, N1, M_PI);
  ok = ok && lok;
  VERBOSE(<< (lok ? "OK" : "FAILURE") << "\n")
 
  VERBOSE(<< "  * Interpolation of sine using Kochanek spline (default setup) method (open interval) ... ")
  // initialize the tuple interpolator (1D):
  tupInt->Initialize(); // reset
  tupInt->SetInterpolationTypeToSpline(); // spline
  vtkSmartPointer<vtkKochanekSpline> kochSpline = vtkSmartPointer<vtkKochanekSpline>::New();
  kochSpline->SetClosed(false);
  tupInt->SetInterpolatingSpline(kochSpline);
  tupInt->SetNumberOfComponents(1); // 1D (NOTE: set #components AFTER interpolation-type!)
  lok = TestInterpolation(tupInt, 0.1, "sin_koch_spline_open_int.csv", FSin, xs, ys, N1, M_PI);
  ok = ok && lok;
  VERBOSE(<< (lok ? "OK" : "FAILURE") << "\n")
 
  VERBOSE(<< "  * Interpolation of sine using Kochanek spline (default setup) method (closed interval) ... ")
  // initialize the tuple interpolator (1D):
  tupInt->Initialize(); // reset
  tupInt->SetInterpolationTypeToSpline(); // spline
  kochSpline->SetClosed(true);
  tupInt->SetInterpolatingSpline(kochSpline);
  tupInt->SetNumberOfComponents(1); // 1D (NOTE: set #components AFTER interpolation-type!)
  lok = TestInterpolation(tupInt, 0.06, "sin_koch_spline_closed_int.csv", FSin, xs, ys, N1, M_PI);
  ok = ok && lok;
  VERBOSE(<< (lok ? "OK" : "FAILURE") << "\n")
 
 
  VERBOSE(<< "  * Interpolation of Runge using linear method ... ")
  // initialize the tuple interpolator (1D):
  tupInt->Initialize();
  tupInt->SetInterpolationTypeToLinear(); // linear
  tupInt->SetNumberOfComponents(1); // 1D (NOTE: set #components AFTER interpolation-type!)
  lok = TestInterpolation(tupInt, 0.25 /* around 0! */, "runge_linear_int.csv", FRunge, xr, yr, N2, 5.0);
  ok = ok && lok;
  VERBOSE(<< (lok ? "OK" : "FAILURE") << "\n")
 
  VERBOSE(<< "  * Interpolation of Runge using cardinal spline method ... ")
  // initialize the tuple interpolator (1D):
  tupInt->SetInterpolationTypeToSpline(); // spline (implicit reset!)
  cardSpline->SetClosed(false);
  tupInt->SetInterpolatingSpline(cardSpline);
  tupInt->SetNumberOfComponents(1); // 1D (NOTE: set #components AFTER interpolation-type!)
  lok = TestInterpolation(tupInt, 0.15 /* around 0! */, "runge_card_spline_int.csv", FRunge, xr, yr, N2, 5.0);
  ok = ok && lok;
  VERBOSE(<< (lok ? "OK" : "FAILURE") << "\n")
 
  VERBOSE(<< "  * Interpolation of Runge using Kochanek spline method ... ")
  // initialize the tuple interpolator (1D):
  tupInt->Initialize(); // reset
  tupInt->SetInterpolationTypeToSpline(); // spline (implicit reset!)
  kochSpline->SetClosed(false);
  tupInt->SetInterpolatingSpline(kochSpline);
  tupInt->SetNumberOfComponents(1); // 1D (NOTE: set #components AFTER interpolation-type!)
  lok = TestInterpolation(tupInt, 0.18 /* around 0! */, "runge_koch_spline_int.csv", FRunge, xr, yr, N2, 5.0);
  ok = ok && lok;
  VERBOSE(<< (lok ? "OK" : "FAILURE") << "\n")
 
 
  delete[] xs;
  delete[] ys;
  delete[] xr;
  delete[] yr;
  cardSpline = NULL;
  kochSpline = NULL;
  tupInt = NULL;
 
  VERBOSE(<< "Application result: ")
  if (ok)
  {
    VERBOSE(<< "OK\n\n")
    return EXIT_SUCCESS;
  }
  else
  {
    VERBOSE(<< "FAILURE\n\n")
    return EXIT_FAILURE;
  }
}
