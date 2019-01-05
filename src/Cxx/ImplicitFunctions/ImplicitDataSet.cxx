#include <vtkImageData.h>
#include <vtkImplicitDataSet.h>
#include <vtkRTAnalyticSource.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

int main(int /* argc */, char * /* argv */[]) {
  vtkSmartPointer<vtkRTAnalyticSource> waveletSource =
      vtkSmartPointer<vtkRTAnalyticSource>::New();
  waveletSource->Update();

  vtkSmartPointer<vtkImplicitDataSet> implicitWavelet =
      vtkSmartPointer<vtkImplicitDataSet>::New();
  implicitWavelet->SetDataSet(waveletSource->GetOutput());

  double x[3] = {.5, 0, 0};
  // Value should roughly be 258.658.
  cout << "x: " << implicitWavelet->EvaluateFunction(x) << endl;

  return EXIT_SUCCESS;
}
