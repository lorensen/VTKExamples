#include <vtkBoundedPointSource.h>
#include <vtkCamera.h>
#include <vtkCone.h>
#include <vtkCylinder.h>
#include <vtkExtractPoints.h>
#include <vtkGlyph3DMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphere.h>
#include <vtkSphereSource.h>
#include <vtkSuperquadric.h>

#include <vector>

int main(int /*argc*/, char* /* argv */[])
{
  // Create implicit functions
  auto cone = vtkSmartPointer<vtkCone>::New();
  cone->SetAngle(30.0);
  auto sphere = vtkSmartPointer<vtkSphere>::New();
  auto cylinder = vtkSmartPointer<vtkCylinder>::New();
  auto superquadric = vtkSmartPointer<vtkSuperquadric>::New();
  superquadric->SetPhiRoundness(2.5);
  superquadric->SetThetaRoundness(.5);

  // Store the functions
  std::vector<vtkSmartPointer<vtkImplicitFunction>> functions;
  functions.push_back(sphere);
  functions.push_back(cone);
  functions.push_back(cylinder);
  functions.push_back(superquadric);

  auto pointSource = vtkSmartPointer<vtkBoundedPointSource>::New();
  pointSource->SetNumberOfPoints(100000);

  // Rows and columns
  unsigned int gridXDimensions = 2;
  unsigned int gridYDimensions = 2;

  // Need a renderer even if there is no actor
  std::vector<vtkSmartPointer<vtkRenderer>> renderers;
  double background[6] = {.4, .5, .6, .6, .5, .4};
  for (size_t i = 0; i < gridXDimensions * gridYDimensions; i++)
  {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    renderers[i]->SetBackground(background);
    auto fwdIt = std::rotate(background, background + 1, background + 6);
  }

  // Glyphs
  double radius = .02;
  auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(radius);

  // One render window
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  int rendererSize = 256;
  renderWindow->SetSize(rendererSize * gridXDimensions,
                        rendererSize * gridYDimensions);

  // Create a pipeline for each function
  for (int row = 0; row < static_cast<int>(gridYDimensions); row++)
  {
    for (int col = 0; col < static_cast<int>(gridXDimensions); col++)
    {
      int index = row * gridXDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {static_cast<double>(col) * rendererSize /
                                (gridXDimensions * rendererSize),
                            static_cast<double>(gridYDimensions - (row + 1)) *
                                rendererSize / (gridYDimensions * rendererSize),
                            static_cast<double>(col + 1) * rendererSize /
                                (gridXDimensions * rendererSize),
                            static_cast<double>(gridYDimensions - row) *
                                rendererSize /
                                (gridYDimensions * rendererSize)};
      renderWindow->AddRenderer(renderers[index]);
      renderers[index]->SetViewport(viewport);
      if (index > static_cast<int>(functions.size() - 1))
      {
        continue;
      }
      // Define the pipeline
      auto extract = vtkSmartPointer<vtkExtractPoints>::New();
      extract->SetInputConnection(pointSource->GetOutputPort());
      extract->SetImplicitFunction(functions[index]);

      auto glyph = vtkSmartPointer<vtkGlyph3DMapper>::New();
      glyph->SetInputConnection(extract->GetOutputPort());
      glyph->SetSourceConnection(sphereSource->GetOutputPort());
      glyph->ScalingOff();

      auto glyphActor = vtkSmartPointer<vtkActor>::New();
      glyphActor->SetMapper(glyph);

      renderers[index]->AddActor(glyphActor);
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(-30);
      renderers[index]->GetActiveCamera()->Dolly(1.1);
      renderers[index]->ResetCameraClippingRange();
    }
  }
  auto iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renderWindow);

  renderWindow->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
