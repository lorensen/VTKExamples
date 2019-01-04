#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkGaussianSplatter.h>
#include <vtkSphereSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> input =
    vtkSmartPointer<vtkPolyData>::New();

  if(argc == 1) // Generate the data
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(.01);
    sphereSource->Update();
    input->ShallowCopy(sphereSource->GetOutput());
  }
  else // Read the data from a file
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    input->ShallowCopy(reader->GetOutput());

  }

  vtkSmartPointer<vtkGaussianSplatter> splatter =
    vtkSmartPointer<vtkGaussianSplatter>::New();
  splatter->SetInputData(input);

  unsigned int n = 200;
  splatter->SetSampleDimensions(n,n,n);
  splatter->SetRadius(.02);
  splatter->SetExponentFactor(-10);
  splatter->SetEccentricity(2);
  splatter->Update();

  vtkSmartPointer<vtkContourFilter> isoSurface =
    vtkSmartPointer<vtkContourFilter>::New();
  isoSurface->SetInputConnection(splatter->GetOutputPort());
  isoSurface->SetValue(0, .95 * splatter->GetRadius());

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(isoSurface->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(1.0, 0.3882, 0.2784);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.2, .3, .4);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
