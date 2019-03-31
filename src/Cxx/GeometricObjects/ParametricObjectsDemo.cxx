#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkMath.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNamedColors.h>
#include <vtkParametricFunctionSource.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

#include <vtkParametricBoy.h>
#include <vtkParametricConicSpiral.h>
#include <vtkParametricCrossCap.h>
#include <vtkParametricDini.h>
#include <vtkParametricEllipsoid.h>
#include <vtkParametricEnneper.h>
#include <vtkParametricFigure8Klein.h>
#include <vtkParametricKlein.h>
#include <vtkParametricMobius.h>
#include <vtkParametricRandomHills.h>
#include <vtkParametricRoman.h>
#include <vtkParametricSpline.h>
#include <vtkParametricSuperEllipsoid.h>
#include <vtkParametricSuperToroid.h>
#include <vtkParametricTorus.h>
// Extra parametric surfaces.
#include <vtkParametricBohemianDome.h>
#include <vtkParametricBour.h>
#include <vtkParametricCatalanMinimal.h>
#include <vtkParametricHenneberg.h>
#include <vtkParametricKuen.h>
#include <vtkParametricPluckerConoid.h>
#include <vtkParametricPseudosphere.h>

// For glyphing
#include <vtkArrowSource.h>
#include <vtkDataSet.h>
#include <vtkGlyph3D.h>
#include <vtkMaskPoints.h>

// For writing out the image.
#include <vtkBMPWriter.h>
#include <vtkImageWriter.h>
#include <vtkJPEGWriter.h>
#include <vtkPNGWriter.h>
#include <vtkPNMWriter.h>
#include <vtkPostScriptWriter.h>
#include <vtkTIFFWriter.h>
#include <vtkWindowToImageFilter.h>

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <string>
#include <vector>

namespace {

// For holding the arguments from the command line
// True/false non-positional parameters with optional value(s)
// For positional parameters, use the variable name as key,
// e.g. varName,true,value
typedef std::map<std::string, std::pair<bool, std::vector<std::string>>>
    TCmdArgs;

/**
 * Show the command lime parameters.
 *
 * @param fn: The program name.
 */
void ShowUsage(std::string fn);

/**
 * Parse the parameters from the command line.
 *
 * @param cmdArgs The command arguments (initialised before calling this
 * function)
 * @param cmdArgs The vector of strings from the command line.
 *
 * @return true if the parse was successful, false if unsuccessful or if help
 * was specified.
 */
bool ParseArgs(TCmdArgs& cmdArgs, std::vector<std::string> const& argvArgs);

/**
 * Create a map of the parametric functions and set some parameters.
 * The first key groups the parametric functions and the
 *   second key is the name of the function.
 *
 * @return The map of functions.
 */
std::map<int, std::map<std::string, vtkSmartPointer<vtkParametricFunction>>>
GetParametricFunctions();

/**
 * Write the render window view to an image file.
 *
 * Image types supported are:
 *  BMP, JPEG, PNM, PNG, PostScript, TIFF.
 * The default parameters are used for all writers, change as needed.
 *
 * @param fileName The file name, if no extension then PNG is assumed.
 * @param renWin The render window.
 * @param rgba Used to set the buffer type.
 *
 */
void WriteImage(std::string const& fileName, vtkRenderWindow* renWin,
                bool rgba = true);

/**
 * Get the centre of the object from the bounding box.
 */
std::vector<double> GetCentre(const std::vector<double>& bounds);

/**
 * Calculate the maximum length of side of the bounding box.
 */
double GetMaximumLength(const std::vector<double>& bounds);

/**
 * Display the dimensions of the bounding box, maximum diagonal length
 *    and coordinates of the centre.
 *
 * @param name: The name of the object.
 * @param index: The index of the object.
 * @param bounds: The bounding box of the object.
 *
 */
void DisplayBoundingBoxAndCenter(std::string const& name, int const& index,
                                 std::vector<double> const& bounds);

} // namespace

int main(int argc, char* argv[])
{
  //  std::pair<std::map<std::string, bool>, std::pair<std::string, int>>

  // These are the default arguments
  TCmdArgs cmdArgs;
  cmdArgs["w"].first = false;
  cmdArgs["b"].first = false;
  cmdArgs["n"].first = false;
  cmdArgs["s"].first = false;

  // Let's get any command arguments
  std::vector<std::string> argvArgs;
  for (auto i = 1; i < argc; ++i)
  {
    argvArgs.push_back(argv[i]);
  }
  if (!argvArgs.empty())
  {
    if (!ParseArgs(cmdArgs, argvArgs))
    {
      ShowUsage(argv[0]);
      return EXIT_SUCCESS;
    }
  }

  std::pair<std::string, int> singleSurface;
  if (cmdArgs["s"].first)
  {
    if (cmdArgs["s"].second.size() > 0)
    {
      singleSurface.first = cmdArgs["s"].second[0];
      singleSurface.second = -1;
    }
    else
    {
      std::cerr << "Surface name is missing." << std::endl;
      return EXIT_FAILURE;
    }
  }

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto rendererSize = 200;
  auto gridColumnDimensions = 5;
  auto gridRowDimensions = 5;

  if (cmdArgs["s"].first)
  {
    rendererSize = 800;
    gridColumnDimensions = 1;
    gridRowDimensions = 1;
  }

  // Create one text property for all
  auto textProperty = vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetJustificationToCentered();
  textProperty->SetFontSize(rendererSize / 12);
  textProperty->SetColor(colors->GetColor3d("LavenderBlush").GetData());

  // Create a parametric function source, renderer, mapper, and actor
  // for each object
  std::vector<vtkSmartPointer<vtkParametricFunctionSource>> pfnSrcs;
  std::vector<vtkSmartPointer<vtkRenderer>> renderers;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  std::vector<vtkSmartPointer<vtkActor>> actors;
  std::vector<vtkSmartPointer<vtkTextMapper>> textmappers;
  std::vector<vtkSmartPointer<vtkActor2D>> textactors;

  // Glyph the normals.
  std::vector<vtkSmartPointer<vtkMaskPoints>> maskPts;
  std::vector<vtkSmartPointer<vtkArrowSource>> arrow;
  std::vector<vtkSmartPointer<vtkGlyph3D>> glyph;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> glyphMapper;
  std::vector<vtkSmartPointer<vtkActor>> glyphActor;

  auto backProperty = vtkSmartPointer<vtkProperty>::New();
  if (cmdArgs["b"].first)
  {
    backProperty->SetColor(colors->GetColor3d("Peru").GetData());
  }

  std::vector<std::vector<double>> boundingBox;

  // Get the parametric functions and build the pipeline
  auto pfn = GetParametricFunctions();

  if (cmdArgs["s"].first)
  {
    // Is the surface name in the map?
    std::vector<bool> surfaceExists;
    for (auto& t : pfn)
    {
      if (t.second.find(cmdArgs["s"].second[0]) == t.second.end())
        surfaceExists.push_back(false);
      else
        surfaceExists.push_back(true);
    }
    if (std::find(std::begin(surfaceExists), std::end(surfaceExists), true) ==
        end(surfaceExists))
    {
      // All entries in surfaceExists are false
      std::cout << "Nonexistent surface: " << cmdArgs["s"].second[0]
                << std::endl;
      return EXIT_FAILURE;
    }
  }

  // The count of parametric objects
  auto objCount = 0;
  for (auto t : pfn)
  {
    for (auto obj : t.second)
    {
      if (cmdArgs["s"].first)
      {
        if (obj.first == singleSurface.first)
        {
          singleSurface.second = objCount;
        }
      }
      pfnSrcs.push_back(vtkSmartPointer<vtkParametricFunctionSource>::New());
      pfnSrcs[objCount]->SetParametricFunction(pfn[t.first][obj.first]);
      pfnSrcs[objCount]->SetUResolution(51);
      pfnSrcs[objCount]->SetVResolution(51);
      pfnSrcs[objCount]->SetWResolution(51);
      pfnSrcs[objCount]->Update();

      mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
      mappers[objCount]->SetInputConnection(pfnSrcs[objCount]->GetOutputPort());

      actors.push_back(vtkSmartPointer<vtkActor>::New());
      actors[objCount]->SetMapper(mappers[objCount]);
      actors[objCount]->GetProperty()->SetColor(
          colors->GetColor3d("NavajoWhite").GetData());
      if (cmdArgs["b"].first)
      {

        actors[objCount]->SetBackfaceProperty(backProperty);
      }

      textmappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
      textmappers[objCount]->SetInput(obj.first.c_str());
      textmappers[objCount]->SetTextProperty(textProperty);

      textactors.push_back(vtkSmartPointer<vtkActor2D>::New());
      textactors[objCount]->SetMapper(textmappers[objCount]);
      textactors[objCount]->SetPosition(rendererSize / 2.0, 8);

      renderers.push_back(vtkSmartPointer<vtkRenderer>::New());

      double bounds[6];
      pfnSrcs[objCount]->GetOutput()->GetBounds(bounds);
      std::vector<double> v(std::begin(bounds), std::end(bounds));
      boundingBox.push_back(v);
      // DisplayBoundingBoxAndCenter(obj.first, objCount, v);

      if (cmdArgs["n"].first)
      {
        // Glyphing
        maskPts.push_back(vtkSmartPointer<vtkMaskPoints>::New());
        maskPts[objCount]->RandomModeOn();
        maskPts[objCount]->SetMaximumNumberOfPoints(150);
        maskPts[objCount]->SetInputConnection(
            pfnSrcs[objCount]->GetOutputPort());

        arrow.push_back(vtkSmartPointer<vtkArrowSource>::New());
        arrow[objCount]->SetTipResolution(16);
        arrow[objCount]->SetTipLength(0.3);
        arrow[objCount]->SetTipRadius(0.1);

        double glyphScale = GetMaximumLength(boundingBox[objCount]);

        glyph.push_back(vtkSmartPointer<vtkGlyph3D>::New());
        glyph[objCount]->SetSourceConnection(arrow[objCount]->GetOutputPort());
        glyph[objCount]->SetInputConnection(maskPts[objCount]->GetOutputPort());
        glyph[objCount]->SetVectorModeToUseNormal();
        glyph[objCount]->SetScaleFactor(glyphScale / 10.0);
        glyph[objCount]->OrientOn();
        glyph[objCount]->Update();

        glyphMapper.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
        glyphMapper[objCount]->SetInputConnection(
            glyph[objCount]->GetOutputPort());

        glyphActor.push_back(vtkSmartPointer<vtkActor>::New());
        glyphActor[objCount]->SetMapper(glyphMapper[objCount]);
        glyphActor[objCount]->GetProperty()->SetColor(
            colors->GetColor3d("GreenYellow").GetData());
      }
      objCount++;
    }
  }

  // Need a renderer even if there is no actor
  for (auto i = objCount; i < gridColumnDimensions * gridRowDimensions; i++)
  {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    static_cast<vtkRenderer*>(renderers.back().GetPointer())
        ->SetBackground(colors->GetColor3d("MidnightBlue").GetData());
  }

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(rendererSize * gridColumnDimensions,
                        rendererSize * gridRowDimensions);

  for (auto row = 0; row < gridRowDimensions; row++)
  {
    for (auto col = 0; col < gridColumnDimensions; col++)
    {
      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {
          static_cast<double>(col) * rendererSize /
              (gridColumnDimensions * rendererSize),
          static_cast<double>(gridRowDimensions - (row + 1)) * rendererSize /
              (gridRowDimensions * rendererSize),
          static_cast<double>(col + 1) * rendererSize /
              (gridColumnDimensions * rendererSize),
          static_cast<double>(gridRowDimensions - row) * rendererSize /
              (gridRowDimensions * rendererSize)};
      if (!cmdArgs["s"].first)
      {
        auto index = row * gridColumnDimensions + col;
        renderWindow->AddRenderer(renderers[index]);
        renderers[index]->SetViewport(viewport);
        if (index > objCount - 1)
        {
          continue;
        }
        renderers[index]->AddActor(actors[index]);
        if (cmdArgs["n"].first)
        {
          renderers[index]->AddActor(glyphActor[index]);
        }
        renderers[index]->AddActor(textactors[index]);
        renderers[index]->SetBackground(
            colors->GetColor3d("MidnightBlue").GetData());
        renderers[index]->ResetCamera();
        renderers[index]->GetActiveCamera()->Azimuth(30);
        renderers[index]->GetActiveCamera()->Elevation(-30);
        renderers[index]->GetActiveCamera()->Zoom(0.9);
        renderers[index]->ResetCameraClippingRange();
      }

      else
      {
        auto index = singleSurface.second;
        if (index != -1)
        {
          renderWindow->AddRenderer(renderers[index]);
          renderers[index]->SetViewport(viewport);
          renderers[index]->AddActor(actors[index]);
          if (cmdArgs["n"].first)
          {
            renderers[index]->AddActor(glyphActor[index]);
          }
          renderers[index]->AddActor(textactors[index]);
          renderers[index]->SetBackground(
              colors->GetColor3d("MidnightBlue").GetData());
          renderers[index]->ResetCamera();
          renderers[index]->GetActiveCamera()->Azimuth(30);
          renderers[index]->GetActiveCamera()->Elevation(-30);
          renderers[index]->GetActiveCamera()->Zoom(0.9);
          renderers[index]->ResetCameraClippingRange();
        }
      }
    }
  }

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  if (cmdArgs["s"].first)
  {
    renderWindow->SetWindowName(singleSurface.first.c_str());
  }
  else
  {
    renderWindow->SetWindowName("ParametricObjectsDemo");
  }
  renderWindow->Render();
  if (cmdArgs["w"].first)
  {
    // -------------------------------
    // Save the image
    // -------------------------------
    if (cmdArgs["s"].first)
    {
      WriteImage(singleSurface.first, renderWindow, false);
    }
    else
    {
      WriteImage("ParametricObjectsDemo", renderWindow, false);
    }
  }

  interactor->Start();

  return EXIT_SUCCESS;
}

namespace {

void ShowUsage(std::string fn)
{
  // Remove the folder (if present) then remove the extension in this order
  // since the folder name may contain perionds.
  auto last_slash_idx = fn.find_last_of("\\/");
  if (std::string::npos != last_slash_idx)
  {
    fn.erase(0, last_slash_idx + 1);
  }
  auto period_idx = fn.rfind('.');
  if (std::string::npos != period_idx)
  {
    fn.erase(period_idx);
  }
  std::cout << "\nusage: " << fn << "[-h][-s SURFACE_NAME][-w][-b][-n]\n\n"
            << "Display the parametric surfaces.\n\n"
            << "optional arguments:\n"
            << "  -h, --help            show this help message and exit\n"
            << "  -s SURFACE_NAME, --surface_name SURFACE_NAME\n"
            << "                        The name of the surface.\n"
            << "  -w, --write_image     Write out the the image.\n"
            << "  -b, --back_face       Color the back-face.\n"
            << "  -n, --normals         Display normals.\n"
            << std::endl;
}

bool ParseArgs(TCmdArgs& cmdArgs, std::vector<std::string> const& argvArgs)
{
  if (!argvArgs.empty())
  {
    for (auto it = argvArgs.begin(); it != argvArgs.end(); ++it)
    {
      if (*it == "-w")
      {
        cmdArgs["w"].first = true;
      }
      if (*it == "-b")
      {
        cmdArgs["b"].first = true;
      }
      if (*it == "-n")
      {
        cmdArgs["n"].first = true;
      }
      if (*it == "-s")
      {
        if (std::next(it) != argvArgs.end())
        {
          ++it;
          std::string fn = *it;
          if (fn[0] != '-')
          {
            cmdArgs["s"].first = true;
            cmdArgs["s"].second.push_back(fn);
          }
          else
          {
            std::cerr << "-s must be followed by a surface name." << std::endl;
            return false;
          }
        }
        else
        {
          std::cerr << "-s must be followed by a surface name." << std::endl;
          return false;
        }
      }
    }
  }
  return true;
}

std::map<int, std::map<std::string, vtkSmartPointer<vtkParametricFunction>>>
GetParametricFunctions()
{
  std::map<int, std::map<std::string, vtkSmartPointer<vtkParametricFunction>>>
      pfn;
  pfn[0]["Boy"] = vtkSmartPointer<vtkParametricBoy>::New();
  pfn[0]["ConicSpiral"] = vtkSmartPointer<vtkParametricConicSpiral>::New();
  pfn[0]["CrossCap"] = vtkSmartPointer<vtkParametricCrossCap>::New();
  pfn[0]["Dini"] = vtkSmartPointer<vtkParametricDini>::New();
  pfn[0]["Ellipsoid"] = vtkSmartPointer<vtkParametricEllipsoid>::New();
  pfn[0]["Enneper"] = vtkSmartPointer<vtkParametricEnneper>::New();
  pfn[0]["Figure8Klein"] = vtkSmartPointer<vtkParametricFigure8Klein>::New();
  pfn[0]["Klein"] = vtkSmartPointer<vtkParametricKlein>::New();
  pfn[0]["Mobius"] = vtkSmartPointer<vtkParametricMobius>::New();
  pfn[0]["RandomHills"] = vtkSmartPointer<vtkParametricRandomHills>::New();
  pfn[0]["Roman"] = vtkSmartPointer<vtkParametricRoman>::New();
  pfn[0]["SuperEllipsoid"] =
      vtkSmartPointer<vtkParametricSuperEllipsoid>::New();
  pfn[0]["SuperToroid"] = vtkSmartPointer<vtkParametricSuperToroid>::New();
  pfn[0]["Torus"] = vtkSmartPointer<vtkParametricTorus>::New();
  pfn[0]["Spline"] = vtkSmartPointer<vtkParametricSpline>::New();
  // Extra parametric surfaces.
  pfn[1]["BohemianDome"] = vtkSmartPointer<vtkParametricBohemianDome>::New();
  pfn[1]["Bour"] = vtkSmartPointer<vtkParametricBour>::New();
  pfn[1]["CatalanMinimal"] =
      vtkSmartPointer<vtkParametricCatalanMinimal>::New();
  pfn[1]["Henneberg"] = vtkSmartPointer<vtkParametricHenneberg>::New();
  pfn[1]["Kuen"] = vtkSmartPointer<vtkParametricKuen>::New();
  pfn[1]["PluckerConoid"] = vtkSmartPointer<vtkParametricPluckerConoid>::New();
  pfn[1]["Pseudosphere"] = vtkSmartPointer<vtkParametricPseudosphere>::New();

  // Now set some parameters.
  static_cast<vtkParametricEllipsoid*>(pfn[0]["Ellipsoid"].GetPointer())
      ->SetXRadius(0.5);
  static_cast<vtkParametricEllipsoid*>(pfn[0]["Ellipsoid"].GetPointer())
      ->SetYRadius(2.0);
  static_cast<vtkParametricMobius*>(pfn[0]["Mobius"].GetPointer())
      ->SetRadius(2.0);
  static_cast<vtkParametricMobius*>(pfn[0]["Mobius"].GetPointer())
      ->SetMinimumV(-0.5);
  static_cast<vtkParametricMobius*>(pfn[0]["Mobius"].GetPointer())
      ->SetMaximumV(0.5);
  static_cast<vtkParametricRandomHills*>(pfn[0]["RandomHills"].GetPointer())
      ->AllowRandomGenerationOn();
  static_cast<vtkParametricRandomHills*>(pfn[0]["RandomHills"].GetPointer())
      ->SetRandomSeed(1);
  static_cast<vtkParametricRandomHills*>(pfn[0]["RandomHills"].GetPointer())
      ->SetNumberOfHills(30);
  static_cast<vtkParametricSuperEllipsoid*>(
      pfn[0]["SuperEllipsoid"].GetPointer())
      ->SetN1(0.5);
  static_cast<vtkParametricSuperEllipsoid*>(
      pfn[0]["SuperEllipsoid"].GetPointer())
      ->SetN2(0.4);
  static_cast<vtkParametricSuperToroid*>(pfn[0]["SuperToroid"].GetPointer())
      ->SetN1(0.5);
  static_cast<vtkParametricSuperToroid*>(pfn[0]["SuperToroid"].GetPointer())
      ->SetN2(3.0);
  // The spline needs points
  auto inputPoints = vtkSmartPointer<vtkPoints>::New();
  auto rng = vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
  rng->SetSeed(8775070);
  for (auto p = 0; p < 10; p++)
  {
    std::array<double, 3> xyz;
    for (auto& idx : xyz)
    {
      idx = rng->GetRangeValue(-1.0, 1.0);
      rng->Next();
    }
    inputPoints->InsertNextPoint(xyz.data());
  }
  static_cast<vtkParametricSpline*>(pfn[0]["Spline"].GetPointer())
      ->SetPoints(inputPoints);
  // Extra parametric surfaces.
  static_cast<vtkParametricBohemianDome*>(pfn[1]["BohemianDome"].GetPointer())
      ->SetA(5.0);
  static_cast<vtkParametricBohemianDome*>(pfn[1]["BohemianDome"].GetPointer())
      ->SetB(1.0);
  static_cast<vtkParametricBohemianDome*>(pfn[1]["BohemianDome"].GetPointer())
      ->SetC(2.0);
  static_cast<vtkParametricKuen*>(pfn[1]["Kuen"].GetPointer())
      ->SetDeltaV0(0.001);
  return pfn;
}

std::vector<double> GetCentre(const std::vector<double>& bounds)
{
  std::vector<double> centre;
  if (bounds.size() != 6)
  {
    return centre;
  }
  for (unsigned int i = 1; i < bounds.size(); i += 2)
  {
    centre.push_back(bounds[i] - (bounds[i] - bounds[i - 1]) / 2.0);
  }
  return centre;
}

double GetMaximumLength(const std::vector<double>& bounds)
{
  auto maxLen = -1.0;
  if (bounds.size() != 6)
  {
    return maxLen;
  }
  for (auto i = 0; i < bounds.size(); i += 2)
  {
    maxLen = std::max(maxLen, std::abs(bounds[i + 1] - bounds[i]));
  }
  return maxLen;
}

void DisplayBoundingBoxAndCenter(std::string const& name, int const& index,
                                 std::vector<double> const& bounds)
{
  if (bounds.size() != 6)
  {
    return;
  }
  auto maxLength = GetMaximumLength(bounds);
  auto centre = GetCentre(bounds);
  std::cout << std::left << std::setw(21) << name << std::right << ": "
            << std::setw(2) << index << "\n"
            << std::left << std::setw(21) << "  Bounds (min, max)"
            << ": x:(" << std::right << std::fixed << std::setw(6)
            << std::setprecision(2) << bounds[0] << ", " << std::setw(6)
            << bounds[1] << ") y:(" << std::setw(6) << bounds[2] << ", "
            << std::setw(6) << bounds[3] << ") z:(" << std::setw(6) << bounds[4]
            << ", " << std::setw(6) << bounds[5] << ")\n"
            << std::left << std::setw(21) << "  Maximum side length"
            << ": " << std::right << std::setw(6) << maxLength << "\n"
            << std::left << std::setw(21) << "  Centre (x, y, z)"
            << ": (" << std::right << std::setw(6) << centre[0] << ", "
            << std::setw(6) << centre[1] << ", " << std::setw(6) << centre[2]
            << ")\n"
            << std::endl;
}

void WriteImage(std::string const& fileName, vtkRenderWindow* renWin, bool rgba)
{
  if (!fileName.empty())
  {
    std::string fn = fileName;
    std::string path;
    std::string ext;
    auto found = fn.find_last_of(".");
    if (found == std::string::npos)
    {
      path = fn;
      ext = ".png";
      fn += ext;
    }
    else
    {
      path = fileName.substr(0, found);
      ext = fileName.substr(found, fileName.size());
    }
    std::locale loc;
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [=](char const& c) { return std::tolower(c, loc); });
    auto writer = vtkSmartPointer<vtkImageWriter>::New();
    if (ext == ".bmp")
    {
      writer = vtkSmartPointer<vtkBMPWriter>::New();
    }
    else if (ext == ".jpg")
    {
      writer = vtkSmartPointer<vtkJPEGWriter>::New();
    }
    else if (ext == ".pnm")
    {
      writer = vtkSmartPointer<vtkPNMWriter>::New();
    }
    else if (ext == ".ps")
    {
      if (rgba)
      {
        rgba = false;
      }
      writer = vtkSmartPointer<vtkPostScriptWriter>::New();
    }
    else if (ext == ".tiff")
    {
      writer = vtkSmartPointer<vtkTIFFWriter>::New();
    }
    else
    {
      writer = vtkSmartPointer<vtkPNGWriter>::New();
    }
    auto window_to_image_filter =
        vtkSmartPointer<vtkWindowToImageFilter>::New();
    window_to_image_filter->SetInput(renWin);
    window_to_image_filter->SetScale(1); // image quality
    if (rgba)
    {
      window_to_image_filter->SetInputBufferTypeToRGBA();
    }
    else
    {
      window_to_image_filter->SetInputBufferTypeToRGB();
    }
    // Read from the front buffer.
    window_to_image_filter->ReadFrontBufferOff();
    window_to_image_filter->Update();

    writer->SetFileName(fn.c_str());
    writer->SetInputConnection(window_to_image_filter->GetOutputPort());
    writer->Write();
  }
  else
  {
    std::cerr << "No filename provided." << std::endl;
  }

  return;
}

} // namespace
