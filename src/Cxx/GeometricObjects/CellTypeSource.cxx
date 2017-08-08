#include <vtkSmartPointer.h>
#include <vtkCellTypeSource.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellType.h>
#include <vtkCellTypes.h>
#include <vtkTessellatorFilter.h>

#include <vtkCellData.h>
#include <vtkIntArray.h>

#include <vtkShrinkFilter.h>

#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>

#include <vtkLookupTable.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkMath.h>
#include <vtkColorSeries.h>
#include <vtkNamedColors.h>

#include <map>

int main (int argc, char *argv[])
{
  std::string cellName = "vtkTetra";
  if (argc > 1)
  {
    cellName = std::string(argv[1]);
  }

  // Store cell class names in a map
  std::map<std::string,int> cellMap;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_LINE)] =
    VTK_LINE;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_QUADRATIC_EDGE)] =
    VTK_QUADRATIC_EDGE;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_CUBIC_LINE)] =
    VTK_CUBIC_LINE;

  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_TRIANGLE)] =
    VTK_TRIANGLE;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_QUADRATIC_TRIANGLE)] =
    VTK_QUADRATIC_TRIANGLE;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_QUAD)] =
    VTK_QUAD;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_QUADRATIC_QUAD)] =
    VTK_QUADRATIC_QUAD;

  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_TETRA)] =
    VTK_TETRA;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_HEXAHEDRON)] =
    VTK_HEXAHEDRON;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_WEDGE)] =
    VTK_WEDGE;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_PYRAMID)] =
    VTK_PYRAMID;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_QUADRATIC_WEDGE)] =
    VTK_QUADRATIC_WEDGE;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_QUADRATIC_PYRAMID)] =
    VTK_QUADRATIC_PYRAMID;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_QUADRATIC_HEXAHEDRON)] =
    VTK_QUADRATIC_HEXAHEDRON;
  cellMap[vtkCellTypes::GetClassNameFromTypeId(VTK_QUADRATIC_TETRA)] =
    VTK_QUADRATIC_TETRA;

  if (cellMap[std::string(cellName)] == 0)
    {
      std::cout << "Cell type " << cellName << " is not supported." << std::endl;
      return EXIT_FAILURE;
    }
  int dims[3] = {2, 2, 1};
  vtkSmartPointer<vtkCellTypeSource> source =
    vtkSmartPointer<vtkCellTypeSource>::New();
  source->SetCellType(cellMap[cellName]);
  source->Update();
  std::cout << "Cell: "
            << cellName << std::endl;

  vtkPoints *originalPoints = source->GetOutput()->GetPoints();
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(source->GetOutput()->GetNumberOfPoints());
  vtkMath::RandomSeed(5070); // for testing
  for (int i = 0; i <points->GetNumberOfPoints(); ++i)
  {
    double currentPoint[3];
    originalPoints->GetPoint(i, currentPoint);
    points->SetPoint(i,currentPoint[0] + vtkMath::Random(-.1,.1),
                       currentPoint[1] + vtkMath::Random(-.1,.1),
                       currentPoint[2] + vtkMath::Random(-.1,.1));
  }
  source->GetOutput()->SetPoints(points);

  int numCells = source->GetOutput()->GetNumberOfCells();
  std::cout << "Number of cells: " << numCells << std::endl;
  vtkSmartPointer<vtkIntArray> idArray =
    vtkSmartPointer<vtkIntArray>::New();
  idArray->SetNumberOfTuples(numCells);
  for (int i = 0; i < numCells; ++i)
  {
    idArray->InsertTuple1(i, i + 1);
  }
  idArray->SetName("Ids");
  source->GetOutput()->GetCellData()->AddArray(idArray);
  source->GetOutput()->GetCellData()->SetActiveScalars("Ids");

  vtkSmartPointer<vtkShrinkFilter> shrink =
    vtkSmartPointer<vtkShrinkFilter>::New();
  shrink->SetInputConnection(source->GetOutputPort());
  shrink->SetShrinkFactor(.8);

  vtkSmartPointer<vtkTessellatorFilter> tessellate =
    vtkSmartPointer<vtkTessellatorFilter>::New();
  tessellate->SetInputConnection(shrink->GetOutputPort());
  tessellate->SetMaximumNumberOfSubdivisions(3);

  // Create a lookup table to map cell data to colors
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();

  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  int seriesEnum = colorSeries->BREWER_QUALITATIVE_SET3;;
  colorSeries->SetColorScheme(seriesEnum);
  colorSeries->BuildLookupTable(lut, colorSeries->ORDINAL);

  // Fill in a few known colors, the rest will be generated if needed
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  //Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(source->GetOutputPort());
  mapper->SetInputConnection(shrink->GetOutputPort());
  mapper->SetScalarRange(0, numCells + 1);
  mapper->SetLookupTable(lut);
  mapper->SetScalarModeToUseCellData();
  mapper->SetResolveCoincidentTopologyToPolygonOffset();
  if (source->GetCellType() == VTK_QUADRATIC_PYRAMID ||
      source->GetCellType() == VTK_QUADRATIC_WEDGE)
  {
    mapper->SetInputConnection(shrink->GetOutputPort());
  }
  else
  {
    mapper->SetInputConnection(tessellate->GetOutputPort());
  }
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->EdgeVisibilityOn();
//  actor->GetProperty()->SetLineWidth(3);

  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(20);
  textProperty->SetJustificationToCentered();
  textProperty->SetColor(colors->GetColor3d("Lamp_Black").GetData());

  vtkSmartPointer<vtkTextMapper> textMapper =
    vtkSmartPointer<vtkTextMapper>::New();
  textMapper->SetInput(cellName.c_str());
  textMapper->SetTextProperty(textProperty);

  vtkSmartPointer<vtkActor2D> textActor =
    vtkSmartPointer<vtkActor2D>::New();
  textActor->SetMapper(textMapper);
  textActor->SetPosition(320, 20);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddViewProp(textActor);
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();

  //Render and interact
  renderWindow->SetSize(640, 480);  
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
