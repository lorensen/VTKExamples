#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>

#include <vtkHexagonalPrism.h>
#include <vtkHexahedron.h>
#include <vtkPentagonalPrism.h>
#include <vtkPolyhedron.h>
#include <vtkPyramid.h>
#include <vtkTetra.h>
#include <vtkVoxel.h>
#include <vtkWedge.h>

#include <vector>

void CreateHexagonalPrismActor(vtkActor* actor);
void CreateHexahedronActor(vtkActor* actor);
void CreatePentagonalPrismActor(vtkActor* actor);
void CreatePolyhedronActor(vtkActor* actor);
void CreatePyramidActor(vtkActor* actor);
void CreateTetraActor(vtkActor* actor);
void CreateVoxelActor(vtkActor* actor);
void CreateWedgeActor(vtkActor* actor);

int main(int, char *[])
{
  std::vector<vtkSmartPointer<vtkActor> > actors;

  vtkSmartPointer<vtkActor> hexagonalPrismActor =
    vtkSmartPointer<vtkActor>::New();
  CreateHexagonalPrismActor(hexagonalPrismActor);
  actors.push_back(hexagonalPrismActor);

  vtkSmartPointer<vtkActor> hexahedronActor =
    vtkSmartPointer<vtkActor>::New();
  CreateHexahedronActor(hexahedronActor);
  actors.push_back(hexahedronActor);

  vtkSmartPointer<vtkActor> pentagonalPrismActor =
    vtkSmartPointer<vtkActor>::New();
  CreatePentagonalPrismActor(pentagonalPrismActor);
  actors.push_back(pentagonalPrismActor);

  vtkSmartPointer<vtkActor> polyhedronActor =
    vtkSmartPointer<vtkActor>::New();
  CreatePolyhedronActor(polyhedronActor);
  actors.push_back(polyhedronActor);

  vtkSmartPointer<vtkActor> pyramidActor =
    vtkSmartPointer<vtkActor>::New();
  CreatePyramidActor(pyramidActor);
  actors.push_back(pyramidActor);

  vtkSmartPointer<vtkActor> tetraActor =
    vtkSmartPointer<vtkActor>::New();
  CreateTetraActor(tetraActor);
  actors.push_back(tetraActor);

    vtkSmartPointer<vtkActor> voxelActor =
    vtkSmartPointer<vtkActor>::New();
  CreateVoxelActor(voxelActor);
  actors.push_back(voxelActor);

  vtkSmartPointer<vtkActor> wedgeActor =
    vtkSmartPointer<vtkActor>::New();
  CreateWedgeActor(wedgeActor);
  actors.push_back(wedgeActor);

  std::vector<vtkSmartPointer<vtkRenderer> > renderers;

  for(unsigned int i = 0; i < actors.size(); i++)
  {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }

  int gridDimensions = 3;
  int rendererSize = 200;

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(
    rendererSize*gridDimensions, rendererSize*gridDimensions);

  for(unsigned int row = 0; row < gridDimensions; row++)
  {
    for(unsigned int col = 0; col < gridDimensions; col++)
    {
      int index = row * gridDimensions + col;

      if(index > actors.size() - 1)
      {
        continue;
      }

      // (xmin, ymin, xmax, ymax)
      double viewport[4] =
        {static_cast<double>(col) * rendererSize / (gridDimensions * rendererSize),
         static_cast<double>(gridDimensions - (row+1)) * rendererSize / (gridDimensions * rendererSize),
         static_cast<double>(col+1)*rendererSize / (gridDimensions * rendererSize),
         static_cast<double>(gridDimensions - row) * rendererSize / (gridDimensions * rendererSize)};

      renderWindow->AddRenderer(renderers[index]);
      renderers[index]->SetViewport(viewport);
      renderers[index]->AddActor(actors[index]);
      //renderers[index]->AddActor(textactors[index]);
      renderers[index]->SetBackground(.2, .3, .4);
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(-30);
      renderers[index]->ResetCameraClippingRange();
    }
  }


  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CreateHexagonalPrismActor(vtkActor* actor)
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.5, 0.0, 0.3);
  points->InsertNextPoint(0.93, 0.25, 0.3);
  points->InsertNextPoint(0.93, 0.75, 0.3);
  points->InsertNextPoint(0.716, 0.875, 0.4);
  points->InsertNextPoint(0.55, 0.95, 0.3);
  points->InsertNextPoint(0.067, 0.6, 0.1);
  points->InsertNextPoint(0.05, 0.4, 0.7);
  points->InsertNextPoint(0.5, 0.6, 0.7);
  points->InsertNextPoint(0.93, 0.4, 0.7);
  points->InsertNextPoint(0.93, 0.9, 0.7);
  points->InsertNextPoint(0.06, 0.7, 0.7);
  points->InsertNextPoint(0.07, 0.3, 0.7);

  vtkSmartPointer<vtkHexagonalPrism> hexagonalPrism =
    vtkSmartPointer<vtkHexagonalPrism>::New();
  hexagonalPrism->GetPointIds()->SetNumberOfIds(12);
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
  hexagonalPrism->GetPointIds()->SetId(10,12);
  hexagonalPrism->GetPointIds()->SetId(11,11);

  // Add the hexahedron to a cell array
  vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
  cellArray->InsertNextCell(hexagonalPrism);

  // Add the points and hexahedron to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(hexagonalPrism->GetCellType(), hexagonalPrism->GetPointIds());

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(uGrid->GetProducerPort());

  actor->SetMapper(mapper);
}


void CreateHexahedronActor(vtkActor* actor)
{
  // Setup the coordinates of eight points
  // (the two faces must be in counter clockwise order as viewd from the outside)

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
  hex->GetPointIds()->SetId(0,0);
  hex->GetPointIds()->SetId(1,1);
  hex->GetPointIds()->SetId(2,2);
  hex->GetPointIds()->SetId(3,3);
  hex->GetPointIds()->SetId(4,4);
  hex->GetPointIds()->SetId(5,5);
  hex->GetPointIds()->SetId(6,6);
  hex->GetPointIds()->SetId(7,7);

  // Add the hexahedron to a cell array
  vtkSmartPointer<vtkCellArray> hexs =
    vtkSmartPointer<vtkCellArray>::New();
  hexs->InsertNextCell(hex);

  // Add the points and hexahedron to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(uGrid->GetProducerPort());

  actor->SetMapper(mapper);
}

void CreatePentagonalPrismActor(vtkActor* actor)
{
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

  vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
  cellArray->InsertNextCell(pentagonalPrism);

  // Add the points and hexahedron to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(pentagonalPrism->GetCellType(), pentagonalPrism->GetPointIds());

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(uGrid->GetProducerPort());

  actor->SetMapper(mapper);

}

void CreatePolyhedronActor(vtkActor* actor)
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1.21412, 0, 1.58931);
  points->InsertNextPoint(0.375185,   1.1547,     1.58931);
  points->InsertNextPoint(-0.982247,  0.713644,   1.58931);
  points->InsertNextPoint(-0.982247,  -0.713644,  1.58931);
  points->InsertNextPoint(0.375185,   -1.1547,    1.58931);
  points->InsertNextPoint(1.96449,    0,          0.375185);
  points->InsertNextPoint(0.607062,   1.86835,    0.375185);
  points->InsertNextPoint(-1.58931,   1.1547,     0.375185);
  points->InsertNextPoint(-1.58931,   -1.1547,    0.375185);
  points->InsertNextPoint(0.607062,   -1.86835,   0.375185);
  points->InsertNextPoint(1.58931,    1.1547,     -0.375185);
  points->InsertNextPoint(-0.607062,  1.86835,    -0.375185);
  points->InsertNextPoint(-1.96449,   0,          -0.375185);
  points->InsertNextPoint(-0.607062,  -1.86835,   -0.375185);
  points->InsertNextPoint(1.58931,    -1.1547,    -0.375185);
  points->InsertNextPoint(0.982247,   0.713644,   -1.58931);
  points->InsertNextPoint(-0.375185,  1.1547,     -1.58931);
  points->InsertNextPoint(-1.21412,   0,          -1.58931);
  points->InsertNextPoint(-0.375185,  -1.1547,    -1.58931);
  points->InsertNextPoint(0.982247,   -0.713644,  -1.58931);

  vtkSmartPointer<vtkPolyhedron> polyhedron =
    vtkSmartPointer<vtkPolyhedron>::New();
  polyhedron->GetPointIds()->SetNumberOfIds(20);
  polyhedron->GetPointIds()->SetId(0,0);
  polyhedron->GetPointIds()->SetId(1,1);
  polyhedron->GetPointIds()->SetId(2,2);
  polyhedron->GetPointIds()->SetId(3,3);
  polyhedron->GetPointIds()->SetId(4,4);
  polyhedron->GetPointIds()->SetId(5,5);
  polyhedron->GetPointIds()->SetId(6,6);
  polyhedron->GetPointIds()->SetId(7,7);
  polyhedron->GetPointIds()->SetId(8,8);
  polyhedron->GetPointIds()->SetId(9,9);
  polyhedron->GetPointIds()->SetId(10,10);
  polyhedron->GetPointIds()->SetId(11,11);
  polyhedron->GetPointIds()->SetId(12,12);
  polyhedron->GetPointIds()->SetId(13,13);
  polyhedron->GetPointIds()->SetId(14,14);
  polyhedron->GetPointIds()->SetId(15,15);
  polyhedron->GetPointIds()->SetId(16,16);
  polyhedron->GetPointIds()->SetId(17,17);
  polyhedron->GetPointIds()->SetId(18,18);
  polyhedron->GetPointIds()->SetId(19,19);


  vtkIdType dodechedronPointsIds[20] = {0,   1,  2,  3,  4,  5,  6,  7,  8,  9,
                                        10, 11, 12, 13, 14, 15, 16, 17, 18, 19};


  vtkIdType dodechedronFace[12][5] = {{0, 1, 2, 3, 4},
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
  {19, 18, 17, 16, 15}};

  vtkSmartPointer<vtkCellArray> dodechedronFaces =
    vtkSmartPointer<vtkCellArray>::New();
  for (int i = 0; i < 12; i++)
  {
  dodechedronFaces->InsertNextCell(5, dodechedronFace[i]);
  }

  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();

  uGrid->InsertNextCell(VTK_POLYHEDRON, 20, dodechedronPointsIds,
        12, dodechedronFaces->GetPointer());

  /* doesn't work
  vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
  cellArray->InsertNextCell(polyhedron);

  // Add the points and hexahedron to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(polyhedron->GetCellType(), polyhedron->GetPointIds());
  */

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(uGrid->GetProducerPort());

  actor->SetMapper(mapper);
}

void CreatePyramidActor(vtkActor* actor)
{
  vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();

  float p0[3] = {1.0, 1.0, 1.0};
  float p1[3] = {-1.0, 1.0, 1.0};
  float p2[3] = {-1.0, -1.0, 1.0};
  float p3[3] = {1.0, -1.0, 1.0};
  float p4[3] = {0.0, 0.0, 0.0};

  points->InsertNextPoint(p0);
  points->InsertNextPoint(p1);
  points->InsertNextPoint(p2);
  points->InsertNextPoint(p3);
  points->InsertNextPoint(p4);

  vtkSmartPointer<vtkPyramid> pyramid =
      vtkSmartPointer<vtkPyramid>::New();
  pyramid->GetPointIds()->SetId(0,0);
  pyramid->GetPointIds()->SetId(1,1);
  pyramid->GetPointIds()->SetId(2,2);
  pyramid->GetPointIds()->SetId(3,3);
  pyramid->GetPointIds()->SetId(4,4);

  vtkSmartPointer<vtkCellArray> cells =
      vtkSmartPointer<vtkCellArray>::New();
  cells->InsertNextCell (pyramid);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
      vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(pyramid->GetCellType(),pyramid->GetPointIds());

  //Create an actor and mapper
  vtkSmartPointer<vtkDataSetMapper> mapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInput(ug);

  actor->SetMapper(mapper);
}

void CreateTetraActor(vtkActor* actor)
{
  vtkSmartPointer< vtkPoints > points =
    vtkSmartPointer< vtkPoints > :: New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);
  points->InsertNextPoint(1, 1, 0);
  points->InsertNextPoint(0, 1, 1);
  points->InsertNextPoint(5, 5, 5);
  points->InsertNextPoint(6, 5, 5);
  points->InsertNextPoint(6, 6, 5);
  points->InsertNextPoint(5, 6, 6);

  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructuredGrid->SetPoints(points);

  vtkSmartPointer<vtkTetra> tetra =
    vtkSmartPointer<vtkTetra>::New();
  tetra->GetPointIds()->SetId(0, 0);
  tetra->GetPointIds()->SetId(1, 1);
  tetra->GetPointIds()->SetId(2, 2);
  tetra->GetPointIds()->SetId(3, 3);

  vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
  cellArray->InsertNextCell(tetra);
  unstructuredGrid->SetCells(VTK_TETRA, cellArray);

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(unstructuredGrid->GetProducerPort());

  actor->SetMapper(mapper);
}

void CreateVoxelActor(vtkActor* actor)
{
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
  voxel->GetPointIds()->SetId(0, 0);
  voxel->GetPointIds()->SetId(1, 1);
  voxel->GetPointIds()->SetId(2, 2);
  voxel->GetPointIds()->SetId(3, 3);
  voxel->GetPointIds()->SetId(4, 4);
  voxel->GetPointIds()->SetId(5, 5);
  voxel->GetPointIds()->SetId(6, 6);
  voxel->GetPointIds()->SetId(7, 7);

  vtkSmartPointer<vtkCellArray> cells =
    vtkSmartPointer<vtkCellArray>::New();
  cells->InsertNextCell(voxel);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(voxel->GetCellType(),voxel->GetPointIds());

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInput(ug);

  actor->SetMapper(mapper);
}

void CreateWedgeActor(vtkActor* actor)
{
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
  wedge->GetPointIds()->SetId(0,0);
  wedge->GetPointIds()->SetId(1,1);
  wedge->GetPointIds()->SetId(2,2);
  wedge->GetPointIds()->SetId(3,3);
  wedge->GetPointIds()->SetId(4,4);
  wedge->GetPointIds()->SetId(5,5);

  vtkSmartPointer<vtkCellArray> cells =
    vtkSmartPointer<vtkCellArray>::New();
  cells->InsertNextCell(wedge);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(wedge->GetCellType(),wedge->GetPointIds());

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInput(ug);

  actor->SetMapper(mapper);
}
