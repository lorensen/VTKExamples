#include <vtkSmartPointer.h>
#include <vtkDiscreteMarchingCubes.h>
#include <vtkWindowedSincPolyDataFilter.h>

#include <vtkMath.h>
#include <vtkImageData.h>
#include <vtkSphere.h>
#include <vtkSampleFunction.h>
#include <vtkImageThreshold.h>
#include <vtkImageMathematics.h>
#include <vtkPolyDataMapper.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkLookupTable.h>

#include <vtkNamedColors.h>

static vtkSmartPointer<vtkLookupTable> MakeColors (unsigned int n);
static vtkSmartPointer<vtkImageData> MakeBlob(int n, double radius);

int main (int /* argc */, char * /* argv */ [])
{
  int n = 20;
  double radius = 8;

  vtkSmartPointer<vtkImageData> blob = MakeBlob(n, radius);

  vtkSmartPointer<vtkDiscreteMarchingCubes> discrete =
    vtkSmartPointer<vtkDiscreteMarchingCubes>::New();
  discrete->SetInputData(blob);
  discrete->GenerateValues(n, 1, n);

  unsigned int smoothingIterations = 15;
  double passBand = 0.001;
  double featureAngle = 120.0;

  vtkSmartPointer<vtkWindowedSincPolyDataFilter> smoother =
    vtkSmartPointer<vtkWindowedSincPolyDataFilter>::New();
  smoother->SetInputConnection(discrete->GetOutputPort());
  smoother->SetNumberOfIterations(smoothingIterations);
  smoother->BoundarySmoothingOff();
  smoother->FeatureEdgeSmoothingOff();
  smoother->SetFeatureAngle(featureAngle);
  smoother->SetPassBand(passBand);
  smoother->NonManifoldSmoothingOn();
  smoother->NormalizeCoordinatesOn();
  smoother->Update();

  vtkSmartPointer<vtkLookupTable> lut = MakeColors(n);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(smoother->GetOutputPort());
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(0, lut->GetNumberOfColors());

// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  ren1->AddActor(actor);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  ren1->SetBackground(colors->GetColor3d("Burlywood").GetData());

  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}

vtkSmartPointer<vtkImageData> MakeBlob(int n, double radius)
{
  vtkSmartPointer<vtkMath> math =
    vtkSmartPointer<vtkMath>::New();

  vtkSmartPointer<vtkImageData> blobImage =
    vtkSmartPointer<vtkImageData>::New();

  for (int i = 0; i < n; ++i)
  {
    vtkSmartPointer<vtkSphere> sphere =
      vtkSmartPointer<vtkSphere>::New();
    sphere->SetRadius(radius);
    double maxR = 50 - 2.0 * radius;
    sphere->SetCenter(int(math->Random(-maxR, maxR)),
                      int(math->Random(-maxR, maxR)), int(math->Random(-maxR, maxR)));

    vtkSmartPointer<vtkSampleFunction> sampler =
      vtkSmartPointer<vtkSampleFunction>::New();
    sampler->SetImplicitFunction(sphere);
    sampler->SetOutputScalarTypeToFloat();
    sampler->SetSampleDimensions(100, 100, 100);
    sampler->SetModelBounds(-50, 50, -50, 50, -50, 50);

    vtkSmartPointer<vtkImageThreshold> thres =
      vtkSmartPointer<vtkImageThreshold>::New();
    thres->SetInputConnection(sampler->GetOutputPort());
    thres->ThresholdByLower(radius * radius);
    thres->ReplaceInOn();
    thres->ReplaceOutOn();
    thres->SetInValue(i + 1);
    thres->SetOutValue(0);
    thres->Update();
    if (i == 0)
    {
      blobImage->DeepCopy(thres->GetOutput());
    }

    vtkSmartPointer<vtkImageMathematics>     maxValue =
      vtkSmartPointer<vtkImageMathematics>::New();
    maxValue->SetInputData(0, blobImage);
    maxValue->SetInputData(1, thres->GetOutput());
    maxValue->SetOperationToMax();
    maxValue->Modified();
    maxValue->Update();

    blobImage->DeepCopy(maxValue->GetOutput());
  }
  return blobImage;
}

// Generate some random colors
vtkSmartPointer<vtkLookupTable> MakeColors (unsigned int n)
{
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetNumberOfColors(n);
  lut->SetTableRange(0, n - 1);
  lut->SetScaleToLinear();
  lut->Build();
  lut->SetTableValue(0, 0, 0, 0, 1);

  vtkSmartPointer<vtkMath> math =
    vtkSmartPointer<vtkMath>::New();
  math->RandomSeed(5071);
  for ( int i = 1; i < static_cast<int>(n); ++i)
  {
    lut->SetTableValue(i, math->Random(.4, 1),
                       math->Random(.4, 1), math->Random(.4, 1), 1.0);
  }
  return lut;
}
