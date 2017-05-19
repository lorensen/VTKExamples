#include <vtkNamedColors.h>
#include <vtkSmartPointer.h>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#ifdef WIN32
#define snprintf _snprintf_s
#endif

namespace
{
//! Some STL Utilities.
class STLHelpers
{
public:
  //---------------------------------------------------------------------------
  STLHelpers() {}

  //---------------------------------------------------------------------------
  virtual ~STLHelpers() {}

  //-----------------------------------------------------------------------------
  // Convert a string to lowercase.
  std::string ToLowercase(const std::string& str)
  {
    std::string s;
    std::transform(str.begin(), str.end(), std::back_inserter(s),
      (int (*)(int))std::tolower);
    return s;
  }

  //-----------------------------------------------------------------------------
  // Replace all occurrences of old_value in a string with new_value.
  std::string ReplaceAll(std::string& str, const std::string& old_value,
    const std::string& new_value)
  {
    size_t start_pos = 0;
    while ((start_pos = str.find(old_value, start_pos)) != std::string::npos)
    {
      str.replace(start_pos, old_value.length(), new_value);
      // It could be that 'new_value' is a substring of 'old_value'.
      start_pos += new_value.length();
    }
    return str;
  }

  //-----------------------------------------------------------------------------
  // An implementation of the C++11 next(iter,n) found in the header <iterator>.
  // ForwardIt must meet the requirements of ForwardIterator.
  // Return the nth successor of iterator it.
  template <typename ForwardIt>
  ForwardIt Next(ForwardIt iter,
    typename std::iterator_traits<ForwardIt>::difference_type n = 1)
  {
    std::advance(iter, n);
    return iter;
  }

  //-----------------------------------------------------------------------------
  // Return true if the iterator points to the last element.
  template <typename Iter, typename Cont>
  bool IsLast(Iter iter, const Cont& cont)
  {
    return (iter != cont.end()) && (Next(iter) == cont.end());
  }
};

// Convert to and from HTML color strings.
class HTMLToFromRGBAColor
{
public:
  //---------------------------------------------------------------------------
  HTMLToFromRGBAColor() {}

  //---------------------------------------------------------------------------
  virtual ~HTMLToFromRGBAColor() {}

  //-----------------------------------------------------------------------------
  bool IsValidHTMLColorString(std::string const& s)
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

  //-----------------------------------------------------------------------------
  std::string RGBToHTMLColor(vtkColor3ub const& rgb)
  {
    std::string s = "#";
    char buff[9];
    snprintf(buff, sizeof(buff) - 1, "%02x", rgb.GetRed());
    s += buff;
    snprintf(buff, sizeof(buff) - 1, "%02x", rgb.GetGreen());
    s += buff;
    snprintf(buff, sizeof(buff) - 1, "%02x", rgb.GetBlue());
    s += buff;
    return s;
  }

  //-----------------------------------------------------------------------------
  vtkColor3ub HTMLColorToRGB(std::string const& colorString)
  {
    vtkColor3ub c(0, 0, 0);
    if (IsValidHTMLColorString(colorString))
    {
      std::string t = colorString.substr(1);
      std::string v = t.substr(0, 2);
      c.SetRed(
        static_cast<unsigned char>(strtoul(t.substr(0, 2).c_str(), NULL, 16)));
      c.SetGreen(
        static_cast<unsigned char>(strtoul(t.substr(2, 2).c_str(), NULL, 16)));
      c.SetBlue(
        static_cast<unsigned char>(strtoul(t.substr(4, 2).c_str(), NULL, 16)));
    }
    return c;
  }

  //-----------------------------------------------------------------------------
  double RGBToLumaCCIR601(vtkColor3ub const& rgb)
  {
    return 0.299 * rgb.GetRed() + 0.587 * rgb.GetGreen() +
           0.114 * rgb.GetBlue();
  }
};

//! Holds the color names and information about table layout and ordering.
/*!
  This class creates a series of maps and vectors of color names from
  a series of python dictionaries and lists.
  */
class ColorStructures
{
public:
  //---------------------------------------------------------------------------
  ColorStructures() { this->Init(); }

  //---------------------------------------------------------------------------
  virtual ~ColorStructures() {}

private:
  //---------------------------------------------------------------------------
  void Init()
  {
    // These strings correspond to the maps and lists used in the Python
    // version of this code (NamedColorPatches.py).
    const std::string cnStr = "\
'Red':['IndianRed', 'LightCoral', 'Salmon', 'DarkSalmon',\
'LightSalmon', 'Red', 'Crimson', 'FireBrick', 'DarkRed'],\
'Pink':['Pink', 'LightPink', 'HotPink', 'DeepPink',\
'MediumVioletRed', 'PaleVioletRed'],\
'Orange':['LightSalmon', 'Coral', 'Tomato', 'OrangeRed',\
'DarkOrange', 'Orange'],\
'Yellow':['Gold', 'Yellow', 'LightYellow', 'LemonChiffon',\
'LightGoldenrodYellow', 'PapayaWhip', 'Moccasin',\
'PeachPuff', 'PaleGoldenrod', 'Khaki', 'DarkKhaki'],\
'Purple':['Lavender', 'Thistle', 'Plum', 'Violet', 'Orchid',\
'Fuchsia', 'Magenta', 'MediumOrchid', 'MediumPurple',\
'BlueViolet', 'DarkViolet', 'DarkOrchid', 'DarkMagenta',\
'Purple', 'Indigo', 'DarkSlateBlue', 'SlateBlue',\
'MediumSlateBlue'],\
'Green':['GreenYellow', 'Chartreuse', 'LawnGreen', 'Lime',\
'LimeGreen', 'PaleGreen', 'LightGreen',\
'MediumSpringGreen', 'SpringGreen', 'MediumSeaGreen',\
'SeaGreen', 'ForestGreen', 'Green', 'DarkGreen',\
'YellowGreen', 'OliveDrab', 'Olive', 'DarkOliveGreen',\
'MediumAquamarine', 'DarkSeaGreen', 'LightSeaGreen',\
'DarkCyan', 'Teal'],\
'Blue/Cyan':['Aqua', 'Cyan', 'LightCyan', 'PaleTurquoise',\
'Aquamarine', 'Turquoise', 'MediumTurquoise',\
'DarkTurquoise', 'CadetBlue', 'SteelBlue',\
'LightSteelBlue', 'PowderBlue', 'LightBlue',\
'SkyBlue', 'LightSkyBlue', 'DeepSkyBlue',\
'DodgerBlue', 'CornflowerBlue', 'RoyalBlue', 'Blue',\
'MediumBlue', 'DarkBlue', 'Navy', 'MidnightBlue'],\
'Brown':['Cornsilk', 'BlanchedAlmond', 'Bisque', 'NavajoWhite',\
'Wheat', 'BurlyWood', 'Tan', 'RosyBrown', 'SandyBrown',\
'Goldenrod', 'DarkGoldenrod', 'Peru', 'Chocolate',\
'SaddleBrown', 'Sienna', 'Brown', 'Maroon'],\
'White':['White', 'Snow', 'Honeydew', 'MintCream', 'Azure',\
'AliceBlue', 'GhostWhite', 'WhiteSmoke', 'Seashell',\
'Beige', 'OldLace', 'FloralWhite', 'Ivory',\
'AntiqueWhite', 'Linen',\
'LavenderBlush', 'MistyRose'],\
'Gray':['Gainsboro', 'LightGrey', 'Silver', 'DarkGray', 'Gray',\
'DimGray', 'LightSlateGray', 'SlateGray', 'DarkSlateGray',\
'Black']\
";
    const std::string cnOrderStr =
      "['Red', 'Pink', 'Orange', 'Yellow', 'Purple', 'Green',\
'Blue/Cyan', 'Brown', 'White', 'Gray']";
    const std::string cnStartTableStr = "['Red', 'Green', 'Brown']";
    const std::string cnEndTableStr = "['Purple', 'Blue/Cyan', 'Gray']";

    const std::string vtkcnStr = "\
'Whites':['antique_white', 'azure', 'bisque', 'blanched_almond',\
'cornsilk', 'eggshell', 'floral_white', 'gainsboro',\
'ghost_white', 'honeydew', 'ivory', 'lavender',\
'lavender_blush', 'lemon_chiffon', 'linen', 'mint_cream',\
'misty_rose', 'moccasin', 'navajo_white', 'old_lace',\
'papaya_whip',  'peach_puff', 'seashell', 'snow',\
'thistle', 'titanium_white', 'wheat', 'white',\
'white_smoke', 'zinc_white'],\
'Greys':['cold_grey', 'dim_grey', 'grey', 'light_grey',\
'slate_grey', 'slate_grey_dark', 'slate_grey_light',\
'warm_grey'],\
'Blacks':['black', 'ivory_black', 'lamp_black'],\
'Reds':['alizarin_crimson', 'brick', 'cadmium_red_deep', 'coral',\
'coral_light', 'deep_pink', 'english_red', 'firebrick',\
'geranium_lake', 'hot_pink', 'indian_red', 'light_salmon',\
'madder_lake_deep', 'maroon', 'pink', 'pink_light',\
'raspberry', 'red', 'rose_madder', 'salmon', 'tomato',\
'venetian_red'],\
'Browns':['beige', 'brown', 'brown_madder', 'brown_ochre',\
'burlywood', 'burnt_sienna', 'burnt_umber', 'chocolate',\
'deep_ochre', 'flesh', 'flesh_ochre', 'gold_ochre',\
'greenish_umber', 'khaki', 'khaki_dark', 'light_beige',\
'peru', 'rosy_brown', 'raw_sienna', 'raw_umber', 'sepia',\
'sienna', 'saddle_brown', 'sandy_brown', 'tan',\
'van_dyke_brown'],\
'Oranges':['cadmium_orange', 'cadmium_red_light', 'carrot',\
'dark_orange', 'mars_orange', 'mars_yellow', 'orange',\
'orange_red', 'yellow_ochre'],\
'Yellows':['aureoline_yellow', 'banana', 'cadmium_lemon',\
'cadmium_yellow', 'cadmium_yellow_light', 'gold',\
'goldenrod', 'goldenrod_dark', 'goldenrod_light',\
'goldenrod_pale', 'light_goldenrod', 'melon',\
'naples_yellow_deep', 'yellow', 'yellow_light'],\
'Greens':['chartreuse', 'chrome_oxide_green', 'cinnabar_green',\
'cobalt_green', 'emerald_green', 'forest_green', 'green',\
'green_dark', 'green_pale', 'green_yellow', 'lawn_green',\
'lime_green', 'mint', 'olive', 'olive_drab',\
'olive_green_dark', 'permanent_green', 'sap_green',\
'sea_green', 'sea_green_dark', 'sea_green_medium',\
'sea_green_light', 'spring_green', 'spring_green_medium',\
'terre_verte', 'viridian_light', 'yellow_green'],\
'Cyans':['aquamarine', 'aquamarine_medium', 'cyan', 'cyan_white',\
'turquoise', 'turquoise_dark', 'turquoise_medium',\
'turquoise_pale'],\
'Blues':['alice_blue', 'blue', 'blue_light', 'blue_medium',\
'cadet', 'cobalt', 'cornflower', 'cerulean', 'dodger_blue',\
'indigo', 'manganese_blue', 'midnight_blue', 'navy',\
'peacock',  'powder_blue', 'royal_blue', 'slate_blue',\
'slate_blue_dark', 'slate_blue_light',\
'slate_blue_medium', 'sky_blue', 'sky_blue_deep',\
'sky_blue_light', 'steel_blue', 'steel_blue_light',\
'turquoise_blue', 'ultramarine'],\
'Magentas':['blue_violet', 'cobalt_violet_deep', 'magenta',\
'orchid', 'orchid_dark', 'orchid_medium',\
'permanent_red_violet', 'plum', 'purple',\
'purple_medium', 'ultramarine_violet', 'violet',\
'violet_dark', 'violet_red', 'violet_red_medium',\
'violet_red_pale']\
";
    const std::string vtkcnOrderStr =
      "['Whites', 'Greys', 'Blacks', 'Reds', 'Oranges',\
'Browns', 'Yellows', 'Greens', 'Cyans', 'Blues',\
'Magentas']";
    const std::string vtkcnStartTableStr = "['Whites', 'Browns', 'Cyans']";
    const std::string vtkcnEndTableStr = "['Oranges', 'Greens', 'Magentas']";

    this->cn = this->ParseDictionary(cnStr);
    this->cnOrder = this->ParseList(cnOrderStr);
    this->cnStartTable = this->ParseList(cnStartTableStr);
    this->cnEndTable = this->ParseList(cnEndTableStr);

    this->vtkcn = this->ParseDictionary(vtkcnStr);
    this->vtkcnOrder = this->ParseList(vtkcnOrderStr);
    this->vtkcnStartTable = this->ParseList(vtkcnStartTableStr);
    this->vtkcnEndTable = this->ParseList(vtkcnEndTableStr);
  }

private:
  //---------------------------------------------------------------------------
  //! Words are delimited by single quotes.
  std::string ParseWords(std::string const& str)
  {
    size_t idx1 = str.find_first_of("'");
    size_t idx2 = str.find_last_of("'");
    if (idx1 != std::string::npos && idx2 != std::string::npos)
    {
      return str.substr(idx1 + 1, idx2 - idx1 - 1);
    }
    return "";
  }

  //---------------------------------------------------------------------------
  //! Convert a list to a vector.
  std::vector<std::string> ParseList(std::string const& str)
  {
    std::vector<std::string> result;
    size_t idx1 = 0;
    size_t idx2 = 0;
    while (idx1 != std::string::npos && idx2 != std::string::npos &&
           idx1 < str.size())
    {
      idx1 = str.find("'", idx1);
      idx2 = str.find("'", idx1 + 1);
      if (idx1 != std::string::npos)
      {
        if (idx2 != std::string::npos)
        {
          result.push_back(str.substr(idx1 + 1, idx2 - idx1 - 1));
        }
        else
        {
          break;
        }
      }
      else
      {
        break;
      }
      idx1 = idx2 + 1;
    }
    return result;
  }

  //---------------------------------------------------------------------------
  //! Convert a dictionary to a map.
  std::map<std::string, std::vector<std::string>> ParseDictionary(
    std::string const& str)
  {
    std::map<std::string, std::vector<std::string>> result;
    size_t idx0 = 0;
    size_t idx1 = 0;
    size_t idx2 = 0;
    std::string key;
    std::vector<std::string> value;
    while (idx1 != std::string::npos && idx2 != std::string::npos)
    {
      idx1 = str.find('[', idx1);
      if (idx1 != std::string::npos)
      {
        idx2 = str.find(']', idx1 + 1);
        key = ParseWords(str.substr(idx0, idx1 - idx0));
        if (idx2 != std::string::npos)
        {
          value = ParseList(str.substr(idx1, idx2 - idx1));
        }
        else
        {
          break;
        }
        idx0 = idx1 = idx2;
      }
      else
      {
        break;
      }
      result[key] = value;
    }
    return result;
  }

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

ColorStructures cs = ColorStructures();
STLHelpers stlHelpers = STLHelpers();
HTMLToFromRGBAColor htmlRGBA = HTMLToFromRGBAColor();
}

/*!
  This class creates HTML Tables displaying all the colors in
  the class vtkNamedColors grouped by various categories.
*/
class HTMLTableMaker
{

public:
  //-----------------------------------------------------------------------------
  HTMLTableMaker() { this->nc = vtkSmartPointer<vtkNamedColors>::New(); }

  //-----------------------------------------------------------------------------
  ~HTMLTableMaker() {}

  //-----------------------------------------------------------------------------
  std::string MakeWebColorPage()
  {
    std::string res = this->MakeHTMLHeader();
    res += "<body>\n";
    res += "<h1>Colors available in vtkNamedColors</h1>\n";
    res += "<table style=\"font-size:90%\" cellpadding=\"4\">\n";
    res +=
      "<caption style=\"background:lightgrey\">Web Color Names</caption>\n";
    res += "<tr valign=\"top\">\n";
    res += this->MakeWebColorTables();
    res += "</table>\n";
    res += "</body>\n";
    return res;
  }

  //-----------------------------------------------------------------------------
  std::string MakeVTKColorPage()
  {
    std::string res = this->MakeHTMLHeader();
    res += "<body>\n";
    res += "<h1>Colors available in vtkNamedColors</h1>\n";
    res += "<p>The web colors take precedence over colors of the same";
    res += " name in VTK Color Names.</p>\n";
    res += "<table style=\"font-size:90%\" cellpadding=\"4\">\n";
    res +=
      "<caption style=\"background:lightgrey\">VTK Color Names</caption>\n";
    res += "<tr valign=\"top\">\n";
    res += this->MakeVTKColorTables();
    res += "</table>\n";
    res += "</body>\n";
    return res;
  }

  //-----------------------------------------------------------------------------
  std::string MakeSynonymColorPage()
  {
    std::string res = this->MakeHTMLHeader();
    res += "<body>\n";
    res += "<h1>Synonyms in vtkNamedColors</h1>\n";
    res += "<table style=\"font-size:90%\" cellpadding=\"4\">\n";
    res += "<caption style=\"background:lightgrey\"></caption>\n";
    res += "<tr valign=\"top\">\n";
    res += this->MakeSynonymColorTable();
    res += "</table>\n";
    res += "</body>\n";
    return res;
  }

  //-----------------------------------------------------------------------------
  std::string MakeCombinedColorPage()
  {
    std::string res = this->MakeHTMLHeader();
    res += "<body>\n";
    res += "<h1>Colors available in vtkNamedColors</h1>\n";
    res += "<p>The class vtkNamedColors provides color names and their";
    res += " values for the convenience of the user.</p>\n";
    res += "<p>The following tables show the available colors along with";
    res += " their red, green and blue values.</p>\n";
    res += this->MakeHTMLIndex();
    res += "<h2><a id=\"WebColorNames\">Web color Names</h2>";
    res += "These colors correspond to those in";
    res += " <a href=\"http://en.wikipedia.org/wiki/Web_colors\"";
    res += " title=\"Web Colors\">Web Colors</a>.\n";
    res += "<table style=\"font-size:90%\" cellpadding=\"4\">\n";
    res += "<tr valign=\"top\">\n";
    res += this->MakeWebColorTables();
    res += "</table>\n";
    res += "<h2><a id=\"VTKColorNames\">VTK color Names</h2>";
    res += "<p>The colors mainly correspond to those in vtkColors.txt.\n</p>\n";
    res += "<p>The web colors (above) take precedence over colors of the";
    res += " same name in vtkColors.txt.</p>\n";
    res += "<table style=\"font-size:90%\" cellpadding=\"4\">\n";
    res += "<tr valign=\"top\">\n";
    res += this->MakeVTKColorTables();
    res += "</table>\n";
    res += "<h2><a id=\"Synonyms\">Synonyms</h2>";
    res += "<table style=\"font-size:90%\" cellpadding=\"4\">\n";
    res += "<tr valign=\"top\">\n";
    res += this->MakeSynonymColorTable();
    res += "</table>\n";
    res += "</body>\n";
    return res;
  }

private:
  //-----------------------------------------------------------------------------
  std::vector<vtkStdString> ParseColorNames(const vtkStdString& colorNames)
  {
    // The delimiter for a color.
    const std::string colorDelimiter = "\n";
    std::vector<vtkStdString> cn;
    size_t start = 0;
    size_t end = colorNames.find(colorDelimiter);
    while (end != std::string::npos)
    {
      cn.push_back(colorNames.substr(start, end - start));
      start = end + 1;
      end = colorNames.find(colorDelimiter, start);
    }
    // Get the last color.
    if (!colorNames.empty())
    {
      cn.push_back(colorNames.substr(start, colorNames.size() - start));
    }
    return cn;
  }

  //-----------------------------------------------------------------------------
  std::vector<std::vector<vtkStdString>> ParseSynonyms(
    const vtkStdString& synonyms)
  {
    // The delimiter for a string of synonyms.
    const vtkStdString synonymDelimiter = "\n\n";
    size_t start = 0;
    size_t end = synonyms.find(synonymDelimiter);
    std::vector<vtkStdString> cn;
    std::vector<std::vector<vtkStdString>> syn;
    vtkStdString str;
    while (end != std::string::npos)
    {
      str = synonyms.substr(start, end - start);
      cn = ParseColorNames(str);
      syn.push_back(cn);
      start = end + 2;
      end = synonyms.find(synonymDelimiter, start);
    }
    // Get the last set of synonyms.
    if (!synonyms.empty())
    {
      str = synonyms.substr(start, end - start);
      cn = ParseColorNames(str);
      syn.push_back(cn);
    }
    return syn;
  }

  //-----------------------------------------------------------------------------
  std::string MakeHTMLHeader()
  {
    std::string s = "<!DOCTYPE html>\n";
    s += "<html lang=\"en\" dir=\"ltr\" class=\"client-nojs\">\n";
    s += "<head>\n";
    s += "<title>vtkNamedColors</title>\n";
    s += "<meta charset=\"UTF-8\" />\n";
    s += "</head>\n";
    return s;
  }

  //-----------------------------------------------------------------------------
  std::string MakeHTMLIndex()
  {
    std::string s = "<h2>Index</h2>\n";
    s += "<ul>\n";
    s += "\t<li><a href=\"#WebColorNames\">Web color Names</li>\n";
    s += "\t<li><a href=\"#VTKColorNames\">VTK color Names</li>\n";
    s += "\t<li><a href=\"#Synonyms\">Synonyms</li>\n";
    s += "</ul>\n";
    return s;
  }

  //-----------------------------------------------------------------------------
  std::string MakeTableHeader()
  {
    std::string s = "<tr>\n";
    s += "<th style=\"background:lightgrey\">HTML name</th>\n";
    s += "<th style=\"background:lightgrey\">Decimal code<br />\n";
    s += "&#160;&#160;R&#160;&#160;&#160;&#160;&#160;&#160;";
    s += "G&#160;&#160;&#160;&#160;&#160;&#160;B</th>\n";
    s += "</tr>\n";
    return s;
  }

  //-----------------------------------------------------------------------------
  std::string MakeSynonymTableHeader()
  {
    std::string s = "<tr>\n";
    s += "<th style=\"background:lightgrey\">Synonyms</th>\n";
    s += "<th style=\"background:lightgrey\">Decimal code<br />\n";
    s += "&#160;&#160;R&#160;&#160;&#160;&#160;&#160;&#160;";
    s += "G&#160;&#160;&#160;&#160;&#160;&#160;B</th>\n";
    s += "</tr>\n";
    return s;
  }

  //-----------------------------------------------------------------------------
  std::string MakeTD(std::string const& name)
  {
    std::string s = "<tr>\n";
    s += "<td colspan=\"2\" style=\"background:whitesmoke;";
    s +=
      "color:slategray;text-align:left\"><big><b>" + name + "</b></big></td>\n";
    s += "</tr>\n";
    return s;
  }

  //-----------------------------------------------------------------------------
  std::string FormatRGBForHTML(vtkColor3ub const& rgb)
  {
    std::string s;
    char buff[9];
    snprintf(buff, sizeof(buff) - 1, "%3d", rgb.GetRed());
    s += buff;
    s += +",";
    snprintf(buff, sizeof(buff) - 1, "%3d", rgb.GetGreen());
    s += buff;
    s += +",";
    snprintf(buff, sizeof(buff) - 1, "%3d", rgb.GetBlue());
    s += buff;
    s = stlHelpers.ReplaceAll(s, " ", "&#160;");
    s = stlHelpers.ReplaceAll(s, ",", "&#160;&#160;");
    return s;
  }

  //-----------------------------------------------------------------------------
  /*!
    Use when the name is a color name known to the web browser.
  */
  std::string MakeTR(const std::string& name, vtkColor3ub const& rgb,
    const std::string& textColor)
  {
    std::string s = "<tr>\n";
    s += "<td style=\"background:" + name + ";color:" + textColor;
    s += "\">" + name + "</td>\n";
    s += "<td style=\"background:" + name + ";color:" + textColor;
    s += "\"><tt>" + this->FormatRGBForHTML(rgb) + "</tt></td>\n";
    s += "</tr>\n";
    return s;
  }

  //-----------------------------------------------------------------------------
  /*!
    Use when the name is not a color name known to the web browser.
   */
  std::string MakeSynonymTR(const std::string& name,
    const std::string& nameColor, vtkColor3ub const& rgb,
    const std::string& textColor)
  {
    std::string s = "<tr>\n";
    s += "<td style=\"background:" + nameColor + ";color:" + textColor;
    s += "\">" + name + "</td>\n";
    s += "<td style=\"background:" + nameColor + ";color:" + textColor;
    s += "\"><tt>" + this->FormatRGBForHTML(rgb) + "</tt></td>\n";
    s += "</tr>\n";
    return s;
  }

  //-----------------------------------------------------------------------------
  std::string MakeWebColorTables()
  {
    std::string res;
    for (std::vector<std::string>::const_iterator p = cs.cnOrder.begin();
         p != cs.cnOrder.end(); ++p)
    {
      if (std::find(cs.cnStartTable.begin(), cs.cnStartTable.end(), *p) !=
          cs.cnStartTable.end())
      {
        res += "<td>\n";
        res += "<table>\n";
        res += this->MakeTableHeader();
      }
      // Add in the name of the group in the color table.
      res += this->MakeTD(*p + " colors");
      std::vector<std::string> values = cs.cn[*p];
      for (std::vector<std::string>::const_iterator q = values.begin();
           q != values.end(); ++q)
      {
        vtkColor3ub rgb = this->nc->GetColor3ub(*q);
        double y = htmlRGBA.RGBToLumaCCIR601(rgb);
        std::string textColor = "#000000"; // Black
        if (y < 255 / 2.0)
        {
          textColor = "#ffffff"; // White
        }
        // Make the row for each color in the group.
        // Here we use the name to set the background color
        //  as it is known to the web browser.
        res += this->MakeTR(*q, rgb, textColor);
      }
      if (std::find(cs.cnEndTable.begin(), cs.cnEndTable.end(), *p) !=
          cs.cnEndTable.end())
      {
        res += "</table>\n";
        res += "</td>\n";
      }
    }
    return res;
  }

  //-----------------------------------------------------------------------------
  std::string MakeVTKColorTables()
  {
    std::string res;

    for (std::vector<std::string>::const_iterator p = cs.vtkcnOrder.begin();
         p != cs.vtkcnOrder.end(); ++p)
    {
      if (std::find(cs.vtkcnStartTable.begin(), cs.vtkcnStartTable.end(), *p) !=
          cs.vtkcnStartTable.end())
      {
        res += "<td>\n";
        res += "<table>\n";
        res += this->MakeTableHeader();
      }
      // Add in the name of the group in the color table.
      res += this->MakeTD(*p);
      std::vector<std::string> values = cs.vtkcn[*p];
      for (std::vector<std::string>::const_iterator q = values.begin();
           q != values.end(); ++q)
      {
        vtkColor3ub rgb = this->nc->GetColor3ub(*q);
        double y = htmlRGBA.RGBToLumaCCIR601(rgb);
        std::string textColor = "#000000"; // Black
        if (y < 255 / 2.0)
        {
          textColor = "#ffffff"; // White
        }
        // We must set the background color to a specific
        // HTML color as the color name may not be a standard
        // name known to the web browser.
        std::string nameColor = htmlRGBA.RGBToHTMLColor(rgb);
        // Make the row for each color in the group.
        res += this->MakeSynonymTR(*q, nameColor, rgb, textColor);
      }
      if (std::find(cs.vtkcnEndTable.begin(), cs.vtkcnEndTable.end(), *p) !=
          cs.vtkcnEndTable.end())
      {
        res += "</table>\n";
        res += "</td>\n";
      }
    }
    return res;
  }

  //-----------------------------------------------------------------------------
  std::string MakeSynonymColorTable()
  {
    std::vector<std::vector<vtkStdString>> synonyms =
      this->ParseSynonyms(this->nc->GetSynonyms());
    std::vector<std::string> cn;
    for (std::map<std::string, std::vector<std::string>>::const_iterator p =
           cs.cn.begin();
         p != cs.cn.end(); ++p)
    {
      for (std::vector<std::string>::const_iterator q = p->second.begin();
           q != p->second.end(); ++q)
      {
        cn.push_back(*q);
      }
    }
    std::map<std::string, std::string> d;
    for (std::vector<std::string>::const_iterator p = cn.begin(); p != cn.end();
         ++p)
    {
      d[stlHelpers.ToLowercase(*p)] = *p;
    }
    std::string res;
    res += "<td>\n";
    res += "<table>\n";
    res += this->MakeSynonymTableHeader();
    for (std::vector<std::vector<vtkStdString>>::iterator p = synonyms.begin();
         p != synonyms.end(); ++p)
    {
      for (std::vector<vtkStdString>::iterator q = p->begin(); q != p->end();
           ++q)
      {
        // Replace the lowercase name with the proper name.
        if (d.find(*q) != d.end())
        {
          *q = d[*q];
        }
      }
      std::sort(p->begin(), p->end());
      std::string names;
      for (std::vector<vtkStdString>::iterator q = p->begin(); q != p->end();
           ++q)
      {
        names += *q;
        if (!stlHelpers.IsLast(q, *p))
        {
          names += ", ";
        }
      }
      vtkColor3ub rgb = this->nc->GetColor3ub(*(p->begin()));
      double y = htmlRGBA.RGBToLumaCCIR601(rgb);
      std::string textColor = "#000000"; // Black
      if (y < 255 / 2.0)
      {
        textColor = "#ffffff"; // White
      }
      // We must set the background color to a specific
      // HTML color because names is just a list of
      // synonyms for that particular color.
      std::string nameColor = htmlRGBA.RGBToHTMLColor(rgb);
      // Make the row for each color in the group.
      res += this->MakeSynonymTR(names, nameColor, rgb, textColor);
    }
    res += "</table>\n";
    res += "</td>\n";
    return res;
  }

private:
  vtkSmartPointer<vtkNamedColors> nc;
};

int main(int, char* [])
{
  HTMLTableMaker ncp;

  std::ofstream outputFile;
  outputFile.open(
    "VTKNamedColorPatches.html", ios::out | ios::trunc | ios::binary);
  outputFile << ncp.MakeCombinedColorPage();
  outputFile.close();

  return EXIT_SUCCESS;
}
