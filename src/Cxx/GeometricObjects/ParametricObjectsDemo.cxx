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
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace {

// Holds the arguments from the command line as a map.
// e.g. key = name; value = (true|false,[value_0 ... value_n])
typedef std::map<std::string, std::pair<bool, std::vector<std::string>>>
    TCmdArgs;

class CommandLineParser
{
public:
  /**
   * @param argvArgs: the command line arguments as a vector of strings.
   * @param optArgs: the non-positional keys and their value.
   * @param optArgsParam: the non-positional keys that have parameters and their
   * value.
   * @param posNum: the expected number of positional variables.
   * @param posNumKName: the name of the positional values.
   */
  CommandLineParser(std::vector<std::string>& argvArgs,
                    std::map<std::string, std::string>& optArgs,
                    std::map<std::string, std::string>& optArgsParam,
                    int posNum = 0, std::string const& posName = "_PKN");

  ~CommandLineParser();

public:
  /**
   * Parse the parameters from the command line.
   *
   * @return true if the parse was successful, false if unsuccessful.
   */
  bool Parse();

  /**
   * Get the parsed command line arguments.
   *
   * @return The parsed arguments.
   */
  TCmdArgs GetCommandArguments()
  {
    return this->cmdArgs;
  }

  /**
   * @return The error message if Parse() failed.
   */
  std::string GetParseError()
  {
    return this->parseError;
  }

  /**
   * @return The key name used to identify positional arguments.
   */
  std::string getPositionalKeyName()
  {
    return this->posName;
  }

  /**
   * @return A string of the parsed command arguments.
   */
  std::string DisplayCommandArguments();

private:
  /**
   * Separate the key from the value, e.g -kv -> k v.
   *
   * @return The vector with the keys separated from their value(s).
   */
  std::vector<std::string> SeparateKV();

  /**
   * Find any unknown non-positional keys.
   *
   * @return If unknown keys were found, true is returned.
   */
  bool HasUnknownKeys();

  /**
   * Find any duplicate non-positional keys.
   *
   * @return If duplicate keys were found, true is returned.
   */
  bool HasDuplicateKeys();

  /**
   * Take a map and get the set of values in the map.
   *
   * @param m: The map.
   * @param s: The set of values from the map.
   */
  template <typename K, typename V>
  void GetSetOfValues(std::map<K, V> const& m, std::set<V>& s);

  /**
   * Build a map of aliases for the keys from the key/value pairs.
   *
   * @param m: A map of key, value pairs.
   * @param aliases: A map of aliases keyed by value.
   */
  template <typename K, typename V>
  void FindAliases(std::map<K, V> m,
                   std::map<V, std::pair<std::vector<K>, int>>& aliases);

private:
  TCmdArgs cmdArgs;
  std::map<std::string, std::pair<std::vector<std::string>, int>> aliases;
  std::vector<std::string> cmdLineVec;
  std::map<std::string, std::string>& optArgs;
  std::map<std::string, std::string>& optArgsParam;
  int posNum;
  std::string posName;
  std::string parseError;
  std::vector<std::string> cl;
};

/**
 * Show the command lime parameters.
 *
 * @param fn: The program name.
 */
std::string ShowUsage(std::string fn);

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
  // These two maps need to be filled in by the user.
  // key: Optional arguments such as -f or --foo with no parameters.
  // value: A suitable name. For the keys -f or --foo, the name would be the
  // same e.g f.
  std::map<std::string, std::string> optArgs;
  // key: Optional arguments requiring one or more paramters such as -s fn or
  // --some_file fn. value: A suitable name. For the keys -s or --some_file, the
  // name would be the same e.g s. To handle non-optional arguments we use a
  // special key: _PKN (which can be user defined).
  std::map<std::string, std::string> optArgsParam;

  // Specify key/value pairs for the arguments we want.
  optArgs["-b"] = "b";
  optArgs["-n"] = "n";
  optArgs["-w"] = "w";
  // These are followed by one or more parameters on the command line.
  optArgsParam["-s"] = "s";

  // The command line arguments
  std::vector<std::string> cmdVec;
  for (auto i = 1; i < argc; ++i)
  {
    cmdVec.push_back(argv[i]);
  }

  CommandLineParser clp(cmdVec, optArgs, optArgsParam);
  if (!cmdVec.empty())
  {
    // Usually -h and --help are reserved for help.
    if (std::any_of(cmdVec.begin(), cmdVec.end(), [](const std::string& str) {
          return str.size() > 0 && (str == "-h" || str == "--help");
        }))
    {
      std::cout << ShowUsage(argv[0]) << std::endl;
      return EXIT_SUCCESS;
    }
    if (!clp.Parse())
    {
      std::cerr << clp.GetParseError() << std::endl;
      std::cerr << ShowUsage(argv[0]) << std::endl;
      return EXIT_FAILURE;
    }
  }
  TCmdArgs cmdArgs = clp.GetCommandArguments();
  // std::cout << clp.DisplayCommandArguments() << std::endl;

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
  std::vector<std::string> sortedNames;
  for (auto t : pfn)
  {
    for (auto obj : t.second)
    {
      sortedNames.push_back(obj.first);
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
    sortedNames.push_back("");
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
        // Normals can only be computed for polygons and triangle strips.
        // The Spline is a line.
        if (cmdArgs["n"].first && sortedNames[index] != "Spline")
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
          // Normals can only be computed for polygons and triangle strips.
          // The Spline is a line.
          if (cmdArgs["n"].first && singleSurface.first != "Spline")
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

std::string ShowUsage(std::string fn)
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
  std::ostringstream os;
  os << "\nusage: " << fn << "[-h][-s SURFACE_NAME][-w][-b][-n]\n\n"
     << "Display the parametric surfaces.\n\n"
     << "optional arguments:\n"
     << "  -h                    show this help message and exit\n"
     << "  -s SURFACE_NAME       The name of the surface.\n"
     << "  -w                    Write out the the image.\n"
     << "  -b                    Color the back-face.\n"
     << "  -n                    Display normals.\n"
     << std::endl;
  return os.str();
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
  for (auto i = 0; i < int(bounds.size()); i += 2)
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
    std::string ext;
    auto found = fn.find_last_of(".");
    if (found == std::string::npos)
    {
      ext = ".png";
      fn += ext;
    }
    else
    {
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


CommandLineParser::CommandLineParser(
    std::vector<std::string>& cmdLineVec,
    std::map<std::string, std::string>& optArgs,
    std::map<std::string, std::string>& optArgsParam, int posNum,
    std::string const& posName)
  : cmdLineVec(cmdLineVec),
    optArgs(optArgs),
    optArgsParam(optArgsParam),
    posNum(posNum),
    posName(posName)
{
  // Make a set of all the values.
  std::set<std::string> pVals;
  this->GetSetOfValues(this->optArgs, pVals);
  this->GetSetOfValues(this->optArgsParam, pVals);

  // Set the default arguments
  for (auto p : pVals)
  {
    this->cmdArgs[p].first = false;
  }

  // Get the aliases
  this->FindAliases(this->optArgsParam, this->aliases);
  this->FindAliases(this->optArgs, this->aliases);

  cl = this->SeparateKV();
}

CommandLineParser::~CommandLineParser() = default;

std::vector<std::string> CommandLineParser::SeparateKV()
{
  // For keys with parameters, short commands like -xy need to be split into
  // -x y.
  std::vector<std::string> cl;
  if (!this->optArgsParam.empty())
  {
    for (auto v : this->cmdLineVec)
    {
      auto a = v.substr(0, 2);
      if (this->optArgsParam.count(a) > 0 && v.size() > 2)
      {
        cl.push_back(a);
        cl.push_back(v.substr(2));
      }
      else
      {
        cl.push_back(v);
      }
    }
  }
  return cl;
}

bool CommandLineParser::HasUnknownKeys()
{
  auto hasKV = !this->optArgsParam.empty();
  auto hasNKV = !this->optArgs.empty();
  std::vector<std::string> unknownKeys;
  for (auto v : this->cl)
  {
    if (v[0] == '-' || v.substr(0, 2) == "--")
    {
      if ((hasKV && this->optArgsParam.count(v) > 0) ||
          (hasNKV && this->optArgs.count(v) > 0))
      {
        continue;
      }
      else
      {
        unknownKeys.push_back(v);
      }
    }
  }
  if (unknownKeys.size() > 0)
  {
    std::ostringstream os;
    os << "Unknown parameters found: ";
    std::copy(std::begin(unknownKeys), std::prev(std::end(unknownKeys)),
              std::ostream_iterator<std::string>(os, ", "));
    os << unknownKeys.back();
    this->parseError = os.str();
    return true;
  }
  return false;
}

bool CommandLineParser::HasDuplicateKeys()
{
  // Look for duplicate non-positional parameters.
  for (auto k : this->optArgsParam)
  {
    auto c = std::count(this->cl.begin(), this->cl.end(), k.first);
    this->aliases[k.second].second += int(c);
  }
  for (auto k : this->optArgs)
  {
    auto c = std::count(this->cl.begin(), this->cl.end(), k.first);
    this->aliases[k.second].second += int(c);
  }
  std::map<std::string, std::vector<std::string>> duplicates;
  for (auto v : this->aliases)
  {
    if (v.second.second > 1)
    {
      duplicates[v.first] = v.second.first;
    }
  }
  if (duplicates.size() > 0)
  {
    std::ostringstream os;
    os << "Duplicated parameters found: ";
    for (auto d : duplicates)
    {
      os << "(";
      std::copy(std::begin(d.second), std::prev(std::end(d.second)),
                std::ostream_iterator<std::string>(os, ", "));
      os << d.second.back();
      os << ") ";
    }
    // Get rid of trailing spaces
    auto last = os.str().find_last_not_of(' ');
    this->parseError = os.str().substr(0, last + 1);
    return true;
  }
  return false;
}

bool CommandLineParser::Parse()
{
  this->parseError.clear();

  if (!this->cl.empty())
  {
    if (HasUnknownKeys() || HasDuplicateKeys())
    {
      return false;
    }

    std::vector<std::string> positionalArguments;
    for (auto it = this->cl.begin(); it != this->cl.end(); ++it)
    {
      if (!this->optArgs.empty())
      {
        if (this->optArgs.count(*it) > 0)
        {
          this->cmdArgs[this->optArgs[*it]].first = true;
          continue;
        }
      }
      if (!this->optArgsParam.empty())
      {
        if (this->optArgsParam.count(*it) > 0)
        {
          if (std::next(it) != this->cl.end())
          {
            auto key = this->optArgsParam[*it];
            while (std::next(it) != this->cl.end())
            {
              if ((*std::next(it))[0] == '-')
              {
                break;
              }
              ++it;

              std::string fn = *it;
              if (fn[0] != '-')
              {
                if (!this->cmdArgs[key].first)
                {
                  this->cmdArgs[key].first = true;
                }
                this->cmdArgs[key].second.push_back(fn);
              }
              else
              {
                if (this->cmdArgs[key].second.empty())
                {
                  std::ostringstream os;
                  os << key << " must be followed by a parameter.";
                  this->parseError = os.str();
                  return false;
                }
                else
                {
                  break;
                }
              }
            }
          }
          else
          {
            std::ostringstream os;
            os << *it
               << " must be followed by a parameter, reached the end of the "
                  "commands.";
            this->parseError = os.str();
            return false;
          }
          continue;
        }
      }
      positionalArguments.push_back(*it);
    }
    if (this->posNum != int(positionalArguments.size()))
    {
      std::ostringstream os;
      os << "Expected " << this->posNum << " positional arguments, got "
         << positionalArguments.size() << " instead.";
      this->parseError = os.str();
      return false;
    }
    if (!positionalArguments.empty())
    {
      this->cmdArgs[this->posName].first = true;
      this->cmdArgs[this->posName].second = positionalArguments;
    }
    else
    {
      this->cmdArgs[this->posName].first = false;
    }
  }
  return true;
}

std::string CommandLineParser::DisplayCommandArguments()
{
  std::vector<std::string> setParameters;
  std::vector<std::string> unSetParameters;
  for (auto k : this->cmdArgs)
  {
    if (this->cmdArgs[k.first].first)
    {
      setParameters.push_back(k.first);
    }
    else
    {
      unSetParameters.push_back(k.first);
    }
  }
  // Sort them
  std::sort(setParameters.begin(), setParameters.end());
  std::sort(unSetParameters.begin(), unSetParameters.end());

  std::ostringstream os;
  if (setParameters.size() > 0)
  {
    os << "Set parameters:" << std::endl;
    for (auto k : setParameters)
    {
      if (this->cmdArgs[k].first)
      {
        os << "  " << k;
        if (!this->cmdArgs[k].second.empty())
        {
          os << ": ";
          std::copy(std::begin(cmdArgs[k].second),
                    std::prev(std::end(cmdArgs[k].second)),
                    std::ostream_iterator<std::string>(os, ", "));
          os << this->cmdArgs[k].second.back();
        }
        os << std::endl;
      }
    }
  }

  if (unSetParameters.size() > 0)
  {
    os << "Unset parameters:" << std::endl;
    for (auto k : unSetParameters)
    {
      if (!this->cmdArgs[k].first)
      {
        os << "  " << k;
        if (!this->cmdArgs[k].second.empty())
        {
          os << ": ";
          std::copy(std::begin(this->cmdArgs[k].second),
                    std::prev(std::end(this->cmdArgs[k].second)),
                    std::ostream_iterator<std::string>(os, ", "));
          os << this->cmdArgs[k].second.back();
        }
        os << std::endl;
      }
    }
  }
  return os.str();
}

template <typename K, typename V>
void CommandLineParser::GetSetOfValues(std::map<K, V> const& m, std::set<V>& s)
{
  std::for_each(m.begin(), m.end(), [&](const std::pair<const K, V>& element) {
    s.insert(element.second);
  });
}

template <typename K, typename V>
void CommandLineParser::FindAliases(
    std::map<K, V> m, std::map<V, std::pair<std::vector<K>, int>>& aliases)
{
  std::set<V> values;
  this->GetSetOfValues(m, values);
  for (auto v : values)
  {
    std::vector<K> a;
    for (auto it : m)
    {
      if (it.second == v)
      {
        a.push_back(it.first);
      }
    }
    if (a.size() > 0)
    {
      aliases[v] = std::pair<std::vector<K>, int>(a, 0);
    }
  }
}

} // namespace
