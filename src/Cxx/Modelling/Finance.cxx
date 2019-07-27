#include <vtkActor.h>
#include <vtkAxes.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkDataSet.h>
#include <vtkFloatArray.h>
#include <vtkGaussianSplatter.h>
#include <vtkImageData.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTubeFilter.h>
#include <vtkUnstructuredGrid.h>

#include <algorithm>
#include <array>
#include <string>

namespace {
vtkSmartPointer<vtkDataSet> ReadFinancialData(const char* fname, const char* x,
                                              const char* y, const char* z,
                                              const char* s);
int ParseFile(FILE* file, const char* tag, float* data);
} // namespace

int main(int argc, char* argv[])
{
  double bounds[6];

  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " financial_file" << endl;
    return EXIT_FAILURE;
  }
  char* fname = argv[1];

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  // Set the color for the population.
  std::array<unsigned char, 4> popColor{{230, 230, 230, 255}};
  colors->SetColor("PopColor", popColor.data());

  // read data
  auto dataSet = ReadFinancialData(fname, "MONTHLY_PAYMENT", "INTEREST_RATE",
                                   "LOAN_AMOUNT", "TIME_LATE");
  // construct pipeline for original population
  auto popSplatter = vtkSmartPointer<vtkGaussianSplatter>::New();
  popSplatter->SetInputData(dataSet);
  popSplatter->SetSampleDimensions(100, 100, 100);
  popSplatter->SetRadius(0.05);
  popSplatter->ScalarWarpingOff();

  auto popSurface = vtkSmartPointer<vtkContourFilter>::New();
  popSurface->SetInputConnection(popSplatter->GetOutputPort());
  popSurface->SetValue(0, 0.01);

  auto popMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  popMapper->SetInputConnection(popSurface->GetOutputPort());
  popMapper->ScalarVisibilityOff();

  auto popActor = vtkSmartPointer<vtkActor>::New();
  popActor->SetMapper(popMapper);
  popActor->GetProperty()->SetOpacity(0.3);
  popActor->GetProperty()->SetColor(colors->GetColor3d("popColor").GetData());

  // construct pipeline for delinquent population
  auto lateSplatter = vtkSmartPointer<vtkGaussianSplatter>::New();
  lateSplatter->SetInputData(dataSet);
  lateSplatter->SetSampleDimensions(50, 50, 50);
  lateSplatter->SetRadius(0.05);
  lateSplatter->SetScaleFactor(0.005);

  auto lateSurface = vtkSmartPointer<vtkContourFilter>::New();
  lateSurface->SetInputConnection(lateSplatter->GetOutputPort());
  lateSurface->SetValue(0, 0.01);

  auto lateMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  lateMapper->SetInputConnection(lateSurface->GetOutputPort());
  lateMapper->ScalarVisibilityOff();

  auto lateActor = vtkSmartPointer<vtkActor>::New();
  lateActor->SetMapper(lateMapper);
  lateActor->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());

  // create axes
  popSplatter->Update();
  popSplatter->GetOutput()->GetBounds(bounds);

  auto axes = vtkSmartPointer<vtkAxes>::New();
  axes->SetOrigin(bounds[0], bounds[2], bounds[4]);
  axes->SetScaleFactor(popSplatter->GetOutput()->GetLength() / 5);

  auto axesTubes = vtkSmartPointer<vtkTubeFilter>::New();
  axesTubes->SetInputConnection(axes->GetOutputPort());
  axesTubes->SetRadius(axes->GetScaleFactor() / 25.0);
  axesTubes->SetNumberOfSides(6);

  auto axesMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  axesMapper->SetInputConnection(axesTubes->GetOutputPort());

  auto axesActor = vtkSmartPointer<vtkActor>::New();
  axesActor->SetMapper(axesMapper);

  // graphics stuff
  auto renderer = vtkSmartPointer<vtkRenderer>::New();

  auto renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renWin);

  // set up renderer
  renderer->AddActor(lateActor);
  renderer->AddActor(axesActor);
  renderer->AddActor(popActor);
  renderer->SetBackground(colors->GetColor3d("Wheat").GetData());
  renWin->SetSize(640, 480);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Dolly(1.3);
  renderer->ResetCameraClippingRange();

  // interact with data
  renWin->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace {
vtkSmartPointer<vtkDataSet> ReadFinancialData(const char* filename,
                                              const char* x, const char* y,
                                              const char* z, const char* s)
{
  float xyz[3];
  FILE* file;
  int i, npts;
  char tag[80];

  if ((file = fopen(filename, "r")) == 0)
  {
    std::cerr << "ERROR: Can't open file: " << filename << std::endl;
    return NULL;
  }

  int n = fscanf(file, "%79s %d", tag, &npts); // read number of points
  if (n != 2)
  {
    std::cerr << "ERROR: Can't read file: " << filename << std::endl;
    fclose(file);
    return NULL;
  }
  // Check for a reasonable npts
  if (npts <= 0)
  {
    std::cerr << "ERROR: Number of points must be greater that 0" << std::endl;
    fclose(file);
    return NULL;
  }
  // We arbitrarily pick a large upper limit on npts
  if (npts > VTK_INT_MAX / 10)
  {
    std::cerr << "ERROR: npts (" << npts << ") is unreasonably large"
              << std::endl;
    fclose(file);
    return NULL;
  }
  auto dataSet = vtkSmartPointer<vtkUnstructuredGrid>::New();
  float* xV = new float[npts];
  float* yV = new float[npts];
  float* zV = new float[npts];
  float* sV = new float[npts];

  if (!ParseFile(file, x, xV) || !ParseFile(file, y, yV) ||
      !ParseFile(file, z, zV) || !ParseFile(file, s, sV))
  {
    std::cerr << "ERROR: Couldn't read data!" << std::endl;
    delete[] xV;
    delete[] yV;
    delete[] zV;
    delete[] sV;
    fclose(file);
    return NULL;
  }

  auto newPts = vtkSmartPointer<vtkPoints>::New();
  auto newScalars = vtkSmartPointer<vtkFloatArray>::New();

  for (i = 0; i < npts; i++)
  {
    xyz[0] = xV[i];
    xyz[1] = yV[i];
    xyz[2] = zV[i];
    //     std::cout << xV[i] << " " << yV[i] << " " << zV[i] << std::endl;
    newPts->InsertPoint(i, xyz);
    newScalars->InsertValue(i, sV[i]);
  }

  dataSet->SetPoints(newPts);
  dataSet->GetPointData()->SetScalars(newScalars);

  // cleanup
  delete[] xV;
  delete[] yV;
  delete[] zV;
  delete[] sV;
  fclose(file);

  return dataSet;
}

int ParseFile(FILE* file, const char* label, float* data)
{
  char tag[80];
  int i, npts, readData = 0;
  float min = VTK_FLOAT_MAX;
  float max = (-VTK_FLOAT_MAX);

  if (file == NULL || label == NULL)
    return 0;

  rewind(file);

  if (fscanf(file, "%79s %d", tag, &npts) != 2)
  {
    std::cerr << "ERROR: IO Error " << __FILE__ << ":" << __LINE__ << std::endl;
    return 0;
  }
  while (!readData && fscanf(file, "%79s", tag) == 1)
  {
    if (!strcmp(tag, label))
    {
      readData = 1;
      for (i = 0; i < npts; i++)
      {
        if (fscanf(file, "%f", data + i) != 1)
        {
          std::cerr << "ERROR: IO Error " << __FILE__ << ":" << __LINE__
                    << std::endl;
          return 0;
        }
        if (data[i] < min)
          min = data[i];
        if (data[i] > min)
          max = data[i]; // bug here
        // Should be:
        // if ( data[i] > max ) max = data[i];
      }
      // normalize data
      for (i = 0; i < npts; i++) data[i] = min + data[i] / (max - min);
    }
    else
    {
      for (i = 0; i < npts; i++)
      {
        if (fscanf(file, "%*f") != 0)
        {
          std::cerr << "ERROR: IO Error " << __FILE__ << ":" << __LINE__
                    << std::endl;
          return 0;
        }
      }
    }
  }

  if (!readData)
    return 0;
  else
    return 1;
}
} // namespace
