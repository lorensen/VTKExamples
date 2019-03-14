#include <vtkSmartPointer.h>

#include <vtkDelimitedTextReader.h>
#include <vtkGaussianKernel.h>
#include <vtkPointData.h>
#include <vtkPointInterpolator.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkTableToPolyData.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkPointGaussianMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>


int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " points.txt probeSurface.stl" << std::endl;
    return EXIT_FAILURE;
  }
  std::string pointsFile = argv[1];
  std::string probeSurfaceFile = argv[2];

  // Read a points data
  vtkSmartPointer<vtkDelimitedTextReader> pointsReader =
    vtkSmartPointer<vtkDelimitedTextReader>::New();
  pointsReader->SetFileName(pointsFile.c_str());
  pointsReader->DetectNumericColumnsOn();
  pointsReader->SetFieldDelimiterCharacters("\t");
  pointsReader->SetHaveHeaders(true);

  vtkSmartPointer<vtkTableToPolyData> tablePoints =
    vtkSmartPointer<vtkTableToPolyData>::New();
  tablePoints->SetInputConnection(pointsReader->GetOutputPort());
  tablePoints->SetXColumn("x");
  tablePoints->SetYColumn("y");
  tablePoints->SetZColumn("z");
  tablePoints->Update();

  vtkPolyData *points = tablePoints->GetOutput();
  points->GetPointData()->SetActiveScalars("val");
  double* range = points->GetPointData()->GetScalars()->GetRange();

  // Read a probe surface
  vtkSmartPointer<vtkSTLReader> stlReader =
    vtkSmartPointer<vtkSTLReader>::New();
  stlReader->SetFileName(probeSurfaceFile.c_str());
  stlReader->Update();

  vtkPolyData *surface = stlReader->GetOutput();
  double* bounds = surface->GetBounds();

  // Gaussian kernel
  vtkSmartPointer<vtkGaussianKernel> gaussianKernel =
    vtkSmartPointer<vtkGaussianKernel>::New();
  gaussianKernel->SetSharpness(2.0);
  gaussianKernel->SetRadius(12.0);

  vtkSmartPointer<vtkPointInterpolator> interpolator =
    vtkSmartPointer<vtkPointInterpolator>::New();
  interpolator->SetInputData(surface);
  interpolator->SetSourceData(points);
  interpolator->SetKernel(gaussianKernel);

  // Visualize
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(interpolator->GetOutputPort());
  mapper->SetScalarRange(range);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkPointGaussianMapper> pointsMapper =
    vtkSmartPointer<vtkPointGaussianMapper>::New();
  pointsMapper->SetInputData(points);
  pointsMapper->SetScalarRange(range);
  pointsMapper->SetScaleFactor(0.6);
  pointsMapper->EmissiveOff();
  pointsMapper->SetSplatShaderCode(
    "//VTK::Color::Impl\n"
    "float dist = dot(offsetVCVSOutput.xy,offsetVCVSOutput.xy);\n"
    "if (dist > 1.0) {\n"
    "  discard;\n"
    "} else {\n"
    "  float scale = (1.0 - dist);\n"
    "  ambientColor *= scale;\n"
    "  diffuseColor *= scale;\n"
    "};\n"
  );

  vtkSmartPointer<vtkActor> pointsActor =
    vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->AddActor(pointsActor);

  renderWindow->Render();
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Elevation(-45);

  renderWindow->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
