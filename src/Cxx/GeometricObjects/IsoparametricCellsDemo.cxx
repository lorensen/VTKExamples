#include <vtkSmartPointer.h>


#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>

#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>

#include <vtkSphereSource.h>
#include <vtkGlyph3DMapper.h>
#include <vtkLabeledDataMapper.h>

#include <vtkQuadraticEdge.h>
#include <vtkQuadraticTriangle.h>
#include <vtkQuadraticQuad.h>
#include <vtkQuadraticPolygon.h>
#include <vtkQuadraticTetra.h>
#include <vtkQuadraticHexahedron.h>
#include <vtkQuadraticWedge.h>
#include <vtkQuadraticPyramid.h>
#include <vtkBiQuadraticQuad.h>
#include <vtkTriQuadraticHexahedron.h>
#include <vtkQuadraticLinearQuad.h>
#include <vtkQuadraticLinearWedge.h>
#include <vtkBiQuadraticQuadraticWedge.h>
#include <vtkBiQuadraticQuadraticHexahedron.h>
#include <vtkBiQuadraticTriangle.h>
#include <vtkCubicLine.h>

#include <vtkNamedColors.h>

#include <vector>
#include <string>
#include <cstdlib>

// These functions return a vtkUnstructured grid corresponding to the object.
namespace
{

vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticEdge();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticTriangle();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticQuad();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticPolygon();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticTetra();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticHexahedron();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticWedge();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticPyramid();
vtkSmartPointer<vtkUnstructuredGrid> MakeBiQuadraticQuad();
vtkSmartPointer<vtkUnstructuredGrid> MakeTriQuadraticHexahedron();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticLinearQuad();
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticLinearWedge();
vtkSmartPointer<vtkUnstructuredGrid> MakeBiQuadraticQuadraticWedge();
vtkSmartPointer<vtkUnstructuredGrid> MakeBiQuadraticQuadraticHexahedron();
vtkSmartPointer<vtkUnstructuredGrid> MakeBiQuadraticTriangle();
vtkSmartPointer<vtkUnstructuredGrid> MakeCubicLine();
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

  uGrids.push_back(MakeQuadraticEdge());
  titles.push_back("VTK_QUADRATIC_EDGE (= 21)");
  uGrids.push_back(MakeQuadraticTriangle());
  titles.push_back("VTK_QUADRATIC_TRIANGLE (= 22)");
  uGrids.push_back(MakeQuadraticQuad());
  titles.push_back("VTK_QUADRATIC_QUAD (= 23)");
  uGrids.push_back(MakeQuadraticPolygon());
  titles.push_back("VTK_QUADRATIC_POLYGON (= 36)");
  uGrids.push_back(MakeQuadraticTetra());
  titles.push_back("VTK_QUADRATIC_TETRA (= 24)");
  uGrids.push_back(MakeQuadraticHexahedron());
  titles.push_back("VTK_QUADRATIC_HEXAHEDRON (= 25)");
  uGrids.push_back(MakeQuadraticWedge());
  titles.push_back("VTK_QUADRATIC_WEDGE (= 26)");
  uGrids.push_back(MakeQuadraticPyramid());
  titles.push_back("VTK_QUADRATIC_PYRAMID (= 27)");
  uGrids.push_back(MakeBiQuadraticQuad());
  titles.push_back("VTK_BIQUADRATIC_QUAD (= 28)");
  uGrids.push_back(MakeTriQuadraticHexahedron());
  titles.push_back("VTK_TRIQUADRATIC_HEXAHEDRON (= 29)");
  uGrids.push_back(MakeQuadraticLinearQuad());
  titles.push_back("VTK_QUADRATIC_LINEAR_QUAD (= 30)");
  uGrids.push_back(MakeQuadraticLinearWedge());
  titles.push_back("VTK_QUADRATIC_LINEAR_WEDGE (= 31)");
  uGrids.push_back(MakeBiQuadraticQuadraticWedge());
  titles.push_back("VTK_BIQUADRATIC_QUADRATIC_WEDGE (= 32)");
  uGrids.push_back(MakeBiQuadraticQuadraticHexahedron()); 
  titles.push_back("VTK_BIQUADRATIC_QUADRATIC_HEXAHEDRON (= 33)");
  uGrids.push_back(MakeBiQuadraticTriangle());
  titles.push_back("VTK_BIQUADRATIC_TRIANGLE (= 34)");
  uGrids.push_back(MakeCubicLine());
  titles.push_back("VTK_CUBIC_LINE (= 35)");

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetSize(600, 600);
  renWin->SetWindowName("Isoparametric Cell");

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
    std::cout << "Creating: " << titles[i] << std::endl;
    textMappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textActors.push_back(vtkSmartPointer<vtkActor2D>::New());

    textMappers[i]->GetTextProperty()->SetFontSize(10);
    textMappers[i]->GetTextProperty()->ShadowOn();
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
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticEdge()
{
  vtkSmartPointer<vtkQuadraticEdge> quadraticEdge =
    vtkSmartPointer<vtkQuadraticEdge>::New();
  double *pcoords = quadraticEdge->GetParametricCoords();
  for (int i = 0; i < quadraticEdge->GetNumberOfPoints(); ++i)
  {
    quadraticEdge->GetPointIds()->SetId(i, i);
    quadraticEdge->GetPoints()->SetPoint(i,
                                     *(pcoords + 3 * i),
                                     *(pcoords + 3 * i + 1),
                                     *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticEdge->GetPoints());
  ug->InsertNextCell(quadraticEdge->GetCellType(),quadraticEdge->GetPointIds());
  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticTriangle()
{
  vtkSmartPointer<vtkQuadraticTriangle> quadraticTriangle =
    vtkSmartPointer<vtkQuadraticTriangle>::New();
  double *pcoords = quadraticTriangle->GetParametricCoords();
  for (int i = 0; i < quadraticTriangle->GetNumberOfPoints(); ++i)
  {
    quadraticTriangle->GetPointIds()->SetId(i, i);
    quadraticTriangle->GetPoints()->SetPoint(i,
                                     *(pcoords + 3 * i),
                                     *(pcoords + 3 * i + 1),
                                     *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticTriangle->GetPoints());
  ug->InsertNextCell(quadraticTriangle->GetCellType(),quadraticTriangle->GetPointIds());
  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticQuad()
{
  vtkSmartPointer<vtkQuadraticQuad> quadraticQuad =
    vtkSmartPointer<vtkQuadraticQuad>::New();
  double *pcoords = quadraticQuad->GetParametricCoords();
  for (int i = 0; i < 8; ++i)
  {
    quadraticQuad->GetPointIds()->SetId(i, i);
    quadraticQuad->GetPoints()->SetPoint(i,
                                         *(pcoords + 3 * i),
                                         *(pcoords + 3 * i + 1),
                                         *(pcoords + 3 * i + 2));
  }
  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticQuad->GetPoints());
  ug->InsertNextCell(quadraticQuad->GetCellType(),quadraticQuad->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticPolygon()
{
  vtkSmartPointer<vtkQuadraticPolygon> quadraticPolygon =
    vtkSmartPointer<vtkQuadraticPolygon>::New();

  quadraticPolygon->GetPointIds()->SetNumberOfIds(8);
  quadraticPolygon->GetPointIds()->SetId(0,0);
  quadraticPolygon->GetPointIds()->SetId(1,1);
  quadraticPolygon->GetPointIds()->SetId(2,2);
  quadraticPolygon->GetPointIds()->SetId(3,3);
  quadraticPolygon->GetPointIds()->SetId(4,4);
  quadraticPolygon->GetPointIds()->SetId(5,5);
  quadraticPolygon->GetPointIds()->SetId(6,6);
  quadraticPolygon->GetPointIds()->SetId(7,7);

  quadraticPolygon->GetPoints()->SetNumberOfPoints(8);
  quadraticPolygon->GetPoints()->SetPoint(0, 0.0, 0.0, 0.0);
  quadraticPolygon->GetPoints()->SetPoint(1, 2.0, 0.0, 0.0);
  quadraticPolygon->GetPoints()->SetPoint(2, 2.0, 2.0, 0.0);
  quadraticPolygon->GetPoints()->SetPoint(3, 0.0, 2.0, 0.0);
  quadraticPolygon->GetPoints()->SetPoint(4, 1.0, 0.0, 0.0);
  quadraticPolygon->GetPoints()->SetPoint(5, 2.0, 1.0, 0.0);
  quadraticPolygon->GetPoints()->SetPoint(6, 1.0, 2.0, 0.0);
  quadraticPolygon->GetPoints()->SetPoint(7, 0.0, 1.0, 0.0);
  quadraticPolygon->GetPoints()->SetPoint(5, 3.0, 1.0, 0.0);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticPolygon->GetPoints());
  ug->InsertNextCell(quadraticPolygon->GetCellType(),quadraticPolygon->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticTetra()
{
  vtkSmartPointer<vtkQuadraticTetra> quadraticTetra =
    vtkSmartPointer<vtkQuadraticTetra>::New();
  double *pcoords = quadraticTetra->GetParametricCoords();
  for (int i = 0; i < 10; ++i)
  {
    quadraticTetra->GetPointIds()->SetId(i, i);
    quadraticTetra->GetPoints()->SetPoint(i,
                                  *(pcoords + 3 * i),
                                 *(pcoords + 3 * i + 1),
                                 *(pcoords + 3 * i + 2));
  }
  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticTetra->GetPoints());
  ug->InsertNextCell(quadraticTetra->GetCellType(),quadraticTetra->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticHexahedron()
{
  vtkSmartPointer<vtkQuadraticHexahedron> quadraticHexahedron =
    vtkSmartPointer<vtkQuadraticHexahedron>::New();
  double *pcoords = quadraticHexahedron->GetParametricCoords();
  for (int i = 0; i < quadraticHexahedron->GetNumberOfPoints(); ++i)
  {
    quadraticHexahedron->GetPointIds()->SetId(i, i);
    quadraticHexahedron->GetPoints()->SetPoint(i,
                                       *(pcoords + 3 * i),
                                       *(pcoords + 3 * i + 1),
                                       *(pcoords + 3 * i + 2));
  }
  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticHexahedron->GetPoints());
  ug->InsertNextCell(quadraticHexahedron->GetCellType(),quadraticHexahedron->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticWedge()
{
  vtkSmartPointer<vtkQuadraticWedge> quadraticWedge =
    vtkSmartPointer<vtkQuadraticWedge>::New();
  double *pcoords = quadraticWedge->GetParametricCoords();
  for (int i = 0; i < quadraticWedge->GetNumberOfPoints(); ++i)
  {
    quadraticWedge->GetPointIds()->SetId(i, i);
    quadraticWedge->GetPoints()->SetPoint(i,
                                  *(pcoords + 3 * i),
                                  *(pcoords + 3 * i + 1),
                                  *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticWedge->GetPoints());
  ug->InsertNextCell(quadraticWedge->GetCellType(),quadraticWedge->GetPointIds());
  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticPyramid()
{
  vtkSmartPointer<vtkQuadraticPyramid> quadraticPyramid =
    vtkSmartPointer<vtkQuadraticPyramid>::New();
  double *pcoords = quadraticPyramid->GetParametricCoords();
  for (int i = 0; i < quadraticPyramid->GetNumberOfPoints(); ++i)
  {
    quadraticPyramid->GetPointIds()->SetId(i, i);
    quadraticPyramid->GetPoints()->SetPoint(i,
                                  *(pcoords + 3 * i),
                                  *(pcoords + 3 * i + 1),
                                  *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticPyramid->GetPoints());
  ug->InsertNextCell(quadraticPyramid->GetCellType(),quadraticPyramid->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeBiQuadraticQuad()
{
  vtkSmartPointer<vtkBiQuadraticQuad> biQuadraticQuad =
    vtkSmartPointer<vtkBiQuadraticQuad>::New();
  double *pcoords = biQuadraticQuad->GetParametricCoords();
  for (int i = 0; i < biQuadraticQuad->GetNumberOfPoints(); ++i)
  {
    biQuadraticQuad->GetPointIds()->SetId(i, i);
    biQuadraticQuad->GetPoints()->SetPoint(i,
                                 *(pcoords + 3 * i),
                                 *(pcoords + 3 * i + 1),
                                 *(pcoords + 3 * i + 2));
  }
  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(biQuadraticQuad->GetPoints());
  ug->InsertNextCell(biQuadraticQuad->GetCellType(),biQuadraticQuad->GetPointIds());
  return ug;
}

vtkSmartPointer<vtkUnstructuredGrid> MakeTriQuadraticHexahedron()
{
  vtkSmartPointer<vtkTriQuadraticHexahedron> triQuadraticHexahedron =
    vtkSmartPointer<vtkTriQuadraticHexahedron>::New();
  double *pcoords = triQuadraticHexahedron->GetParametricCoords();
  for (int i = 0; i < triQuadraticHexahedron->GetNumberOfPoints(); ++i)
  {
    triQuadraticHexahedron->GetPointIds()->SetId(i, i);
    triQuadraticHexahedron->GetPoints()->SetPoint(i,
                                       *(pcoords + 3 * i),
                                       *(pcoords + 3 * i + 1),
                                       *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(triQuadraticHexahedron->GetPoints());
  ug->InsertNextCell(triQuadraticHexahedron->GetCellType(),triQuadraticHexahedron->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticLinearQuad()
{
  vtkSmartPointer<vtkQuadraticLinearQuad> quadraticLinearQuad =
    vtkSmartPointer<vtkQuadraticLinearQuad>::New();
  double *pcoords = quadraticLinearQuad->GetParametricCoords();
  for (int i = 0; i < quadraticLinearQuad->GetNumberOfPoints(); ++i)
  {
    quadraticLinearQuad->GetPointIds()->SetId(i, i);
    quadraticLinearQuad->GetPoints()->SetPoint(i,
                                       *(pcoords + 3 * i),
                                       *(pcoords + 3 * i + 1),
                                       *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticLinearQuad->GetPoints());
  ug->InsertNextCell(quadraticLinearQuad->GetCellType(),quadraticLinearQuad->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticLinearWedge()
{
  vtkSmartPointer<vtkQuadraticLinearWedge> quadraticLinearWedge =
    vtkSmartPointer<vtkQuadraticLinearWedge>::New();
  double *pcoords = quadraticLinearWedge->GetParametricCoords();
  for (int i = 0; i < 12; ++i)
  {
    quadraticLinearWedge->GetPointIds()->SetId(i, i);
    quadraticLinearWedge->GetPoints()->SetPoint(i,
                                       *(pcoords + 3 * i),
                                       *(pcoords + 3 * i + 1),
                                       *(pcoords + 3 * i + 2));
  }
  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(quadraticLinearWedge->GetPoints());
  ug->InsertNextCell(quadraticLinearWedge->GetCellType(),quadraticLinearWedge->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeBiQuadraticQuadraticWedge()
{
  vtkSmartPointer<vtkBiQuadraticQuadraticWedge> biQuadraticQuadraticWedge =
    vtkSmartPointer<vtkBiQuadraticQuadraticWedge>::New();
  double *pcoords = biQuadraticQuadraticWedge->GetParametricCoords();
  for (int i = 0; i < biQuadraticQuadraticWedge->GetNumberOfPoints(); ++i)
  {
    biQuadraticQuadraticWedge->GetPointIds()->SetId(i, i);
    biQuadraticQuadraticWedge->GetPoints()->SetPoint(i,
                                  *(pcoords + 3 * i),
                                  *(pcoords + 3 * i + 1),
                                  *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(biQuadraticQuadraticWedge->GetPoints());
  ug->InsertNextCell(biQuadraticQuadraticWedge->GetCellType(),biQuadraticQuadraticWedge->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeBiQuadraticQuadraticHexahedron()
{
  vtkSmartPointer<vtkBiQuadraticQuadraticHexahedron> biQuadraticQuadraticHexahedron =
    vtkSmartPointer<vtkBiQuadraticQuadraticHexahedron>::New();
  double *pcoords = biQuadraticQuadraticHexahedron->GetParametricCoords();
  for (int i = 0; i < biQuadraticQuadraticHexahedron->GetNumberOfPoints(); ++i)
  {
    biQuadraticQuadraticHexahedron->GetPointIds()->SetId(i, i);
    biQuadraticQuadraticHexahedron->GetPoints()->SetPoint(i,
                                       *(pcoords + 3 * i),
                                       *(pcoords + 3 * i + 1),
                                       *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(biQuadraticQuadraticHexahedron->GetPoints());
  ug->InsertNextCell(biQuadraticQuadraticHexahedron->GetCellType(),biQuadraticQuadraticHexahedron->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeBiQuadraticTriangle()
{
  vtkSmartPointer<vtkQuadraticTriangle> biQuadraticTriangle =
    vtkSmartPointer<vtkQuadraticTriangle>::New();
  double *pcoords = biQuadraticTriangle->GetParametricCoords();
  for (int i = 0; i < biQuadraticTriangle->GetNumberOfPoints(); ++i)
  {
    biQuadraticTriangle->GetPointIds()->SetId(i, i);
    biQuadraticTriangle->GetPoints()->SetPoint(i,
                                     *(pcoords + 3 * i),
                                     *(pcoords + 3 * i + 1),
                                     *(pcoords + 3 * i + 2));
  }
  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(biQuadraticTriangle->GetPoints());
  ug->InsertNextCell(biQuadraticTriangle->GetCellType(),biQuadraticTriangle->GetPointIds());
  return ug;
}
vtkSmartPointer<vtkUnstructuredGrid> MakeCubicLine()
{
  vtkSmartPointer<vtkCubicLine> cubicLine =
    vtkSmartPointer<vtkCubicLine>::New();
  double *pcoords = cubicLine->GetParametricCoords();
  for (int i = 0; i < cubicLine->GetNumberOfPoints(); ++i)
  {
    cubicLine->GetPointIds()->SetId(i, i);
    cubicLine->GetPoints()->SetPoint(i,
                                 *(pcoords + 3 * i),
                                 *(pcoords + 3 * i + 1),
                                 *(pcoords + 3 * i + 2));
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(cubicLine->GetPoints());
  ug->InsertNextCell(cubicLine->GetCellType(),cubicLine->GetPointIds());
  return ug;
}
}
