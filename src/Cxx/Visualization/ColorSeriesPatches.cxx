
/*
 * Produce a HTML page called VTKColorSeriesPatches.html showing the available
 * color series in vtkColorSeries.
 *
 * It also shows how to select the text color based on luminance.
 * In this case Digital CCIR601 is used which gives less weight to the red and
 * blue components of a color.
 *
 */

#include <vtkColorSeries.h>
#include <vtkNamedColors.h>
#include <vtkSmartPointer.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace {

//! Convert to and from HTML color strings.
class HTMLToFromRGBAColor
{
public:
  HTMLToFromRGBAColor() = default;
  virtual ~HTMLToFromRGBAColor() = default;

public:
  bool IsValidHTMLColorString(std::string const& s);
  std::string RGBToHTMLColor(vtkColor3ub const& rgb);
  vtkColor3ub HTMLColorToRGB(std::string const& colorString);
  double RGBToLumaCCIR601(vtkColor3ub const& rgb);
};

/**
 * Holds the color series id, name and colors.
 */
class ColorStructures
{
public:
  ColorStructures() : max_colors(0)
  {
    this->Init();
  }

  virtual ~ColorStructures() = default;

private:
  void Init();

public:
  std::map<int, std::pair<std::string, std::vector<vtkColor3ub>>> cs_colors;
  int max_colors;
};

/**
 * This class creates a HTML Table displaying all the colors in
 * the class vtkColorSeries.
 */
class HTMLTableMaker
{

public:
  HTMLTableMaker() = default;

  ~HTMLTableMaker() = default;

public:
  std::string MakeHTMLTable();

private:
  std::string MakeHTMLStyle();
  std::string MakeHTMLHeader();
  std::string MakeTableHeader();
  std::string MakeTD1(int const idx, std::string const& name);
  std::string MakeTD2(std::vector<vtkColor3ub> const& rgb);
  std::string MakeTable();

private:
  vtkSmartPointer<vtkNamedColors> nc = vtkSmartPointer<vtkNamedColors>::New();
  ColorStructures cs = ColorStructures();
  HTMLToFromRGBAColor htmlRGBA = HTMLToFromRGBAColor();
};
} // namespace

int main(int argc, char* argv[])
{
  HTMLTableMaker ncpt;

  std::ofstream outputFile;
  outputFile.open("VTKColorSeriesPatches.html",
                  ios::out | ios::trunc | ios::binary);
  outputFile << ncpt.MakeHTMLTable();
  outputFile.close();

  return EXIT_SUCCESS;
}

namespace {

bool HTMLToFromRGBAColor::IsValidHTMLColorString(std::string const& s)
{
  if (s.size() == 7 || s.size() == 9) // #rrggbb or #rrggbbaa
  {
    if (s.compare(0, 1, "#") == 0 &&
        s.find_first_not_of("0123456789abcdefABCDEF", 1) == std::string::npos)
    {
      return true;
    }
  }
  return false;
}

std::string HTMLToFromRGBAColor::RGBToHTMLColor(vtkColor3ub const& rgb)
{
  std::string s = "#";
  std::ostringstream os;
  os << std::setfill('0') << std::hex << std::setw(2)
     << static_cast<unsigned int>(rgb.GetRed()) << std::setw(2)
     << static_cast<unsigned int>(rgb.GetGreen()) << std::setw(2)
     << static_cast<unsigned int>(rgb.GetBlue());
  s += os.str();
  return s;
}

vtkColor3ub HTMLToFromRGBAColor::HTMLColorToRGB(std::string const& colorString)
{
  vtkColor3ub c(0, 0, 0);
  if (IsValidHTMLColorString(colorString) && colorString.size() == 7)
  {
    auto i = 1;
    while (i < static_cast<int>(colorString.size()))
    {
      std::istringstream is(colorString.substr(i, 2));
      int x;
      is >> std::hex >> x;
      c[(i - 1) / 2] = x;
      i += 2;
    }
  }
  return c;
}

double HTMLToFromRGBAColor::RGBToLumaCCIR601(vtkColor3ub const& rgb)
{
  return 0.299 * rgb.GetRed() + 0.587 * rgb.GetGreen() + 0.114 * rgb.GetBlue();
}

void ColorStructures::Init()
{
  auto cs = vtkColorSeries::New();
  std::vector<int> sizes;
  for (auto i = 0; i < cs->GetNumberOfColorSchemes(); ++i)
  {
    cs->SetColorScheme(i);
    sizes.push_back(cs->GetNumberOfColors());
    std::vector<vtkColor3ub> vc;
    for (auto j = 0; j < cs->GetNumberOfColors(); ++j)
    {
      vc.push_back(cs->GetColor(j));
    }
    this->cs_colors[i] = std::pair<std::string, std::vector<vtkColor3ub>>(
        cs->GetColorSchemeName(), vc);
  }
  this->max_colors = *std::max_element(sizes.begin(), sizes.end());
}

std::string HTMLTableMaker::MakeHTMLStyle()
{
  std::string s = "  <style>\n";
  s += "\n";
  s += "  body {\n";
  s += "    background-color: snow\n";
  s += "  }\n";
  s += "  h1 {text-align:left;}\n";
  s += "  h2 {text-align:left;}\n";
  s += "  h3 {text-align:left;}\n";
  s += "  h4 {text-align:left;}\n";
  s += "  h5 {text-align:left;}\n";
  s += "  h6 {text-align:left;}\n";
  s += "\n";
  s += "  p {text-align:left;}\n";
  s += "\n";
  s += "  table {\n";
  s += "    font-family: arial, sans-serif;\n";
  s += "    border-collapse: collapse;\n";
  s += "    font-size: medium;\n";
  s += "    padding: 4px;\n";
  s += "  }\n";
  s += "\n";
  s += "  th {\n";
  s += "    background: LightSteelBlue;\n";
  s += "    font-size: medium;\n";
  s += "  }\n";
  s += "\n";
  s += "  th[colspan]:not([colspan=\"1\"]) {\n";
  s += "    background: LightSteelBlue;\n";
  s += "    font-size: medium;\n";
  s += "    text-align : center;\n";
  s += "    vertical-align : top;\n";
  s += "  }\n";
  s += "\n";
  s += "  tr {\n";
  s += "    background: MintCream;\n";
  s += "    vertical-align : top;\n";
  s += "  }\n";
  s += "\n";
  s += "  td {\n";
  s += "    background: MintCream;\n";
  s += "    border: 1px solid #dddddd;\n";
  s += "    text-align: left;\n";
  s += "    padding: 8px;\n";
  s += "    font-family: monospace;\n";
  s += "    font-size: medium;\n";
  s += "    font-weight: bold;\n";
  s += "  }\n";
  s += "\n";
  s += "  td[colspan]:not([colspan=\"1\"]) {\n";
  s += "    text-align : center;\n";
  s += "  }\n";
  s += "\n";
  s += "  .cour {\n";
  s += "    font-family: Courier;\n";
  s += "  }\n";
  s += "\n";
  s += "  html, body {\n";
  s += "    height: 100%;\n";
  s += "  }\n";
  s += "\n";
  s += "  html {\n";
  s += "    display: table;\n";
  s += "    margin: auto;\n";
  s += "  }\n";
  s += "\n";
  s += "  body {\n";
  s += "    display: table-cell;\n";
  s += "    vertical-align: middle;\n";
  s += "  }\n";
  s += "\n";
  s += "  thead {color: DarkGreen;}\n";
  s += "  tbody {color: MidnightBlue;}\n";
  s += "  tfoot {color: SaddleBrown;}\n";
  s += "\n";
  s += "  </style>\n";
  return s;
}

std::string HTMLTableMaker::MakeHTMLHeader()
{
  std::string s = "<!DOCTYPE html>\n";
  s += "<html lang=\"en\">\n";
  s += "<head>\n";
  s += "<meta charset=\"UTF-8\" />\n";
  s += "<title>vtkColorSeries</title>\n";
  s += this->MakeHTMLStyle();
  s += "</head>\n";
  return s;
}

std::string HTMLTableMaker::MakeTableHeader()
{
  std::string s = "<tr>\n";
  s += "<th>Index</th>\n";
  s +=
      "<th colspan=\"" + std::to_string(this->cs.max_colors) + "\">Name</th>\n";
  s += "</tr>\n";
  s += "<tr>\n";
  s += "<th></th>\n";
  s += "<th colspan=\"" + std::to_string(this->cs.max_colors) +
      "\">Colors in the Series</th>\n";
  s += "</tr>\n";
  return s;
}

std::string HTMLTableMaker::MakeTD1(int const idx, std::string const& name)
{
  std::string s = "<tr>\n";
  s += "<td>";
  s += "<b>" + std::to_string(idx) + "</b>";
  s += "</td>\n";

  s += "<td colspan=\"" + std::to_string(this->cs.max_colors) + "\">";
  s += "<b>" + name + "</b>";
  s += "</td>\n";
  s += "</tr>\n";
  return s;
}
std::string HTMLTableMaker::MakeTD2(std::vector<vtkColor3ub> const& rgbs)
{
  std::string s = "<tr>\n";
  s += "<td></td>\n";

  auto cnt = 0;
  for (auto p : rgbs)
  {
    std::ostringstream os;
    os << std::setw(3) << cnt << "&#160;&#160;";
    auto ss = std::regex_replace(os.str(), std::regex(" "), "&#160;");
    auto y = this->htmlRGBA.RGBToLumaCCIR601(p);
    std::string textColor{"#000000"}; // Black
    if (y < 255 / 2.0)
    {
      textColor = "#ffffff"; // White
    }
    s += "<td style=\"background:" + this->htmlRGBA.RGBToHTMLColor(p) +
        ";color:" + textColor;
    s += "\">" + ss + "</td>\n";
    ++cnt;
  }
  if (cnt < this->cs.max_colors)
  {
    s += "<td colspan=\"" + std::to_string(this->cs.max_colors - cnt) +
        "\"> &#160; </td>\n";
  }
  s += "</tr>\n";
  return s;
}

std::string HTMLTableMaker::MakeTable()
{
  auto res = this->MakeTableHeader();
  for (auto const p : this->cs.cs_colors)
  {
    auto idx = p.first;
    auto name = p.second.first;
    res += this->MakeTD1(idx, name);
    res += this->MakeTD2(p.second.second);
  }
  return res;
}

std::string HTMLTableMaker::MakeHTMLTable()
{
  auto res = this->MakeHTMLHeader();
  res += "<body>\n";
  res += "<h1>Color series available in vtkColorSeries</h1>\n";
  res += "<table>\n";
  res += this->MakeTable();
  res += "</table>\n";
  res += "</body>\n";
  return res;
}

} // namespace
