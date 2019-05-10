#include <vtkSmartPointer.h>
#include <vtkImageBlend.h>
#include <vtkFreeTypeTools.h>
#include <vtkImageData.h>
#include <vtkImageIterator.h>
#include <vtkTextProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkImageViewer2.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>

#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageResize.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageAppendComponents.h>

#include <vtksys/CommandLineArguments.hxx>

// stl
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace
{
// Cloud Parameters
struct CloudParameters
{
  CloudParameters() : FontFile(""), MaskFile(""), DPI(200), MaxFontSize(48), MinFontSize(12), FontMultiplier(6), ColorScheme(""),  BackgroundColorName("MidnightBlue"), MaskColorName("black"), BWMask(false), WordColorName(""), Gap(2)
  {};
  void Print(ostream& os)
  {
    os << "Cloud Parameters" << std::endl;
    os << "  BackgroundColorName: " << BackgroundColorName << std::endl;
    os << "  BWMask: " << (BWMask ? "true" : "false") << std::endl;
    os << "  ColorDistribution: " << ColorDistribution[0] << " " << ColorDistribution[1] << std::endl;
    os << "  ColorScheme: " <<  ColorScheme << std::endl;
    os << "  DPI: " << DPI << std::endl;
    os << "  FontFile: " << FontFile << std::endl;
    os << "  FontMultiplier: " << FontMultiplier << std::endl;
    os << "  Gap: " << Gap << std::endl;
    os << "  MaskColorName: " << MaskColorName << std::endl;
    os << "  MaskFile: " << MaskFile << std::endl;
    os << "  MinFontSize: " << MinFontSize << std::endl;
    os << "  MaxFontSize: " << MaxFontSize << std::endl;
    os << "  OffsetDistribution: " << OffsetDistribution[0] << " " << OffsetDistribution[1] << std::endl;
    os << "  OrientationDistribution: " << OrientationDistribution[0] << " " << OrientationDistribution[1] << std::endl;
    os << "  Sizes: " << Sizes[0] << " " << Sizes[1] << std::endl;
    os << "  StopWords: ";
      for (auto s : StopWords)
      {
        os << s << " ";
      }
    os << std::endl;
    os << "  WordColorName: " << WordColorName << std::endl;
  }
  std::string              BackgroundColorName;
  bool                     BWMask;
  std::string              ColorScheme;
  int                      DPI;
  std::string              FontFile;
  int                      Gap;
  std::string              MaskColorName;
  std::string              MaskFile;
  int                      MaxFontSize;
  int                      MinFontSize;
  int                      FontMultiplier;
  std::vector<double>      ColorDistribution;
  std::vector<int>         OffsetDistribution;
  std::vector<double>      OrientationDistribution;
  std::vector<int>         Sizes;
  std::vector<std::string> StopWords;
  std::string              WordColorName;
};
bool ProcessCommandLine(vtksys::CommandLineArguments &arg,
                        CloudParameters &cloudParameters);

// Declaring the type of Predicate that accepts 2 pairs and return a bool
typedef std::function<bool(
    std::pair<std::string, int>,
    std::pair<std::string, int>)> Comparator;

std::multiset<std::pair<std::string, int>, Comparator > FindWordsSortedByFrequency(std::string &, CloudParameters &cloudParameters);
struct ExtentOffset
{
   ExtentOffset(int _x = 0.0, int _y = 0.0) : x(_x), y(_y) {}
   int x,y;
};
struct ArchimedesValue
{
   ArchimedesValue(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
   double x,y;
};
bool AddWordToFinal(const std::string,
                    const int,
                    const CloudParameters &,
                    std::mt19937 &, 
                    std::vector<ExtentOffset> &,
                    vtkImageBlend *,
                    std::array<int, 6> &);


void ArchimedesSpiral (std::vector<ExtentOffset>&, std::vector<int>&);
void ReplaceMaskColorWithBackgroundColor(vtkImageData*, CloudParameters &);
void CreateStopList(std::vector<std::string> &StopList);
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

  // Get the file that contains the text to be converted to a word cloud
  char** newArgv = nullptr;
  int newArgc = 0;
  arg.GetUnusedArguments(&newArgc, &newArgv);
  if (newArgc < 2)
  {
    std::cout << "Usage: " << argv[0] << " textFileName " << arg.GetHelp() << std::endl;
    return EXIT_FAILURE;
  }

  // Open the text file
  std::ifstream t(newArgv[1]);
  std::stringstream buffer;
  buffer << t.rdbuf();
  std::string s = buffer.str();
  t.close();

  // Generate a path for placement of words
  std::vector<ExtentOffset> offset;
  ArchimedesSpiral(offset, cloudParameters.Sizes);

  // Sort the word by frequency
  std::multiset<std::pair<std::string, int>, Comparator> sortedWords = FindWordsSortedByFrequency(s, cloudParameters);

  // Create a mask image
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  vtkColor3ub maskColor = colors->GetColor3ub(cloudParameters.MaskColorName.c_str());
  auto maskImage = vtkSmartPointer<vtkImageData>::New();
  if (cloudParameters.MaskFile == "")
  {
    auto defaultMask = vtkSmartPointer<vtkImageCanvasSource2D>::New();
    defaultMask->SetScalarTypeToUnsignedChar();
    defaultMask->SetNumberOfScalarComponents(3);
    defaultMask->SetExtent(0, cloudParameters.Sizes[0], 0, cloudParameters.Sizes[1], 0, 0);
    defaultMask->SetDrawColor(maskColor.GetData()[0], maskColor.GetData()[1], maskColor.GetData()[2]);
    defaultMask->FillBox(0, cloudParameters.Sizes[0] - 1, 0, cloudParameters.Sizes[1] - 1);
    defaultMask->Update();
    maskImage = defaultMask->GetOutput();
  }
  else
  {
    // Read the image
    auto readerFactory =
      vtkSmartPointer<vtkImageReader2Factory>::New();
    vtkSmartPointer<vtkImageReader2> reader;
    reader.TakeReference(
      readerFactory->CreateImageReader2(cloudParameters.MaskFile.c_str()));
      reader->SetFileName(cloudParameters.MaskFile.c_str());
    reader->Update();
    auto resize = vtkSmartPointer<vtkImageResize>::New();
    resize->SetInputData(reader->GetOutput());
    resize->InterpolateOff();
    resize->SetOutputDimensions(cloudParameters.Sizes[0],
                                cloudParameters.Sizes[1],
                                1);
    if (cloudParameters.BWMask)
    {
      auto appendFilter = vtkSmartPointer<vtkImageAppendComponents>::New();
      appendFilter->SetInputConnection(0, resize->GetOutputPort());
      appendFilter->AddInputConnection(0, resize->GetOutputPort());
      appendFilter->AddInputConnection(0, resize->GetOutputPort());
      appendFilter->Update();
      maskImage = appendFilter->GetOutput();
    }
    else
    {
      auto rgbImage = vtkSmartPointer<vtkImageExtractComponents>::New();
      rgbImage->SetInputConnection(resize->GetOutputPort());
      rgbImage->SetComponents(0, 1, 2);
      rgbImage->Update();
      maskImage = rgbImage->GetOutput();
    }

    }

  // Create an image that will hold the final image
  auto final = vtkSmartPointer<vtkImageBlend>::New();
  final->AddInputData(maskImage);
  final->SetOpacity(0, 0.0);
  final->Update();

  // Try to add each word
  int numberSkipped = 0;
  std::mt19937 mt(4355412); //Standard mersenne twister engine
  std::array<int, 6> extent;
  bool added;
  for (std::pair<std::string, int> element : sortedWords)
  {
    added = AddWordToFinal(
      element.first,
      element.second,
      cloudParameters,
      mt,
      offset,
      final,
      extent);
    if (added)
    {
//      std::cout << element.first << ": " << element.second << std::endl;
    }
    else
    {
      numberSkipped++;
//      std::cout << "skipped: " << element.first << ": " << element.second << std::endl;
    }
  }
  std::cout << "Skipped " << numberSkipped << " words" << std::endl;

  // If a maskFile is specified, replace the maskColor with the background color
    ReplaceMaskColorWithBackgroundColor(final->GetOutput(), cloudParameters);

  // Display the final image
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  auto imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputData(final->GetOutput());
  imageViewer->SetSize(640, 480);
  imageViewer->SetupInteractor(interactor);
  imageViewer->GetRenderer()->SetBackground(colors->GetColor3d("Wheat").GetData());
  imageViewer->GetRenderer()->ResetCamera();

  vtkCamera* camera = imageViewer->GetRenderer()->GetActiveCamera();
  camera->ParallelProjectionOn();
  camera->SetParallelScale(cloudParameters.Sizes[0] * .4);

  imageViewer->GetRenderWindow()->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace
{
std::multiset<std::pair<std::string, int>, Comparator > FindWordsSortedByFrequency(std::string &s, CloudParameters &cloudParameters)
{
  // Create a stop list
  std::vector<std::string> stopList;
  CreateStopList(stopList);
  for (auto s : cloudParameters.StopWords)
  {
    stopList.push_back(s);
  }
  
  // Drop the case of all words
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);

  // Extract words
  std::regex wordRegex("(\\w+)");
  auto wordsBegin = 
    std::sregex_iterator(s.begin(), s.end(), wordRegex);
  auto wordsEnd = std::sregex_iterator();

  // Store the words in a map that will contain frequencies
  std::map<std::string, int> wordContainer;
  const int N = 1;
  int stop = 0;
  int keep = 0;
  for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i)
  {
    std::string matchStr = (*i).str();

    // Skip the word if it is in the stop list or contains a digit
    auto it = std::find (stopList.begin(), stopList.end(), matchStr);
    const auto digit = (*i).str().find_first_of("0123456789");
    if (it != stopList.end() || digit != std::string::npos)
    {
      stop++;
      continue;
    }
    else
    {
      keep++;
    }
    // Only include words that have more than N characters
    if (matchStr.size() > N)
    {
      // Raise the case of he first letter in the word
      std::transform(matchStr.begin(), matchStr.begin() + 1, matchStr.begin(), ::toupper);
      wordContainer[matchStr]++;
    }
  }
  std::cout << "Kept " << keep << " words" << std::endl;
  std::cout << "Stopped " << stop << " words" << std::endl;

  // Defining a lambda function to compare two pairs. It will compare
  // two pairs using second field
  Comparator compFunctor =
    [](std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2)
    {
      if (elem1.second == elem2.second)
      {
        return elem1.first.length() > elem2.first.length();
      }
      return elem1.second  > elem2.second;
    };
 
  // Declaring a multiset that will store the pairs using above comparision logic
  std::multiset<std::pair<std::string, int>, Comparator> setOfWords(
    wordContainer.begin(), wordContainer.end(), compFunctor);

  return setOfWords;
}
bool AddWordToFinal(const std::string word,
                    const int frequency,
                    const CloudParameters &cloudParameters,
                    std::mt19937 &mt,
                    std::vector<ExtentOffset> &offset,
                    vtkImageBlend *final,
                    std::array<int, 6> &extent)
{
  // Skip single character words
  if (frequency < 1)
  {
    return false;
  }

  // Create an image of the string
  vtkFreeTypeTools *freeType = vtkFreeTypeTools::GetInstance();
  freeType->ScaleToPowerTwoOff();

  // Create random distributions
  std::uniform_real_distribution<> orientationDist(
    cloudParameters.OrientationDistribution[0], cloudParameters.OrientationDistribution[1]);
  std::uniform_real_distribution<> colorDist(
    cloudParameters.ColorDistribution[0], cloudParameters.ColorDistribution[1]);

  // Setup a property for the strings containing fixed parameters
  auto colors = vtkSmartPointer<vtkNamedColors>::New();
  auto textProperty = vtkSmartPointer<vtkTextProperty>::New();
  if (cloudParameters.WordColorName.size() > 0)
  {
    textProperty->SetColor(colors->GetColor3d(cloudParameters.WordColorName).GetData());
  }
  else
  {
  textProperty->SetColor(colorDist(mt), colorDist(mt), colorDist(mt));
  }
  textProperty->SetVerticalJustificationToCentered();
  textProperty->SetJustificationToCentered();

  // Check if a font file is present
  if (cloudParameters.FontFile.length() > 0)
  {
    textProperty->SetFontFile(cloudParameters.FontFile.c_str());
    textProperty->SetFontFamily(VTK_FONT_FILE);
  }
  else
  {
    textProperty->SetFontFamilyToArial();
  }
  // Set the font size
  int fontSize = cloudParameters.FontMultiplier * frequency;
  if (fontSize > cloudParameters.MaxFontSize)
  {
    fontSize = cloudParameters.MaxFontSize;
  }
  if (fontSize < cloudParameters.MinFontSize)
  {
    fontSize = cloudParameters.MinFontSize;
  }

  textProperty->SetFontSize(fontSize);
  textProperty->SetOrientation(orientationDist(mt));

  // For each string, create an image and see if it overlaps with other images,
  // if so, skip it
  int accepted = 0;
  std::string spaces;
  for (int p = 0; p < cloudParameters.Gap; ++p)
  {
    spaces.push_back(' ');
  }

  auto textImage = vtkSmartPointer<vtkImageData>::New();
  freeType->RenderString(textProperty,
                         spaces + word + spaces,
                         cloudParameters.DPI,
                         textImage.GetPointer());

  // Set the extent of the text image
  std::array<int, 4> bb;
  freeType->GetBoundingBox(textProperty,
                           spaces + word + spaces,
                           cloudParameters.DPI,
                           bb.data());
  vtkColor3ub maskColor = colors->GetColor3ub(cloudParameters.MaskColorName.c_str());
  unsigned char maskR = maskColor.GetData()[0];
  unsigned char maskG = maskColor.GetData()[1];
  unsigned char maskB = maskColor.GetData()[2];

  std::uniform_real_distribution<> offsetDist(
    cloudParameters.OffsetDistribution[0],
    cloudParameters.OffsetDistribution[1]);

  for (auto it = offset.begin();
       it < offset.end();
       ++it)
  {
    int offsetX = (*it).x + offsetDist(mt); // add some noise to the offset
    int offsetY = (*it).y + offsetDist(mt);
    // Make sure the text image will fit on the final image
    if (offsetX + bb[1] - bb[0] < cloudParameters.Sizes[0] - 1 &&
        offsetY + bb[3] - bb[2] < cloudParameters.Sizes[1] - 1 &&
        offsetX >= 0 && offsetY >= 0)
    {
      textImage->SetExtent(offsetX, offsetX + bb[1] - bb[0],
                           offsetY, offsetY + bb[3] - bb[2],
                           0, 0);
      auto image = vtkSmartPointer<vtkImageData>::New();
      final->Update();

      // Does the text image overlap with images on the final image 
      vtkImageIterator<unsigned char> finalIt(final->GetOutput(),
                                              textImage->GetExtent());
      textImage->GetExtent(extent.data());
      bool good = true;
      while( !finalIt.IsAtEnd())
      {
        auto finalSpan = finalIt.BeginSpan();
        while(finalSpan != finalIt.EndSpan())
        {
          unsigned char R, G, B;
          R = *finalSpan++;
          G = *finalSpan++;
          B = *finalSpan++;
          // If the pixel does not contain the background color, the word will not fit
          if (R != maskR && G != maskG && B != maskB)
          {
            good = false;
            break;
          }
        }
        if (!good)
        {
          break;
        }
        finalIt.NextSpan();
      }
      if (good)
      {
        accepted++;
        image->DeepCopy(textImage);
        final->AddInputData(image);
        final->Update();
        return true;
      }
    }
  }
  return false;
}

void ArchimedesSpiral(std::vector<ExtentOffset> &offset, std::vector<int> &sizes)
{
   const int centerX = sizes[0] / 2.0;
   const int centerY = sizes[1] / 2.0;

   const std::size_t N = 10000;
   const double deltaAngle = M_PI * 20 / N;
   double maxX = -1000.0;
   double minX = 1000.0;
   double maxY = -1000.0;
   double minY = 1000.0;
   double range = -1000;
   double e = sizes[0] / sizes[1];
   std::vector<ArchimedesValue> archimedes;
   for (std::size_t i = 0; i < N; i += 10)
   {
     double x, y;
     double angle = deltaAngle * i;
     double r = angle;
     x = e * angle * std::cos(angle);
     y = e * angle * std::sin(angle);
     archimedes.push_back(ArchimedesValue(x, y));     
     maxX = std::max(maxX, x);
     minX = std::min(minX, x);
     maxY = std::max(maxY, y);
     minY = std::min(minY, y);
     range = std::max(maxX - minX, maxY - minY);
   }
   double scaleX = 1.0 / range * sizes[0];
   double scaleY = 1.0 / range * sizes[1];
   int j = 0;
   for (auto it = archimedes.begin();
        it < archimedes.end();
        ++it)
   {

     if ((*it).y * scaleX + centerY < 0
         || (*it).x * scaleX + centerX - 50 < 0) continue;
     offset.push_back(ExtentOffset((*it).x * scaleX + centerX - 50,
                                   (*it).y * scaleX + centerY));
   }
}
bool ProcessCommandLine(vtksys::CommandLineArguments &arg, CloudParameters &cloudParameters)
{
  typedef vtksys::CommandLineArguments argT;

  // Need this to get arguments without --'s
  arg.StoreUnusedArguments(true);

  arg.AddArgument("--backgroundColorName",
                  argT::SPACE_ARGUMENT, &cloudParameters.BackgroundColorName, "Name of the color for the background(MignightBlue)");
  arg.AddArgument("--colorDistribution",
                  argT::MULTI_ARGUMENT, &cloudParameters.ColorDistribution, "Distribution of random colors(.6 1.0). If wordColorName is not empty, random colors are generated with this distribution");
  arg.AddArgument("--colorScheme",
                  argT::SPACE_ARGUMENT, &cloudParameters.ColorScheme, "Color scheme(constant)");
  arg.AddArgument("--dpi",
                  argT::SPACE_ARGUMENT, &cloudParameters.DPI, "Dots per inch(200)");
  arg.AddArgument("--fontFile",
                  argT::SPACE_ARGUMENT, &cloudParameters.FontFile, "Font file name(\"\"). If fontFileName is empty, the built-in Arial font is used.");
  arg.AddArgument("--fontMultiplier",
                  argT::SPACE_ARGUMENT, &cloudParameters.FontMultiplier, "Font multiplier(6). This final FontSize is this value * the word frequency.");
  arg.AddArgument("--gap",
                  argT::SPACE_ARGUMENT, &cloudParameters.Gap, "Space gap of words (2). The gap is the number of spaces added to the beginning and end of each word");
  arg.AddArgument("--maskColorName",
                  argT::SPACE_ARGUMENT, &cloudParameters.MaskColorName, "Name of the color for the mask (black). This is the name of the color that defines the foreground of the mask. Usually black or white");
  arg.AddArgument("--maskFile",
                  argT::SPACE_ARGUMENT, &cloudParameters.MaskFile, "Mask file name(\"\"). If the mask file is specified, if will be used as the mask, otherwise a black square is used as the mask.");
  arg.AddArgument("--minFontSize",
                  argT::SPACE_ARGUMENT, &cloudParameters.MinFontSize, "Minimum font size(8)");
  arg.AddArgument("--maxFontSize",
                  argT::SPACE_ARGUMENT, &cloudParameters.MaxFontSize, "Maximum font size(48)");
  arg.AddArgument("--offsetDistribution",
                  argT::MULTI_ARGUMENT, &cloudParameters.OffsetDistribution, "Range of random offsets(-size[0]/100.0 -size{1]/100.0)(-20 20).");
  arg.AddArgument("--orientationDistribution",
                  argT::MULTI_ARGUMENT, &cloudParameters.OrientationDistribution, "Ranges of random orientations(-20 20)");
  arg.AddArgument("--stopWords",
                  argT::MULTI_ARGUMENT, &cloudParameters.StopWords, "User provided stop words(). These will ba added to the built-in stop list.");
  arg.AddArgument("--bwMask"
                  , argT::NO_ARGUMENT, &cloudParameters.BWMask, "Mask image has a single channel(false). Mask images normally have three channels (r,g,b).");
  arg.AddArgument("--size"
                  , argT::MULTI_ARGUMENT, &cloudParameters.Sizes, "Size of image(640 480)");
  arg.AddArgument("--wordColorName",
                  argT::SPACE_ARGUMENT, &cloudParameters.WordColorName, "Name of the color for the words(). If the name is empty, the colorDistribution will generate random colors.");
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

  cloudParameters.Print(std::cout);
  return true;
}
void ReplaceMaskColorWithBackgroundColor(vtkImageData* finalImage, CloudParameters &cloudParameters)
{
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  vtkColor3ub maskColor = colors->GetColor3ub(cloudParameters.MaskColorName.c_str());
  unsigned char maskR = maskColor.GetData()[0];
  unsigned char maskG = maskColor.GetData()[1];
  unsigned char maskB = maskColor.GetData()[2];

  vtkColor3ub backgroundColor = colors->GetColor3ub(cloudParameters.BackgroundColorName.c_str());
  unsigned char bkgR = backgroundColor.GetData()[0];
  unsigned char bkgG = backgroundColor.GetData()[1];
  unsigned char bkgB = backgroundColor.GetData()[2];

  vtkImageIterator<unsigned char> finalIt(finalImage,
                                          finalImage->GetExtent());
  while( !finalIt.IsAtEnd())
  {
    auto finalSpan = finalIt.BeginSpan();
    while(finalSpan != finalIt.EndSpan())
    {
      unsigned char R, G, B;
      R = *finalSpan;
      G = *(finalSpan + 1);
      B = *(finalSpan + 2);
      // If the pixel contains the background color, the word will not fit
      if (R != maskR && G != maskG && B != maskB)
      {
        finalSpan += 3;
        continue;
      }
      else
      {
        *finalSpan = bkgR;
        *(finalSpan + 1) = bkgG;
        *(finalSpan + 2) = bkgB;
      }
      finalSpan += 3;
    }
  finalIt.NextSpan();
  }
}

void CreateStopList(std::vector<std::string> &stopList)
{
  stopList.push_back("a");
  stopList.push_back("able");
  stopList.push_back("about");
  stopList.push_back("above");
  stopList.push_back("abst");
  stopList.push_back("accordance");
  stopList.push_back("according");
  stopList.push_back("accordingly");
  stopList.push_back("across");
  stopList.push_back("act");
  stopList.push_back("actually");
  stopList.push_back("added");
  stopList.push_back("adj");
  stopList.push_back("affected");
  stopList.push_back("affecting");
  stopList.push_back("affects");
  stopList.push_back("after");
  stopList.push_back("afterwards");
  stopList.push_back("again");
  stopList.push_back("against");
  stopList.push_back("ah");
  stopList.push_back("all");
  stopList.push_back("almost");
  stopList.push_back("alone");
  stopList.push_back("along");
  stopList.push_back("already");
  stopList.push_back("also");
  stopList.push_back("although");
  stopList.push_back("always");
  stopList.push_back("am");
  stopList.push_back("among");
  stopList.push_back("amongst");
  stopList.push_back("an");
  stopList.push_back("and");
  stopList.push_back("announce");
  stopList.push_back("another");
  stopList.push_back("any");
  stopList.push_back("anybody");
  stopList.push_back("anyhow");
  stopList.push_back("anymore");
  stopList.push_back("anyone");
  stopList.push_back("anything");
  stopList.push_back("anyway");
  stopList.push_back("anyways");
  stopList.push_back("anywhere");
  stopList.push_back("apparently");
  stopList.push_back("approximately");
  stopList.push_back("are");
  stopList.push_back("aren");
  stopList.push_back("arent");
  stopList.push_back("arise");
  stopList.push_back("around");
  stopList.push_back("as");
  stopList.push_back("aside");
  stopList.push_back("ask");
  stopList.push_back("asking");
  stopList.push_back("at");
  stopList.push_back("auth");
  stopList.push_back("available");
  stopList.push_back("away");
  stopList.push_back("awfully");
  stopList.push_back("b");
  stopList.push_back("back");
  stopList.push_back("be");
  stopList.push_back("became");
  stopList.push_back("because");
  stopList.push_back("become");
  stopList.push_back("becomes");
  stopList.push_back("becoming");
  stopList.push_back("been");
  stopList.push_back("before");
  stopList.push_back("beforehand");
  stopList.push_back("begin");
  stopList.push_back("beginning");
  stopList.push_back("beginnings");
  stopList.push_back("begins");
  stopList.push_back("behind");
  stopList.push_back("being");
  stopList.push_back("believe");
  stopList.push_back("below");
  stopList.push_back("beside");
  stopList.push_back("besides");
  stopList.push_back("between");
  stopList.push_back("beyond");
  stopList.push_back("biol");
  stopList.push_back("both");
  stopList.push_back("brief");
  stopList.push_back("briefly");
  stopList.push_back("but");
  stopList.push_back("by");
  stopList.push_back("c");
  stopList.push_back("ca");
  stopList.push_back("came");
  stopList.push_back("can");
  stopList.push_back("cannot");
  stopList.push_back("can't");
  stopList.push_back("cause");
  stopList.push_back("causes");
  stopList.push_back("certain");
  stopList.push_back("certainly");
  stopList.push_back("co");
  stopList.push_back("com");
  stopList.push_back("come");
  stopList.push_back("comes");
  stopList.push_back("contain");
  stopList.push_back("containing");
  stopList.push_back("contains");
  stopList.push_back("could");
  stopList.push_back("couldnt");
  stopList.push_back("cum");
  stopList.push_back("d");
  stopList.push_back("date");
  stopList.push_back("did");
  stopList.push_back("didn't");
  stopList.push_back("different");
  stopList.push_back("do");
  stopList.push_back("does");
  stopList.push_back("doesn't");
  stopList.push_back("doing");
  stopList.push_back("done");
  stopList.push_back("don't");
  stopList.push_back("down");
  stopList.push_back("downwards");
  stopList.push_back("due");
  stopList.push_back("dr");
  stopList.push_back("during");
  stopList.push_back("e");
  stopList.push_back("each");
  stopList.push_back("ed");
  stopList.push_back("edu");
  stopList.push_back("effect");
  stopList.push_back("eg");
  stopList.push_back("eight");
  stopList.push_back("eighty");
  stopList.push_back("either");
  stopList.push_back("else");
  stopList.push_back("elsewhere");
  stopList.push_back("end");
  stopList.push_back("ending");
  stopList.push_back("enough");
  stopList.push_back("especially");
  stopList.push_back("et");
  stopList.push_back("et-al");
  stopList.push_back("etc");
  stopList.push_back("even");
  stopList.push_back("ever");
  stopList.push_back("every");
  stopList.push_back("everybody");
  stopList.push_back("everyone");
  stopList.push_back("everything");
  stopList.push_back("everywhere");
  stopList.push_back("ex");
  stopList.push_back("except");
  stopList.push_back("f");
  stopList.push_back("far");
  stopList.push_back("few");
  stopList.push_back("ff");
  stopList.push_back("fifth");
  stopList.push_back("first");
  stopList.push_back("five");
  stopList.push_back("fix");
  stopList.push_back("followed");
  stopList.push_back("following");
  stopList.push_back("follows");
  stopList.push_back("for");
  stopList.push_back("former");
  stopList.push_back("formerly");
  stopList.push_back("forth");
  stopList.push_back("found");
  stopList.push_back("four");
  stopList.push_back("from");
  stopList.push_back("further");
  stopList.push_back("furthermore");
  stopList.push_back("g");
  stopList.push_back("gave");
  stopList.push_back("get");
  stopList.push_back("gets");
  stopList.push_back("getting");
  stopList.push_back("give");
  stopList.push_back("given");
  stopList.push_back("gives");
  stopList.push_back("giving");
  stopList.push_back("go");
  stopList.push_back("goes");
  stopList.push_back("gone");
  stopList.push_back("got");
  stopList.push_back("gotten");
  stopList.push_back("h");
  stopList.push_back("had");
  stopList.push_back("happens");
  stopList.push_back("hardly");
  stopList.push_back("has");
  stopList.push_back("hasn");
  stopList.push_back("have");
  stopList.push_back("haven");
  stopList.push_back("having");
  stopList.push_back("he");
  stopList.push_back("hed");
  stopList.push_back("hence");
  stopList.push_back("her");
  stopList.push_back("here");
  stopList.push_back("hereafter");
  stopList.push_back("hereby");
  stopList.push_back("herein");
  stopList.push_back("heres");
  stopList.push_back("hereupon");
  stopList.push_back("hers");
  stopList.push_back("herself");
  stopList.push_back("hes");
  stopList.push_back("hi");
  stopList.push_back("hid");
  stopList.push_back("him");
  stopList.push_back("himself");
  stopList.push_back("his");
  stopList.push_back("hither");
  stopList.push_back("home");
  stopList.push_back("how");
  stopList.push_back("howbeit");
  stopList.push_back("however");
  stopList.push_back("hundred");
  stopList.push_back("i");
  stopList.push_back("id");
  stopList.push_back("ie");
  stopList.push_back("if");
  stopList.push_back("im");
  stopList.push_back("immediate");
  stopList.push_back("immediately");
  stopList.push_back("importance");
  stopList.push_back("important");
  stopList.push_back("in");
  stopList.push_back("inc");
  stopList.push_back("indeed");
  stopList.push_back("index");
  stopList.push_back("information");
  stopList.push_back("instead");
  stopList.push_back("into");
  stopList.push_back("invention");
  stopList.push_back("inward");
  stopList.push_back("is");
  stopList.push_back("isn");
  stopList.push_back("it");
  stopList.push_back("itd");
  stopList.push_back("it");
  stopList.push_back("its");
  stopList.push_back("itself");
  stopList.push_back("j");
  stopList.push_back("jr");
  stopList.push_back("just");
  stopList.push_back("k");
  stopList.push_back("keep");
  stopList.push_back("keeps");
  stopList.push_back("kept");
  stopList.push_back("kg");
  stopList.push_back("km");
  stopList.push_back("know");
  stopList.push_back("known");
  stopList.push_back("knows");
  stopList.push_back("l");
  stopList.push_back("largely");
  stopList.push_back("last");
  stopList.push_back("lately");
  stopList.push_back("later");
  stopList.push_back("latter");
  stopList.push_back("latterly");
  stopList.push_back("laude");
  stopList.push_back("least");
  stopList.push_back("less");
  stopList.push_back("lest");
  stopList.push_back("let");
  stopList.push_back("lets");
  stopList.push_back("like");
  stopList.push_back("liked");
  stopList.push_back("likely");
  stopList.push_back("line");
  stopList.push_back("little");
  stopList.push_back("ll");
  stopList.push_back("look");
  stopList.push_back("looking");
  stopList.push_back("looks");
  stopList.push_back("ltd");
  stopList.push_back("m");
  stopList.push_back("made");
  stopList.push_back("mainly");
  stopList.push_back("make");
  stopList.push_back("makes");
  stopList.push_back("many");
  stopList.push_back("may");
  stopList.push_back("maybe");
  stopList.push_back("me");
  stopList.push_back("mean");
  stopList.push_back("means");
  stopList.push_back("meantime");
  stopList.push_back("meanwhile");
  stopList.push_back("merely");
  stopList.push_back("met");
  stopList.push_back("mg");
  stopList.push_back("mic");
  stopList.push_back("might");
  stopList.push_back("million");
  stopList.push_back("miss");
  stopList.push_back("ml");
  stopList.push_back("more");
  stopList.push_back("moreover");
  stopList.push_back("most");
  stopList.push_back("mostly");
  stopList.push_back("mr");
  stopList.push_back("mrs");
  stopList.push_back("much");
  stopList.push_back("mug");
  stopList.push_back("must");
  stopList.push_back("my");
  stopList.push_back("myself");
  stopList.push_back("n");
  stopList.push_back("na");
  stopList.push_back("name");
  stopList.push_back("namely");
  stopList.push_back("nay");
  stopList.push_back("nd");
  stopList.push_back("near");
  stopList.push_back("nearly");
  stopList.push_back("necessarily");
  stopList.push_back("necessary");
  stopList.push_back("need");
  stopList.push_back("needs");
  stopList.push_back("neither");
  stopList.push_back("never");
  stopList.push_back("nevertheless");
  stopList.push_back("new");
  stopList.push_back("next");
  stopList.push_back("nine");
  stopList.push_back("ninety");
  stopList.push_back("no");
  stopList.push_back("nobody");
  stopList.push_back("non");
  stopList.push_back("none");
  stopList.push_back("nonetheless");
  stopList.push_back("noone");
  stopList.push_back("nor");
  stopList.push_back("normally");
  stopList.push_back("nos");
  stopList.push_back("not");
  stopList.push_back("noted");
  stopList.push_back("nothing");
  stopList.push_back("now");
  stopList.push_back("nowhere");
  stopList.push_back("o");
  stopList.push_back("obtain");
  stopList.push_back("obtained");
  stopList.push_back("obviously");
  stopList.push_back("of");
  stopList.push_back("off");
  stopList.push_back("often");
  stopList.push_back("oh");
  stopList.push_back("ok");
  stopList.push_back("okay");
  stopList.push_back("old");
  stopList.push_back("omitted");
  stopList.push_back("on");
  stopList.push_back("once");
  stopList.push_back("one");
  stopList.push_back("ones");
  stopList.push_back("only");
  stopList.push_back("onto");
  stopList.push_back("or");
  stopList.push_back("ord");
  stopList.push_back("org");
  stopList.push_back("other");
  stopList.push_back("others");
  stopList.push_back("otherwise");
  stopList.push_back("ought");
  stopList.push_back("our");
  stopList.push_back("ours");
  stopList.push_back("ourselves");
  stopList.push_back("out");
  stopList.push_back("outside");
  stopList.push_back("over");
  stopList.push_back("overall");
  stopList.push_back("owing");
  stopList.push_back("own");
  stopList.push_back("p");
  stopList.push_back("page");
  stopList.push_back("pages");
  stopList.push_back("part");
  stopList.push_back("particular");
  stopList.push_back("particularly");
  stopList.push_back("past");
  stopList.push_back("per");
  stopList.push_back("perhaps");
  stopList.push_back("ph");
  stopList.push_back("placed");
  stopList.push_back("please");
  stopList.push_back("plus");
  stopList.push_back("poorly");
  stopList.push_back("possible");
  stopList.push_back("possibly");
  stopList.push_back("potentially");
  stopList.push_back("pp");
  stopList.push_back("predominantly");
  stopList.push_back("present");
  stopList.push_back("previously");
  stopList.push_back("primarily");
  stopList.push_back("probably");
  stopList.push_back("promptly");
  stopList.push_back("proud");
  stopList.push_back("provides");
  stopList.push_back("put");
  stopList.push_back("q");
  stopList.push_back("que");
  stopList.push_back("quickly");
  stopList.push_back("quite");
  stopList.push_back("qv");
  stopList.push_back("r");
  stopList.push_back("ran");
  stopList.push_back("rather");
  stopList.push_back("rd");
  stopList.push_back("re");
  stopList.push_back("readily");
  stopList.push_back("really");
  stopList.push_back("recent");
  stopList.push_back("recently");
  stopList.push_back("ref");
  stopList.push_back("refs");
  stopList.push_back("regarding");
  stopList.push_back("regardless");
  stopList.push_back("regards");
  stopList.push_back("related");
  stopList.push_back("relatively");
  stopList.push_back("research");
  stopList.push_back("respectively");
  stopList.push_back("resulted");
  stopList.push_back("resulting");
  stopList.push_back("results");
  stopList.push_back("right");
  stopList.push_back("run");
  stopList.push_back("s");
  stopList.push_back("said");
  stopList.push_back("same");
  stopList.push_back("saw");
  stopList.push_back("sat");
  stopList.push_back("say");
  stopList.push_back("saying");
  stopList.push_back("says");
  stopList.push_back("sec");
  stopList.push_back("section");
  stopList.push_back("see");
  stopList.push_back("seeing");
  stopList.push_back("seem");
  stopList.push_back("seemed");
  stopList.push_back("seeming");
  stopList.push_back("seems");
  stopList.push_back("seen");
  stopList.push_back("self");
  stopList.push_back("selves");
  stopList.push_back("sent");
  stopList.push_back("seven");
  stopList.push_back("several");
  stopList.push_back("shall");
  stopList.push_back("she");
  stopList.push_back("shed");
  stopList.push_back("shes");
  stopList.push_back("should");
  stopList.push_back("shouldn");
  stopList.push_back("show");
  stopList.push_back("showed");
  stopList.push_back("shown");
  stopList.push_back("showns");
  stopList.push_back("shows");
  stopList.push_back("significant");
  stopList.push_back("significantly");
  stopList.push_back("similar");
  stopList.push_back("similarly");
  stopList.push_back("since");
  stopList.push_back("six");
  stopList.push_back("slightly");
  stopList.push_back("so");
  stopList.push_back("some");
  stopList.push_back("somebody");
  stopList.push_back("somehow");
  stopList.push_back("someone");
  stopList.push_back("somethan");
  stopList.push_back("something");
  stopList.push_back("sometime");
  stopList.push_back("sometimes");
  stopList.push_back("somewhat");
  stopList.push_back("somewhere");
  stopList.push_back("soon");
  stopList.push_back("sorry");
  stopList.push_back("specifically");
  stopList.push_back("specified");
  stopList.push_back("specify");
  stopList.push_back("specifying");
  stopList.push_back("still");
  stopList.push_back("stop");
  stopList.push_back("strongly");
  stopList.push_back("sub");
  stopList.push_back("substantially");
  stopList.push_back("successfully");
  stopList.push_back("such");
  stopList.push_back("sufficiently");
  stopList.push_back("suggest");
  stopList.push_back("sup");
  stopList.push_back("sure");
  stopList.push_back("t");
  stopList.push_back("take");
  stopList.push_back("taken");
  stopList.push_back("taking");
  stopList.push_back("tell");
  stopList.push_back("tends");
  stopList.push_back("th");
  stopList.push_back("than");
  stopList.push_back("thank");
  stopList.push_back("thanks");
  stopList.push_back("thanx");
  stopList.push_back("that");
  stopList.push_back("thats");
  stopList.push_back("the");
  stopList.push_back("their");
  stopList.push_back("theirs");
  stopList.push_back("them");
  stopList.push_back("themselves");
  stopList.push_back("then");
  stopList.push_back("thence");
  stopList.push_back("there");
  stopList.push_back("thereafter");
  stopList.push_back("thereby");
  stopList.push_back("thered");
  stopList.push_back("therefore");
  stopList.push_back("therein");
  stopList.push_back("thereof");
  stopList.push_back("therere");
  stopList.push_back("theres");
  stopList.push_back("thereto");
  stopList.push_back("thereupon");
  stopList.push_back("these");
  stopList.push_back("they");
  stopList.push_back("theyd");
  stopList.push_back("theyre");
  stopList.push_back("think");
  stopList.push_back("this");
  stopList.push_back("those");
  stopList.push_back("thou");
  stopList.push_back("though");
  stopList.push_back("thoughh");
  stopList.push_back("thousand");
  stopList.push_back("throug");
  stopList.push_back("through");
  stopList.push_back("throughout");
  stopList.push_back("thru");
  stopList.push_back("thus");
  stopList.push_back("til");
  stopList.push_back("tip");
  stopList.push_back("to");
  stopList.push_back("together");
  stopList.push_back("too");
  stopList.push_back("took");
  stopList.push_back("toward");
  stopList.push_back("towards");
  stopList.push_back("tried");
  stopList.push_back("tries");
  stopList.push_back("truly");
  stopList.push_back("try");
  stopList.push_back("trying");
  stopList.push_back("ts");
  stopList.push_back("twice");
  stopList.push_back("two");
  stopList.push_back("u");
  stopList.push_back("un");
  stopList.push_back("under");
  stopList.push_back("unfortunately");
  stopList.push_back("unless");
  stopList.push_back("unlike");
  stopList.push_back("unlikely");
  stopList.push_back("until");
  stopList.push_back("unto");
  stopList.push_back("up");
  stopList.push_back("upon");
  stopList.push_back("ups");
  stopList.push_back("us");
  stopList.push_back("use");
  stopList.push_back("used");
  stopList.push_back("useful");
  stopList.push_back("usefully");
  stopList.push_back("usefulness");
  stopList.push_back("uses");
  stopList.push_back("using");
  stopList.push_back("usually");
  stopList.push_back("v");
  stopList.push_back("value");
  stopList.push_back("various");
  stopList.push_back("ve");
  stopList.push_back("very");
  stopList.push_back("via");
  stopList.push_back("viz");
  stopList.push_back("vol");
  stopList.push_back("vols");
  stopList.push_back("vs");
  stopList.push_back("w");
  stopList.push_back("want");
  stopList.push_back("wants");
  stopList.push_back("was");
  stopList.push_back("wasnt");
  stopList.push_back("wasnt");
  stopList.push_back("way");
  stopList.push_back("we");
  stopList.push_back("wed");
  stopList.push_back("welcome");
  stopList.push_back("went");
  stopList.push_back("were");
  stopList.push_back("werent");
  stopList.push_back("what");
  stopList.push_back("whatever");
  stopList.push_back("whats");
  stopList.push_back("when");
  stopList.push_back("whence");
  stopList.push_back("whenever");
  stopList.push_back("where");
  stopList.push_back("whereafter");
  stopList.push_back("whereas");
  stopList.push_back("whereby");
  stopList.push_back("wherein");
  stopList.push_back("wheres");
  stopList.push_back("whereupon");
  stopList.push_back("wherever");
  stopList.push_back("whether");
  stopList.push_back("which");
  stopList.push_back("while");
  stopList.push_back("whim");
  stopList.push_back("whither");
  stopList.push_back("who");
  stopList.push_back("whod");
  stopList.push_back("whoever");
  stopList.push_back("whole");
  stopList.push_back("whom");
  stopList.push_back("whomever");
  stopList.push_back("whos");
  stopList.push_back("whose");
  stopList.push_back("why");
  stopList.push_back("widely");
  stopList.push_back("will");
  stopList.push_back("willing");
  stopList.push_back("wish");
  stopList.push_back("with");
  stopList.push_back("within");
  stopList.push_back("without");
  stopList.push_back("wont");
  stopList.push_back("words");
  stopList.push_back("world");
  stopList.push_back("would");
  stopList.push_back("wouldnt");
  stopList.push_back("www");
  stopList.push_back("x");
  stopList.push_back("y");
  stopList.push_back("yes");
  stopList.push_back("yet");
  stopList.push_back("you");
  stopList.push_back("youd");
  stopList.push_back("your");
  stopList.push_back("youre");
  stopList.push_back("yours");
  stopList.push_back("yourself");
  stopList.push_back("yourselves");
  stopList.push_back("z");
  stopList.push_back("zero");
}
}
  
