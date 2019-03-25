#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkArrowSource.h>
#include <vtkAxesActor.h>
#include <vtkButterflySubdivisionFilter.h>
#include <vtkCamera.h>
#include <vtkCaptionActor2D.h>
#include <vtkCleanPolyData.h>
#include <vtkColor.h>
#include <vtkColorSeries.h>
#include <vtkColorTransferFunction.h>
#include <vtkConeSource.h>
#include <vtkDataObjectAlgorithm.h>
#include <vtkDataSetMapper.h>
#include <vtkElevationFilter.h>
#include <vtkGlyph3D.h>
#include <vtkLinearSubdivisionFilter.h>
#include <vtkMaskPoints.h>
#include <vtkNamedColors.h>
#include <vtkObjectFactory.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricTorus.h>
#include <vtkParametricEllipsoid.h>
#include <vtkParametricBoy.h>
#include <vtkParametricMobius.h>
#include <vtkParametricRandomHills.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderLargeImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphere.h>
#include <vtkSphereSource.h>
#include <vtkSuperquadricSource.h>
#include <vtkTriangleFilter.h>
#include <vtkTextActor.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

#include <algorithm>

/**
 * @class Sources
 * @brief This class acts as a storage vehicle for the various sources.
 *
 * If you add more sources, you may need to provide one or all of these filters:
 *  - A Triangle filter
 *  - A Normal filter
 *  - An elevation filter.
 *  - A CleanPolyData filter.
 *  - For parametric sources, we may need to apply one of both of JoinUOff() or JoinVOff().
 *
 * Use the representative sources provided here as templates.
*/
class Sources : public vtkPolyDataAlgorithm
{
public:

  static Sources *New();

  vtkTypeMacro(Sources, vtkPolyDataAlgorithm);

  // If you add more sources update this dictionary.
  enum SurfaceType
  {
    PARAMETRIC_TORUS = 0,
    PARAMETRIC_ELLIPSOID,
    BOY,
    SPHERE,
    MOBIUS,
    CONE,
    RANDOM_HILLS,
    SUPERQUADRIC
  };

  Sources() : vtkPolyDataAlgorithm()
  {
  }

  static void ParametricTorusSource(vtkPolyData* src)
  {
    vtkSmartPointer<vtkParametricTorus> torus =
      vtkSmartPointer<vtkParametricTorus>::New();
    torus->JoinUOff();
    torus->JoinVOff();

    vtkSmartPointer<vtkParametricFunctionSource> torusSource =
      vtkSmartPointer<vtkParametricFunctionSource>::New();
    torusSource->SetParametricFunction(torus);
    torusSource->SetScalarModeToZ();
    torusSource->Update();

    src->ShallowCopy(torusSource->GetOutput());
   }

  static void EllipsoidSource(vtkPolyData* src)
  {
    vtkSmartPointer<vtkParametricEllipsoid> ellipsoid =
      vtkSmartPointer<vtkParametricEllipsoid>::New();
    ellipsoid->SetXRadius(0.5);
    ellipsoid->SetYRadius(1.0);
    ellipsoid->SetZRadius(2.0);
    ellipsoid->JoinUOff();
    //ellipsoid->JoinVOff();

    vtkSmartPointer<vtkParametricFunctionSource> ellipsoidSource =
      vtkSmartPointer<vtkParametricFunctionSource>::New();
    ellipsoidSource->SetParametricFunction(ellipsoid);
    ellipsoidSource->SetScalarModeToZ();
    ellipsoidSource->Update();

    src->ShallowCopy(ellipsoidSource->GetOutput());
  }

  static void BoySource(vtkPolyData* src)
  {
    vtkSmartPointer<vtkParametricBoy> boy =
      vtkSmartPointer<vtkParametricBoy>::New();
    boy->JoinUOff();
    //boy->JoinVOff();

    vtkSmartPointer<vtkParametricFunctionSource> boySource =
      vtkSmartPointer<vtkParametricFunctionSource>::New();
    boySource->SetParametricFunction(boy);
    boySource->SetScalarModeToZ();
    boySource->Update();
    src->ShallowCopy(boySource->GetOutput());
  }

  static void MobiusSource(vtkPolyData* src)
  {
    vtkSmartPointer<vtkParametricMobius> mobius =
      vtkSmartPointer<vtkParametricMobius>::New();
    mobius->SetRadius(2);
    mobius->SetMinimumV(-0.5);
    mobius->SetMaximumV(0.5);
    mobius->JoinUOff();

    vtkSmartPointer<vtkParametricFunctionSource> mobiusSource =
      vtkSmartPointer<vtkParametricFunctionSource>::New();
    mobiusSource->SetParametricFunction(mobius);
    mobiusSource->SetScalarModeToX();
    mobiusSource->Update();

    src->ShallowCopy(mobiusSource->GetOutput());
  }

  static void ParametricRandomHills(vtkPolyData* src)
  {
    vtkSmartPointer<vtkParametricRandomHills> randomHills =
      vtkSmartPointer<vtkParametricRandomHills>::New();
    //randomHills->AllowRandomGenerationOff();
    randomHills->SetRandomSeed(1);
    randomHills->SetNumberOfHills(30);

    vtkSmartPointer<vtkParametricFunctionSource> randomHillsSource =
      vtkSmartPointer<vtkParametricFunctionSource>::New();
    randomHillsSource->SetParametricFunction(randomHills);
    randomHillsSource->SetScalarModeToZ();
    randomHillsSource->SetUResolution(10);
    randomHillsSource->SetVResolution(10);
    randomHillsSource->Update();

    src->ShallowCopy(randomHillsSource->GetOutput());
  }

  static void SphereSource(vtkPolyData* src)
  {
    vtkSmartPointer<vtkSphereSource> sphere =
      vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetPhiResolution(11);
    sphere->SetThetaResolution(11);
    sphere->Update();
    double* sphereBounds = sphere->GetOutput()->GetBounds();

    vtkSmartPointer<vtkElevationFilter> elev =
      vtkSmartPointer<vtkElevationFilter>::New();
    elev->SetInputConnection(sphere->GetOutputPort());
    elev->SetLowPoint(0, sphereBounds[2], 0);
    elev->SetHighPoint(0, sphereBounds[3], 0);
    elev->Update();

    src->ShallowCopy(elev->GetPolyDataOutput());
  }

  /**
   * Make a torus as the source.
   */
  static void SuperquadricSource(vtkPolyData* src)
  {
    vtkSmartPointer<vtkSuperquadricSource> source =
      vtkSmartPointer<vtkSuperquadricSource>::New();
    source->SetCenter(0.0, 0.0, 0.0);
    source->SetScale(1.0, 1.0, 1.0);
    source->SetPhiResolution(64);
    source->SetThetaResolution(64);
    source->SetThetaRoundness(1);
    source->SetThickness(0.5);
    source->SetSize(10);
    source->SetToroidal(1);

    // The quadric is made of strips, so pass it through a triangle filter as
    // the curvature filter only operates on polys
    vtkSmartPointer<vtkTriangleFilter> tri =
      vtkSmartPointer<vtkTriangleFilter>::New();
    tri->SetInputConnection(source->GetOutputPort());

    // The quadric has nasty discontinuities from the way the edges are generated
    // so let's pass it though a CleanPolyDataFilter and merge any points which
    // are coincident, or very close
    vtkSmartPointer<vtkCleanPolyData> cleaner =
      vtkSmartPointer<vtkCleanPolyData>::New();
    cleaner->SetInputConnection(tri->GetOutputPort());
    cleaner->SetTolerance(0.005);
    cleaner->Update();
    double* cleanerBounds = cleaner->GetOutput()->GetBounds();

    vtkSmartPointer<vtkElevationFilter> elev =
      vtkSmartPointer<vtkElevationFilter>::New();
    elev->SetInputConnection(cleaner->GetOutputPort());
    elev->SetLowPoint(0, cleanerBounds[2], 0);
    elev->SetHighPoint(0, cleanerBounds[3], 0);
    elev->Update();

    src->ShallowCopy(elev->GetPolyDataOutput());
  }

  static void ConeSource(vtkPolyData* src)
  {
    vtkSmartPointer<vtkConeSource> cone =
      vtkSmartPointer<vtkConeSource>::New();
    cone->SetResolution(6);
    cone->CappingOn();
    cone->Update();
    double* coneBounds = cone->GetOutput()->GetBounds();

    vtkSmartPointer<vtkPolyDataNormals> coneNormals =
      vtkSmartPointer<vtkPolyDataNormals>::New();
    coneNormals->SetInputConnection(cone->GetOutputPort());

    vtkSmartPointer<vtkElevationFilter> elev =
      vtkSmartPointer<vtkElevationFilter>::New();
    elev->SetInputConnection(coneNormals->GetOutputPort());
    elev->SetLowPoint(coneBounds[0], 0, 0);
    elev->SetHighPoint(coneBounds[1], 0, 0);

    // vtkButterflySubdivisionFilter and vtkLinearSubdivisionFilter operate on triangles.
    vtkSmartPointer<vtkTriangleFilter> tf =
      vtkSmartPointer<vtkTriangleFilter>::New();
    tf->SetInputConnection(elev->GetOutputPort());
    tf->Update();

    src->ShallowCopy(tf->GetOutput());
   }
};

vtkStandardNewMacro(Sources);

/**
 * Make a lookup table using a predefined color series.
 *
 * @param scalarRange The range of the scalars to be coloured.
 *
 * @return A lookup table.
*/
vtkSmartPointer<vtkColorTransferFunction> MakeLUT(double *scalarRange)
{
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  //Select a color scheme.
  //for (unsigned int i = 0; i < 62; ++i)
  //{
  //  colorSeries->SetColorScheme(i);
  //  std::cout << "Colour scheme: " << colorSeries->GetColorScheme() << ": " << colorSeries->GetColorSchemeName();
  //}

  // Colour scheme 61: Brewer Qualitative Set3
  colorSeries->SetColorScheme(61);
  // We use this colour series to create the transfer function.
  vtkSmartPointer<vtkColorTransferFunction> lut =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  lut->SetColorSpaceToHSV();
  int numColors = colorSeries->GetNumberOfColors();
  for(int i = 0; i < numColors; ++i)
  {
    vtkColor3ub color = colorSeries->GetColor(i);
    std::vector<double> c;
    for(unsigned int j = 0; j < 3; ++j)
    {
      c.push_back(color[j] / 255.0);
    }
    double t = scalarRange[0] + (scalarRange[1] - scalarRange[0]) / (numColors - 1) * i;
    lut->AddRGBPoint(t, c[0], c[1], c[2]);
  }
  return lut;
}

/**
 * Create the actor for glyphing the normals.
 *
 * @param source the surface.
 * @param glyphPoints The number of points used by the mask filter.
 * @param scalarRange The range in terms of scalar minimum and maximum.
 * @param scaleFactor The scaling factor for the glyph.
 * @param lut The lookup table to use.
 *
 * @return The glyph actor.
*/

vtkSmartPointer<vtkActor> GlyphActor(vtkPolyData* source, int glyphPoints, double *scalarRange,
  double scaleFactor, vtkColorTransferFunction* lut)
{
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();
  // Subsample the dataset.
  vtkSmartPointer<vtkMaskPoints> maskPts =
    vtkSmartPointer<vtkMaskPoints>::New();
  maskPts->SetInputData(source);
  maskPts->SetOnRatio(source->GetNumberOfPoints() / glyphPoints);
  maskPts->SetRandomMode(1);

  vtkSmartPointer<vtkGlyph3D> arrowGlyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  arrowGlyph->SetScaleFactor(scaleFactor);
  arrowGlyph->SetVectorModeToUseNormal();
  arrowGlyph->SetColorModeToColorByScalar();
  arrowGlyph->SetScaleModeToScaleByVector();
  arrowGlyph->OrientOn();
  arrowGlyph->SetSourceConnection(arrowSource->GetOutputPort());
  arrowGlyph->SetInputConnection(maskPts->GetOutputPort());
  arrowGlyph->Update();

  vtkSmartPointer<vtkDataSetMapper> arrowGlyphMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  // Colour by scalars.
  arrowGlyphMapper->SetScalarRange(scalarRange);
  arrowGlyphMapper->SetColorModeToMapScalars();
  arrowGlyphMapper->ScalarVisibilityOn();
  arrowGlyphMapper->SetLookupTable(lut);
  arrowGlyphMapper->SetInputConnection(arrowGlyph->GetOutputPort());

  vtkSmartPointer<vtkActor> glyphActor =
    vtkSmartPointer<vtkActor>::New();
  glyphActor->SetMapper(arrowGlyphMapper);
  return glyphActor;
}

/**
 * Create the actor for a surface.
 *
 * @param surface The surface.
 * @param scalarRange The range in terms of scalar minimum and maximum.
 * @param lut The lookup table to use.
 *
 * @return The actor for the surface.
*/
vtkSmartPointer<vtkActor> MakeSurfaceActor(vtkPolyData* surface, double *scalarRange, vtkColorTransferFunction* lut)
{
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(surface);
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(scalarRange);
  mapper->SetColorModeToMapScalars();
  mapper->ScalarVisibilityOn();
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  return actor;
}

/**
 * Create a label.
 *
 * @param textLabel The label.
 * @param renWinSize The size of the render window. Used to set the font size.
 *
 * @return The actor for the text label.
*/
vtkSmartPointer<vtkActor2D> MakeLabel(const char* textLabel, int renWinSize)
{
  // Create one text property for all
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetJustificationToCentered();
  textProperty->SetFontSize(int(renWinSize / 20));

  vtkSmartPointer<vtkTextMapper> mapper =
    vtkSmartPointer<vtkTextMapper>::New();
  mapper->SetInput(textLabel);
  mapper->SetTextProperty(textProperty);

  vtkSmartPointer<vtkActor2D> actor =
    vtkSmartPointer<vtkActor2D>::New();
  actor->SetMapper(mapper);
  actor->SetPosition(renWinSize / 2.0, renWinSize / 20);
  return actor;
}

/**
 * Make an axis actor.
 *
 * @return The axis actor.
*/
vtkSmartPointer<vtkAxesActor> MakeAxesActor()
{
  vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
  axes->SetShaftTypeToCylinder();
  axes->SetXAxisLabelText("X");
  axes->SetYAxisLabelText("Y");
  axes->SetZAxisLabelText("Z");
  axes->SetTotalLength(1.0, 1.0, 1.0);
  axes->SetCylinderRadius(1.0 * axes->GetCylinderRadius());
  axes->SetConeRadius(1.75 * axes->GetConeRadius());
  axes->SetSphereRadius(1.0 * axes->GetSphereRadius());
  axes->GetXAxisCaptionActor2D()->GetTextActor()->GetScaledTextProperty();
  axes->GetXAxisCaptionActor2D()->GetTextActor()->SetTextScaleModeToNone();
  axes->GetYAxisCaptionActor2D()->GetTextActor()->GetScaledTextProperty();
  axes->GetYAxisCaptionActor2D()->GetTextActor()->SetTextScaleModeToNone();
  axes->GetZAxisCaptionActor2D()->GetTextActor()->GetScaledTextProperty();
  axes->GetZAxisCaptionActor2D()->GetTextActor()->SetTextScaleModeToNone();
  return axes;
}

/**
 * Create an orientation marker for a given renderer.
 *
 * @param renderer The renderer.
 * @param iren The interactor.
 *
 * @return: The orientation marker.
*/
vtkSmartPointer<vtkOrientationMarkerWidget> MakeOrientationMarker(vtkRenderer* renderer,
  vtkRenderWindowInteractor* iren)
{
  vtkSmartPointer<vtkOrientationMarkerWidget> om =
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  auto axesActor = MakeAxesActor();
  om->SetOrientationMarker(axesActor);
  // Position lower left in the viewport.
  om->SetViewport(0, 0, 0.2, 0.2);
  om->SetInteractor(iren);
  om->SetDefaultRenderer(renderer);
  om->EnabledOn();
  om->InteractiveOn();
  return om;
}

/**
 * Save the image as a PNG.
 *
 * @param ren the renderer.
 * @param fn the file name.
 * @param magnification the magnification, usually 1.
*/
void WritePNG(vtkRenderer* ren, char* fn, int magnification=1)
{
  vtkSmartPointer<vtkRenderLargeImage> renLgeIm =
    vtkSmartPointer<vtkRenderLargeImage>::New();
  vtkSmartPointer<vtkPNGWriter> imgWriter =
    vtkSmartPointer<vtkPNGWriter>::New();
  renLgeIm->SetInput(ren);
  renLgeIm->SetMagnification(magnification);
  imgWriter->SetInputConnection(renLgeIm->GetOutputPort());
  imgWriter->SetFileName(fn);
  imgWriter->Write();
}

/**
 * Demonstrates point data subdivision with the glyphing of normals on the surface.
 *
 * This program takes a surface and displays three surfaces.
 *
 * The first surface is the original surface and the second and third surfaces have
 * had linear and butterfly interpolation applied respectively.
 *
 * The user can control the object to use, normal generation, type of shading
 * and number of points to use for the normals.
*/
int main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0]
      << "sourceToUse: (PARAMETRIC_TORUS; PARAMETRIC_ELLIPSOID; BOY; SPHERE; MOBIUS; CONE; RANDOM_HILLS; SUPERQUADRIC)"
      << "[displayNormals]"
      << "[gouraudInterpolation]"
      << "[glyphPoints]" << std::endl;
    return EXIT_FAILURE;
    }

  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  Sources::SurfaceType sourceToUse = static_cast<Sources::SurfaceType>(atoi(argv[1]));
  switch (sourceToUse)
  {
    case Sources::PARAMETRIC_TORUS:
      Sources::ParametricTorusSource(polyData);
      break;
    case Sources::PARAMETRIC_ELLIPSOID:
      Sources::EllipsoidSource(polyData);
      break;
    case Sources::BOY:
      Sources::BoySource(polyData.GetPointer());
      break;
    case Sources::SPHERE:
      Sources::SphereSource(polyData);
      break;
    case Sources::MOBIUS:
      Sources::MobiusSource(polyData);
      break;
    case Sources::CONE:
      Sources::ConeSource(polyData);
      break;
    case Sources::RANDOM_HILLS:
      Sources::ParametricRandomHills(polyData);
      break;
    case Sources::SUPERQUADRIC:
      Sources::SuperquadricSource(polyData);
      break;
    default:
      std::cout << "The source " << sourceToUse << " is not available" << std::endl
                << "Available sources are: PARAMETRIC_TORUS; PARAMETRIC_ELLIPSOID; BOY; SPHERE; MOBIUS; CONE; RANDOM_HILLS; SUPERQUADRIC" << std::endl;
      return EXIT_FAILURE;
  }

  bool displayNormals = true;
  if (argc > 2)
  {
    displayNormals = (atoi(argv[2]) != 0);
  }

  bool gouraudInterpolation = true;
  if (argc > 3)
  {
    gouraudInterpolation = (atoi(argv[3]) != 0);
  }

  int glyphPoints = 50;
  if (argc > 4)
  {
    glyphPoints = atoi(argv[4]);
  }

  // The size of the render window.
  int renWinXSize = 600;
  int renWinYSize = renWinXSize / 3;
  int minRenWinDim = std::min(renWinXSize, renWinYSize);

  // [xMin, xMax, yMin, yMax, zMin, zMax]
  double *bounds = polyData->GetBounds();
  // Use this to scale the normal glyph.
  std::vector<double> dims;
  dims.push_back(std::abs(bounds[1] - bounds[0]));
  dims.push_back(std::abs(bounds[3] - bounds[2]));
  dims.push_back(std::abs(bounds[5] - bounds[4]));
  double scaleFactor = *std::min_element(dims.begin(), dims.end()) * 0.2;

  polyData->GetPointData()->GetScalars()->SetName("Elevation");
  double *scalarRange = polyData->GetScalarRange();

  vtkSmartPointer<vtkButterflySubdivisionFilter> butterfly =
    vtkSmartPointer<vtkButterflySubdivisionFilter>::New();
  butterfly->SetInputData(polyData);
  butterfly->SetNumberOfSubdivisions(3);
  butterfly->Update();

  vtkSmartPointer<vtkLinearSubdivisionFilter> linear =
    vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
  linear->SetInputData(polyData);
  linear->SetNumberOfSubdivisions(3);
  linear->Update();

  vtkSmartPointer<vtkColorTransferFunction> lut = MakeLUT(scalarRange);

  std::vector<vtkSmartPointer<vtkActor> > actors;
  actors.push_back(MakeSurfaceActor(butterfly->GetOutput(), scalarRange, lut));
  actors.push_back(MakeSurfaceActor(linear->GetOutput(), scalarRange, lut));
  actors.push_back(MakeSurfaceActor(polyData, scalarRange, lut));

  // Let's visualise the normals.
  std::vector<vtkSmartPointer<vtkActor> > glyphActors;
  if (displayNormals)
  {
    glyphActors.push_back(GlyphActor(butterfly->GetOutput(), glyphPoints, scalarRange, scaleFactor, lut));
    glyphActors.push_back(GlyphActor(linear->GetOutput(), glyphPoints, scalarRange, scaleFactor, lut));
    glyphActors.push_back(GlyphActor(polyData, glyphPoints, scalarRange, scaleFactor, lut));
  }

  std::vector<vtkSmartPointer<vtkActor2D> > labelActors;
  labelActors.push_back(MakeLabel("Butterfly Subdivision", minRenWinDim));
  labelActors.push_back(MakeLabel("Linear Subdivision", minRenWinDim));
  labelActors.push_back(MakeLabel("Original", minRenWinDim));

  std::vector<vtkSmartPointer<vtkRenderer> > ren;
  ren.push_back(vtkSmartPointer<vtkRenderer>::New());
  ren.push_back(vtkSmartPointer<vtkRenderer>::New());
  ren.push_back(vtkSmartPointer<vtkRenderer>::New());
  ren[2]->SetViewport(0, 0, 1.0 / 3.0, 1);  // Original
  ren[1]->SetViewport(1.0 / 3.0, 0, 2.0 / 3.0, 1);  // Linear
  ren[0]->SetViewport(2.0 / 3.0, 0, 1, 1);  // Butterfly

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkNamedColors> nc =
    vtkSmartPointer<vtkNamedColors>::New();

  // Orientation markers.
  std::vector<vtkSmartPointer<vtkOrientationMarkerWidget> > om;

  // Shared camera
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();

  // Make the imaging pipelines.
  for(unsigned int i = 0; i < ren.size(); ++i)
  {
    renWin->AddRenderer(ren[i]);

    ren[i]->AddActor(actors[i]);
    ren[i]->AddActor(labelActors[i]);
    ren[i]->SetBackground(nc->GetColor3d("SlateGray").GetData());
    ren[i]->SetActiveCamera(camera);
    if (displayNormals)
    {
      ren[i]->AddActor(glyphActors[i]);
    }

    om.push_back(MakeOrientationMarker(ren[i], iren));
  }
  renWin->SetSize(renWinXSize, renWinYSize);

  iren->Initialize();

  if (gouraudInterpolation)
  {
    for (unsigned int i = 0; i < actors.size(); ++i)
    {
      actors[i]->GetProperty()->SetInterpolationToGouraud();
    }
  }
  else
  {
    for (unsigned int i = 0; i < actors.size(); ++i)
    {
      actors[i]->GetProperty()->SetInterpolationToFlat();
    }
  }
  renWin->Render();
  ren[0]->ResetCamera();
  renWin->Render();

  iren->Start();

  // WritePNG(iren->GetRenderWindow()->GetRenderers()->GetFirstRenderer(), "PointDataSubdivision.png");

  return EXIT_SUCCESS;
}
