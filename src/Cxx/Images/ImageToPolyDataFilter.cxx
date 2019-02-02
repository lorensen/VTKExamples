#include <vtkActor.h>
#include <vtkLookupTable.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkImageToPolyDataFilter.h>
#include <vtkImageQuantizeRGBToIndex.h>
#include <vtkCamera.h>
#include <vtkPNGReader.h>
#include <vtkTriangleFilter.h>

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    std::cerr << "Required arguments: filename.png" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkPNGReader> reader =
    vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageQuantizeRGBToIndex> quant =
    vtkSmartPointer<vtkImageQuantizeRGBToIndex>::New();
  quant->SetInputConnection(reader->GetOutputPort());
  quant->SetNumberOfColors(16);

  vtkSmartPointer<vtkImageToPolyDataFilter> i2pd =
    vtkSmartPointer<vtkImageToPolyDataFilter>::New();
  i2pd->SetInputConnection(quant->GetOutputPort());
  i2pd->SetLookupTable(quant->GetLookupTable());
  i2pd->SetColorModeToLUT();
  i2pd->SetOutputStyleToPolygonalize();
  i2pd->SetError(0);
  i2pd->DecimationOn();
  i2pd->SetDecimationError(0.0);
  i2pd->SetSubImageSize(25);

  // Need a triangle filter because the polygons are complex and concave
  vtkSmartPointer<vtkTriangleFilter> tf =
    vtkSmartPointer<vtkTriangleFilter>::New();
  tf->SetInputConnection(i2pd->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(tf->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);

  renderer->SetBackground(1, 1, 1);
  renderWindow->SetSize(300, 250);

  renderWindow->Render();
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
