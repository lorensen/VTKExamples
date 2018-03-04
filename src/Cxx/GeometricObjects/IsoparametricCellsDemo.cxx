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
#include <vtkTextProperty.h>
#include <vtkUnstructuredGrid.h>

#include <vtkBiQuadraticQuad.h>
#include <vtkBiQuadraticQuadraticHexahedron.h>
#include <vtkBiQuadraticQuadraticWedge.h>
#include <vtkBiQuadraticTriangle.h>
#include <vtkCubicLine.h>
#include <vtkQuadraticEdge.h>
#include <vtkQuadraticHexahedron.h>
#include <vtkQuadraticLinearQuad.h>
#include <vtkQuadraticLinearWedge.h>
#include <vtkQuadraticPolygon.h>
#include <vtkQuadraticPyramid.h>
#include <vtkQuadraticQuad.h>
#include <vtkQuadraticTetra.h>
#include <vtkQuadraticTriangle.h>
#include <vtkQuadraticWedge.h>
#include <vtkTriQuadraticHexahedron.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>
#include <vector>

// These functions return a vtkUnstructured grid corresponding to the object.
namespace
{
template<typename T> vtkSmartPointer<vtkUnstructuredGrid> MakeUnstructuredGrid(vtkSmartPointer<T>);
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticPolygon();
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

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuadraticEdge>::New()));
  titles.push_back("VTK_QUADRATIC_EDGE (= 21)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuadraticTriangle>::New()));
  titles.push_back("VTK_QUADRATIC_TRIANGLE (= 22)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuadraticQuad>::New()));
  titles.push_back("VTK_QUADRATIC_QUAD (= 23)");

  uGrids.push_back(MakeQuadraticPolygon());
  titles.push_back("VTK_QUADRATIC_POLYGON (= 36)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuadraticTetra>::New()));
  titles.push_back("VTK_QUADRATIC_TETRA (= 24)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuadraticHexahedron>::New()));
  titles.push_back("VTK_QUADRATIC_HEXAHEDRON (= 25)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuadraticWedge>::New()));
  titles.push_back("VTK_QUADRATIC_WEDGE (= 26)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuadraticPyramid>::New()));
  titles.push_back("VTK_QUADRATIC_PYRAMID (= 27)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkBiQuadraticQuad>::New()));
  titles.push_back("VTK_BIQUADRATIC_QUAD (= 28)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkTriQuadraticHexahedron>::New()));
  titles.push_back("VTK_TRIQUADRATIC_HEXAHEDRON (= 29)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuadraticLinearQuad>::New()));
  titles.push_back("VTK_QUADRATIC_LINEAR_QUAD (= 30)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkQuadraticLinearWedge>::New()));
  titles.push_back("VTK_QUADRATIC_LINEAR_WEDGE (= 31)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkBiQuadraticQuadraticWedge>::New()));
  titles.push_back("VTK_BIQUADRATIC_QUADRATIC_WEDGE (= 32)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkBiQuadraticQuadraticHexahedron>::New()));
  titles.push_back("VTK_BIQUADRATIC_QUADRATIC_HEXAHEDRON (= 33)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkBiQuadraticTriangle>::New()));
  titles.push_back("VTK_BIQUADRATIC_TRIANGLE (= 34)");

  uGrids.push_back(MakeUnstructuredGrid(
                     vtkSmartPointer<vtkCubicLine>::New()));
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
        static_cast<double>(col) / xGridDimensions,
        static_cast<double>(yGridDimensions - (row + 1))/ yGridDimensions,
        static_cast<double>(col + 1) / xGridDimensions,
        static_cast<double>(yGridDimensions - row) / yGridDimensions
      };

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
}
