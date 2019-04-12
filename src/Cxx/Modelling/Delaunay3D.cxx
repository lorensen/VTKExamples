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

#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>

#include <vtkXMLPolyDataReader.h>

#include <sstream>

int main ( int argc, char *argv[] )
{
  float alpha = .5;
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " filename.vtp [alpha]" << std::endl;
    return EXIT_FAILURE;
  }
  if (argc > 2)
  {
    alpha = atof(argv[2]);
  }
  //Read the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkNamedColors> color =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkDataSetMapper> originalMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  originalMapper->SetInputConnection(reader->GetOutputPort());
  originalMapper->ScalarVisibilityOff();
  originalMapper->SetScalarModeToUseCellData();

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(color->GetColor3d("tomato").GetData());
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
  delaunayMapper->SetScalarModeToUseCellData();

  vtkSmartPointer<vtkActor> delaunayActor =
    vtkSmartPointer<vtkActor>::New();
  delaunayActor->SetMapper(delaunayMapper);
  delaunayActor->GetProperty()->SetColor(color->GetColor3d("banana").GetData());
  delaunayActor->GetProperty()->SetInterpolationToFlat();

  // Generate a mesh from the input points. If Alpha is non-zero, then
  // tetrahedra, triangles, edges and vertices that lie within the
  // alpha radius are output.
  vtkSmartPointer<vtkDelaunay3D> delaunay3DAlpha =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay3DAlpha->SetInputConnection (cleaner->GetOutputPort());
  delaunay3DAlpha->SetAlpha(alpha);
  delaunay3DAlpha->Update();
  std::cout << "Alpha: " << alpha << std::endl;

  vtkSmartPointer<vtkUnsignedCharArray> cellData =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  cellData->SetNumberOfComponents(3);

  int numTetras = 0;
  int numLines = 0;
  int numTris = 0;
  int numVerts = 0;

  auto it = delaunay3DAlpha->GetOutput()->NewCellIterator();
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
      cellData->InsertNextTypedTuple(color->GetColor3ub("Lime").GetData());
    }
  }
  it->Delete();

  std::stringstream ss;
  ss << "numTetras: " << numTetras << std::endl;
  ss << "numLines: " << numLines << std::endl;
  ss << "numTris: " << numTris << std::endl;
  ss << "numVerts: " << numVerts;

  // Set the cell color depending on cell type
  delaunay3DAlpha->GetOutput()->GetCellData()->SetScalars(cellData);

  vtkSmartPointer<vtkDataSetMapper> delaunayAlphaMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  delaunayAlphaMapper->SetInputConnection(delaunay3DAlpha->GetOutputPort());
  delaunayAlphaMapper->SetScalarModeToUseCellData();

  vtkSmartPointer<vtkActor> delaunayAlphaActor =
    vtkSmartPointer<vtkActor>::New();
  delaunayAlphaActor->SetMapper(delaunayAlphaMapper);
  delaunayAlphaActor->GetProperty()->SetPointSize(5.0);
  delaunayAlphaActor->GetProperty()->SetInterpolationToFlat();

  // Visualize

  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(16);
  textProperty->SetColor(color->GetColor3d("Black").GetData());

  vtkSmartPointer<vtkTextMapper> textMapper =
    vtkSmartPointer<vtkTextMapper>::New();  
  textMapper->SetInput(ss.str().c_str());
  textMapper->SetTextProperty(textProperty);

  vtkSmartPointer<vtkActor2D> textActor =
    vtkSmartPointer<vtkActor2D>::New();
  textActor->SetMapper(textMapper);
  textActor->SetPosition(10, 10);

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
  delaunayAlphaRenderer->AddViewProp(textActor);

  originalRenderer->SetBackground(
    color->GetColor3d("Slate_Grey").GetData());
  delaunayRenderer->SetBackground(
    color->GetColor3d("Light_Grey").GetData());
  delaunayAlphaRenderer->SetBackground(
    color->GetColor3d("Grey").GetData());

  originalRenderer->ResetCamera();
  renderWindow->Render();

  // Render and interact
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
