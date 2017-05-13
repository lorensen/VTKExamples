#include <vtkVersion.h>
#include <vtkPolyData.h>
#if VTK_MAJOR_VERSION <= 5
#include <vtkPLOT3DReader.h>
#else
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#endif
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredGridGeometryFilter.h>

int main ( int argc, char *argv[] )
{
  if(argc < 3)
  {
    std::cout << "Required parameters: XYZFilename.bin QFileName.bin" << std::endl;
    return EXIT_FAILURE;
  }

  std::string xyzFilename = argv[1];
  std::string qFilename = argv[2];

#if VTK_MAJOR_VERSION <= 5
  vtkSmartPointer<vtkPLOT3DReader> reader =
    vtkSmartPointer<vtkPLOT3DReader>::New();
#else
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> reader =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
#endif
  reader->SetXYZFileName(xyzFilename.c_str());
  reader->SetQFileName(qFilename.c_str());
  reader->SetScalarFunctionNumber(100);
  reader->SetVectorFunctionNumber(202);
  reader->Update();

  vtkSmartPointer<vtkStructuredGridGeometryFilter> geometryFilter =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  geometryFilter->SetInputConnection(reader->GetOutputPort());
#else
  geometryFilter->SetInputData(reader->GetOutput()->GetBlock(0));
#endif
  geometryFilter->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(geometryFilter->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
