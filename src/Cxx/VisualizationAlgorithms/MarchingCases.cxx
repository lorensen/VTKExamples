#include <vtkContourFilter.h>
#include <vtkCubeSource.h>
#include <vtkExtractEdges.h>
#include <vtkFloatArray.h>
#include <vtkGlyph3D.h>
#include <vtkIdList.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPointData.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShrinkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkThresholdPoints.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTubeFilter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVectorText.h>

#include <map>

namespace
{
void case1 (vtkFloatArray *, vtkVectorText *, int, int);
void case2 (vtkFloatArray *, vtkVectorText *, int, int);
void case3 (vtkFloatArray *, vtkVectorText *, int, int);
void case4 (vtkFloatArray *, vtkVectorText *, int, int);
void case5 (vtkFloatArray *, vtkVectorText *, int, int);
void case6 (vtkFloatArray *, vtkVectorText *, int, int);
void case7 (vtkFloatArray *, vtkVectorText *, int, int);
void case8 (vtkFloatArray *, vtkVectorText *, int, int);
void case9 (vtkFloatArray *, vtkVectorText *, int, int);
void case10(vtkFloatArray *, vtkVectorText *, int, int);
void case11(vtkFloatArray *, vtkVectorText *, int, int);
void case12(vtkFloatArray *, vtkVectorText *, int, int);
void case13(vtkFloatArray *, vtkVectorText *, int, int);
void case14(vtkFloatArray *, vtkVectorText *, int, int);
}

int main (int argc, char *argv[])
{
  std::map<int, void (*)(vtkFloatArray*, vtkVectorText*, int, int)> cases;
  cases[1]  = &case1;
  cases[2]  = &case2;
  cases[3]  = &case3;
  cases[4]  = &case4;
  cases[5]  = &case5;
  cases[6]  = &case6;
  cases[7]  = &case7;
  cases[8]  = &case8;
  cases[9]  = &case9;
  cases[10] = &case10;
  cases[11] = &case11;
  cases[12] = &case12;
  cases[13] = &case13;
  cases[14] = &case14;

  std::vector<int> mcCases;
  int mcCase = 12;
  std::cout << "argc is " << argc << std::endl;
  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      mcCase = atoi(argv[i]);
      if (std::abs(mcCase) < 1 || std::abs(mcCase) > 14)
      {
        std::cout << argv[0] << " bad case number " << mcCase << std::endl;
        return EXIT_FAILURE;
      }
      mcCases.push_back(mcCase);
    }
  }
  else
  {
    mcCases.push_back(12);
  }

  vtkSmartPointer<vtkNamedColors> color =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetSize(640, 480);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  std::vector<vtkSmartPointer<vtkRenderer>> renderers;
  int gridSize = ((mcCases.size() + 3) / 4) * 4;
  gridSize = mcCases.size() < 4 ? mcCases.size() : gridSize;
  std::cout << "gridSize: " << gridSize << std::endl;
  for (int i = 0; i < gridSize; ++i)
  {
    // Create the Renderer
    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    renderers.push_back(renderer);
    renWin->AddRenderer(renderer);
  }

  for (size_t i = 0; i < mcCases.size(); ++i)
  {
    // Define a Single Cube
    vtkSmartPointer<vtkFloatArray> Scalars =
      vtkSmartPointer<vtkFloatArray>::New();
    Scalars->InsertNextValue(1.0);
    Scalars->InsertNextValue(0.0);
    Scalars->InsertNextValue(0.0);
    Scalars->InsertNextValue(1.0);
    Scalars->InsertNextValue(0.0);
    Scalars->InsertNextValue(0.0);
    Scalars->InsertNextValue(0.0);
    Scalars->InsertNextValue(0.0);

    vtkSmartPointer<vtkPoints> Points =
      vtkSmartPointer<vtkPoints>::New();
    Points->InsertNextPoint(0, 0, 0);
    Points->InsertNextPoint(1, 0, 0);
    Points->InsertNextPoint(1, 1, 0);
    Points->InsertNextPoint(0, 1, 0);
    Points->InsertNextPoint(0, 0, 1);
    Points->InsertNextPoint(1, 0, 1);
    Points->InsertNextPoint(1, 1, 1);
    Points->InsertNextPoint(0, 1, 1);

    vtkSmartPointer<vtkIdList> Ids =
      vtkSmartPointer<vtkIdList>::New();
    Ids->InsertNextId(0);
    Ids->InsertNextId(1);
    Ids->InsertNextId(2);
    Ids->InsertNextId(3);
    Ids->InsertNextId(4);
    Ids->InsertNextId(5);
    Ids->InsertNextId(6);
    Ids->InsertNextId(7);

    vtkSmartPointer<vtkUnstructuredGrid> Grid =
      vtkSmartPointer<vtkUnstructuredGrid>::New();
    Grid->Allocate(10, 10);
    Grid->InsertNextCell(12, Ids);
    Grid->SetPoints(Points);
    Grid->GetPointData()->SetScalars(Scalars);

  // Find the triangles that lie along the 0.5 contour in this cube.
    vtkSmartPointer<vtkContourFilter> Marching =
      vtkSmartPointer<vtkContourFilter>::New();
    Marching->SetInputData(Grid);
    Marching->SetValue(0, 0.5);
    Marching->Update();

  // Extract the edges of the triangles just found.
    vtkSmartPointer<vtkExtractEdges> triangleEdges =
      vtkSmartPointer<vtkExtractEdges>::New();
    triangleEdges->SetInputConnection(Marching->GetOutputPort());

  // Draw the edges as tubes instead of lines.  Also create the associated
  // mapper and actor to display the tubes.
    vtkSmartPointer<vtkTubeFilter> triangleEdgeTubes =
      vtkSmartPointer<vtkTubeFilter>::New();
    triangleEdgeTubes->SetInputConnection(triangleEdges->GetOutputPort());
    triangleEdgeTubes->SetRadius(.005);
    triangleEdgeTubes->SetNumberOfSides(6);
    triangleEdgeTubes->UseDefaultNormalOn();
    triangleEdgeTubes->SetDefaultNormal(.577, .577, .577);

    vtkSmartPointer<vtkPolyDataMapper> triangleEdgeMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    triangleEdgeMapper->SetInputConnection(triangleEdgeTubes->GetOutputPort());
    triangleEdgeMapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> triangleEdgeActor =
      vtkSmartPointer<vtkActor>::New();
    triangleEdgeActor->SetMapper(triangleEdgeMapper);
    triangleEdgeActor->GetProperty()->SetDiffuseColor(
      color->GetColor3d("lamp_black").GetData());
    triangleEdgeActor->GetProperty()->SetSpecular(.4);
    triangleEdgeActor->GetProperty()->SetSpecularPower(10);

  // Shrink the triangles we found earlier.  Create the associated mapper
  // and actor.  Set the opacity of the shrunken triangles.
    vtkSmartPointer<vtkShrinkPolyData> aShrinker =
      vtkSmartPointer<vtkShrinkPolyData>::New();
    aShrinker->SetShrinkFactor(1);
    aShrinker->SetInputConnection(Marching->GetOutputPort());

    vtkSmartPointer<vtkPolyDataMapper> aMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    aMapper->ScalarVisibilityOff();
    aMapper->SetInputConnection(aShrinker->GetOutputPort());

    vtkSmartPointer<vtkActor> Triangles =
      vtkSmartPointer<vtkActor>::New();
    Triangles->SetMapper(aMapper);
    Triangles->GetProperty()->SetDiffuseColor(
      color->GetColor3d("banana").GetData());
    Triangles->GetProperty()->SetOpacity(.6);

  // Draw a cube the same size and at the same position as the one
  // created previously.  Extract the edges because we only want to see
  // the outline of the cube.  Pass the edges through a vtkTubeFilter so
  // they are displayed as tubes rather than lines.
    vtkSmartPointer<vtkCubeSource> CubeModel =
      vtkSmartPointer<vtkCubeSource>::New();
    CubeModel->SetCenter(.5, .5, .5);

    vtkSmartPointer<vtkExtractEdges> Edges =
      vtkSmartPointer<vtkExtractEdges>::New();
    Edges->SetInputConnection(CubeModel->GetOutputPort());

    vtkSmartPointer<vtkTubeFilter> Tubes =
      vtkSmartPointer<vtkTubeFilter>::New();
    Tubes->SetInputConnection(Edges->GetOutputPort());
    Tubes->SetRadius(.01);
    Tubes->SetNumberOfSides(6);
    Tubes->UseDefaultNormalOn();
    Tubes->SetDefaultNormal(.577, .577, .577);
  // Create the mapper and actor to display the cube edges.
    vtkSmartPointer<vtkPolyDataMapper> TubeMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    TubeMapper->SetInputConnection(Tubes->GetOutputPort());
    vtkSmartPointer<vtkActor> CubeEdges =
      vtkSmartPointer<vtkActor>::New();
    CubeEdges->SetMapper(TubeMapper);
    CubeEdges->GetProperty()->SetDiffuseColor(
      color->GetColor3d("khaki").GetData());
    CubeEdges->GetProperty()->SetSpecular(.4);
    CubeEdges->GetProperty()->SetSpecularPower(10);

  // Create a sphere to use as a glyph source for vtkGlyph3D.
    vtkSmartPointer<vtkSphereSource> Sphere =
      vtkSmartPointer<vtkSphereSource>::New();
    Sphere->SetRadius(0.04);
    Sphere->SetPhiResolution(20);
    Sphere->SetThetaResolution(20);
  // Remove the part of the cube with data values below 0.5.
    vtkSmartPointer<vtkThresholdPoints> ThresholdIn =
      vtkSmartPointer<vtkThresholdPoints>::New();
    ThresholdIn->SetInputData(Grid);
    ThresholdIn->ThresholdByUpper(.5);
  // Display spheres at the vertices remaining in the cube data set after
  // it was passed through vtkThresholdPoints.
    vtkSmartPointer<vtkGlyph3D> Vertices =
      vtkSmartPointer<vtkGlyph3D>::New();
    Vertices->SetInputConnection(ThresholdIn->GetOutputPort());
    Vertices->SetSourceConnection(Sphere->GetOutputPort());
  // Create a mapper and actor to display the glyphs.
    vtkSmartPointer<vtkPolyDataMapper> SphereMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    SphereMapper->SetInputConnection(Vertices->GetOutputPort());
    SphereMapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> CubeVertices =
      vtkSmartPointer<vtkActor>::New();
    CubeVertices->SetMapper(SphereMapper);
    CubeVertices->GetProperty()->SetDiffuseColor(
      color->GetColor3d("tomato").GetData());

  // Define the text for the label
    vtkSmartPointer<vtkVectorText> caseLabel =
      vtkSmartPointer<vtkVectorText>::New();
    caseLabel->SetText("Case 1");

  // Set up a transform to move the label to a new position.
    vtkSmartPointer<vtkTransform> aLabelTransform =
      vtkSmartPointer<vtkTransform>::New();
    aLabelTransform->Identity();
    aLabelTransform->Translate(-0.2, 0, 1.25);
    aLabelTransform->Scale(.05, .05, .05);

  // Move the label to a new position.
    vtkSmartPointer<vtkTransformPolyDataFilter> labelTransform =
      vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    labelTransform->SetTransform(aLabelTransform);
    labelTransform->SetInputConnection(caseLabel->GetOutputPort());

  // Create a mapper and actor to display the text.
    vtkSmartPointer<vtkPolyDataMapper> labelMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    labelMapper->SetInputConnection(labelTransform->GetOutputPort());

    vtkSmartPointer<vtkActor> labelActor =
      vtkSmartPointer<vtkActor>::New();
    labelActor->SetMapper(labelMapper);

  // Define the base that the cube sits on.  Create its associated mapper
  // and actor.  Set the position of the actor.
    vtkSmartPointer<vtkCubeSource> baseModel =
      vtkSmartPointer<vtkCubeSource>::New();
    baseModel->SetXLength(1.5);
    baseModel->SetYLength(.01);
    baseModel->SetZLength(1.5);

    vtkSmartPointer<vtkPolyDataMapper> baseMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    baseMapper->SetInputConnection(baseModel->GetOutputPort());

    vtkSmartPointer<vtkActor> base =
      vtkSmartPointer<vtkActor>::New();
    base->SetMapper(baseMapper);
    base->SetPosition(.5, -0.09, .5);

  // Set the scalar values for this case of marching cubes.
  // A negative case number will generate a complementary case
    mcCase = mcCases[i];
    if (mcCase < 0)
    {
      cases[-mcCase](Scalars, caseLabel, 0, 1);
    }
    else
    {
      cases[mcCase](Scalars, caseLabel, 1, 0);
    }
  // Force the grid to update.
    Grid->Modified();

  // Add the actors to the renderer
    renderers[i]->AddActor(triangleEdgeActor);
    renderers[i]->AddActor(base);
    renderers[i]->AddActor(labelActor);
    renderers[i]->AddActor(CubeEdges);
    renderers[i]->AddActor(CubeVertices);
    renderers[i]->AddActor(Triangles);
  // Set the background color.
    renderers[i]->SetBackground(color->GetColor3d("slate_grey").GetData());

  // Position the camera.
    renderers[i]->GetActiveCamera()->Dolly(1.2);
    renderers[i]->GetActiveCamera()->Azimuth(30);
    renderers[i]->GetActiveCamera()->Elevation(20);
    renderers[i]->ResetCamera();
    renderers[i]->ResetCameraClippingRange();
    if (i > 0)
    {
      renderers[i]->SetActiveCamera(renderers[0]->GetActiveCamera());
    }
  }
  // Setup viewports for the renderers
  int rendererSize = 300;
  unsigned int xGridDimensions = mcCases.size() < 4 ? mcCases.size() : 4;
  unsigned int yGridDimensions = (mcCases.size() - 1) / 4 + 1; 
  std::cout << "x, y: " << xGridDimensions << " " << yGridDimensions << std::endl;
  renWin->SetSize(
    rendererSize * xGridDimensions, rendererSize * yGridDimensions);
  for (int row = 0; row < static_cast<int>(yGridDimensions); row++)
  {
    for (int col = 0; col < static_cast<int>(xGridDimensions); col++)
    {
      int index = row * xGridDimensions + col;

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
      renderers[index]->SetViewport(viewport);
    }
  }

  iren->Initialize();
  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
}

namespace
{
void case1(vtkFloatArray *scalars,
           vtkVectorText *caseLabel,
           int IN, int OUT)
{
  scalars->InsertValue(0, IN);
  scalars->InsertValue(1, OUT);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, OUT);
  scalars->InsertValue(4, OUT);
  scalars->InsertValue(5, OUT);
  scalars->InsertValue(6, OUT);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 1 - 00000001");
  }
  else
  {
    caseLabel->SetText("Case 1c - 11111110");
  }
}

void case2(vtkFloatArray *scalars,
           vtkVectorText *caseLabel,
           int IN, int OUT)
{
  scalars->InsertValue(0, IN);
  scalars->InsertValue(1, IN);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, OUT);
  scalars->InsertValue(4, OUT);
  scalars->InsertValue(5, OUT);
  scalars->InsertValue(6, OUT);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 2 - 00000011");
  }
  else
  {
    caseLabel->SetText("Case 2c - 11111100");
  }
}

void case3(vtkFloatArray *scalars,
           vtkVectorText *caseLabel,
           int IN, int OUT)
{
  scalars->InsertValue(0, IN);
  scalars->InsertValue(1, OUT);
  scalars->InsertValue(2, IN);
  scalars->InsertValue(3, OUT);
  scalars->InsertValue(4, OUT);
  scalars->InsertValue(5, OUT);
  scalars->InsertValue(6, OUT);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 3 - 00000101");
  }
  else
  {
    caseLabel->SetText("Case 3c - 11111010");
  }
}

void case4(vtkFloatArray *scalars,
           vtkVectorText *caseLabel,
           int IN, int OUT)
{
  scalars->InsertValue(0, IN);
  scalars->InsertValue(1, OUT);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, OUT);
  scalars->InsertValue(4, OUT);
  scalars->InsertValue(5, OUT);
  scalars->InsertValue(6, IN);
  scalars->InsertValue(7, OUT);
  if (IN == 1) {
    caseLabel->SetText("Case 4 - 01000001");
  }
  else
  {
    caseLabel->SetText("Case 4c - 10111110");
  }
}

void case5(vtkFloatArray *scalars,
           vtkVectorText *caseLabel,
           int IN, int OUT)
{
  scalars->InsertValue(0, OUT);
  scalars->InsertValue(1, IN);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, OUT);
  scalars->InsertValue(4, IN);
  scalars->InsertValue(5, IN);
  scalars->InsertValue(6, OUT);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 5 - 00110010");
  }
  else
  {
    caseLabel->SetText("Case 5c - 11001101");
  }
}

void case6(vtkFloatArray *scalars,
           vtkVectorText *caseLabel,
           int IN, int OUT)
{
  scalars->InsertValue(0, OUT);
  scalars->InsertValue(1, IN);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, IN);
  scalars->InsertValue(4, IN);
  scalars->InsertValue(5, OUT);
  scalars->InsertValue(6, OUT);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 6 - 00011010");
  }
  else
  {
    caseLabel->SetText("Case 6c - 11100101");
  }
}

void case7(vtkFloatArray *scalars,
           vtkVectorText *caseLabel,
           int IN, int OUT)
{
  scalars->InsertValue(0, IN);
  scalars->InsertValue(1, IN);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, OUT);
  scalars->InsertValue(4, OUT);
  scalars->InsertValue(5, OUT);
  scalars->InsertValue(6, IN);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 7 - 01000011");
  }
  else
  {
    caseLabel->SetText("Case 7c - 10111100");
  }
}

void case8(vtkFloatArray *scalars,
           vtkVectorText *caseLabel,
           int IN, int OUT)
{
  scalars->InsertValue(0, IN);
  scalars->InsertValue(1, IN);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, OUT);
  scalars->InsertValue(4, IN);
  scalars->InsertValue(5, IN);
  scalars->InsertValue(6, OUT);
  scalars->InsertValue(7, OUT);
    if (IN == 1)
    {
      caseLabel->SetText("Case 8 - 00110011");
    }
    else
    {
      caseLabel->SetText("Case 8c - 11001100");
    }
}

void case9(vtkFloatArray *scalars,
           vtkVectorText *caseLabel,
           int IN, int OUT)
{
  scalars->InsertValue(0, OUT);
  scalars->InsertValue(1, IN);
  scalars->InsertValue(2, IN);
  scalars->InsertValue(3, IN);
  scalars->InsertValue(4, OUT);
  scalars->InsertValue(5, OUT);
  scalars->InsertValue(6, IN);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 9 - 01001110");
  }
  else
  {
    caseLabel->SetText("Case 9c - 10110001");
  }
}
void case10(vtkFloatArray *scalars,
            vtkVectorText *caseLabel,
            int IN, int OUT)
{
  scalars->InsertValue(0, IN);
  scalars->InsertValue(1, OUT);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, IN);
  scalars->InsertValue(4, OUT);
  scalars->InsertValue(5, IN);
  scalars->InsertValue(6, IN);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 10 - 01101001");
  }
  else
  {
    caseLabel->SetText("Case 10c - 10010110");
  }
}

void case11(vtkFloatArray *scalars,
            vtkVectorText *caseLabel,
            int IN, int OUT)
{
  scalars->InsertValue(0, IN);
  scalars->InsertValue(1, OUT);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, OUT);
  scalars->InsertValue(4, IN);
  scalars->InsertValue(5, IN);
  scalars->InsertValue(6, IN);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 11 - 01110001");
  }
  else
  {
    caseLabel->SetText("Case 11c - 10001110");
  }
}

void case12(vtkFloatArray *scalars,
            vtkVectorText *caseLabel,
            int IN, int OUT)
{
  scalars->InsertValue(0, OUT);
  scalars->InsertValue(1, IN);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, IN);
  scalars->InsertValue(4, IN);
  scalars->InsertValue(5, IN);
  scalars->InsertValue(6, OUT);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 12 - 00111010");
  }
  else
  {
    caseLabel->SetText("Case 12c - 11000101");
  }
}

void case13(vtkFloatArray *scalars,
            vtkVectorText *caseLabel,
            int IN, int OUT)
{
  scalars->InsertValue(0, OUT);
  scalars->InsertValue(1, IN);
  scalars->InsertValue(2, OUT);
  scalars->InsertValue(3, IN);
  scalars->InsertValue(4, IN);
  scalars->InsertValue(5, OUT);
  scalars->InsertValue(6, IN);
  scalars->InsertValue(7, OUT);
  if (IN == 1)
  {
    caseLabel->SetText("Case 13 - 01011010");
  }
  else
  {
    caseLabel->SetText("Case 13c - 10100101");
  }
}

void case14(vtkFloatArray *scalars,
            vtkVectorText *caseLabel,
            int IN, int OUT)
{
  scalars->InsertValue(0, IN);
  scalars->InsertValue(1, OUT);
  scalars->InsertValue(2, IN);
  scalars->InsertValue(3, IN);
  scalars->InsertValue(4, OUT);
  scalars->InsertValue(5, IN);
  scalars->InsertValue(6, IN);
  scalars->InsertValue(7, IN);
  if (IN == 1)
  {
    caseLabel->SetText("Case 14 - 11101101");
  }
  else
  {
    caseLabel->SetText("Case 14c - 00010010");
  }
}
}
