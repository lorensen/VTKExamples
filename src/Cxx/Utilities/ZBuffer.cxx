// This demo creates depth map for a polydata instance by extracting
// exact ZBuffer values.
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkBMPWriter.h>
#include <vtkImageShiftScale.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVersion.h>
#include <vtkWindowToImageFilter.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " input(.vtp) output(.bmp)"
              << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkXMLPolyDataReader> fileReader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  vtkSmartPointer<vtkWindowToImageFilter> filter =
      vtkSmartPointer<vtkWindowToImageFilter>::New();
  vtkSmartPointer<vtkBMPWriter> imageWriter =
      vtkSmartPointer<vtkBMPWriter>::New();
  vtkSmartPointer<vtkImageShiftScale> scale =
      vtkSmartPointer<vtkImageShiftScale>::New();

  // Read .vtp file
  fileReader->SetFileName(argv[1]);

  // Build visualization enviroment
  mapper->SetInputConnection(fileReader->GetOutputPort());
  actor->SetMapper(mapper);
  renderer->AddActor(actor);
  renWin->AddRenderer(renderer);
  interactor->SetRenderWindow(renWin);
  renWin->Render();

  // Create Depth Map
  filter->SetInput(renWin);
#if VTK_MAJOR_VERSION >= 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  filter->SetScale(1);
#else
  filter->SetMagnification(1);
#endif
  filter->SetInputBufferTypeToZBuffer(); // Extract z buffer value

  scale->SetOutputScalarTypeToUnsignedChar();
  scale->SetInputConnection(filter->GetOutputPort());
  scale->SetShift(0);
  scale->SetScale(-255);

  // Write depth map as a .bmp image
  imageWriter->SetFileName(argv[2]);
  imageWriter->SetInputConnection(scale->GetOutputPort());
  imageWriter->Write();

  return EXIT_SUCCESS;
}
