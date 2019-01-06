#include <vtkSmartPointer.h>

#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLDataSetWriter.h>

#include <vtkVertex.h>
#include <vtkPolyVertex.h>
#include <vtkLine.h>
#include <vtkPolyLine.h>
#include <vtkTriangle.h>
#include <vtkTriangleStrip.h>
#include <vtkPolygon.h>
#include <vtkPixel.h>
#include <vtkQuad.h>
#include <vtkTetra.h>
#include <vtkVoxel.h>
#include <vtkHexahedron.h>
#include <vtkWedge.h>
#include <vtkPyramid.h>
#include <vtkPentagonalPrism.h>
#include <vtkHexagonalPrism.h>

#include <vector>
#include <string>
#include <cstdlib>

// These functions return a vtkUnstructured grid corresponding to the object.
namespace
{
template<typename T> vtkSmartPointer<vtkUnstructuredGrid> MakeUnstructuredGrid(vtkSmartPointer<T>);

vtkSmartPointer<vtkUnstructuredGrid> MakePolyVertex();
vtkSmartPointer<vtkUnstructuredGrid> MakePolyLine();
vtkSmartPointer<vtkUnstructuredGrid> MakeTriangleStrip();
vtkSmartPointer<vtkUnstructuredGrid> MakePolygon();
}

int main(int, char *[])
{
  std::vector<std::string> filenames;
  std::vector<vtkSmartPointer<vtkUnstructuredGrid> > uGrids;

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkVertex>::New()));
  filenames.push_back("Vertex.vtu");

  uGrids.push_back(MakePolyVertex());
  filenames.push_back("PolyVertex.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkLine>::New()));
  filenames.push_back("Line.vtu");

  uGrids.push_back(MakePolyLine());
  filenames.push_back("PolyLine.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkTriangle>::New()));
  filenames.push_back("Triangle.vtu");

  uGrids.push_back(MakeTriangleStrip());
  filenames.push_back("TriangleStrip.vtu");

  uGrids.push_back(MakePolygon());
  filenames.push_back("Polygon.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkPixel>::New()));
  filenames.push_back("Pixel.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuad>::New()));
  filenames.push_back("Quad.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkTetra>::New()));
  filenames.push_back("Tetra.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkVoxel>::New()));
  filenames.push_back("Voxel.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkHexahedron>::New()));
  filenames.push_back("Hexahedron.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkWedge>::New()));
  filenames.push_back("Wedge.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkPyramid>::New()));
  filenames.push_back("Pyramid.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkPentagonalPrism>::New()));
  filenames.push_back("PentagonalPrism.vtu");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkHexagonalPrism>::New()));
  filenames.push_back("HexagonalPrism.vtu");

  // Write each grid into  a file
  for (unsigned int i = 0; i < uGrids.size(); ++i)
  {
    std::cout << "Writing: " << filenames[i] << std::endl;
    vtkSmartPointer<vtkXMLDataSetWriter> writer =
      vtkSmartPointer<vtkXMLDataSetWriter>::New();
    writer->SetFileName(filenames[i].c_str());
    writer->SetInputData(uGrids[i]);
    writer->Write();
  }

  return EXIT_SUCCESS;
}
namespace
{
template<typename T> vtkSmartPointer<vtkUnstructuredGrid> MakeUnstructuredGrid(vtkSmartPointer<T> aCell)
{
  double *pcoords = aCell->GetParametricCoords();
  for (int i = 0; i < aCell->GetNumberOfPoints(); ++i)
  {
    aCell->GetPointIds()->SetId(i, i);
    aCell->GetPoints()->SetPoint(i,
                                     *(pcoords + 3 * i),
                                     *(pcoords + 3 * i + 1),
                                     *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(aCell->GetPoints());
  ug->InsertNextCell(aCell->GetCellType(),aCell->GetPointIds());
  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakePolyVertex()
{
  // A polyvertex is a cell represents a set of 0D vertices
  int numberOfVertices = 6;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);
  points->InsertNextPoint(0, 1, 0);
  points->InsertNextPoint(0, 0, 1);
  points->InsertNextPoint(1, 0, .4);
  points->InsertNextPoint(0, 1, .6);

  vtkSmartPointer<vtkPolyVertex> polyVertex =
    vtkSmartPointer<vtkPolyVertex>::New();
  polyVertex->GetPointIds()->SetNumberOfIds(numberOfVertices);

  for (int i = 0; i < numberOfVertices; ++i)
  {
    polyVertex->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(polyVertex->GetCellType(),polyVertex->GetPointIds());

  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakePolyLine()
{
  // A polyline is a cell that represents a set of 1D lines
  int numberOfVertices = 5;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, .5, 0);
  points->InsertNextPoint(.5, 0, 0);
  points->InsertNextPoint(1, .3, 0);
  points->InsertNextPoint(1.5, .4, 0);
  points->InsertNextPoint(2.0, .4, 0);

  vtkSmartPointer<vtkPolyLine> polyline =
    vtkSmartPointer<vtkPolyLine>::New();
  polyline->GetPointIds()->SetNumberOfIds(numberOfVertices);

  for (int i = 0; i < numberOfVertices; ++i)
  {
    polyline->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(polyline->GetCellType(),polyline->GetPointIds());

  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeTriangleStrip()
{
  // A triangle is a cell that represents a triangle strip
  int numberOfVertices = 10;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(.5, 1, 0);
  points->InsertNextPoint(1, -.1, 0);
  points->InsertNextPoint(1.5, .8, 0);
  points->InsertNextPoint(2.0, -.1, 0);
  points->InsertNextPoint(2.5, .9, 0);
  points->InsertNextPoint(3.0, 0, 0);
  points->InsertNextPoint(3.5, .8, 0);
  points->InsertNextPoint(4.0, -.2, 0);
  points->InsertNextPoint(4.5, 1.1, 0);

  vtkSmartPointer<vtkTriangleStrip> trianglestrip =
    vtkSmartPointer<vtkTriangleStrip>::New();
  trianglestrip->GetPointIds()->SetNumberOfIds(numberOfVertices);
  for (int i = 0; i < numberOfVertices; ++i)
  {
    trianglestrip->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(trianglestrip->GetCellType(),trianglestrip->GetPointIds());

  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakePolygon()
{
  // A polygon is a cell that represents a polygon
  int numberOfVertices = 6;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, -.1, 0);
  points->InsertNextPoint(.8, .5, 0);
  points->InsertNextPoint(1, 1, 0);
  points->InsertNextPoint(.6, 1.2, 0);
  points->InsertNextPoint(0, .8, 0);

  vtkSmartPointer<vtkPolygon> polygon =
    vtkSmartPointer<vtkPolygon>::New();
  polygon->GetPointIds()->SetNumberOfIds(numberOfVertices);
  for (int i = 0; i < numberOfVertices; ++i)
  {
    polygon->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(polygon->GetCellType(),polygon->GetPointIds());

  return ug;
}
}
