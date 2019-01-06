#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkDataSetMapper.h>
#include <vtkGlyph3DMapper.h>
#include <vtkLabeledDataMapper.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkUnstructuredGrid.h>

#include <vtkHexagonalPrism.h>
#include <vtkHexahedron.h>
#include <vtkLine.h>
#include <vtkPentagonalPrism.h>
#include <vtkPixel.h>
#include <vtkPolygon.h>
#include <vtkPolyLine.h>
#include <vtkPolyVertex.h>
#include <vtkPyramid.h>
#include <vtkQuad.h>
#include <vtkTetra.h>
#include <vtkTriangle.h>
#include <vtkTriangleStrip.h>
#include <vtkVertex.h>
#include <vtkVoxel.h>
#include <vtkWedge.h>

#include <cstdlib>
#include <string>
#include <vector>

// These functions return a vtkUnstructured grid corresponding to the object.
namespace
{

vtkSmartPointer<vtkUnstructuredGrid> MakeVertex();
vtkSmartPointer<vtkUnstructuredGrid> MakePolyVertex();
vtkSmartPointer<vtkUnstructuredGrid> MakeLine();
vtkSmartPointer<vtkUnstructuredGrid> MakePolyLine();
vtkSmartPointer<vtkUnstructuredGrid> MakeTriangle();
vtkSmartPointer<vtkUnstructuredGrid> MakeTriangleStrip();
vtkSmartPointer<vtkUnstructuredGrid> MakePolygon();
vtkSmartPointer<vtkUnstructuredGrid> MakePixel();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuad();
vtkSmartPointer<vtkUnstructuredGrid> MakeTetra();
vtkSmartPointer<vtkUnstructuredGrid> MakeVoxel();
vtkSmartPointer<vtkUnstructuredGrid> MakeHexahedron();
vtkSmartPointer<vtkUnstructuredGrid> MakeWedge();
vtkSmartPointer<vtkUnstructuredGrid> MakePyramid();
vtkSmartPointer<vtkUnstructuredGrid> MakePentagonalPrism();
vtkSmartPointer<vtkUnstructuredGrid> MakeHexagonalPrism();
}

int main(int, char *[])
{
  std::vector<std::string> titles;
  std::vector<vtkSmartPointer<vtkTextMapper> > textMappers;
  std::vector<vtkSmartPointer<vtkActor2D> > textActors;

  std::vector<vtkSmartPointer<vtkUnstructuredGrid> > uGrids;
  std::vector<vtkSmartPointer<vtkDataSetMapper> > mappers;
  std::vector<vtkSmartPointer<vtkActor> > actors;
  std::vector<vtkSmartPointer<vtkRenderer> > renderers;

  uGrids.push_back(MakeVertex());
  titles.push_back("VTK_VERTEX (=1)");
  uGrids.push_back(MakePolyVertex());
  titles.push_back("VTK_POLY_VERTEX (=2)");
  uGrids.push_back(MakeLine());
  titles.push_back("VTK_LINE (=3)");
  uGrids.push_back(MakePolyLine());
  titles.push_back("VTK_POLY_LINE (=4)");
  uGrids.push_back(MakeTriangle());
  titles.push_back("VTK_TRIANGLE (=5)");
  uGrids.push_back(MakeTriangleStrip());
  titles.push_back("VTK_TRIANGLE_STRIP (=6)");
  uGrids.push_back(MakePolygon());
  titles.push_back("VTK_POLYGON (=7)");
  uGrids.push_back(MakePixel());
  titles.push_back("VTK_PIXEL (=8)");
  uGrids.push_back(MakeQuad());
  titles.push_back("VTK_QUAD (=9)");
  uGrids.push_back(MakeTetra());
  titles.push_back("VTK_TETRA (=10)");
  uGrids.push_back(MakeVoxel());
  titles.push_back("VTK_VOXEL (=11)");
  uGrids.push_back(MakeHexahedron());
  titles.push_back("VTK_HEXAHEDRON (=12)");
  uGrids.push_back(MakeWedge());
  titles.push_back("VTK_WEDGE (=13)");
  uGrids.push_back(MakePyramid());
  titles.push_back("VTK_PYRAMID (=14)");
  uGrids.push_back(MakePentagonalPrism());
  titles.push_back("VTK_PENTAGONAL_PRISM (=15)");
  uGrids.push_back(MakeHexagonalPrism());
  titles.push_back("VTK_HEXAGONAL_PRISM (=16)");

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetSize(600, 600);
  renWin->SetWindowName("Linear Cell");

  vtkSmartPointer<vtkRenderWindowInteractor> iRen =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iRen->SetRenderWindow(renWin);

  // Create one sphere for all
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetPhiResolution(21);
  sphere->SetThetaResolution(21);
  sphere->SetRadius(.08);

  // Create one text property for all
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(10);
  textProperty->SetJustificationToCentered();

  // Create and link the mappers actors and renderers together.
  for (unsigned int i = 0; i < uGrids.size(); ++i)
  {
    std::cout << "Creatng: " << titles[i] << std::endl;
    textMappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textActors.push_back(vtkSmartPointer<vtkActor2D>::New());

    mappers.push_back(vtkSmartPointer<vtkDataSetMapper>::New());
    actors.push_back(vtkSmartPointer<vtkActor>::New());
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    mappers[i]->SetInputData(uGrids[i]);
    actors[i]->SetMapper(mappers[i]);
    actors[i]->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
    actors[i]->GetProperty()->EdgeVisibilityOn();
    actors[i]->GetProperty()->SetLineWidth(3);
    actors[i]->GetProperty()->SetOpacity(.5);
    renderers[i]->AddViewProp(actors[i]);

    textMappers[i]->SetInput(titles[i].c_str());
    textActors[i]->SetMapper(textMappers[i]);
    textActors[i]->SetPosition(50, 10);
    renderers[i]->AddViewProp(textActors[i]);

    // Label the points
    vtkSmartPointer<vtkLabeledDataMapper> labelMapper =
      vtkSmartPointer<vtkLabeledDataMapper>::New();
    labelMapper->SetInputData(uGrids[i]);
    vtkSmartPointer<vtkActor2D> labelActor =
      vtkSmartPointer<vtkActor2D>::New();
    labelActor->SetMapper(labelMapper);
    renderers[i]->AddViewProp(labelActor);

    // Glyph the points
    vtkSmartPointer<vtkGlyph3DMapper> pointMapper =
      vtkSmartPointer<vtkGlyph3DMapper>::New();
    pointMapper->SetInputData(uGrids[i]);
    pointMapper->SetSourceConnection(sphere->GetOutputPort());
    pointMapper->ScalingOff();
    pointMapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> pointActor =
      vtkSmartPointer<vtkActor>::New();
    pointActor->SetMapper(pointMapper);
    pointActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
    pointActor->GetProperty()->SetSpecular(.6);
    pointActor->GetProperty()->SetSpecularColor(1.0,1.0,1.0);
    pointActor->GetProperty()->SetSpecularPower(100);
    renderers[i]->AddViewProp(pointActor);

    renWin->AddRenderer(renderers[i]);
  }

  // Setup the viewports
  int xGridDimensions = 4;
  int yGridDimensions = 4;
  int rendererSize = 240;

  renWin->SetSize(
    rendererSize * xGridDimensions, rendererSize * yGridDimensions);

  for(int row = 0; row < yGridDimensions; row++)
  {
    for(int col = 0; col < xGridDimensions; col++)
    {
      int index = row * xGridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {
        static_cast<double>(col) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - (row + 1)) * rendererSize /
        (yGridDimensions * rendererSize),
        static_cast<double>(col + 1) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - row) * rendererSize /
        (yGridDimensions * rendererSize)};
      if(index > int(actors.size()) - 1)
      {
        // Add a renderer even if there is no actor.
        // This makes the render window background all the same color.
        vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
        ren->SetBackground(colors->GetColor3d("SlateGray").GetData());
        ren->SetViewport(viewport);
        renWin->AddRenderer(ren);
        continue;
      }

      renderers[index]->SetViewport(viewport);
      renderers[index]->SetBackground(colors->GetColor3d("SlateGray").GetData());
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(-30);
      if (index == 0)
      {
        renderers[index]->GetActiveCamera()->Dolly(.1);
      }
      else
      {

      }
      renderers[index]->ResetCameraClippingRange();
    }
  }


  iRen->Initialize();

  renWin->Render();

  iRen->Start();

  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkUnstructuredGrid> MakeVertex()
{
  // A vertex is a cell that represents a 3D point
  int numberOfVertices = 1;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);

  vtkSmartPointer<vtkVertex> vertex =
    vtkSmartPointer<vtkVertex>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
    vertex->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(vertex->GetCellType(),vertex->GetPointIds());

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

vtkSmartPointer<vtkUnstructuredGrid> MakeLine()
{
  // A line is a cell that represents a 1D point
  int numberOfVertices = 2;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(.5, .5, 0);

  vtkSmartPointer<vtkLine> line =
    vtkSmartPointer<vtkLine>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
    line->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(line->GetCellType(),line->GetPointIds());

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

vtkSmartPointer<vtkUnstructuredGrid> MakeTriangle()
{
  // A triangle is a cell that represents a 1D point
  int numberOfVertices = 3;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(.5, .5, 0);
  points->InsertNextPoint(.2, 1, 0);

  vtkSmartPointer<vtkTriangle> triangle =
    vtkSmartPointer<vtkTriangle>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
    triangle->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(triangle->GetCellType(),triangle->GetPointIds());

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

vtkSmartPointer<vtkUnstructuredGrid> MakePixel()

{
  // A pixel is a cell that represents a pixel
  vtkSmartPointer<vtkPixel> pixel =
    vtkSmartPointer<vtkPixel>::New();
  pixel->GetPoints()->SetPoint (0, 0, 0, 0);
  pixel->GetPoints()->SetPoint (1, 1, 0, 0);
  pixel->GetPoints()->SetPoint (2, 0, 1, 0);
  pixel->GetPoints()->SetPoint (3, 1, 1, 0);

  pixel->GetPointIds()->SetId(0,0);
  pixel->GetPointIds()->SetId(1,1);
  pixel->GetPointIds()->SetId(2,2);
  pixel->GetPointIds()->SetId(3,3);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(pixel->GetPoints());
  ug->InsertNextCell(pixel->GetCellType(),pixel->GetPointIds());

  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeQuad()

{
  // A quad is a cell that represents a quad
  vtkSmartPointer<vtkQuad> quad =
    vtkSmartPointer<vtkQuad>::New();
  quad->GetPoints()->SetPoint (0, 0, 0, 0);
  quad->GetPoints()->SetPoint (1, 1, 0, 0);
  quad->GetPoints()->SetPoint (2, 1, 1, 0);
  quad->GetPoints()->SetPoint (3, 0, 1, 0);

  quad->GetPointIds()->SetId(0,0);
  quad->GetPointIds()->SetId(1,1);
  quad->GetPointIds()->SetId(2,2);
  quad->GetPointIds()->SetId(3,3);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quad->GetPoints());
  ug->InsertNextCell(quad->GetCellType(),quad->GetPointIds());

  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeTetra()
{
  // Make a tetrahedron.
  int numberOfVertices = 4;

  vtkSmartPointer< vtkPoints > points =
    vtkSmartPointer< vtkPoints > :: New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);
  points->InsertNextPoint(1, 1, 0);
  points->InsertNextPoint(0, 1, 1);

  vtkSmartPointer<vtkTetra> tetra =
    vtkSmartPointer<vtkTetra>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
      tetra->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
  cellArray->InsertNextCell(tetra);

  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructuredGrid->SetPoints(points);
  unstructuredGrid->SetCells(VTK_TETRA, cellArray);

  return unstructuredGrid;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeVoxel()
{
  // A voxel is a representation of a regular grid in 3-D space.
  int numberOfVertices = 8;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);
  points->InsertNextPoint(0, 1, 0);
  points->InsertNextPoint(1, 1, 0);
  points->InsertNextPoint(0, 0, 1);
  points->InsertNextPoint(1, 0, 1);
  points->InsertNextPoint(0, 1, 1);
  points->InsertNextPoint(1, 1, 1);

  vtkSmartPointer<vtkVoxel> voxel =
    vtkSmartPointer<vtkVoxel>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
    voxel->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(voxel->GetCellType(),voxel->GetPointIds());

  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeHexahedron()
{
  // A regular hexagon (cube) with all faces square and three squares around
  // each vertex is created below.

  // Setup the coordinates of eight points
  // (the two faces must be in counter clockwise
  // order as viewed from the outside).

  int numberOfVertices = 8;

  // Create the points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 1.0);
  points->InsertNextPoint(1.0, 0.0, 1.0);
  points->InsertNextPoint(1.0, 1.0, 1.0);
  points->InsertNextPoint(0.0, 1.0, 1.0);

  // Create a hexahedron from the points
  vtkSmartPointer<vtkHexahedron> hex =
    vtkSmartPointer<vtkHexahedron>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
    hex->GetPointIds()->SetId(i, i);
  }

  // Add the points and hexahedron to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());

  return uGrid;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeWedge()
{

  // A wedge consists of two triangular ends and three rectangular faces.

  int numberOfVertices = 6;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  points->InsertNextPoint(0, 1, 0);
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(0, .5, .5);
  points->InsertNextPoint(1, 1, 0);
  points->InsertNextPoint(1, 0.0, 0.0);
  points->InsertNextPoint(1, .5, .5);

  vtkSmartPointer<vtkWedge> wedge =
    vtkSmartPointer<vtkWedge>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
    wedge->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(wedge->GetCellType(),wedge->GetPointIds());

  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakePyramid()
{
  // Make a regular square pyramid.
  int numberOfVertices = 5;

  vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();

  float p0[3] = {1.0, 1.0, 0.0};
  float p1[3] = {-1.0, 1.0, 0.0};
  float p2[3] = {-1.0, -1.0, 0.0};
  float p3[3] = {1.0, -1.0, 0.0};
  float p4[3] = {0.0, 0.0, 1.0};

  points->InsertNextPoint(p0);
  points->InsertNextPoint(p1);
  points->InsertNextPoint(p2);
  points->InsertNextPoint(p3);
  points->InsertNextPoint(p4);

  vtkSmartPointer<vtkPyramid> pyramid =
      vtkSmartPointer<vtkPyramid>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
    pyramid->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
      vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(pyramid->GetCellType(),pyramid->GetPointIds());

  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakePentagonalPrism()
{
  vtkSmartPointer<vtkPentagonalPrism> pentagonalPrism =
    vtkSmartPointer<vtkPentagonalPrism>::New();

  pentagonalPrism->GetPointIds()->SetId(0,0);
  pentagonalPrism->GetPointIds()->SetId(1,1);
  pentagonalPrism->GetPointIds()->SetId(2,2);
  pentagonalPrism->GetPointIds()->SetId(3,3);
  pentagonalPrism->GetPointIds()->SetId(4,4);
  pentagonalPrism->GetPointIds()->SetId(5,5);
  pentagonalPrism->GetPointIds()->SetId(6,6);
  pentagonalPrism->GetPointIds()->SetId(7,7);
  pentagonalPrism->GetPointIds()->SetId(8,8);
  pentagonalPrism->GetPointIds()->SetId(9,9);

  double scale = 2.0;
  pentagonalPrism->GetPoints()->SetPoint(0, 11/scale, 10/scale, 10/scale);
  pentagonalPrism->GetPoints()->SetPoint(1, 13/scale, 10/scale, 10/scale);
  pentagonalPrism->GetPoints()->SetPoint(2, 14/scale, 12/scale, 10/scale);
  pentagonalPrism->GetPoints()->SetPoint(3, 12/scale, 14/scale, 10/scale);
  pentagonalPrism->GetPoints()->SetPoint(4, 10/scale, 12/scale, 10/scale);
  pentagonalPrism->GetPoints()->SetPoint(5, 11/scale, 10/scale, 14/scale);
  pentagonalPrism->GetPoints()->SetPoint(6, 13/scale, 10/scale, 14/scale);
  pentagonalPrism->GetPoints()->SetPoint(7, 14/scale, 12/scale, 14/scale);
  pentagonalPrism->GetPoints()->SetPoint(8, 12/scale, 14/scale, 14/scale);
  pentagonalPrism->GetPoints()->SetPoint(9, 10/scale, 12/scale, 14/scale);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(pentagonalPrism->GetPoints());
  ug->InsertNextCell(pentagonalPrism->GetCellType(),pentagonalPrism->GetPointIds());

  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeHexagonalPrism()
{
  vtkSmartPointer<vtkHexagonalPrism> hexagonalPrism =
    vtkSmartPointer<vtkHexagonalPrism>::New();
  hexagonalPrism->GetPointIds()->SetId(0,0);
  hexagonalPrism->GetPointIds()->SetId(1,1);
  hexagonalPrism->GetPointIds()->SetId(2,2);
  hexagonalPrism->GetPointIds()->SetId(3,3);
  hexagonalPrism->GetPointIds()->SetId(4,4);
  hexagonalPrism->GetPointIds()->SetId(5,5);
  hexagonalPrism->GetPointIds()->SetId(6,6);
  hexagonalPrism->GetPointIds()->SetId(7,7);
  hexagonalPrism->GetPointIds()->SetId(8,8);
  hexagonalPrism->GetPointIds()->SetId(9,9);
  hexagonalPrism->GetPointIds()->SetId(10,10);
  hexagonalPrism->GetPointIds()->SetId(11,11);

  double scale = 2.0;
  hexagonalPrism->GetPoints()->SetPoint(0, 11/scale, 10/scale, 10/scale);
  hexagonalPrism->GetPoints()->SetPoint(1, 13/scale, 10/scale, 10/scale);
  hexagonalPrism->GetPoints()->SetPoint(2, 14/scale, 12/scale, 10/scale);
  hexagonalPrism->GetPoints()->SetPoint(3, 13/scale, 14/scale, 10/scale);
  hexagonalPrism->GetPoints()->SetPoint(4, 11/scale, 14/scale, 10/scale);
  hexagonalPrism->GetPoints()->SetPoint(5, 10/scale, 12/scale, 10/scale);
  hexagonalPrism->GetPoints()->SetPoint(6, 11/scale, 10/scale, 14/scale);
  hexagonalPrism->GetPoints()->SetPoint(7, 13/scale, 10/scale, 14/scale);
  hexagonalPrism->GetPoints()->SetPoint(8, 14/scale, 12/scale, 14/scale);
  hexagonalPrism->GetPoints()->SetPoint(9, 13/scale, 14/scale, 14/scale);
  hexagonalPrism->GetPoints()->SetPoint(10, 11/scale, 14/scale, 14/scale);
  hexagonalPrism->GetPoints()->SetPoint(11, 10/scale, 12/scale, 14/scale);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(hexagonalPrism->GetPoints());
  ug->InsertNextCell(hexagonalPrism->GetCellType(),hexagonalPrism->GetPointIds());

  return ug;
}

}
