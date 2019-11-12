
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#ifdef VTK_CELL_ARRAY_V2
#include <vtkCellArrayIterator.h>
#endif // VTK_CELL_ARRAY_V2
#include <vtkConnectivityFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkDecimatePro.h>
#include <vtkMCubesReader.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename" << std::endl;
    std::cout << "where: filename is pine_root.tri." << std::endl;
    return EXIT_FAILURE;
  }

  /**
   * Count the triangles in the polydata.
   * @param pd: vtkPolyData.
   * @return The number of triangles.
   */
  auto NumberofTriangles = [](vtkPolyData* pd) {
    vtkCellArray* cells = pd->GetPolys();
    vtkIdType npts = 0;
    auto numOfTriangles = 0;
#ifdef VTK_CELL_ARRAY_V2

    // Newer versions of vtkCellArray prefer local iterators:
    std::cout << pd->GetNumberOfPolys() << std::endl;
    auto cellIter = vtk::TakeSmartPointer(cells->NewIterator());
    for (cellIter->GoToFirstCell(); !cellIter->IsDoneWithTraversal();
         cellIter->GoToNextCell())
    {
      auto cell = cellIter->GetCurrentCell();
      if (cell == nullptr)
      {
        break;
      }
      // If a cell has three points it is a triangle.
      if (cell->GetNumberOfIds() == 3)
      {
        numOfTriangles++;
      }
    }

#else  // VTK_CELL_ARRAY_V2

    // Older implementations of vtkCellArray use internal iterator APIs (not
    // thread safe):
    vtkIdType* pts;
    for (auto i = 0; i < pd->GetNumberOfPolys(); ++i)
    {
      int c = cells->GetNextCell(npts, pts);
      if (c == 0)
      {
        break;
      }
      // If a cell has three points it is a triangle.
      if (npts == 3)
      {
        numOfTriangles++;
      }
    }
#endif // VTK_CELL_ARRAY_V2

    return numOfTriangles;
  };
  ///**
  //* Count the triangles in the polydata.
  //* @param pd: vtkPolyData.
  //* @return The number of triangles.
  //*/
  // auto NumberofTriangles = [](vtkPolyData* pd) {
  //  vtkCellArray* cells = pd->GetPolys();
  //  vtkIdType npts = 0;
  //  vtkIdType* pts;
  //  auto numOfTriangles = 0;
  //  for (auto i = 0; i < pd->GetNumberOfPolys(); ++i)
  //  {
  //    int c = cells->GetNextCell(npts, pts);
  //    if (c == 0)
  //    {
  //      break;
  //    }
  //    // If a cell has three points it is a triangle.
  //    if (npts == 3)
  //    {
  //      numOfTriangles++;
  //    }
  //  }
  //  return numOfTriangles;
  //};

  std::string fileName = argv[1];

  vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();

  // Create the pipeline.
  vtkSmartPointer<vtkMCubesReader> reader =
      vtkSmartPointer<vtkMCubesReader>::New();
  reader->SetFileName(fileName.c_str());
  reader->FlipNormalsOff();
  reader->Update();
  std::cout << "Before Decimation." << std::endl;
  std::cout << "There are: " << NumberofTriangles(reader->GetOutput())
            << " triangles." << std::endl;

  vtkSmartPointer<vtkDecimatePro> deci = vtkSmartPointer<vtkDecimatePro>::New();
  deci->SetInputConnection(reader->GetOutputPort());
  deci->SetTargetReduction(0.9);
  deci->SetAbsoluteError(0.0005);
  deci->SetFeatureAngle(30);
  deci->SetErrorIsAbsolute(1);
  deci->AccumulateErrorOn();
  // deci->SplittingOff();
  deci->Update();
  std::cout << "After Decimation." << std::endl;
  std::cout << "There are: " << NumberofTriangles(deci->GetOutput())
            << " triangles." << std::endl;

  vtkSmartPointer<vtkConnectivityFilter> connect =
      vtkSmartPointer<vtkConnectivityFilter>::New();
  connect->SetInputConnection(deci->GetOutputPort());
  connect->SetExtractionModeToLargestRegion();
  connect->Update();
  std::cout << "After Connectivity." << std::endl;
  // Note the use of dynamic_cast<vtkPolyData*> here.
  std::cout << "There are: "
            << NumberofTriangles(
                   dynamic_cast<vtkPolyData*>(connect->GetOutput()))
            << " triangles." << std::endl;

  vtkSmartPointer<vtkDataSetMapper> isoMapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
  isoMapper->SetInputConnection(connect->GetOutputPort());
  isoMapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> isoActor = vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetColor(colors->GetColor3d("raw_sienna").GetData());

  // Get an outline of the data set for context.
  vtkSmartPointer<vtkOutlineFilter> outline =
      vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(reader->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

  // Create the Renderer, RenderWindow and RenderWindowInteractor.
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size.
  ren->AddActor(outlineActor);
  ren->AddActor(isoActor);
  // renWin->SetSize(750, 750);
  renWin->SetSize(512, 512);
  ren->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkCamera* cam = ren->GetActiveCamera();
  cam->SetFocalPoint(40.6018, 37.2813, 50.1953);
  cam->SetPosition(40.6018, -280.533, 47.0172);
  cam->ComputeViewPlaneNormal();
  cam->SetClippingRange(26.1073, 1305.36);
  cam->SetViewAngle(20.9219);
  cam->SetViewUp(0.0, 0.0, 1.0);

  iren->Initialize();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
