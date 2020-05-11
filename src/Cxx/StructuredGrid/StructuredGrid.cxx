#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellData.h>
#include <vtkCellIterator.h>
#include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredGrid.h>

#include <iterator>
#include <map>
#include <set>

#define USE_POINT_DATA
// Uncomment the next line if you want to use cell data instead
// #undef USE_POINT_DATA

int main(int, char*[])
{
  vtkNew<vtkNamedColors> colors;

  size_t nx = 2, ny = 3, nz = 2;
  auto dataSize = nx * ny * nz;

  vtkNew<vtkDoubleArray> pointValues;
  pointValues->SetNumberOfComponents(1);
  pointValues->SetNumberOfTuples(dataSize);
  for (size_t i = 0; i < dataSize; ++i)
  {
    pointValues->SetValue(i, i);
  }

  auto numberOfCells = (nx - 1) * (ny - 1) * (nz - 1);
  vtkNew<vtkDoubleArray> cellValues;
  cellValues->SetNumberOfTuples(numberOfCells);
  for (size_t i = 0; i < numberOfCells; ++i)
  {
    cellValues->SetValue(i, i);
  }

  vtkNew<vtkPoints> points;
  auto x = 0.0;
  auto y = 0.0;
  auto z = 0.0;
  for (unsigned int k = 0; k < nz; k++)
  {
    z += 2.0;
    for (unsigned int j = 0; j < ny; j++)
    {
      y += 1.0;
      for (unsigned int i = 0; i < nx; i++)
      {
        x += .5;
        points->InsertNextPoint(x, y, z);
      }
    }
  }

  // Create a grid
  vtkNew<vtkStructuredGrid> structuredGrid;
  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(static_cast<int>(nx), static_cast<int>(ny),
                                static_cast<int>(nz));
  structuredGrid->SetPoints(points);
  structuredGrid->GetCellData()->SetScalars(cellValues);
  structuredGrid->GetPointData()->SetScalars(pointValues);

  // The key is the cell Id and the value is a set of corresponding point Ids.
  std::map<vtkIdType, std::set<vtkIdType>> cellPointIds;
  vtkCellIterator* it = structuredGrid->NewCellIterator();
  for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell())
  {
    vtkIdList* pointIds = it->GetPointIds();
    std::set<vtkIdType> ptIds;
    for (vtkIdType* id = pointIds->begin(); id != pointIds->end(); ++id)
    {
      ptIds.insert(*id);
    }
    cellPointIds[it->GetCellId()] = ptIds;
  }
  it->Delete();

  std::cout << "Cells and their points" << std::endl;
  for (auto cell : cellPointIds)
  {
    std::cout << "Cell Id: " << cell.first << " Point Ids: ";
    for (auto id = cell.second.begin(); id != cell.second.end(); ++id)
      if (id != std::prev(cell.second.end()))
      {
        std::cout << *id << ", ";
      }
      else
      {
        std::cout << *id << std::endl;
      }
  }

  // The key is the point Id and the value is a set of corresponding cell Ids.
  std::map<vtkIdType, std::set<vtkIdType>>
      commonPointIds; // = cellPointIds.begin()->second;
  for (auto cell : cellPointIds)
  {
    for (auto pointId : cell.second)
    {
      commonPointIds[pointId].insert(cell.first);
    }
  }

  std::cout << "Point Ids shared between cells" << std::endl;
  for (auto point = commonPointIds.begin(); point != commonPointIds.end();
       ++point)
  {
    if (point->second.size() > 1)
    {
      std::cout << "Point Id: " << point->first << " CellIds: ";
      for (auto cellId = point->second.begin(); cellId != point->second.end();
           ++cellId)
      {
        if (cellId != std::prev(point->second.end()))
        {
          std::cout << *cellId << ", ";
        }
        else
        {
          std::cout << *cellId << std::endl;
        }
      }
    }
  }

#if defined(USE_POINT_DATA)
  // Use the point data
  // Map the scalar values in the image to colors with a lookup table:
  vtkNew<vtkLookupTable> lut;
  lut->SetNumberOfTableValues(dataSize);
  lut->Build();

  // Create a mapper and actor
  vtkNew<vtkDataSetMapper> mapper;
  mapper->SetInputData(structuredGrid);
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(0, dataSize - 1);
  mapper->ScalarVisibilityOn();
#else
  // Use the cell data
  vtkNew<vtkLookupTable> lut;
  lut->SetNumberOfTableValues(numberOfCells);
  lut->Build();
  // Assign some specific colors in this case
  lut->SetTableValue(0, colors->GetColor4d("Red").GetData());
  lut->SetTableValue(numberOfCells - 1, colors->GetColor4d("Banana").GetData());

  // Create a mapper and actor
  vtkNew<vtkDataSetMapper> mapper;
  mapper->SetInputData(structuredGrid);
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(0, numberOfCells - 1);
  // mapper->ScalarVisibilityOff();
#endif
  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  // Create a renderer, render window, and interactor
  vtkNew<vtkRenderer> ren;
  vtkNew<vtkRenderWindow> renWin;
  renWin->AddRenderer(ren);
  vtkNew<vtkRenderWindowInteractor> iRen;
  iRen->SetRenderWindow(renWin);

  // Add the actor to the scene
  ren->AddActor(actor);
  ren->SetBackground(colors->GetColor3d("SlateGray").GetData());

  ren->GetActiveCamera()->Azimuth(60);
  ren->GetActiveCamera()->Elevation(-45);
  ren->GetActiveCamera()->Dolly(1.2);
  ren->ResetCamera();

  // Render and interact
  renWin->Render();
  renWin->SetSize(800, 800);
  renWin->SetWindowName("StructuredGrid");
  iRen->Start();

  return EXIT_SUCCESS;
}
