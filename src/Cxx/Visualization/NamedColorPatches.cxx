
/*
 * Produce a HTML page called VTKNamedColorPatches.html showing the available
 * colors in vtkNamedColors.
 *
 * It also shows how to select the text color based on luminance.
 * In this case Digital CCIR601 is used which gives less weight to the red and
 * blue components of a color.
 *
 */

#include <vtkNamedColors.h>
#include <vtkSmartPointer.h>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <locale>
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
 * Holds the color names, grouped by color class, and information about table
 * layout and ordering.
 */
class ColorStructures
{
public:
  ColorStructures()
  {
    this->Init();
  }

  virtual ~ColorStructures() = default;

private:
  void Init();

public:
  std::map<std::string, std::vector<std::string>> cn;
  // Ordering of the tables and when to start and end a column of
  // tables in the layout.
  std::vector<std::string> cnOrder;
  std::vector<std::string> cnStartTable;
  std::vector<std::string> cnEndTable;

  std::map<std::string, std::vector<std::string>> vtkcn;
  // Ordering of the tables and when to start and end a column of
  // tables in the layout.
  std::vector<std::string> vtkcnOrder;
  std::vector<std::string> vtkcnStartTable;
  std::vector<std::string> vtkcnEndTable;
};

/**
 * This class creates HTML Tables displaying all the colors in
 * the class vtkNamedColors grouped by various categories.
 */
class HTMLTableMaker
{

public:
  HTMLTableMaker() = default;

  ~HTMLTableMaker() = default;

public:
  std::string MakeWebColorPage();
  std::string MakeVTKColorPage();
  std::string MakeSynonymColorPage();
  std::string MakeCombinedColorPage();

private:
  std::vector<std::vector<std::string>> GetSynonyms();
  std::string FormatRGBForHTML(vtkColor3ub const& rgb);
  std::string MakeHTMLStyle();
  std::string MakeHTMLHeader();
  std::string MakeHTMLIndex();
  std::string MakeTableHeader(std::string const& title);
  std::string MakeTD(std::string const& name);
  //! Use when the name is a color name known to the web browser.
  std::string MakeTR(const std::string& name, vtkColor3ub const& rgb,
                     const std::string& textColor);
  //! Use when the name is not a color name known to the web browser.
  std::string MakeTR_HTML(const std::string& name, const std::string& htmlColor,
                          vtkColor3ub const& rgb, const std::string& textColor);
  std::string MakeWebColorTables();
  std::string MakeVTKColorTables();
  std::string MakeSynonymColorTable();

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
  outputFile.open("VTKNamedColorPatches.html",
                  ios::out | ios::trunc | ios::binary);
  outputFile << ncpt.MakeCombinedColorPage();
  // outputFile << ncpt.MakeWebColorPage();
  // outputFile << ncpt.MakeVTKColorPage();
  // outputFile << ncpt.MakeSynonymColorPage();
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
  // clang-format off
    this->cn = {
		  {"Red",
			  {"IndianRed", "LightCoral", "Salmon", "DarkSalmon",
			  "LightSalmon", "Red", "Crimson", "FireBrick", "DarkRed"}},
      {"Pink",
        {"Pink", "LightPink", "HotPink", "DeepPink",
        "MediumVioletRed", "PaleVioletRed"}},
      {"Orange",
        {"LightSalmon", "Coral", "Tomato", "OrangeRed",
        "DarkOrange", "Orange"}},
      {"Yellow",
        {"Gold", "Yellow", "LightYellow", "LemonChiffon",
        "LightGoldenrodYellow", "PapayaWhip", "Moccasin",
        "PeachPuff", "PaleGoldenrod", "Khaki", "DarkKhaki"}},
      {"Purple",
        {"Lavender", "Thistle", "Plum", "Violet", "Orchid",
        "Fuchsia", "Magenta", "MediumOrchid", "MediumPurple",
        "BlueViolet", "DarkViolet", "DarkOrchid", "DarkMagenta",
        "Purple", "Indigo", "DarkSlateBlue", "SlateBlue",
        "MediumSlateBlue"}},
      {"Green",
        {"GreenYellow", "Chartreuse", "LawnGreen", "Lime",
        "LimeGreen", "PaleGreen", "LightGreen",
        "MediumSpringGreen", "SpringGreen", "MediumSeaGreen",
        "SeaGreen", "ForestGreen", "Green", "DarkGreen",
        "YellowGreen", "OliveDrab", "Olive", "DarkOliveGreen",
        "MediumAquamarine", "DarkSeaGreen", "LightSeaGreen",
        "DarkCyan", "Teal"}},
      {"Blue/Cyan",
        {"Aqua", "Cyan", "LightCyan", "PaleTurquoise",
        "Aquamarine", "Turquoise", "MediumTurquoise",
        "DarkTurquoise", "CadetBlue", "SteelBlue",
        "LightSteelBlue", "PowderBlue", "LightBlue",
        "SkyBlue", "LightSkyBlue", "DeepSkyBlue",
        "DodgerBlue",  "CornflowerBlue", "RoyalBlue", "Blue",
        "MediumBlue",  "DarkBlue", "Navy", "MidnightBlue"}},
      {"Brown",
        {"Cornsilk", "BlanchedAlmond", "Bisque", "NavajoWhite",
        "Wheat", "BurlyWood", "Tan", "RosyBrown", "SandyBrown",
        "Goldenrod", "DarkGoldenrod", "Peru", "Chocolate",
        "SaddleBrown", "Sienna", "Brown", "Maroon"}},
      {"White",
        {"White", "Snow", "Honeydew", "MintCream", "Azure",
        "AliceBlue", "GhostWhite", "WhiteSmoke", "Seashell",
        "Beige", "OldLace", "FloralWhite", "Ivory",
        "AntiqueWhite", "Linen",
        "LavenderBlush", "MistyRose"}},
      {"Gray",
        {"Gainsboro", "LightGrey", "Silver", "DarkGray", "Gray",
        "DimGray", "LightSlateGray", "SlateGray", "DarkSlateGray",
        "Black"}}
    };
    // Ordering of the tables and when to start and end a column of tables
    // in the layout.
    this->cnOrder = {
      "Red",   "Pink",      "Orange", "Yellow", "Purple",
      "Green", "Blue/Cyan", "Brown",  "White",  "Gray"};
    this->cnStartTable = {"Red", "Green", "Brown"};
    this->cnEndTable = {"Purple", "Blue/Cyan", "Gray"};

    this->vtkcn = {
      {"Whites",
        {"antique_white", "azure", "bisque",  "blanched_almond",
        "cornsilk", "eggshell", "floral_white", "gainsboro",
        "ghost_white", "honeydew", "ivory", "lavender",
        "lavender_blush", "lemon_chiffon", "linen", "mint_cream",
        "misty_rose", "moccasin", "navajo_white", "old_lace",
        "papaya_whip", "peach_puff", "seashell", "snow",
        "thistle", "titanium_white", "wheat", "white",
        "white_smoke", "zinc_white"}},
      {"Greys",
        {"cold_grey", "dim_grey", "grey", "light_grey",
        "slate_grey", "slate_grey_dark", "slate_grey_light",
        "warm_grey"}},
      {"Blacks",
        {"black", "ivory_black", "lamp_black"}},
      {"Reds",
        {"alizarin_crimson", "brick",  "cadmium_red_deep",  "coral",
        "coral_light", "deep_pink", "english_red", "firebrick",
        "geranium_lake", "hot_pink", "indian_red", "light_salmon",
        "madder_lake_deep", "maroon", "pink", "pink_light",
        "raspberry", "red", "rose_madder", "salmon", "tomato",
        "venetian_red"}},
      {"Browns",
        {"beige", "brown", "brown_madder", "brown_ochre",
        "burlywood", "burnt_sienna", "burnt_umber", "chocolate",
        "deep_ochre", "flesh", "flesh_ochre", "gold_ochre",
        "greenish_umber", "khaki", "khaki_dark", "light_beige",
        "peru", "rosy_brown", "raw_sienna", "raw_umber", "sepia",
        "sienna", "saddle_brown", "sandy_brown", "tan",
        "van_dyke_brown"}},
      {"Oranges",
        {"cadmium_orange", "cadmium_red_light", "carrot",
        "dark_orange", "mars_orange", "mars_yellow", "orange",
        "orange_red", "yellow_ochre"}},
      {"Yellows",
        {"aureoline_yellow", "banana", "cadmium_lemon",
        "cadmium_yellow", "cadmium_yellow_light", "gold",
        "goldenrod", "goldenrod_dark", "goldenrod_light",
        "goldenrod_pale", "light_goldenrod", "melon",
        "naples_yellow_deep", "yellow", "yellow_light"}},
      {"Greens",
        {"chartreuse", "chrome_oxide_green", "cinnabar_green",
        "cobalt_green", "emerald_green", "forest_green", "green",
        "green_dark", "green_pale", "green_yellow", "lawn_green",
        "lime_green", "mint", "olive", "olive_drab",
        "olive_green_dark", "permanent_green", "sap_green",
        "sea_green", "sea_green_dark", "sea_green_medium",
        "sea_green_light", "spring_green", "spring_green_medium",
        "terre_verte", "viridian_light", "yellow_green"}},
      {"Cyans",
        {"aquamarine", "aquamarine_medium", "cyan", "cyan_white",
        "turquoise", "turquoise_dark", "turquoise_medium",
        "turquoise_pale"}},
      {"Blues",
        {"alice_blue", "blue", "blue_light", "blue_medium",
        "cadet", "cobalt", "cornflower", "cerulean", "dodger_blue",
        "indigo", "manganese_blue", "midnight_blue", "navy",
        "peacock", "powder_blue", "royal_blue", "slate_blue",
        "slate_blue_dark", "slate_blue_light",
        "slate_blue_medium", "sky_blue", "sky_blue_deep",
        "sky_blue_light", "steel_blue", "steel_blue_light",
        "turquoise_blue", "ultramarine"}},
      {"Magentas",
        {"blue_violet", "cobalt_violet_deep", "magenta",
        "orchid", "orchid_dark", "orchid_medium",
        "permanent_red_violet", "plum", "purple",
        "purple_medium", "ultramarine_violet", "violet",
        "violet_dark", "violet_red", "violet_red_medium",
        "violet_red_pale"}}
    };
    // Ordering of the tables and when to start and end a column of tables
    // in the layout.
    this->vtkcnOrder = {
      "Whites",  "Greys",  "Blacks", "Reds",  "Oranges", "Browns",
      "Yellows", "Greens", "Cyans",  "Blues", "Magentas"};
    this->vtkcnStartTable = {"Whites", "Browns",  "Cyans"};
    this->vtkcnEndTable = {"Oranges", "Greens", "Magentas"};
  // clang-format on
}

std::string HTMLTableMaker::MakeWebColorPage()
{
  std::string res = this->MakeHTMLHeader();
  res += "<body>\n";
  res += "<h1>Colors available in vtkNamedColors</h1>\n";
  res += "<table>\n";
  res += "<tr>\n";
  res += "<th colspan=\"3\">Web Color Names</th>\n";
  res += "</tr>\n";
  res += "<tr>\n";
  res += this->MakeWebColorTables();
  res += "</tr>\n";
  res += "</table>\n";
  res += "</body>\n";
  return res;
}

std::string HTMLTableMaker::MakeVTKColorPage()
{
  std::string res = this->MakeHTMLHeader();
  res += "<body>\n";
  res += "<h1>Colors available in vtkNamedColors</h1>\n";
  res += "The web colors take precedence over colors of the same";
  res += " name in VTK Color Names.\n";
  res += "<table>\n";
  res += "<tr>\n";
  res += "<th colspan=\"3\">VTK Color Names</th>\n";
  res += "</tr>\n";
  res += "<tr>\n";
  res += this->MakeVTKColorTables();
  res += "</tr>\n";
  res += "</table>\n";
  res += "</body>\n";
  return res;
}

std::string HTMLTableMaker::MakeSynonymColorPage()
{
  std::string res = this->MakeHTMLHeader();
  res += "<body>\n";
  res += "<h1>Synonyms in vtkNamedColors</h1>\n";
  res += "<table>\n";
  res += "<tr>\n";
  res += "<th colspan=\"2\">Synonyms</th>\n";
  res += "</tr>\n";
  res += "<tr>\n";
  res += this->MakeSynonymColorTable();
  res += "</tr>\n";
  res += "</table>\n";
  res += "</body>\n";
  return res;
}

std::string HTMLTableMaker::MakeCombinedColorPage()
{
  std::string res = this->MakeHTMLHeader();
  res += "<body>\n";
  res += "<h1>Colors available in vtkNamedColors</h1>\n";
  res += "The class vtkNamedColors provides color names and their";
  res += " values for the convenience of the user.\n";
  res += "<br>The following tables show the available colors along with";
  res += " their red, green and blue values.\n";
  res += this->MakeHTMLIndex();
  res += "<table>\n";
  res += "<tr>\n";
  res += "<th colspan=\"3\"><a id=\"WebColorNames\">Web color Names</a></th>\n";
  res += "</tr>\n";
  res += "<tr>\n";
  res += this->MakeWebColorTables();
  res += "</tr>\n";
  res += "</table>\n";
  res += "<br>\n";

  res += "<table>\n";
  res += "<tr>\n";
  res += "<th colspan=\"3\"><a id=\"VTKColorNames\">VTK color Names</a></th>\n";
  res += "</tr>\n";
  res += "<tr>\n";
  res += this->MakeVTKColorTables();
  res += "</tr>\n";
  res += "</table>\n";
  res += "<br>\n";

  res += "<table>\n";
  res += "<tr>\n";
  res += "<th colspan=\"2\"><a id=\"Synonyms\">Synonyms</a></th>\n";
  res += "</tr>\n";
  res += "<tr>\n";
  res += this->MakeSynonymColorTable();
  res += "</tr>\n";
  res += "</table>\n";
  res += "</body>\n";
  return res;
}

std::vector<std::vector<std::string>> HTMLTableMaker::GetSynonyms()
{
  auto ncsyn = this->nc->GetSynonyms();
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

std::string HTMLTableMaker::MakeHTMLStyle()
{
  std::string s = "  <style>\n";
  s += "  \n";
  s += "  body {\n";
  s += "    background-color: snow\n";
  s += "  }\n";
  s += "  h1 {text-align:left;}\n";
  s += "  h2 {text-align:left;}\n";
  s += "  h3 {text-align:left;}\n";
  s += "  h4 {text-align:left;}\n";
  s += "  h5 {text-align:left;}\n";
  s += "  h6 {text-align:left;}\n";
  s += "  \n";
  s += "  p {text-align:left;}\n";
  s += "  \n";
  s += "  table {\n";
  s += "    font-family: arial, sans-serif;\n";
  s += "    border-collapse: collapse;\n";
  s += "    font-size: medium;\n";
  s += "    padding: 4px;\n";
  s += "  }\n";
  s += "\n";
  s += "  th[colspan]:not([colspan=\"1\"]) {\n";
  s += "    background: LightSteelBlue;\n";
  s += "    font-size: x-large;\n";
  s += "    text-align : center;";
  s += "    vertical-align : top;\n";
  s += "  }\n";
  s += "  th {\n";
  s += "    background: LightSteelBlue;\n";
  s += "  }\n";
  s += "  td, th {\n";
  s += "    border: 1px solid #dddddd;\n";
  s += "    text-align: left;\n";
  s += "    padding: 8px;\n";
  s += "    font-family: monospace;\n";
  s += "    font-size: medium;\n";
  s += "    font-weight: bold;\n";
  s += "  }\n";
  s += "\n";
  s += "  tr {\n";
  s += "    background: WhiteSmoke;\n";
  s += "    vertical-align : top;\n";
  s += "  }\n";
  s += "\n";
  s += "  td[colspan]:not([colspan=\"1\"]) {\n";
  s += "    background: MintCream;\n";
  s += "    font-size: large;\n";
  s += "    text-align : center;";
  s += "    vertical-align : top;\n";
  s += "  }\n";
  s += "  td {\n";
  s += "    background: WhiteSmoke;\n";
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
  s += "<title>vtkNamedColors</title>\n";
  s += this->MakeHTMLStyle();
  s += "</head>\n";
  return s;
}

std::string HTMLTableMaker::MakeHTMLIndex()
{
  std::string s = "<h2>Index</h2>\n";
  s += "<ul>\n";
  s += "\t<li><a href=\"#WebColorNames\">Web color Names</a>";
  s += " These colors correspond to those in";
  s += " <a href=\"http://en.wikipedia.org/wiki/Web_colors\"";
  s += " title=\"Web Colors\">Web Colors</a>.\n";
  s += "</li>\n";
  s += "\t<li><a href=\"#VTKColorNames\">VTK color Names</a>\n";
  s += " The colors correspond to additional colors commonly used in VTK.\n";
  s += "<br>The web colors take precedence over colors with\n";
  s += " the same name (case insensitive) here.\n";
  s += "</li>\n";
  s += "\t<li><a href=\"#Synonyms\">Synonyms</a></li>\n";
  s += "</ul>\n";
  return s;
}

std::string HTMLTableMaker::MakeTableHeader(std::string const& title)
{
  std::string s = "<tr>\n";
  s += "<th>";
  s += title;
  s += "</th>\n";
  s += "<th>Decimal code<br>\n";
  s += "&#160;&#160;R";
  s += "&#160;&#160;&#160;&#160;G";
  s += "&#160;&#160;&#160;&#160;B</th>\n";
  s += "</tr>\n";
  return s;
}

std::string HTMLTableMaker::MakeTD(std::string const& name)
{
  std::string s = "<tr>\n";
  s += "<td colspan=\"2\">";
  s += "<b>" + name + "</b>";
  s += "</td>\n";
  s += "</tr>\n";
  return s;
}

std::string HTMLTableMaker::FormatRGBForHTML(vtkColor3ub const& rgb)
{
  std::ostringstream os;
  os << std::setw(3) << static_cast<unsigned int>(rgb.GetRed())
     << "&#160;&#160;" << std::setw(3)
     << static_cast<unsigned int>(rgb.GetGreen()) << "&#160;&#160;"
     << std::setw(3) << static_cast<unsigned int>(rgb.GetBlue());
  return std::regex_replace(os.str(), std::regex(" "), "&#160;");
}

std::string HTMLTableMaker::MakeTR(const std::string& name,
                                   vtkColor3ub const& rgb,
                                   const std::string& textColor)
{
  std::string s = "<tr>\n";
  s += "<td style=\"background:" + name + ";color:" + textColor;
  s += "\">" + name + "</td>\n";
  s += "<td style=\"background:" + name + ";color:" + textColor;
  s += "\">" + this->FormatRGBForHTML(rgb) + "</td>\n";
  s += "</tr>\n";
  return s;
}

std::string HTMLTableMaker::MakeTR_HTML(const std::string& name,
                                        const std::string& htmlColor,
                                        vtkColor3ub const& rgb,
                                        const std::string& textColor)
{
  std::string s = "<tr>\n";
  s += "<td style=\"background:" + htmlColor + ";color:" + textColor;
  s += "\">" + name + "</td>\n";
  s += "<td style=\"background:" + htmlColor + ";color:" + textColor;
  s += "\">" + this->FormatRGBForHTML(rgb) + "</td>\n";
  s += "</tr>\n";
  return s;
}

std::string HTMLTableMaker::MakeWebColorTables()
{
  std::string res;
  for (auto p : cs.cnOrder)
  {
    if (std::find(this->cs.cnStartTable.begin(), this->cs.cnStartTable.end(),
                  p) != this->cs.cnStartTable.end())
    {
      res += "<td>\n";
      res += "<table>\n";
      res += this->MakeTableHeader("HTML name");
    }
    // Add in the name of the group in the color table.
    res += this->MakeTD(p + " colors");
    auto values = this->cs.cn[p];
    for (auto q : values)
    {
      auto rgb = this->nc->GetColor3ub(q);
      auto y = this->htmlRGBA.RGBToLumaCCIR601(rgb);
      std::string textColor{"#000000"}; // Black
      if (y < 255 / 2.0)
      {
        textColor = "#ffffff"; // White
      }
      // Make the row for each color in the group.
      // Here we use the name to set the background color
      //  as it is known to the web browser.
      res += this->MakeTR(q, rgb, textColor);
    }
    if (std::find(this->cs.cnEndTable.begin(), this->cs.cnEndTable.end(), p) !=
        this->cs.cnEndTable.end())
    {
      res += "</table>\n";
      res += "</td>\n";
    }
  }
  return res;
}

std::string HTMLTableMaker::MakeVTKColorTables()
{
  std::string res;

  for (auto p : cs.vtkcnOrder)
  {
    if (std::find(this->cs.vtkcnStartTable.begin(),
                  this->cs.vtkcnStartTable.end(),
                  p) != this->cs.vtkcnStartTable.end())
    {
      res += "<td>\n";
      res += "<table>\n";
      res += this->MakeTableHeader("HTML name");
    }
    // Add in the name of the group in the color table.
    res += this->MakeTD(p);
    auto values = this->cs.vtkcn[p];
    for (auto q : values)
    {
      auto rgb = this->nc->GetColor3ub(q);
      auto y = this->htmlRGBA.RGBToLumaCCIR601(rgb);
      std::string textColor{"#000000"}; // Black
      if (y < 255 / 2.0)
      {
        textColor = "#ffffff"; // White
      }
      // We must set the background color to a specific
      // HTML color as the color name may not be a standard
      // name known to the web browser.
      auto htmlColor = htmlRGBA.RGBToHTMLColor(rgb);
      // Make the row for each color in the group.
      res += this->MakeTR_HTML(q, htmlColor, rgb, textColor);
    }
    if (std::find(this->cs.vtkcnEndTable.begin(), this->cs.vtkcnEndTable.end(),
                  p) != this->cs.vtkcnEndTable.end())
    {
      res += "</table>\n";
      res += "</td>\n";
    }
  }
  return res;
}

std::string HTMLTableMaker::MakeSynonymColorTable()
{
  auto synonyms = this->GetSynonyms();
  std::vector<std::string> cn;
  for (const auto p : this->cs.cn)
  {
    std::copy(p.second.begin(), p.second.end(), std::back_inserter(cn));
  }
  std::map<std::string, std::string> d;
  for (const auto p : cn)
  {
    // Make a lowercase key.
    std::string key;
    key.resize(p.size());
    std::transform(
        p.begin(), p.end(), key.begin(),
        [](unsigned char const & c) -> unsigned char { return std::tolower(c); });
    d[key] = p;
  }
  // End point of first table.
  auto end1 = synonyms.size() / 2;
  if (end1 * 2 < synonyms.size())
  {
    end1 += 1;
  }
  std::string res;
  res += "<td>\n";
  res += "<table>\n";
  res += this->MakeTableHeader("Synonyms");
  size_t count = 0;
  for (auto p : synonyms)
  {
    if (count == end1)
    {
      res += "</table>\n";
      res += "</td>\n";
      res += "<td>\n";
      res += "<table>\n";
      res += this->MakeTableHeader("Synonyms");
    }
    for (auto& q : p)
    {
      // Replace the lowercase name with the proper name.
      if (d.find(q) != d.end())
      {
        q = d[q];
      }
    }
    std::sort(p.begin(), p.end());
    std::string names;
    for (auto q : p)
    {
      names += q;
      if (q != p.back())
      {
        names += ", ";
      }
    }
    auto rgb = this->nc->GetColor3ub(*(p.begin()));
    auto y = this->htmlRGBA.RGBToLumaCCIR601(rgb);
    std::string textColor{"#000000"}; // Black
    if (y < 255 / 2.0)
    {
      textColor = "#ffffff"; // White
    }
    // We must set the background color to a specific
    // HTML color because names is just a list of
    // synonyms for that particular color.
    auto htmlColor = this->htmlRGBA.RGBToHTMLColor(rgb);
    // Make the row for each color in the group.
    res += this->MakeTR_HTML(names, htmlColor, rgb, textColor);
    count++;
  }
  res += "</table>\n";
  res += "</td>\n";
  return res;
}

} // namespace
