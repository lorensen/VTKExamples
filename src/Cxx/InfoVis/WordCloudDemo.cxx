#include <vtkSmartPointer.h>
#include <vtkWordCloud.h>

#include <vtkTextProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkImageViewer2.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkColorSeries.h>

#include <vtksys/CommandLineArguments.hxx>

namespace
{
// Cloud Parameters
class CloudParameters
{
public:
  CloudParameters() :
    BackgroundColorName("MidnightBlue"),
    BWMask(false),
    ColorSchemeName(""),
    DPI(200),
    FileName(""),
    FontFileName(""),
    FontMultiplier(6),
    Gap(2),
    MaskColorName("black"),
    MaskFileName(""),
    MaxFontSize(48),
    MinFontSize(12),
    MinFrequency(1),
    StopListFileName(""),
    Title(""),
    WordColorName(""){};
  void Print(ostream& os)
  {
    os << "Cloud Parameters" << std::endl;
    os << "  BackgroundColorName: " << BackgroundColorName << std::endl;
    os << "  BWMask: " << (BWMask ? "true" : "false") << std::endl;
    os << "  ColorDistribution: " << ColorDistribution[0] << " " << ColorDistribution[1] << std::endl;
    os << "  ColorSchemeName: " <<  ColorSchemeName << std::endl;
    os << "  DPI: " << DPI << std::endl;
    os << "  FontFileName: " << FontFileName << std::endl;
    os << "  FontMultiplier: " << FontMultiplier << std::endl;
    os << "  Gap: " << Gap << std::endl;
    os << "  MaskColorName: " << MaskColorName << std::endl;
    os << "  MaskFileName: " << MaskFileName << std::endl;
    os << "  MinFontSize: " << MinFontSize << std::endl;
    os << "  MaxFontSize: " << MaxFontSize << std::endl;
    os << "  MinFrequency: " << MinFrequency << std::endl;
    os << "  OffsetDistribution: " << OffsetDistribution[0] << " " << OffsetDistribution[1] << std::endl;
    os << "  OrientationDistribution: " << OrientationDistribution[0] << " " << OrientationDistribution[1] << std::endl;
    os << "  Orientations: ";
    for (auto o : Orientations)
    {
      os << o << " ";
    }
    os << std::endl;
    os << "  ReplacementPairs: ";
    for (auto p = 0; p < ReplacementPairs.size(); p += 2)
    {
      os << ReplacementPairs[p] << "->" << ReplacementPairs[p + 1] << " ";
    }
    os << std::endl;
    os << "  Sizes: " << Sizes[0] << " " << Sizes[1] << std::endl;
    os << "  StopWords: ";
    for (auto s : StopWords)
    {
      os << s << " ";
    }
    os << std::endl;
    os << "  Title: " << Title << std::endl;
    os << "  WordColorName: " << WordColorName << std::endl;
  }
  std::string              BackgroundColorName;
  bool                     BWMask;
  std::string              ColorSchemeName;
  std::vector<double>      ColorDistribution;
  int                      DPI;
  std::string              FileName;
  std::string              FontFileName;
  int                      FontMultiplier;
  int                      Gap;
  std::string              MaskColorName;
  std::string              MaskFileName;
  int                      MaxFontSize;
  int                      MinFontSize;
  int                      MinFrequency;
  std::vector<int>         OffsetDistribution;
  std::vector<double>      OrientationDistribution;
  std::vector<double>      Orientations;
  std::vector<std::string> ReplacementPairs;
  std::vector<int>         Sizes;
  std::vector<std::string> StopWords;
  std::string              StopListFileName;
  std::string              Title;
  std::string              WordColorName;
};

bool ProcessCommandLine(
  vtksys::CommandLineArguments &arg,
  CloudParameters &cloudParameters);

void CloudParametersToWordCloud(
  CloudParameters &cloudParameters,
  vtkSmartPointer<vtkWordCloud> &wordCloud);
}

int main (int argc,  char *argv[])
{
  // Process command line argumemts
  CloudParameters cloudParameters;
  vtksys::CommandLineArguments arg;
  arg.Initialize(argc, argv);
  if (!ProcessCommandLine(arg, cloudParameters))
  {
    return EXIT_FAILURE;
  }

  // Transfer parameters to word cloud member data
  auto wordCloud = vtkSmartPointer<vtkWordCloud>::New();
  CloudParametersToWordCloud (cloudParameters, wordCloud);

  // Get the file that contains the text to be converted to a word cloud
  char** newArgv = nullptr;
  int newArgc = 0;
  arg.GetUnusedArguments(&newArgc, &newArgv);
  if (newArgc < 2)
  {
    std::cout << "Usage: " << argv[0] << " textFileName " << arg.GetHelp() << std::endl;
    return EXIT_FAILURE;
  }

  wordCloud->SetFileName(newArgv[1]);
  wordCloud->Update();
  wordCloud->Print(std::cout);
  std::cout << "Kept Words: "    << wordCloud->GetKeptWords().size() << std::endl;
  std::cout << "Stopped Words: " << wordCloud->GetStoppedWords().size() << std::endl;
  std::cout << "Skipped Words: " << wordCloud->GetSkippedWords().size() << std::endl;

  // Display the final image
  auto colors = vtkSmartPointer<vtkNamedColors>::New();
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  auto imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputData(wordCloud->GetOutput());
  imageViewer->SetupInteractor(interactor);
  imageViewer->GetRenderer()->SetBackground(
    colors->GetColor3d(wordCloud->GetBackgroundColorName()).GetData());
  imageViewer->SetSize(wordCloud->GetSizes()[0], wordCloud->GetSizes()[1]);
  imageViewer->GetRenderer()->ResetCamera();

  // Zoom in a bit
  vtkCamera* camera = imageViewer->GetRenderer()->GetActiveCamera();
  camera->ParallelProjectionOn();
  camera->SetParallelScale(wordCloud->GetAdjustedSizes()[0] * .4);

  imageViewer->GetRenderWindow()->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace
{
bool ProcessCommandLine(vtksys::CommandLineArguments &arg,
                        CloudParameters &cloudParameters)
{
  typedef vtksys::CommandLineArguments argT;

  // Need this to get arguments without --'s
  arg.StoreUnusedArguments(true);

  arg.AddArgument("--backgroundColorName",
                  argT::SPACE_ARGUMENT, &cloudParameters.BackgroundColorName, "Name of the color for the background(MignightBlue)");
  arg.AddArgument("--colorDistribution",
                  argT::MULTI_ARGUMENT, &cloudParameters.ColorDistribution, "Distribution of random colors(.6 1.0). If wordColorName is not empty, random colors are generated with this distribution");
  arg.AddArgument("--colorSchemeName",
                  argT::SPACE_ARGUMENT, &cloudParameters.ColorSchemeName, "Color scheme name()");
  arg.AddArgument("--dpi",
                  argT::SPACE_ARGUMENT, &cloudParameters.DPI, "Dots per inch(200)");
  arg.AddArgument("--fontFileName",
                  argT::SPACE_ARGUMENT, &cloudParameters.FontFileName, "Font file name(\"\"). If fontFileName is empty, the built-in Arial font is used.");
  arg.AddArgument("--fontMultiplier",
                  argT::SPACE_ARGUMENT, &cloudParameters.FontMultiplier, "Font multiplier(6). This final FontSize is this value * the word frequency.");
  arg.AddArgument("--gap",
                  argT::SPACE_ARGUMENT, &cloudParameters.Gap, "Space gap of words (2). The gap is the number of spaces added to the beginning and end of each word");
  arg.AddArgument("--maskColorName",
                  argT::SPACE_ARGUMENT, &cloudParameters.MaskColorName, "Name of the color for the mask (black). This is the name of the color that defines the foreground of the mask. Usually black or white");
  arg.AddArgument("--maskFileName",
                  argT::SPACE_ARGUMENT, &cloudParameters.MaskFileName, "Mask file name(\"\"). If the mask file is specified, if will be used as the mask, otherwise a black square is used as the mask.");
  arg.AddArgument("--minFontSize",
                  argT::SPACE_ARGUMENT, &cloudParameters.MinFontSize, "Minimum font size(8)");
  arg.AddArgument("--minFrequency",
                  argT::SPACE_ARGUMENT, &cloudParameters.MinFrequency, "Minimum word frequency accepted(2)");
  arg.AddArgument("--maxFontSize",
                  argT::SPACE_ARGUMENT, &cloudParameters.MaxFontSize, "Maximum font size(48)");
  arg.AddArgument("--offsetDistribution",
                  argT::MULTI_ARGUMENT, &cloudParameters.OffsetDistribution, "Range of random offsets(-size[0]/100.0 -size{1]/100.0)(-20 20).");
  arg.AddArgument("--orientationDistribution",
                  argT::MULTI_ARGUMENT, &cloudParameters.OrientationDistribution, "Ranges of random orientations(-20 20)");
  arg.AddArgument("--orientations",
                  argT::MULTI_ARGUMENT, &cloudParameters.Orientations, "List of discrete orientations (). If non-empty, these will be used instead of the orientations distribution");
  arg.AddArgument("--stopListFileName",
                  argT::SPACE_ARGUMENT, &cloudParameters.StopListFileName, "User provided stop list file. Replaces built-in stop list().");
  arg.AddArgument("--stopWords",
                  argT::MULTI_ARGUMENT, &cloudParameters.StopWords, "User provided stop words(). These will ba added to the built-in stop list.");
  arg.AddArgument("--bwMask"
                  , argT::NO_ARGUMENT, &cloudParameters.BWMask, "Mask image has a single channel(false). Mask images normally have three channels (r,g,b).");
  arg.AddArgument("--size"
                  , argT::MULTI_ARGUMENT, &cloudParameters.Sizes, "Size of image(640 480)");
  arg.AddArgument("--wordColorName",
                  argT::SPACE_ARGUMENT, &cloudParameters.WordColorName, "Name of the color for the words(). If the name is empty, the colorDistribution will generate random colors.");
  arg.AddArgument("--replacementPairs",
                  argT::MULTI_ARGUMENT, &cloudParameters.ReplacementPairs, "Replace word with another word ().");
  arg.AddArgument("--title",
                  argT::SPACE_ARGUMENT, &cloudParameters.Title, "Use this word and set a high frequency().");
  bool help = false;
  arg.AddArgument("--help"
                  , argT::NO_ARGUMENT, &help, "Show help(false)");
  arg.Parse();
  if (help)
  {
    std::cout << "Usage: " << "WordCloud" << " textFileName " << arg.GetHelp() << std::endl;
    return false;
  }

  // Set defaults for vector arguments
  if (cloudParameters.ColorDistribution.size() == 0)
  {
    cloudParameters.ColorDistribution.push_back(.6);
    cloudParameters.ColorDistribution.push_back(1.0);
  }

  if (cloudParameters.OrientationDistribution.size() == 0)
  {
    cloudParameters.OrientationDistribution.push_back(-20);
    cloudParameters.OrientationDistribution.push_back(20);
  }
  if (cloudParameters.Sizes.size() == 0)
  {
    cloudParameters.Sizes.push_back(640);
    cloudParameters.Sizes.push_back(480);
  }
  if (cloudParameters.OffsetDistribution.size() == 0)
  {
    cloudParameters.OffsetDistribution.push_back(-cloudParameters.Sizes[0] / 100.0);
    cloudParameters.OffsetDistribution.push_back( cloudParameters.Sizes[1] / 100.0);
  }
  return true;
}
void CloudParametersToWordCloud(
  CloudParameters &cloudParameters,
  vtkSmartPointer<vtkWordCloud> &wordCloud)
{
  wordCloud->SetBackgroundColorName(cloudParameters.BackgroundColorName);
  wordCloud->SetBWMask(cloudParameters.BWMask);
  wordCloud->SetColorSchemeName(cloudParameters.ColorSchemeName);
  wordCloud->SetFontFileName(cloudParameters.FontFileName);

  std::array<double, 2> colorDistribution;
  colorDistribution[0] = cloudParameters.ColorDistribution[0];
  colorDistribution[1] = cloudParameters.ColorDistribution[1];
  wordCloud->SetColorDistribution(colorDistribution);
  wordCloud->SetDPI(cloudParameters.DPI);
  wordCloud->SetFileName(cloudParameters. FileName);
  wordCloud->SetFontFileName(cloudParameters.FontFileName);
  wordCloud->SetFontMultiplier(cloudParameters.FontMultiplier);
  wordCloud->SetGap(cloudParameters.Gap);
  wordCloud->SetMaskColorName(cloudParameters.MaskColorName);
  wordCloud->SetMaskFileName(cloudParameters.MaskFileName);
  wordCloud->SetMaxFontSize(cloudParameters.MaxFontSize);
  wordCloud->SetMinFontSize(cloudParameters.MinFontSize);
  wordCloud->SetMinFrequency(cloudParameters.MinFrequency);

  std::array<int, 2> offsetDistribution;
  offsetDistribution[0] = cloudParameters.OffsetDistribution[0];
  offsetDistribution[1] = cloudParameters.OffsetDistribution[1];
  wordCloud->SetOffsetDistribution(offsetDistribution);

  std::array<double, 2> orientationDistribution;
  orientationDistribution[0] = cloudParameters.OrientationDistribution[0];
  orientationDistribution[1] = cloudParameters.OrientationDistribution[1];
  wordCloud->SetOrientationDistribution(orientationDistribution);
  wordCloud->SetOrientations(cloudParameters.Orientations);
  
  std::vector<std::tuple<std::string,std::string>> replacementPairs;
  std::tuple<std::string,std::string> replacementPair; 
  for (auto p = 0; p < cloudParameters.ReplacementPairs.size(); p += 2)
  {
    std::string from = cloudParameters.ReplacementPairs[p];
    std::string to = cloudParameters.ReplacementPairs[p + 1];
    replacementPair = std::make_tuple(from, to);
    replacementPairs.push_back(replacementPair);
  }
  wordCloud->SetReplacementPairs(replacementPairs);

  std::array<int, 2> sizes;
  sizes[0] = cloudParameters.Sizes[0];
  sizes[1] = cloudParameters.Sizes[1];
  wordCloud->SetSizes(sizes);

  std::set<std::string> stopWords;
  for (auto s : cloudParameters.StopWords)
  {
    stopWords.insert(s);
  }
  wordCloud->SetStopWords(stopWords);
  wordCloud->SetStopListFileName(cloudParameters.StopListFileName);
  wordCloud->SetWordColorName(cloudParameters.WordColorName);
  std::string title(cloudParameters.Title);
  wordCloud->SetTitle(title);
}
}
