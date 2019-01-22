#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkExtractVOI.h>
#include <vtkFlyingEdges2D.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <array>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Generate 2D contour lines, corresponding to tissue density, "
                 "on one CT slice through the head."
              << std::endl;
    std::cout << "The contour lines are colored by the tissue density."
              << std::endl;
    std::cout << "Usage: " << argv[0] << " FullHead.mhd [useContourFilter]"
              << std::endl;
    std::cout << "where: filename is FullHead.mhd," << std::endl;
    std::cout << "       useContourFilter = 0|1" << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "Contouring, using vtkFlyingEdges2D: FullHead.mhd"
              << std::endl;
    std::cout << "Frog, using vtkContourFilter: FullHead.mhd, 1" << std::endl;
    return EXIT_FAILURE;
  }
  auto useContourFilter = false;
  if (argc > 2)
  {
    if (atoi(argv[2]) != 0)
    {
      useContourFilter = true;
    }
  }

  if (useContourFilter)
  {
    std::cout << "Using vtkContourFilter." << std::endl;
  }
  else
  {
    std::cout << "Using vtkFlyingEdges2D." << std::endl;
  }

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  // 8.1.0+
  vtkNew<vtkNamedColors> colors;
#else
  vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
#endif

  // Create the RenderWindow, Renderer and both Actors.
#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkRenderer> ren1;
  vtkNew<vtkRenderWindow> renWin;
  vtkNew<vtkRenderWindowInteractor> iren;
#else
  vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
#endif
  renWin->AddRenderer(ren1);
  iren->SetRenderWindow(renWin);

  // Create the pipeline.
#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkMetaImageReader> reader;
#else
  vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
#endif
  reader->SetFileName(argv[1]);
  reader->Update();

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkExtractVOI> extractVOI;
#else
  vtkSmartPointer<vtkExtractVOI> extractVOI = vtkSmartPointer<vtkExtractVOI>::New();
#endif
  extractVOI->SetInputConnection(reader->GetOutputPort());
  extractVOI->SetVOI(0, 255, 0, 255, 45, 45);
  extractVOI->Update();
  // double* scalarRange = extractVOI->GetOutput()->GetScalarRange();
  std::array<double, 2> scalarRange = {{500, 1150}};
  // std::cout << scalarRange[0] << ", " << scalarRange[1] << std::endl;

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkContourFilter> contour;
  vtkNew<vtkFlyingEdges2D> flyingEdges;
  vtkNew<vtkPolyDataMapper> isoMapper;
#else
  vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
  vtkSmartPointer<vtkFlyingEdges2D> flyingEdges = vtkSmartPointer<vtkFlyingEdges2D>::New();
  vtkSmartPointer<vtkPolyDataMapper> isoMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#endif

  if (useContourFilter)
  {
    contour->SetInputConnection(extractVOI->GetOutputPort());
    contour->GenerateValues(12, scalarRange.data());
    isoMapper->SetInputConnection(contour->GetOutputPort());
  }
  else
  {
    flyingEdges->SetInputConnection(extractVOI->GetOutputPort());
    flyingEdges->GenerateValues(12, scalarRange.data());
    isoMapper->SetInputConnection(flyingEdges->GetOutputPort());
  }
  isoMapper->ScalarVisibilityOn();
  isoMapper->SetScalarRange(scalarRange.data());

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkActor> isoActor;
#else
  vtkSmartPointer<vtkActor> isoActor = vtkSmartPointer<vtkActor>::New();
#endif
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetColor(colors->GetColor3d("Wheat").GetData());

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkOutlineFilter> outline;
#else
  vtkSmartPointer<vtkOutlineFilter> outline = vtkSmartPointer<vtkOutlineFilter>::New();
#endif
  outline->SetInputConnection(extractVOI->GetOutputPort());

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkPolyDataMapper> outlineMapper;
#else
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#endif
  outlineMapper->SetInputConnection(outline->GetOutputPort());

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkActor> outlineActor;
#else
  vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
#endif
  outlineActor->SetMapper(outlineMapper);

  // Add the actors to the renderer, set the background and size.
  ren1->AddActor(outlineActor);
  ren1->AddActor(isoActor);
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Dolly(1.5);
  ren1->ResetCameraClippingRange();

  renWin->SetSize(640, 480);
  renWin->SetWindowName("Full Head");
  renWin->Render();

  iren->Start();
  return EXIT_SUCCESS;
}
