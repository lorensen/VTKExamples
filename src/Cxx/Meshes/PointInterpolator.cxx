#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDelimitedTextReader.h>
#include <vtkGaussianKernel.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPointGaussianMapper.h>
#include <vtkPointInterpolator.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkTableToPolyData.h>

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0]
              << " sparsePoints.txt InterpolatingOnSTL_final.stl" << std::endl;
    return EXIT_FAILURE;
  }
  std::string pointsFile = argv[1];
  std::string probeSurfaceFile = argv[2];

  // Read a points data
  auto pointsReader = vtkSmartPointer<vtkDelimitedTextReader>::New();
  pointsReader->SetFileName(pointsFile.c_str());
  pointsReader->DetectNumericColumnsOn();
  pointsReader->SetFieldDelimiterCharacters("\t");
  pointsReader->SetHaveHeaders(true);

  auto tablePoints = vtkSmartPointer<vtkTableToPolyData>::New();
  tablePoints->SetInputConnection(pointsReader->GetOutputPort());
  tablePoints->SetXColumn("x");
  tablePoints->SetYColumn("y");
  tablePoints->SetZColumn("z");
  tablePoints->Update();

  vtkPolyData* points = tablePoints->GetOutput();
  points->GetPointData()->SetActiveScalars("val");
  double* range = points->GetPointData()->GetScalars()->GetRange();

  // Read a probe surface
  auto stlReader = vtkSmartPointer<vtkSTLReader>::New();
  stlReader->SetFileName(probeSurfaceFile.c_str());
  stlReader->Update();

  vtkPolyData* surface = stlReader->GetOutput();
  // double* bounds = surface->GetBounds();

  // Gaussian kernel
  auto gaussianKernel = vtkSmartPointer<vtkGaussianKernel>::New();
  gaussianKernel->SetSharpness(2.0);
  gaussianKernel->SetRadius(12.0);

  auto interpolator = vtkSmartPointer<vtkPointInterpolator>::New();
  interpolator->SetInputData(surface);
  interpolator->SetSourceData(points);
  interpolator->SetKernel(gaussianKernel);

  // Visualize
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(interpolator->GetOutputPort());
  mapper->SetScalarRange(range);

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto pointsMapper = vtkSmartPointer<vtkPointGaussianMapper>::New();
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
      "};\n");

  auto pointsActor = vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);
  renderWindow->SetWindowName("PointInterpolator");

  auto iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
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
