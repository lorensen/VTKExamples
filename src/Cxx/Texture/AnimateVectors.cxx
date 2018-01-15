#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkGlyph3D.h>
#include <vtkLineSource.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkTexture.h>
#include <vtkThresholdPoints.h>

#include <vector>

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " carotid.vtk vecAnim1.vtk ..." << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);


// read data
//
// create pipeline
//
  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkThresholdPoints> threshold =
    vtkSmartPointer<vtkThresholdPoints>::New();
  threshold->SetInputConnection(reader->GetOutputPort());
  threshold->ThresholdByUpper(200);

  vtkSmartPointer<vtkLineSource> line =
    vtkSmartPointer<vtkLineSource>::New();
  line->SetResolution(1);
  
  vtkSmartPointer<vtkGlyph3D> lines =
    vtkSmartPointer<vtkGlyph3D>::New();
  lines->SetInputConnection(threshold->GetOutputPort());
  lines->SetSourceConnection(line->GetOutputPort());
  lines->SetScaleFactor(0.005);
  lines->SetScaleModeToScaleByScalar();
  lines->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> vectorMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vectorMapper->SetInputConnection(lines->GetOutputPort());
  vectorMapper->SetScalarRange(lines->GetOutput()->GetScalarRange());
  
  vtkSmartPointer<vtkActor> vectorActor =
    vtkSmartPointer<vtkActor>::New();
  vectorActor->SetMapper(vectorMapper);
  vectorActor->GetProperty()->SetOpacity(0.99);
  vectorActor->GetProperty()->SetLineWidth(1.5);

// outline
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

//  texture maps
  std::vector<vtkSmartPointer<vtkTexture> > textureMaps;
  for (int i =  2; i < argc; ++i)
  {
    vtkSmartPointer<vtkStructuredPointsReader> tmap =
      vtkSmartPointer<vtkStructuredPointsReader>::New();
    tmap->SetFileName(argv[i]);

    vtkSmartPointer<vtkTexture> texture =
      vtkSmartPointer<vtkTexture>::New();
    texture->SetInputConnection(tmap->GetOutputPort());
    texture->InterpolateOff();
    texture->RepeatOff();
    textureMaps.push_back(texture);
  }
  vectorActor->SetTexture(textureMaps[0]);

// Add the actors to the renderer, set the background and size
//
  renderer->AddActor(vectorActor);
  renderer->AddActor(outlineActor);

  vtkSmartPointer<vtkCamera> cam1 =
    vtkSmartPointer<vtkCamera>::New();
  cam1->SetClippingRange(17.4043, 870.216);
  cam1->SetFocalPoint(136.71, 104.025, 23);
  cam1->SetPosition(204.747, 258.939, 63.7925);
  cam1->SetViewUp(-0.102647, -0.210897, 0.972104);
  cam1->Zoom(1.5);
  renderer->SetActiveCamera(cam1);

  renderer->SetBackground(colors->GetColor3d("Wheat").GetData());
  renderWindow->SetSize(640, 480);

// go into loop
  for (int j = 0; j < 100; ++j)
  {
    for (size_t i = 0; i < textureMaps.size(); ++i)
    {
      vectorActor->SetTexture(textureMaps[i]);
      renderWindow->Render();
    }
  }
  interactor->Start();
  return EXIT_SUCCESS;
}
