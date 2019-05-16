#include <vtkAnnotatedCubeActor.h>
#include <vtkAxesActor.h>
#include <vtkBandedPolyDataContourFilter.h>
#include <vtkCamera.h>
#include <vtkCaptionActor2D.h>
#include <vtkCellData.h>
#include <vtkColorSeries.h>
#include <vtkColorTransferFunction.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkElevationFilter.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkPropAssembly.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTextProperty.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

#include <array>

namespace {
/**
 * Nake the annotated cube actor with different colored faces.
 *
 * @param colors: Used to set the colors of the cube faces.
 * @return The annotated cube actor.
 */
vtkSmartPointer<vtkPropAssembly> MakeAnnotatedCubeActor(vtkNamedColors* colors);

/**
 * Make an axes actor.
 *
 * @param scale: Sets the scale and direction of the axes.
 * @param xyzLabels: Labels for the axes.
 * @return The axes actor.
 */
vtkSmartPointer<vtkAxesActor>
MakeAxesActor(std::array<double, 3>& scale,
              std::array<std::string, 3>& xyzLabels);

} // namespace

int main(int, char*[])
{
  // Basic stuff setup
  // Set up the renderer, window, and interactor
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto ren = vtkSmartPointer<vtkRenderer>::New();
  auto renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  renWin->SetSize(640, 480);
  auto iRen = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iRen->SetRenderWindow(renWin);

  // Create a cone with an elliptical base whose major axis is in the
  // X-direction.
  auto coneSource = vtkSmartPointer<vtkConeSource>::New();
  coneSource->SetCenter(0.0, 0.0, 0.0);
  coneSource->SetRadius(5.0);
  coneSource->SetHeight(15.0);
  coneSource->SetDirection(0, 1, 0);
  coneSource->SetResolution(60);
  coneSource->Update();

  auto transform = vtkSmartPointer<vtkTransform>::New();
  transform->Scale(1.0, 1.0, 0.75);

  auto transF = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transF->SetInputConnection(coneSource->GetOutputPort());
  transF->SetTransform(transform);

  double bounds[6];
  transF->GetOutput()->GetBounds(bounds);

  auto elevation = vtkSmartPointer<vtkElevationFilter>::New();
  elevation->SetInputConnection(transF->GetOutputPort());
  elevation->SetLowPoint(0, bounds[2], 0);
  elevation->SetHighPoint(0, bounds[3], 0);

  auto bandedContours = vtkSmartPointer<vtkBandedPolyDataContourFilter>::New();
  bandedContours->SetInputConnection(elevation->GetOutputPort());
  bandedContours->SetScalarModeToValue();
  bandedContours->GenerateContourEdgesOn();
  bandedContours->GenerateValues(11, elevation->GetScalarRange());

  // Make a lookup table using a color series.
  auto colorSeries = vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_DIVERGING_SPECTRAL_11);

  auto lut = vtkSmartPointer<vtkLookupTable>::New();
  colorSeries->BuildLookupTable(lut, vtkColorSeries::ORDINAL);

  auto coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(bandedContours->GetOutputPort());
  coneMapper->SetScalarRange(elevation->GetScalarRange());
  coneMapper->SetLookupTable(lut);

  auto coneActor = vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);

  // Contouring
  auto contourLineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  contourLineMapper->SetInputData(bandedContours->GetContourEdgesOutput());
  contourLineMapper->SetScalarRange(elevation->GetScalarRange());
  contourLineMapper->SetResolveCoincidentTopologyToPolygonOffset();

  auto contourLineActor = vtkSmartPointer<vtkActor>::New();
  contourLineActor->SetMapper(contourLineMapper);
  contourLineActor->GetProperty()->SetColor(
      colors->GetColor3d("DimGray").GetData());

  // Set up the Orientation Marker Widget.
  auto prop_assembly = MakeAnnotatedCubeActor(colors);
  auto om1 = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  om1->SetOrientationMarker(prop_assembly);
  om1->SetInteractor(iRen);
  om1->SetDefaultRenderer(ren);
  om1->On();
  om1->InteractiveOn();

  std::array<std::string, 3> xyzLabels{{"X", "Y", "Z"}};
  std::array<double, 3> scale{{1.0, 1.0, 1.0}};
  auto axes = MakeAxesActor(scale, xyzLabels);

  auto om2 = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  om2->SetOrientationMarker(axes);
  // Position lower right in the viewport.
  om2->SetViewport(0.8, 0, 1.0, 0.2);
  om2->SetInteractor(iRen);
  om2->EnabledOn();
  om2->InteractiveOn();

  ren->AddActor(coneActor);
  ren->AddActor(contourLineActor);
  ren->SetBackground2(colors->GetColor3d("RoyalBlue").GetData());
  ren->SetBackground(colors->GetColor3d("MistyRose").GetData());
  ren->GradientBackgroundOn();
  ren->GetActiveCamera()->Azimuth(45);
  ren->GetActiveCamera()->Pitch(-22.5);
  ren->ResetCamera();

  renWin->SetSize(600, 600);
  renWin->Render();
  renWin->SetWindowName("ColoredAnnotatedCube");
  renWin->Render();
  iRen->Start();

  return EXIT_SUCCESS;
}

namespace {
vtkSmartPointer<vtkPropAssembly> MakeAnnotatedCubeActor(vtkNamedColors* colors)
{
  // Annotated Cube setup
  auto annotated_cube = vtkSmartPointer<vtkAnnotatedCubeActor>::New();
  annotated_cube->SetFaceTextScale(0.366667);

  // Anatomic labeling
  annotated_cube->SetXPlusFaceText("X+");
  annotated_cube->SetXMinusFaceText("X-");
  annotated_cube->SetYPlusFaceText("Y+");
  annotated_cube->SetYMinusFaceText("Y-");
  annotated_cube->SetZPlusFaceText("Z+");
  annotated_cube->SetZMinusFaceText("Z-");

  // Change the vector text colors
  annotated_cube->GetTextEdgesProperty()->SetColor(
      colors->GetColor3d("Black").GetData());
  annotated_cube->GetTextEdgesProperty()->SetLineWidth(1);

  annotated_cube->GetXPlusFaceProperty()->SetColor(
      colors->GetColor3d("Turquoise").GetData());
  annotated_cube->GetXMinusFaceProperty()->SetColor(
      colors->GetColor3d("Turquoise").GetData());
  annotated_cube->GetYPlusFaceProperty()->SetColor(
      colors->GetColor3d("Mint").GetData());
  annotated_cube->GetYMinusFaceProperty()->SetColor(
      colors->GetColor3d("Mint").GetData());
  annotated_cube->GetZPlusFaceProperty()->SetColor(
      colors->GetColor3d("Tomato").GetData());
  annotated_cube->GetZMinusFaceProperty()->SetColor(
      colors->GetColor3d("Tomato").GetData());
  annotated_cube->SetXFaceTextRotation(90);
  annotated_cube->SetYFaceTextRotation(180);
  annotated_cube->SetZFaceTextRotation(-90);
  // Make the annotated cube transparent
  annotated_cube->GetCubeProperty()->SetOpacity(0);

  // Colored faces cube setup
  auto cube_source = vtkSmartPointer<vtkCubeSource>::New();
  cube_source->Update();

  auto face_colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
  face_colors->SetNumberOfComponents(3);
  auto face_x_plus = colors->GetColor3ub("Red").GetData();
  auto face_x_minus = colors->GetColor3ub("Green").GetData();
  auto face_y_plus = colors->GetColor3ub("Blue").GetData();
  auto face_y_minus = colors->GetColor3ub("Yellow").GetData();
  auto face_z_plus = colors->GetColor3ub("Cyan").GetData();
  auto face_z_minus = colors->GetColor3ub("Magenta").GetData();
  face_colors->InsertNextTypedTuple(face_x_minus);
  face_colors->InsertNextTypedTuple(face_x_plus);
  face_colors->InsertNextTypedTuple(face_y_minus);
  face_colors->InsertNextTypedTuple(face_y_plus);
  face_colors->InsertNextTypedTuple(face_z_minus);
  face_colors->InsertNextTypedTuple(face_z_plus);

  cube_source->GetOutput()->GetCellData()->SetScalars(face_colors);
  cube_source->Update();

  auto cube_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  cube_mapper->SetInputData(cube_source->GetOutput());
  cube_mapper->Update();

  auto cube_actor = vtkSmartPointer<vtkActor>::New();
  cube_actor->SetMapper(cube_mapper);

  // Assemble the colored cube and annotated cube texts into a composite prop.
  auto prop_assembly = vtkSmartPointer<vtkPropAssembly>::New();
  prop_assembly->AddPart(annotated_cube);
  prop_assembly->AddPart(cube_actor);
  return prop_assembly;
}

vtkSmartPointer<vtkAxesActor>
MakeAxesActor(std::array<double, 3>& scale,
              std::array<std::string, 3>& xyzLabels)
{
  auto axes = vtkSmartPointer<vtkAxesActor>::New();
  axes->SetScale(scale[0], scale[1], scale[2]);
  axes->SetShaftTypeToCylinder();
  axes->SetXAxisLabelText(xyzLabels[0].c_str());
  axes->SetYAxisLabelText(xyzLabels[1].c_str());
  axes->SetZAxisLabelText(xyzLabels[2].c_str());
  axes->SetCylinderRadius(0.5 * axes->GetCylinderRadius());
  axes->SetConeRadius(1.025 * axes->GetConeRadius());
  axes->SetSphereRadius(1.5 * axes->GetSphereRadius());
  vtkTextProperty* tprop =
      axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty();
  tprop->ItalicOn();
  tprop->ShadowOn();
  tprop->SetFontFamilyToTimes();
  // Use the same text properties on the other two axes.
  axes->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy(tprop);
  axes->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy(tprop);
  return axes;
}

} // namespace
