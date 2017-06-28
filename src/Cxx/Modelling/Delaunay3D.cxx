#include <vtkDelaunay3D.h>
#include <vtkSmartPointer.h>

#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCleanPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellIterator.h>
#include <vtkCellData.h>
#include <vtkUnsignedCharArray.h>
#include <vtkNamedColors.h>

#include <vtkXMLPolyDataReader.h>

int main ( int argc, char *argv[] )
{
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " filename.vtp" << std::endl;
    return EXIT_FAILURE;
  }

  //Read the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkDataSetMapper> originalMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  originalMapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(1,0,0);
  originalActor->GetProperty()->SetInterpolationToFlat();

  // Clean the polydata. This will remove duplicate points that may be
  // present in the input data.
  vtkSmartPointer<vtkCleanPolyData> cleaner =
    vtkSmartPointer<vtkCleanPolyData>::New();
  cleaner->SetInputConnection (reader->GetOutputPort());

  // Generate a tetrahedral mesh from the input points. By
  // default, the generated volume is the convex hull of the points.
  vtkSmartPointer<vtkDelaunay3D> delaunay3D =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay3D->SetInputConnection (cleaner->GetOutputPort());

  vtkSmartPointer<vtkDataSetMapper> delaunayMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  delaunayMapper->SetInputConnection(delaunay3D->GetOutputPort());

  vtkSmartPointer<vtkActor> delaunayActor =
    vtkSmartPointer<vtkActor>::New();
  delaunayActor->SetMapper(delaunayMapper);
  delaunayActor->GetProperty()->SetColor(1,0,0);
  delaunayActor->GetProperty()->SetInterpolationToFlat();

  // Generate a mesh from the input points. If Alpha is non-zero, then
  // tetrahedra, triangles, edges and vertices that lie within the
  // alpha radius are output.
  vtkSmartPointer<vtkDelaunay3D> delaunay3DAlpha =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay3DAlpha->SetInputConnection (cleaner->GetOutputPort());
  delaunay3DAlpha->SetAlpha(.02);
  delaunay3DAlpha->Update();
  vtkCellIterator *it = delaunay3DAlpha->GetOutput()->NewCellIterator();

  vtkSmartPointer<vtkNamedColors> color =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkUnsignedCharArray> cellData =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  cellData->SetNumberOfComponents(3);

  // Set the cell color depending on cell type
  int numTetras = 0;
  int numLines = 0;
  int numTris = 0;
  int numVerts = 0;

  for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell())
  {
    if (it->GetCellType() == VTK_TETRA)
    {
      numTetras++;
      cellData->InsertNextTypedTuple(color->GetColor3ub("Banana").GetData());
    }
    else if (it->GetCellType() == VTK_LINE)
    {
      numLines++;
      cellData->InsertNextTypedTuple(color->GetColor3ub("Peacock").GetData());
    }
    else if (it->GetCellType() == VTK_TRIANGLE)
    {
      numTris++;
      cellData->InsertNextTypedTuple(color->GetColor3ub("Tomato").GetData());
    }
    else if (it->GetCellType() == VTK_VERTEX)
    {
      numVerts++;
      cellData->InsertNextTypedTuple(color->GetColor3ub("Wheat").GetData());
    }
  }
  it->Delete();
  std::cout << "numTetras: " << numTetras << std::endl;
  std::cout << "numLines: " << numLines << std::endl;
  std::cout << "numTris: " << numTris << std::endl;
  std::cout << "numVerts: " << numVerts << std::endl;
  delaunay3DAlpha->GetOutput()->GetCellData()->SetScalars(cellData);

  vtkSmartPointer<vtkDataSetMapper> delaunayAlphaMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  delaunayAlphaMapper->SetInputConnection(delaunay3DAlpha->GetOutputPort());

  vtkSmartPointer<vtkActor> delaunayAlphaActor =
    vtkSmartPointer<vtkActor>::New();
  delaunayAlphaActor->SetMapper(delaunayAlphaMapper);
  delaunayAlphaActor->GetProperty()->SetColor(1,0,0);
  delaunayAlphaActor->GetProperty()->SetInterpolationToFlat();

  // Visualize

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double centerViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};

  // Shared camera
  vtkSmartPointer<vtkCamera> sharedCamera =
    vtkSmartPointer<vtkCamera>::New();

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetActiveCamera(sharedCamera);

  vtkSmartPointer<vtkRenderer> delaunayRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  delaunayRenderer->SetActiveCamera(sharedCamera);

  vtkSmartPointer<vtkRenderer> delaunayAlphaRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  delaunayAlphaRenderer->SetActiveCamera(sharedCamera);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900,300);

  renderWindow->AddRenderer(originalRenderer);
  originalRenderer->SetViewport(leftViewport);
  renderWindow->AddRenderer(delaunayRenderer);
  delaunayRenderer->SetViewport(centerViewport);
  renderWindow->AddRenderer(delaunayAlphaRenderer);
  delaunayAlphaRenderer->SetViewport(rightViewport);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  originalRenderer->AddActor(originalActor);
  delaunayRenderer->AddActor(delaunayActor);
  delaunayAlphaRenderer->AddActor(delaunayAlphaActor);

  originalRenderer->SetBackground(
    color->GetColor3d("Bisque").GetData());
  delaunayRenderer->SetBackground(
    color->GetColor3d("Wheat").GetData());
  delaunayAlphaRenderer->SetBackground(
    color->GetColor3d("Cornsilk").GetData());

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
