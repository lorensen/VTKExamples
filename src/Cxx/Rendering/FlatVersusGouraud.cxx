#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <vtkContourFilter.h>
#include <vtkCylinderSource.h>
#include <vtkOBJReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkQuadric.h>
#include <vtkSampleFunction.h>
#include <vtkSphereSource.h>

#include <vtkNamedColors.h>

namespace
{
void CreateSphere(vtkSmartPointer<vtkRenderer>&, bool);
void CreateCylinder(vtkSmartPointer<vtkRenderer>&, bool);
void CreateIsoSurface(vtkSmartPointer<vtkRenderer>&, bool);
void CreateModel(vtkSmartPointer<vtkRenderer>&, bool, char*);
}

int main(int argc, char* argv[])
{

  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename" << std::endl;
    std::cout << "where: filename is the file cow.obj" << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<vtkSmartPointer<vtkRenderer>> renderers;

  // Create the 8 renderers
  vtkSmartPointer<vtkRenderer> flatSphereRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderers.push_back(flatSphereRenderer);
  vtkSmartPointer<vtkRenderer> flatCylinderRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderers.push_back(flatCylinderRenderer);
  vtkSmartPointer<vtkRenderer> flatIsoSurfaceRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderers.push_back(flatIsoSurfaceRenderer);
  vtkSmartPointer<vtkRenderer> flatModelRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderers.push_back(flatModelRenderer);
  vtkSmartPointer<vtkRenderer> smoothSphereRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderers.push_back(smoothSphereRenderer);
  vtkSmartPointer<vtkRenderer> smoothCylinderRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderers.push_back(smoothCylinderRenderer);
  vtkSmartPointer<vtkRenderer> smoothIsoSurfaceRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderers.push_back(smoothIsoSurfaceRenderer);
  vtkSmartPointer<vtkRenderer> smoothModelRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderers.push_back(smoothModelRenderer);

  // Add the actors
  CreateSphere(flatSphereRenderer, true);
  CreateCylinder(flatCylinderRenderer, true);
  CreateIsoSurface(flatIsoSurfaceRenderer, true);
  CreateModel(flatModelRenderer, true, argv[1]);

  CreateSphere(smoothSphereRenderer, false);
  CreateCylinder(smoothCylinderRenderer, false);
  CreateIsoSurface(smoothIsoSurfaceRenderer, false);
  CreateModel(smoothModelRenderer, false, argv[1]);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  // Setup viewports for the renderers
  int rendererSize = 256;
  unsigned int xGridDimensions = 4;
  unsigned int yGridDimensions = 2;
  renderWindow->SetSize(rendererSize * xGridDimensions,
                        rendererSize * yGridDimensions);
  for (int row = 0; row < static_cast<int>(yGridDimensions); row++)
  {
    for (int col = 0; col < static_cast<int>(xGridDimensions); col++)
    {
      int index = row * xGridDimensions + col;
      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {
        static_cast<double>(col) / xGridDimensions,
        static_cast<double>(yGridDimensions - (row + 1)) / yGridDimensions,
        static_cast<double>(col + 1) / xGridDimensions,
        static_cast<double>(yGridDimensions - row) / yGridDimensions};
      renderers[index]->SetViewport(viewport);
    }
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  for (size_t r = 0; r < renderers.size(); ++r)
  {
    renderers[r]->SetBackground(colors->GetColor3d("SlateGray").GetData());
    renderers[r]->GetActiveCamera()->Azimuth(20);
    renderers[r]->GetActiveCamera()->Elevation(30);
    renderers[r]->ResetCamera();
    if (r > 3)
    {
      renderers[r]->SetActiveCamera(renderers[r - 4]->GetActiveCamera());
    }
    renderWindow->AddRenderer(renderers[r]);
  }
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace
{
void CreateSphere(vtkSmartPointer<vtkRenderer>& renderer, bool flat)
{
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  if (flat)
  {
    actor->GetProperty()->SetInterpolationToFlat();
  }
  else
  {
    actor->GetProperty()->SetInterpolationToGouraud();
  }
  renderer->AddActor(actor);
}

void CreateCylinder(vtkSmartPointer<vtkRenderer>& renderer, bool flat)
{
  vtkSmartPointer<vtkCylinderSource> cylinder =
    vtkSmartPointer<vtkCylinderSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cylinder->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  if (flat)
  {
    actor->GetProperty()->SetInterpolationToFlat();
  }
  else
  {
    actor->GetProperty()->SetInterpolationToGouraud();
  }
  renderer->AddActor(actor);
}

void CreateIsoSurface(vtkSmartPointer<vtkRenderer>& renderer, bool flat)
{
  double range[2];
  // Sample quadric function
  vtkSmartPointer<vtkQuadric> quadric = vtkSmartPointer<vtkQuadric>::New();
  quadric->SetCoefficients(1, 2, 3, 0, 1, 0, 0, 0, 0, 0);

  vtkSmartPointer<vtkSampleFunction> sample =
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(25, 25, 25);
  sample->SetImplicitFunction(quadric);

  // Generate implicit surface
  vtkSmartPointer<vtkContourFilter> contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetInputConnection(sample->GetOutputPort());
  range[0] = 1.0;
  range[1] = 6.0;
  contour->GenerateValues(5, range);

  // Map contour
  vtkSmartPointer<vtkPolyDataMapper> contourMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contour->GetOutputPort());
  contourMapper->SetScalarRange(0, 7);

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(contourMapper);
  if (flat)
  {
    actor->GetProperty()->SetInterpolationToFlat();
  }
  else
  {
    actor->GetProperty()->SetInterpolationToGouraud();
  }
  renderer->AddActor(actor);
  return;
}

void CreateModel(vtkSmartPointer<vtkRenderer>& renderer, bool flat,
                 char* fileName)
{
  vtkSmartPointer<vtkOBJReader> reader = vtkSmartPointer<vtkOBJReader>::New();
  reader->SetFileName(fileName);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  if (flat)
  {
    actor->GetProperty()->SetInterpolationToFlat();
  }
  else
  {
    actor->GetProperty()->SetInterpolationToGouraud();
  }
  renderer->AddActor(actor);
}
}
