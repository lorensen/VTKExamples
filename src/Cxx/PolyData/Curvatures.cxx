#include <vtkSmartPointer.h>

#include <vtkCurvatures.h>

#include <vtkXMLPolyDataReader.h>

#include <vtkLookupTable.h>
#include <vtkColorTransferFunction.h>
#include <vtkColorSeries.h>

#include <vtkPointData.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkScalarBarActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " Filename(.vtp)" << std::endl;
    return EXIT_FAILURE;
  }

  // Create a polydata
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkCurvatures> curvaturesFilter =
    vtkSmartPointer<vtkCurvatures>::New();
  curvaturesFilter->SetInputConnection(reader->GetOutputPort());
  curvaturesFilter->SetCurvatureTypeToMinimum();
  curvaturesFilter->SetCurvatureTypeToMaximum();
  curvaturesFilter->SetCurvatureTypeToGaussian();
  curvaturesFilter->SetCurvatureTypeToMean();
  curvaturesFilter->Update();

  // Get scalar range from command line if present, otherwise use
  // range of computed curvature
  double scalarRange[2];
  if (argc >= 4)
  {
    scalarRange[0] = atof(argv[2]);
    scalarRange[1] = atof(argv[3]);
  }
  else
  {
    curvaturesFilter->GetOutput()->GetScalarRange(scalarRange);
  }

  int scheme = 16;
  if (argc >= 5)
  {
    scheme = atoi(argv[4]);
  }

  // Build a lookup table
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetColorScheme(scheme);
  std::cout << "Using color scheme #: "
            << colorSeries->GetColorScheme() << " is "
            << colorSeries->GetColorSchemeName() << std::endl;

  vtkSmartPointer<vtkColorTransferFunction> lut =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  lut->SetColorSpaceToHSV();

  // Use a color series to create a transfer function
  int numColors = colorSeries->GetNumberOfColors();
  for (int i = 0; i < numColors; i++)
  {
      vtkColor3ub color = colorSeries->GetColor(i);
    double dColor[3];
    dColor[0] = static_cast<double> (color[0]) / 255.0;
    dColor[1] = static_cast<double> (color[1]) / 255.0;
    dColor[2] = static_cast<double> (color[2]) / 255.0;
    double t = scalarRange[0] + (scalarRange[1] - scalarRange[0])
      / (numColors - 1) * i;
    lut->AddRGBPoint(t, dColor[0], dColor[1], dColor[2]);
  }

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(curvaturesFilter->GetOutputPort());
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(scalarRange);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a scalar bar
  vtkSmartPointer<vtkScalarBarActor> scalarBar =
    vtkSmartPointer<vtkScalarBarActor>::New();
  scalarBar->SetLookupTable(mapper->GetLookupTable());
  scalarBar->SetTitle(
    curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetName());
  scalarBar->SetNumberOfLabels(5);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->AddActor2D(scalarBar);

  renderer->SetBackground(.1, .2, .3); // Background color blue

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
