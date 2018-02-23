#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkHull.h>
#include <vtkNamedColors.h>
#include <vtkPlanes.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

#include <string>
#include <vector>

int main(int, char* [])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // These are the two methods we will use.
  std::vector<std::string> titles{"Using frustum planes", "Using bounds"};
  std::vector<vtkSmartPointer<vtkPlanes>> planes;
  for (auto i = 0; i < titles.size(); ++i)
  {
    planes.push_back(vtkSmartPointer<vtkPlanes>::New());
  }

  // Using frustum planes.
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  double planesArray[24];
  camera->GetFrustumPlanes(1, planesArray);
  planes[0]->SetFrustumPlanes(planesArray);

  // Using bounds.
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  double bounds[6];
  sphereSource->GetOutput()->GetBounds(bounds);
  planes[1]->SetBounds(bounds);

  // At this point we have the planes created by both of the methods above.
  // You can do whatever you want with them.

  // For visualisation we will produce an n-sided convex hull
  // and visualise it.

  // Create a common text property.
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(16);
  textProperty->SetJustificationToCentered();

  // Create the render window and interactor.
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetWindowName("Planes");
  vtkSmartPointer<vtkRenderWindowInteractor> iRen =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iRen->SetRenderWindow(renWin);

  std::vector<vtkSmartPointer<vtkHull>> hulls;
  std::vector<vtkSmartPointer<vtkPolyData>> pds;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  std::vector<vtkSmartPointer<vtkActor>> actors;
  std::vector<vtkSmartPointer<vtkTextMapper>> textMappers;
  std::vector<vtkSmartPointer<vtkActor2D>> textActors;
  std::vector<vtkSmartPointer<vtkRenderer>> renderers;

  for (auto i = 0; i < titles.size(); ++i)
  {
    hulls.push_back(vtkSmartPointer<vtkHull>::New());
    hulls[i]->SetPlanes(planes[i]);

    pds.push_back(vtkSmartPointer<vtkPolyData>::New());

    // To generate the convex hull we supply a vtkPolyData object and a bounding
    // box.
    // We define the bounding box to be where we expect the resulting polyhedron
    // to lie.
    // Make it a generous fit as it is only used to create the initial
    // polygons that are eventually clipped.
    hulls[i]->GenerateHull(pds[i], -200, 200, -200, 200, -200, 200);

    mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
    mappers[i]->SetInputData(pds[i]);

    actors.push_back(vtkSmartPointer<vtkActor>::New());
    actors[i]->SetMapper(mappers[i]);
    actors[i]->GetProperty()->SetColor(
      colors->GetColor3d("Moccasin").GetData());
    actors[i]->GetProperty()->SetSpecular(0.8);
    actors[i]->GetProperty()->SetSpecularPower(30);

    textMappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textMappers[i]->SetInput(titles[i].c_str());
    textMappers[i]->SetTextProperty(textProperty);

    textActors.push_back(vtkSmartPointer<vtkActor2D>::New());
    textActors[i]->SetMapper(textMappers[i]);
    textActors[i]->SetPosition(120, 16);

    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    renderers[i]->AddActor(actors[i]);
    renderers[i]->AddViewProp(textActors[i]);

    renWin->AddRenderer(renderers[i]);
  }

  // Setup the viewports
  auto xGridDimensions = 2;
  auto yGridDimensions = 1;
  auto rendererSize = 300;
  renWin->SetSize(rendererSize * xGridDimensions,
                  rendererSize * yGridDimensions);
  for (auto row = 0; row < yGridDimensions; ++row)
  {
    for (auto col = 0; col < xGridDimensions; ++col)
    {
      auto index = row * xGridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {
        static_cast<double>(col) / xGridDimensions,
        static_cast<double>(yGridDimensions - (row + 1)) / yGridDimensions,
        static_cast<double>(col + 1) / xGridDimensions,
        static_cast<double>(yGridDimensions - row) / yGridDimensions};
      if (index > (actors.size() - 1))
      {
        // Add a renderer even if there is no actor.
        // This makes the render window background all the same color.
        vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
        ren->SetBackground(colors->GetColor3d("DarkSlateGray").GetData());
        ren->SetViewport(viewport);
        renWin->AddRenderer(ren);
        continue;
      }

      renderers[index]->SetViewport(viewport);
      renderers[index]->SetBackground(
        colors->GetColor3d("DarkSlateGray").GetData());
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(-30);
      renderers[index]->ResetCameraClippingRange();
    }
  }

  iRen->Initialize();
  renWin->Render();
  iRen->Start();

  return EXIT_SUCCESS;
}
