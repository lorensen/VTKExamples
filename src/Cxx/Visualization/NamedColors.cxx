/*
This example demonstrates the usage of the vtNamedColor class.
*/
#include <vtkActor.h>
#include <vtkAlgorithm.h>
#include <vtkBandedPolyDataContourFilter.h>
#include <vtkConeSource.h>
#include <vtkElevationFilter.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

namespace {
// Get the color names.
std::vector<std::string> GetColorNames(vtkNamedColors* namedColors);

// Get the synonyms.
std::vector<std::vector<std::string>> GetSynonyms(vtkNamedColors* namedColors);

// Print out the colors.
void PrintColors(vtkNamedColors* namedColors);

// Print out the synonyms.
void PrintSynonyms(vtkNamedColors* namedColors);

// Find any synonyms for a specified color.
std::vector<std::string> FindSynonyms(const std::string& color,
                                      vtkNamedColors* namedColors);

} // namespace

// Create a cone, contour it using the banded contour filter and
// color it with the primary additive and subtractive colors.
int main(int, char*[])
{
  auto namedColors = vtkSmartPointer<vtkNamedColors>::New();

  // We can print out the variables.
  // The color name and RGBA values are displayed.
  // namedColors->PrintSelf(std::cout,vtkIndent(2));

  // Here we just print out the colors and any
  // synonyms.
  PrintColors(namedColors);
  PrintSynonyms(namedColors);

  // Create a cone
  auto coneSource = vtkSmartPointer<vtkConeSource>::New();
  coneSource->SetCenter(0.0, 0.0, 0.0);
  coneSource->SetRadius(5.0);
  coneSource->SetHeight(10);
  coneSource->SetDirection(0, 1, 0);
  coneSource->SetResolution(6);
  coneSource->Update();

  double bounds[6];
  coneSource->GetOutput()->GetBounds(bounds);

  auto elevation = vtkSmartPointer<vtkElevationFilter>::New();
  elevation->SetInputConnection(coneSource->GetOutputPort());
  elevation->SetLowPoint(0, bounds[2], 0);
  elevation->SetHighPoint(0, bounds[3], 0);

  auto bcf = vtkSmartPointer<vtkBandedPolyDataContourFilter>::New();
  bcf->SetInputConnection(elevation->GetOutputPort());
  bcf->SetScalarModeToValue();
  bcf->GenerateContourEdgesOn();
  bcf->GenerateValues(7, elevation->GetScalarRange());

  double rgba[4];
  // Test setting and getting colors here.
  // We are also modifying alpha.
  namedColors->GetColor("Red", rgba);
  // Make it semitransparent.
  rgba[3] = 0.5;
  namedColors->SetColor("My Red", rgba);
  // Does "My Red" match anything?
  // Demonstrates how to find synonyms.
  auto matchingColors = FindSynonyms("My Red", namedColors);
  if (!matchingColors.empty())
  {
    std::cout << "Matching colors to My Red: ";
    size_t i = 1;
    for (auto p : matchingColors)
    {
      std::cout << p;
      if (i < matchingColors.size())
      {
        std::cout << ", ";
        i = 1;
      }
      ++i;
    }
    std::cout << std::endl;
  }
  // Build a simple lookup table of
  // primary additive and subtractive colors.
  auto lut = vtkSmartPointer<vtkLookupTable>::New();
  lut->SetNumberOfTableValues(7);
  lut->SetTableValue(0, namedColors->GetColor4d("My Red").GetData());
  // Let's make the dark green one partially transparent.
  namedColors->GetColor("Lime", rgba);
  rgba[3] = 0.3;
  lut->SetTableValue(1, rgba);
  lut->SetTableValue(2, namedColors->GetColor4d("Blue").GetData());
  lut->SetTableValue(3, namedColors->GetColor4d("Cyan").GetData());
  lut->SetTableValue(4, namedColors->GetColor4d("Magenta").GetData());
  lut->SetTableValue(5, namedColors->GetColor4d("Yellow").GetData());
  lut->SetTableValue(6, namedColors->GetColor4d("White").GetData());
  lut->SetTableRange(elevation->GetScalarRange());
  lut->Build();

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(bcf->GetOutputPort());
  mapper->SetScalarRange(elevation->GetScalarRange());
  mapper->SetLookupTable(lut);
  mapper->SetScalarModeToUseCellData();

  auto contourLineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  contourLineMapper->SetInputData(bcf->GetContourEdgesOutput());
  contourLineMapper->SetScalarRange(elevation->GetScalarRange());
  contourLineMapper->SetResolveCoincidentTopologyToPolygonOffset();

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto contourLineActor = vtkSmartPointer<vtkActor>::New();
  contourLineActor->SetMapper(contourLineMapper);
  contourLineActor->GetProperty()->SetColor(
      namedColors->GetColor3d("Black").GetData());

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->AddActor(contourLineActor);
  renderer->SetBackground2(namedColors->GetColor3d("RoyalBlue").GetData());
  renderer->SetBackground(namedColors->GetColor3d("MistyRose").GetData());
  renderer->GradientBackgroundOn();
  renderWindow->SetSize(600, 600);
  renderWindow->Render();
  renderWindow->SetWindowName("NamedColors");
  renderWindow->Render();

  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}

namespace {
std::vector<std::string> GetColorNames(vtkNamedColors* namedColors)
{
  std::stringstream ss(namedColors->GetColorNames());
  std::string color;
  std::vector<std::string> cn;
  while (std::getline(ss, color, '\n'))
  {
    cn.push_back(std::move(color));
  }
  return cn;
}

std::vector<std::vector<std::string>> GetSynonyms(vtkNamedColors* namedColors)
{
  auto ncsyn = namedColors->GetSynonyms();
  std::stringstream ss(std::regex_replace(ncsyn, std::regex("\n\n"), "*"));
  std::string synonyms;
  std::vector<std::vector<std::string>> sn;
  while (std::getline(ss, synonyms, '*'))
  {
    std::vector<std::string> syns;
    std::stringstream ss1(synonyms);
    std::string color;
    while (std::getline(ss1, color, '\n'))
    {
      syns.push_back(std::move(color));
    }
    sn.push_back(std::move(syns));
  }
  return sn;
}

std::vector<std::string> FindSynonyms(const std::string& color,
                                      vtkNamedColors* namedColors)
{
  auto availableColors = GetColorNames(namedColors);
  // We will be matching on RGB only.
  auto myColor = namedColors->GetColor3ub(color);
  // Colors are all stored as lower case, so convert color to lower case.
  std::string lcColor;
  std::transform(color.begin(), color.end(), std::back_inserter(lcColor),
                 (int (*)(int))std::tolower);
  std::vector<std::string> synonyms;
  for (auto p : availableColors)
  {
    auto c = namedColors->GetColor3ub(p);
    if (myColor.Compare(c, 1))
    {
      synonyms.push_back(p);
    }
  }
  return synonyms;
}

void PrintColors(vtkNamedColors* namedColors)
{
  // Get the available colors:
  auto colors = GetColorNames(namedColors);
  std::cout << "There are " << colors.size() << " colors:" << std::endl;
  auto max_str =
      std::max_element(colors.begin(), colors.end(),
                       [](std::string const& a, std::string const& b) {
                         return a.size() < b.size();
                       });
  auto max_str_len = max_str->size();
  auto n = 0;
  std::ostringstream os;
  for (auto const p : colors)
  {
    ++n;
    if (n % 5 == 0)
    {
      os << std::left << p << std::endl;
    }
    else
    {
      os << std::left << std::setw(max_str_len) << p << " ";
    }
  }
  std::string s = std::regex_replace(os.str(), std::regex("\\s+$"), "\n");
  std::cout << s << std::endl;
}

void PrintSynonyms(vtkNamedColors* namedColors)
{
  // Get the synonyms:
  auto synonyms = GetSynonyms(namedColors);
  std::cout << "There are " << synonyms.size() << " synonyms:" << std::endl;
  // Get the size of the longest synonym name.
  size_t max_str_len = 0;
  for (auto const p : synonyms)
  {
    auto max_str = std::max_element(
        p.begin(), p.end(), [](std::string const& a, std::string const& b) {
          return a.size() < b.size();
        });
    max_str_len =
        (max_str_len < max_str->size()) ? max_str->size() : max_str_len;
  }
  for (auto const p : synonyms)
  {
    size_t n = 0;
    for (auto const q : p)
    {
      ++n;
      if (n < p.size())
      {
        std::cout << std::left << std::setw(max_str_len) << q << " ";
      }
      else
      {
        std::cout << q << std::endl;
      }
    }
  }
  std::cout << std::endl;
}
} // namespace
