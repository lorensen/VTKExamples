/*
 * The human data file is taken from:
 * https://github.com/Slicer/Slicer/blob/master/Base/Logic/Resources/OrientationMarkers/Human.vtp
 * Thanks to the Slicer people for providing this.
 *
 */

#include <vtkAnnotatedCubeActor.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCaptionActor2D.h>
#include <vtkNamedColors.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPlaneSource.h>
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
#include <vtkVectorText.h>
#include <vtkXMLPolyDataReader.h>

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <vector>

namespace
{

/**
 * @param scale Sets the scale and direction of the axes.
 * @param xyzLabels Labels for the axes.
 * @return The axes actor.
 */
vtkSmartPointer<vtkAxesActor> MakeAxesActor(
  std::array<double, 3>& scale, std::array<std::string, 3>& xyzLabels);

/**
 * @param colors Used to set the colors of the cube faces.
 * @return The annotated cube actor.
 */
vtkSmartPointer<vtkAnnotatedCubeActor> MakeAnnotatedCubeActor(
  vtkNamedColors* colors);

/**
 * @param scale Sets the scale and direction of the axes.
 * @param xyzLabels Labels for the axes.
 * @param colors Used to set the colors of the cube faces.
 * @return The combined axes and annotated cube prop.
 */
vtkSmartPointer<vtkPropAssembly> MakeCubeActor(
  std::array<double, 3>& scale, std::array<std::string, 3>& xyzLabels,
  vtkNamedColors* colors);

/**
 * Make the traverse, coronal and saggital planes.
 *
 * @param colors Used to set the color of the planes.
 * @return The planes actors.
 */
std::vector<vtkSmartPointer<vtkActor>> MakePlanesActors(vtkNamedColors* colors);

/**
* Generate text to place on the planes.
* Careful placement is needed here.
* @return The text actors.
*/
std::vector<vtkSmartPointer<vtkActor>> AddTextToPlanes();
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " fileName" << std::endl;
    std::cout << "where: fileName is Human.vtp." << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argv[1];

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create the rendering window, renderer, and interactive renderer.
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetSize(780, 780);
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Make an annotated cube actor with axes and then add it into an orientation
  // marker widget.
  // Three of these need to be made.

  // Right Posterior Superior
  std::array<std::string, 3> xyzLabels{{"X", "Y", "Z"}};
  std::array<double, 3> scale{{1.5, -1.5, 1.5}};
  vtkSmartPointer<vtkPropAssembly> axes =
    MakeCubeActor(scale, xyzLabels, colors);
  vtkSmartPointer<vtkOrientationMarkerWidget> om =
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  om->SetOrientationMarker(axes);
  // Position upper left in the viewport.
  om->SetViewport(0.0, 0.8, 0.2, 1.0);
  om->SetInteractor(iren);
  om->EnabledOn();
  om->InteractiveOn();

  // Right, Anterior, Superior.
  std::array<double, 3> scale1{{1.5, 1.5, 1.5}};
  vtkSmartPointer<vtkPropAssembly> axes1 =
    MakeCubeActor(scale1, xyzLabels, colors);
  vtkSmartPointer<vtkOrientationMarkerWidget> om1 =
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  om1->SetOrientationMarker(axes1);
  // Position lower left in the viewport.
  om1->SetViewport(0, 0, 0.2, 0.2);
  om1->SetInteractor(iren);
  om1->EnabledOn();
  om1->InteractiveOn();

  // Left, Posterior, Superior.
  std::array<double, 3> scale2{{-1.5, -1.5, 1.5}};
  vtkSmartPointer<vtkPropAssembly> axes2 =
    MakeCubeActor(scale2, xyzLabels, colors);
  vtkSmartPointer<vtkOrientationMarkerWidget> om2 =
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  om2->SetOrientationMarker(axes2);
  // Position lower right in the viewport.
  om2->SetViewport(0.8, 0, 1.0, 0.2);
  om2->SetInteractor(iren);
  om2->EnabledOn();
  om2->InteractiveOn();

  // Finally create an annotated cube actor adding it into an orientation marker
  // widget.
  vtkSmartPointer<vtkAnnotatedCubeActor> axes3 = MakeAnnotatedCubeActor(colors);
  vtkSmartPointer<vtkOrientationMarkerWidget> om3 =
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  om3->SetOrientationMarker(axes3);
  // Position upper right in the viewport.
  om3->SetViewport(0.8, 0.8, 1.0, 1.0);
  om3->SetInteractor(iren);
  om3->EnabledOn();
  om3->InteractiveOn();

  // Read in the model.
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(fileName.c_str());
  reader->Update();

  vtkSmartPointer<vtkPolyDataMapper> humanMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  humanMapper->SetInputConnection(reader->GetOutputPort());
  humanMapper->SetScalarModeToUsePointFieldData();
  humanMapper->SelectColorArray("Color");
  humanMapper->SetColorModeToDirectScalars();

  vtkSmartPointer<vtkActor> humanActor = vtkSmartPointer<vtkActor>::New();
  humanActor->SetMapper(humanMapper);
  std::vector<double> bounds(6, 0);
  humanActor->GetBounds(&bounds[0]);
  std::vector<double>::iterator maxElt =
    std::max_element(bounds.begin(), bounds.end());
  // Scale the actor
  humanActor->SetScale(1.0 / *maxElt);
  ren->AddActor(humanActor);

  // Make the planes.
  std::vector<vtkSmartPointer<vtkActor>> actors = MakePlanesActors(colors);
  for (auto actor : actors)
  {
    ren->AddViewProp(actor);
  }

  // Label them.
  std::vector<vtkSmartPointer<vtkActor>> textActors = AddTextToPlanes();
  for (auto actor : textActors)
  {
    ren->AddViewProp(actor);
  }

  // Interact
  ren->SetBackground2(colors->GetColor3d("OldLace").GetData());
  ren->SetBackground(colors->GetColor3d("MistyRose").GetData());
  ren->GradientBackgroundOn();
  ren->ResetCamera();
  ren->GetActiveCamera()->Zoom(1.6);
  ren->GetActiveCamera()->SetPosition(-2.3, 4.1, 4.2);
  ren->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);
  ren->ResetCameraClippingRange();
  renWin->Render();
  //  Call SetWindowName after renWin.Render() is called.
  renWin->SetWindowName("Anatomical Orientation");

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace
{

vtkSmartPointer<vtkAxesActor> MakeAxesActor(
  std::array<double, 3>& scale, std::array<std::string, 3>& xyzLabels)
{
  vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
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

vtkSmartPointer<vtkAnnotatedCubeActor> MakeAnnotatedCubeActor(
  vtkNamedColors* colors)
{
  // A cube with labeled faces.
  vtkSmartPointer<vtkAnnotatedCubeActor> cube =
    vtkSmartPointer<vtkAnnotatedCubeActor>::New();
  cube->SetXPlusFaceText("R"); // Right
  cube->SetXMinusFaceText("L"); // Left
  cube->SetYPlusFaceText("A"); // Anterior
  cube->SetYMinusFaceText("P"); // Posterior
  cube->SetZPlusFaceText("S"); // Superior/Cranial
  cube->SetZMinusFaceText("I"); // Inferior/Caudal
  cube->SetFaceTextScale(0.5);
  cube->GetCubeProperty()->SetColor(colors->GetColor3d("Gainsboro").GetData());

  cube->GetTextEdgesProperty()->SetColor(
    colors->GetColor3d("LightSlateGray").GetData());

  // Change the vector text colors.
  cube->GetXPlusFaceProperty()->SetColor(
    colors->GetColor3d("Tomato").GetData());
  cube->GetXMinusFaceProperty()->SetColor(
    colors->GetColor3d("Tomato").GetData());
  cube->GetYPlusFaceProperty()->SetColor(
    colors->GetColor3d("DeepSkyBlue").GetData());
  cube->GetYMinusFaceProperty()->SetColor(
    colors->GetColor3d("DeepSkyBlue").GetData());
  cube->GetZPlusFaceProperty()->SetColor(
    colors->GetColor3d("SeaGreen").GetData());
  cube->GetZMinusFaceProperty()->SetColor(
    colors->GetColor3d("SeaGreen").GetData());
  return cube;
}

vtkSmartPointer<vtkPropAssembly> MakeCubeActor(
  std::array<double, 3>& scale, std::array<std::string, 3>& xyzLabels,
  vtkNamedColors* colors)
{
  // We are combining a vtk.vtkAxesActor and a vtk.vtkAnnotatedCubeActor
  // into a vtk.vtkPropAssembly
  vtkSmartPointer<vtkAnnotatedCubeActor> cube = MakeAnnotatedCubeActor(colors);
  vtkSmartPointer<vtkAxesActor> axes = MakeAxesActor(scale, xyzLabels);

  // Combine orientation markers into one with an assembly.
  vtkSmartPointer<vtkPropAssembly> assembly =
    vtkSmartPointer<vtkPropAssembly>::New();
  assembly->AddPart(axes);
  assembly->AddPart(cube);
  return assembly;
}

vtkSmartPointer<vtkTransformPolyDataFilter> MakePlane(
  std::array<int, 2>& resolution, std::array<double, 3>& origin,
  std::array<double, 3>& point1, std::array<double, 3>& point2,
  std::array<double, 4>& wxyz, std::array<double, 3>& translate)
{
  vtkSmartPointer<vtkPlaneSource> plane =
    vtkSmartPointer<vtkPlaneSource>::New();
  plane->SetResolution(resolution[0], resolution[1]);
  plane->SetOrigin(origin.data());
  plane->SetPoint1(point1.data());
  plane->SetPoint2(point2.data());
  vtkSmartPointer<vtkTransform> trnf = vtkSmartPointer<vtkTransform>::New();
  trnf->RotateWXYZ(wxyz[0], wxyz[1], wxyz[2], wxyz[3]);
  trnf->Translate(translate.data());
  vtkSmartPointer<vtkTransformPolyDataFilter> tpdPlane =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tpdPlane->SetTransform(trnf);
  tpdPlane->SetInputConnection(plane->GetOutputPort());
  return tpdPlane;
}

std::vector<vtkSmartPointer<vtkActor>> MakePlanesActors(vtkNamedColors* colors)
{
  std::vector<vtkSmartPointer<vtkTransformPolyDataFilter>> planes;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  std::vector<vtkSmartPointer<vtkActor>> actors;

  // Parameters for a plane lying in the x-y plane.
  std::array<int, 2> resolution{{10, 10}};
  std::array<double, 3> origin{{0.0, 0.0, 0.0}};
  std::array<double, 3> point1{{1, 0, 0}};
  std::array<double, 3> point2{{0, 1, 0}};

  std::array<double, 4> wxyz0{{0, 0, 0, 0}};
  std::array<double, 3> translate{{-0.5, -0.5, 0}};
  std::array<double, 4> wxyz1{{-90, 1, 0, 0}};
  std::array<double, 4> wxyz2{{-90, 0, 1, 0}};
  planes.push_back(MakePlane(resolution, origin, point1, point2, wxyz0,
                             translate)); // x-y plane
  planes.push_back(MakePlane(resolution, origin, point1, point2, wxyz1,
                             translate)); // x-z plane
  planes.push_back(MakePlane(resolution, origin, point1, point2, wxyz2,
                             translate)); // y-z plane
  for (size_t i = 0; i < planes.size(); ++i)
  {
    mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
    mappers[i]->SetInputConnection(planes[i]->GetOutputPort());
    actors.push_back(vtkSmartPointer<vtkActor>::New());
    actors[i]->SetMapper(mappers[i]);
  }
  actors[0]->GetProperty()->SetColor(
    colors->GetColor3d("SeaGreen").GetData()); // Transverse plane
  actors[1]->GetProperty()->SetColor(
    colors->GetColor3d("DeepSkyBlue").GetData()); // Coronal plane
  actors[2]->GetProperty()->SetColor(
    colors->GetColor3d("Tomato").GetData()); // Saggital plane
  return actors;
}

std::vector<vtkSmartPointer<vtkActor>> AddTextToPlanes()
{
  std::vector<vtkSmartPointer<vtkActor>> textActors;
  std::array<double, 3> scale{{0.04, 0.04, 0.04}};

  vtkSmartPointer<vtkVectorText> text1 = vtkSmartPointer<vtkVectorText>::New();
  text1->SetText("Transverse\nPlane\n\nSuperior\nCranial");
  vtkSmartPointer<vtkTransform> trnf1 = vtkSmartPointer<vtkTransform>::New();
  trnf1->RotateZ(-90);
  vtkSmartPointer<vtkTransformPolyDataFilter> tpdPlane1 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tpdPlane1->SetTransform(trnf1);
  tpdPlane1->SetInputConnection(text1->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> textMapper1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  textMapper1->SetInputConnection(tpdPlane1->GetOutputPort());
  vtkSmartPointer<vtkActor> textActor1 = vtkSmartPointer<vtkActor>::New();
  textActor1->SetMapper(textMapper1);
  textActor1->SetScale(scale.data());
  textActor1->AddPosition(0.4, 0.49, 0.01);
  textActors.push_back(textActor1);

  vtkSmartPointer<vtkVectorText> text2 = vtkSmartPointer<vtkVectorText>::New();
  text2->SetText("Transverse\nPlane\n\nInferior\n(Caudal)");
  vtkSmartPointer<vtkTransform> trnf2 = vtkSmartPointer<vtkTransform>::New();
  trnf2->RotateZ(270);
  trnf2->RotateWXYZ(180, 0, 1, 0);
  vtkSmartPointer<vtkTransformPolyDataFilter> tpdPlane2 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tpdPlane2->SetTransform(trnf2);
  tpdPlane2->SetInputConnection(text2->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> textMapper2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  textMapper2->SetInputConnection(tpdPlane2->GetOutputPort());
  vtkSmartPointer<vtkActor> textActor2 = vtkSmartPointer<vtkActor>::New();
  textActor2->SetMapper(textMapper2);
  textActor2->SetScale(scale.data());
  textActor2->AddPosition(0.4, -0.49, -0.01);
  textActors.push_back(textActor2);

  vtkSmartPointer<vtkVectorText> text3 = vtkSmartPointer<vtkVectorText>::New();
  text3->SetText("Sagittal\nPlane\n\nLeft");
  vtkSmartPointer<vtkTransform> trnf3 = vtkSmartPointer<vtkTransform>::New();
  trnf3->RotateX(90);
  trnf3->RotateWXYZ(-90, 0, 1, 0);
  vtkSmartPointer<vtkTransformPolyDataFilter> tpdPlane3 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tpdPlane3->SetTransform(trnf3);
  tpdPlane3->SetInputConnection(text3->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> textMapper3 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  textMapper3->SetInputConnection(tpdPlane3->GetOutputPort());
  vtkSmartPointer<vtkActor> textActor3 = vtkSmartPointer<vtkActor>::New();
  textActor3->SetMapper(textMapper3);
  textActor3->SetScale(scale.data());
  textActor3->AddPosition(-0.01, 0.49, 0.4);
  textActors.push_back(textActor3);

  vtkSmartPointer<vtkVectorText> text4 = vtkSmartPointer<vtkVectorText>::New();
  text4->SetText("Sagittal\nPlane\n\nRight");
  vtkSmartPointer<vtkTransform> trnf4 = vtkSmartPointer<vtkTransform>::New();
  trnf4->RotateX(90);
  trnf4->RotateWXYZ(-270, 0, 1, 0);
  vtkSmartPointer<vtkTransformPolyDataFilter> tpdPlane4 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tpdPlane4->SetTransform(trnf4);
  tpdPlane4->SetInputConnection(text4->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> textMapper4 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  textMapper4->SetInputConnection(tpdPlane4->GetOutputPort());
  vtkSmartPointer<vtkActor> textActor4 = vtkSmartPointer<vtkActor>::New();
  textActor4->SetMapper(textMapper4);
  textActor4->SetScale(scale.data());
  textActor4->AddPosition(0.01, -0.49, 0.4);
  textActors.push_back(textActor4);

  vtkSmartPointer<vtkVectorText> text5 = vtkSmartPointer<vtkVectorText>::New();
  text5->SetText("Coronal\nPlane\n\nAnterior");
  vtkSmartPointer<vtkTransform> trnf5 = vtkSmartPointer<vtkTransform>::New();
  trnf5->RotateY(-180);
  trnf5->RotateWXYZ(-90, 1, 0, 0);
  vtkSmartPointer<vtkTransformPolyDataFilter> tpdPlane5 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tpdPlane5->SetTransform(trnf5);
  tpdPlane5->SetInputConnection(text5->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> textMapper5 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  textMapper5->SetInputConnection(tpdPlane5->GetOutputPort());
  vtkSmartPointer<vtkActor> textActor5 = vtkSmartPointer<vtkActor>::New();
  textActor5->SetMapper(textMapper5);
  textActor5->SetScale(scale.data());
  textActor5->AddPosition(0.49, 0.01, 0.20);
  textActors.push_back(textActor5);

  vtkSmartPointer<vtkVectorText> text6 = vtkSmartPointer<vtkVectorText>::New();
  text6->SetText("Coronal\nPlane\n\nPosterior");
  vtkSmartPointer<vtkTransform> trnf6 = vtkSmartPointer<vtkTransform>::New();
  trnf6->RotateWXYZ(90, 1, 0, 0);
  vtkSmartPointer<vtkTransformPolyDataFilter> tpdPlane6 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tpdPlane6->SetTransform(trnf6);
  tpdPlane6->SetInputConnection(text6->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> textMapper6 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  textMapper6->SetInputConnection(tpdPlane6->GetOutputPort());
  vtkSmartPointer<vtkActor> textActor6 = vtkSmartPointer<vtkActor>::New();
  textActor6->SetMapper(textMapper6);
  textActor6->SetScale(scale.data());
  textActor6->AddPosition(-0.49, -0.01, 0.3);
  textActors.push_back(textActor6);

  return textActors;
}
}
