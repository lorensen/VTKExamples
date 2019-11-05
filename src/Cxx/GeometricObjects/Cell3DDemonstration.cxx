#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkDataSetMapper.h>
#include <vtkHexagonalPrism.h>
#include <vtkHexahedron.h>
#include <vtkNamedColors.h>
#include <vtkPentagonalPrism.h>
#include <vtkPoints.h>
#include <vtkPolyhedron.h>
#include <vtkProperty.h>
#include <vtkPyramid.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTetra.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVoxel.h>
#include <vtkWedge.h>

#include <array>
#include <cstdlib>
#include <string>
#include <vector>

namespace
{
// These functions return a vtkUnstructured grid corresponding to the object.
vtkSmartPointer<vtkUnstructuredGrid> MakeHexagonalPrism();
vtkSmartPointer<vtkUnstructuredGrid> MakeHexahedron();
vtkSmartPointer<vtkUnstructuredGrid> MakePentagonalPrism();

vtkSmartPointer<vtkUnstructuredGrid> MakePolyhedron();
vtkSmartPointer<vtkUnstructuredGrid> MakePyramid();
vtkSmartPointer<vtkUnstructuredGrid> MakeTetrahedron();

vtkSmartPointer<vtkUnstructuredGrid> MakeVoxel();
vtkSmartPointer<vtkUnstructuredGrid> MakeWedge();
}

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char , 4> bkg{{51, 77, 102, 255}};
  colors->SetColor("BkgColor", bkg.data());

  std::vector<std::string> titles;
  std::vector<vtkSmartPointer<vtkTextMapper> > textMappers;
  std::vector<vtkSmartPointer<vtkActor2D> > textActors;

  std::vector<vtkSmartPointer<vtkUnstructuredGrid> > uGrids;
  std::vector<vtkSmartPointer<vtkDataSetMapper> > mappers;
  std::vector<vtkSmartPointer<vtkActor> > actors;
  std::vector<vtkSmartPointer<vtkRenderer> > renderers;

  uGrids.push_back(MakeHexagonalPrism());
  titles.push_back("Hexagonal Prism");
  uGrids.push_back(MakeHexahedron());
  titles.push_back("Hexahedron");
  uGrids.push_back(MakePentagonalPrism());
  titles.push_back("Pentagonal Prism");

  uGrids.push_back(MakePolyhedron());
  titles.push_back("Polyhedron");
  uGrids.push_back(MakePyramid());
  titles.push_back("Pyramid");
  uGrids.push_back(MakeTetrahedron());
  titles.push_back("Tetrahedron");

  uGrids.push_back(MakeVoxel());
  titles.push_back("Voxel");
  uGrids.push_back(MakeWedge());
  titles.push_back("Wedge");

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetWindowName("Cell3D Demonstration");

  vtkSmartPointer<vtkRenderWindowInteractor> iRen =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iRen->SetRenderWindow(renWin);

  // Create one text property for all
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(16);
  textProperty->SetJustificationToCentered();

  // Create and link the mappers actors and renderers together.
  for (unsigned int i = 0; i < uGrids.size(); ++i)
  {
    textMappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textActors.push_back(vtkSmartPointer<vtkActor2D>::New());

    mappers.push_back(vtkSmartPointer<vtkDataSetMapper>::New());
    actors.push_back(vtkSmartPointer<vtkActor>::New());
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    mappers[i]->SetInputData(uGrids[i]);

    actors[i]->SetMapper(mappers[i]);
    actors[i]->GetProperty()->SetColor(
      colors->GetColor3d("Seashell").GetData());

    renderers[i]->AddViewProp(actors[i]);

    textMappers[i]->SetInput(titles[i].c_str());
    textMappers[i]->SetTextProperty(textProperty);

    textActors[i]->SetMapper(textMappers[i]);
    textActors[i]->SetPosition(120, 16);
    renderers[i]->AddViewProp(textActors[i]);

    renWin->AddRenderer(renderers[i]);
  }

  int gridDimensions = 3;
  int rendererSize = 300;

  renWin->SetSize(
    rendererSize*gridDimensions, rendererSize*gridDimensions);

  for(int row = 0; row < gridDimensions; row++)
  {
    for(int col = 0; col < gridDimensions; col++)
    {
      int index = row * gridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] =
        {static_cast<double>(col) * rendererSize /
                              (gridDimensions * rendererSize),
         static_cast<double>(gridDimensions - (row+1)) * rendererSize /
                              (gridDimensions * rendererSize),
         static_cast<double>(col+1)*rendererSize /
                              (gridDimensions * rendererSize),
         static_cast<double>(gridDimensions - row) * rendererSize /
                              (gridDimensions * rendererSize)};

      if(index > int(actors.size()) - 1)
      {
        // Add a renderer even if there is no actor.
        // This makes the render window background all the same color.
        vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
        ren->SetBackground(colors->GetColor3d("BkgColor").GetData());
        ren->SetViewport(viewport);
        renWin->AddRenderer(ren);
        continue;
      }

      renderers[index]->SetViewport(viewport);
      renderers[index]->SetBackground(colors->GetColor3d("BkgColor").GetData());
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(-30);
      renderers[index]->GetActiveCamera()->Zoom(0.85);
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
vtkSmartPointer<vtkUnstructuredGrid> MakeHexagonalPrism()
{
  // 3D: hexagonal prism: a wedge with an hexagonal base.
  // Be careful, the base face ordering is different from wedge.

  int numberOfVertices = 12;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  points->InsertNextPoint(0.0, 0.0, 1.0);
  points->InsertNextPoint(1.0, 0.0, 1.0);
  points->InsertNextPoint(1.5, 0.5, 1.0);
  points->InsertNextPoint(1.0, 1.0, 1.0);
  points->InsertNextPoint(0.0, 1.0, 1.0);
  points->InsertNextPoint(-0.5, 0.5, 1.0);

  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(1.5, 0.5, 0.0);
  points->InsertNextPoint(1.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  points->InsertNextPoint(-0.5, 0.5, 0.0);

  vtkSmartPointer<vtkHexagonalPrism> hexagonalPrism =
    vtkSmartPointer<vtkHexagonalPrism>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
    hexagonalPrism->GetPointIds()->SetId(i, i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->InsertNextCell(hexagonalPrism->GetCellType(),
                     hexagonalPrism->GetPointIds());
  ug->SetPoints(points);

  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeHexahedron()
{
  // A regular hexagon (cube) with all faces square and three squares around
  // each vertex is created below.

  // Setup the coordinates of eight points
  // (the two faces must be in counter clockwise
  // order as viewed from the outside).

  // As an exercise you can modify the coordinates of the points to create
  // seven topologically distinct convex hexahedras.

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

vtkSmartPointer<vtkUnstructuredGrid> MakePentagonalPrism()
{

  int numberOfVertices = 10;

  // Create the points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(11, 10, 10);
  points->InsertNextPoint(13, 10, 10);
  points->InsertNextPoint(14, 12, 10);
  points->InsertNextPoint(12, 14, 10);
  points->InsertNextPoint(10, 12, 10);
  points->InsertNextPoint(11, 10, 14);
  points->InsertNextPoint(13, 10, 14);
  points->InsertNextPoint(14, 12, 14);
  points->InsertNextPoint(12, 14, 14);
  points->InsertNextPoint(10, 12, 14);

  // Pentagonal Prism
  vtkSmartPointer<vtkPentagonalPrism> pentagonalPrism =
    vtkSmartPointer<vtkPentagonalPrism>::New();
  for (int i = 0; i < numberOfVertices; ++i)
  {
    pentagonalPrism->GetPointIds()->SetId(i, i);
  }

  // Add the points and hexahedron to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(pentagonalPrism->GetCellType(),
                        pentagonalPrism->GetPointIds());

  return uGrid;
}

vtkSmartPointer<vtkUnstructuredGrid> MakePolyhedron()
{

  // Make a regular dodecahedron. It consists of twelve regular pentagonal
  // faces with three faces meeting at each vertex.
  int numberOfVertices = 20;
  int numberOfFaces = 12;
  int numberOfFaceVertices = 5;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint( 1.21412,   0,         1.58931);
  points->InsertNextPoint( 0.375185,  1.1547,    1.58931);
  points->InsertNextPoint(-0.982247,  0.713644,  1.58931);
  points->InsertNextPoint(-0.982247, -0.713644,  1.58931);
  points->InsertNextPoint( 0.375185, -1.1547,    1.58931);
  points->InsertNextPoint( 1.96449,   0,         0.375185);
  points->InsertNextPoint( 0.607062,  1.86835,   0.375185);
  points->InsertNextPoint(-1.58931,   1.1547,    0.375185);
  points->InsertNextPoint(-1.58931,  -1.1547,    0.375185);
  points->InsertNextPoint( 0.607062, -1.86835,   0.375185);
  points->InsertNextPoint( 1.58931,   1.1547,   -0.375185);
  points->InsertNextPoint(-0.607062,  1.86835,  -0.375185);
  points->InsertNextPoint(-1.96449,   0,        -0.375185);
  points->InsertNextPoint(-0.607062, -1.86835,  -0.375185);
  points->InsertNextPoint( 1.58931,  -1.1547,   -0.375185);
  points->InsertNextPoint( 0.982247,  0.713644, -1.58931);
  points->InsertNextPoint(-0.375185,  1.1547,   -1.58931);
  points->InsertNextPoint(-1.21412,   0,        -1.58931);
  points->InsertNextPoint(-0.375185, -1.1547,   -1.58931);
  points->InsertNextPoint( 0.982247, -0.713644, -1.58931);

  vtkIdType dodechedronPointsIds[20] =
      {0,   1,  2,  3,  4,  5,  6,  7,  8,  9,
       10, 11, 12, 13, 14, 15, 16, 17, 18, 19};


  vtkIdType dodechedronFace[12][5] = {
      {0, 1, 2, 3, 4},
      {0, 5, 10, 6, 1},
      {1, 6, 11, 7, 2},
      {2, 7, 12, 8, 3},
      {3, 8, 13, 9, 4},
      {4, 9, 14, 5, 0},
      {15, 10, 5, 14, 19},
      {16, 11, 6, 10, 15},
      {17, 12, 7, 11, 16},
      {18, 13, 8, 12, 17},
      {19, 14, 9, 13, 18},
      {19, 18, 17, 16, 15}
      };

  vtkNew<vtkIdList> dodechedronFaces;
  for (int i = 0; i < numberOfFaces; i++)
  {
    dodechedronFaces->InsertNextId(numberOfFaceVertices);
    for (int j = 0; j < numberOfFaceVertices; ++j)
    {
      dodechedronFaces->InsertNextId(dodechedronFace[i][j]);
    }
  }

  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->InsertNextCell(VTK_POLYHEDRON,
          numberOfVertices, dodechedronPointsIds,
        numberOfFaces, dodechedronFaces->GetPointer(0));
  uGrid->SetPoints(points);

  return uGrid;
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

vtkSmartPointer<vtkUnstructuredGrid> MakeTetrahedron()
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
}
