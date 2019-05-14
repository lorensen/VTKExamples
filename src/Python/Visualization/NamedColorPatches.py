#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Produce a HTML page called VTKNamedColorPatches.html showing the available
 colors in vtkNamedColors.

It also shows how to select the text color based on luminance.
In this case Digital CCIR601 is used which gives less weight to the
 red and blue components of a color.

"""

from __future__ import print_function

import vtk


def main():
    ncp = HTMLTableMaker()
    res = ncp.MakeCombinedColorPage()
    # res = ncp.MakeWebColorPage()
    # res = ncp.MakeVTKColorPage()
    # res = ncp.MakeSynonymColorPage()
    f = open("VTKNamedColorPatches.html", "w", newline="\n")
    f.write(res)
    f.close()


class HTMLToFromRGBAColor:

    @staticmethod
    def RGBToHTMLColor(rgb):
        """
        Convert an [R, G, B] list to #RRGGBB.
        :param: rgb - The elements of the array rgb are unsigned chars (0..255).
        :return: The html color.
        """
        hexcolor = "#" + ''.join(['{:02x}'.format(x) for x in rgb])
        return hexcolor

    @staticmethod
    def HTMLColorToRGB(colorString):
        """
        Convert #RRGGBB to a [R, G, B] list.
        :param: colorString a string in the form: #RRGGBB where RR, GG, BB are hexadecimal.
        The elements of the array rgb are unsigned chars (0..255).
        :return: The red, green and blue components as a list.
        """
        colorString = colorString.strip()
        if colorString[0] == '#':
            colorString = colorString[1:]
        if len(colorString) != 6:
            raise ValueError("Input #%s is not in #RRGGBB format" % colorString)
        r, g, b = colorString[:2], colorString[2:4], colorString[4:]
        r, g, b = [int(n, 16) for n in (r, g, b)]
        return [r, g, b]

    @staticmethod
    def RGBToLumaCCIR601(rgb):
        """
        RGB -> Luma conversion
        Digital CCIR601 (gives less weight to the R and B components)
        :param: rgb - The elements of the array rgb are unsigned chars (0..255).
        :return: The luminance.
        """
        Y = 0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2]
        return Y

    @staticmethod
    def FormatRGBForHTML(rgb):
        """
        Format the rgb colors for display on a html table.
        :param: rgb - The elements of the array rgb are unsigned chars (0..255).
        :return: A formatted string for the html table.
        """
        s = ','.join(['{:3d}'.format(x) for x in rgb])
        s = s.replace(' ', '&#160;')
        s = s.replace(',', '&#160;&#160;')
        return s


class ColorStructures:
    """
    Holds the color names, grouped by color class, and information about table
    layout and ordering.
    """

    def __init__(self):
        self.cn = {
            'Red': ['IndianRed', 'LightCoral', 'Salmon', 'DarkSalmon',
                    'LightSalmon', 'Red', 'Crimson', 'FireBrick', 'DarkRed'],
            'Pink': ['Pink', 'LightPink', 'HotPink', 'DeepPink',
                     'MediumVioletRed', 'PaleVioletRed'],
            'Orange': ['LightSalmon', 'Coral', 'Tomato', 'OrangeRed',
                       'DarkOrange', 'Orange'],
            'Yellow': ['Gold', 'Yellow', 'LightYellow', 'LemonChiffon',
                       'LightGoldenrodYellow', 'PapayaWhip', 'Moccasin',
                       'PeachPuff', 'PaleGoldenrod', 'Khaki', 'DarkKhaki'],
            'Purple': ['Lavender', 'Thistle', 'Plum', 'Violet', 'Orchid',
                       'Fuchsia', 'Magenta', 'MediumOrchid', 'MediumPurple',
                       'BlueViolet', 'DarkViolet', 'DarkOrchid', 'DarkMagenta',
                       'Purple', 'Indigo', 'DarkSlateBlue', 'SlateBlue',
                       'MediumSlateBlue'],
            'Green': ['GreenYellow', 'Chartreuse', 'LawnGreen', 'Lime',
                      'LimeGreen', 'PaleGreen', 'LightGreen',
                      'MediumSpringGreen', 'SpringGreen', 'MediumSeaGreen',
                      'SeaGreen', 'ForestGreen', 'Green', 'DarkGreen',
                      'YellowGreen', 'OliveDrab', 'Olive', 'DarkOliveGreen',
                      'MediumAquamarine', 'DarkSeaGreen', 'LightSeaGreen',
                      'DarkCyan', 'Teal'],
            'Blue/Cyan': ['Aqua', 'Cyan', 'LightCyan', 'PaleTurquoise',
                          'Aquamarine', 'Turquoise', 'MediumTurquoise',
                          'DarkTurquoise', 'CadetBlue', 'SteelBlue',
                          'LightSteelBlue', 'PowderBlue', 'LightBlue',
                          'SkyBlue', 'LightSkyBlue', 'DeepSkyBlue',
                          'DodgerBlue', 'CornflowerBlue', 'RoyalBlue', 'Blue',
                          'MediumBlue', 'DarkBlue', 'Navy', 'MidnightBlue'],
            'Brown': ['Cornsilk', 'BlanchedAlmond', 'Bisque', 'NavajoWhite',
                      'Wheat', 'BurlyWood', 'Tan', 'RosyBrown', 'SandyBrown',
                      'Goldenrod', 'DarkGoldenrod', 'Peru', 'Chocolate',
                      'SaddleBrown', 'Sienna', 'Brown', 'Maroon'],
            'White': ['White', 'Snow', 'Honeydew', 'MintCream', 'Azure',
                      'AliceBlue', 'GhostWhite', 'WhiteSmoke', 'Seashell',
                      'Beige', 'OldLace', 'FloralWhite', 'Ivory',
                      'AntiqueWhite', 'Linen',
                      'LavenderBlush', 'MistyRose'],
            'Gray': ['Gainsboro', 'LightGrey', 'Silver', 'DarkGray', 'Gray',
                     'DimGray', 'LightSlateGray', 'SlateGray', 'DarkSlateGray',
                     'Black']
        }
        # Ordering of the tables and when to start and end a column of tables
        # in the layout.
        self.cnOrder = ['Red', 'Pink', 'Orange', 'Yellow', 'Purple', 'Green',
                        'Blue/Cyan', 'Brown', 'White', 'Gray']
        self.cnStartTable = ['Red', 'Green', 'Brown']
        self.cnEndTable = ['Purple', 'Blue/Cyan', 'Gray']

        self.vtkcn = {
            'Whites': ['antique_white', 'azure', 'bisque', 'blanched_almond',
                       'cornsilk', 'eggshell', 'floral_white', 'gainsboro',
                       'ghost_white', 'honeydew', 'ivory', 'lavender',
                       'lavender_blush', 'lemon_chiffon', 'linen', 'mint_cream',
                       'misty_rose', 'moccasin', 'navajo_white', 'old_lace',
                       'papaya_whip', 'peach_puff', 'seashell', 'snow',
                       'thistle', 'titanium_white', 'wheat', 'white',
                       'white_smoke', 'zinc_white'],
            'Greys': ['cold_grey', 'dim_grey', 'grey', 'light_grey',
                      'slate_grey', 'slate_grey_dark', 'slate_grey_light',
                      'warm_grey'],
            'Blacks': ['black', 'ivory_black', 'lamp_black'],
            'Reds': ['alizarin_crimson', 'brick', 'cadmium_red_deep', 'coral',
                     'coral_light', 'deep_pink', 'english_red', 'firebrick',
                     'geranium_lake', 'hot_pink', 'indian_red', 'light_salmon',
                     'madder_lake_deep', 'maroon', 'pink', 'pink_light',
                     'raspberry', 'red', 'rose_madder', 'salmon', 'tomato',
                     'venetian_red'],
            'Browns': ['beige', 'brown', 'brown_madder', 'brown_ochre',
                       'burlywood', 'burnt_sienna', 'burnt_umber', 'chocolate',
                       'deep_ochre', 'flesh', 'flesh_ochre', 'gold_ochre',
                       'greenish_umber', 'khaki', 'khaki_dark', 'light_beige',
                       'peru', 'rosy_brown', 'raw_sienna', 'raw_umber', 'sepia',
                       'sienna', 'saddle_brown', 'sandy_brown', 'tan',
                       'van_dyke_brown'],
            'Oranges': ['cadmium_orange', 'cadmium_red_light', 'carrot',
                        'dark_orange', 'mars_orange', 'mars_yellow', 'orange',
                        'orange_red', 'yellow_ochre'],
            'Yellows': ['aureoline_yellow', 'banana', 'cadmium_lemon',
                        'cadmium_yellow', 'cadmium_yellow_light', 'gold',
                        'goldenrod', 'goldenrod_dark', 'goldenrod_light',
                        'goldenrod_pale', 'light_goldenrod', 'melon',
                        'naples_yellow_deep', 'yellow', 'yellow_light'],
            'Greens': ['chartreuse', 'chrome_oxide_green', 'cinnabar_green',
                       'cobalt_green', 'emerald_green', 'forest_green', 'green',
                       'green_dark', 'green_pale', 'green_yellow', 'lawn_green',
                       'lime_green', 'mint', 'olive', 'olive_drab',
                       'olive_green_dark', 'permanent_green', 'sap_green',
                       'sea_green', 'sea_green_dark', 'sea_green_medium',
                       'sea_green_light', 'spring_green', 'spring_green_medium',
                       'terre_verte', 'viridian_light', 'yellow_green'],
            'Cyans': ['aquamarine', 'aquamarine_medium', 'cyan', 'cyan_white',
                      'turquoise', 'turquoise_dark', 'turquoise_medium',
                      'turquoise_pale'],
            'Blues': ['alice_blue', 'blue', 'blue_light', 'blue_medium',
                      'cadet', 'cobalt', 'cornflower', 'cerulean', 'dodger_blue',
                      'indigo', 'manganese_blue', 'midnight_blue', 'navy',
                      'peacock', 'powder_blue', 'royal_blue', 'slate_blue',
                      'slate_blue_dark', 'slate_blue_light',
                      'slate_blue_medium', 'sky_blue', 'sky_blue_deep',
                      'sky_blue_light', 'steel_blue', 'steel_blue_light',
                      'turquoise_blue', 'ultramarine'],
            'Magentas': ['blue_violet', 'cobalt_violet_deep', 'magenta',
                         'orchid', 'orchid_dark', 'orchid_medium',
                         'permanent_red_violet', 'plum', 'purple',
                         'purple_medium', 'ultramarine_violet', 'violet',
                         'violet_dark', 'violet_red', 'violet_red_medium',
                         'violet_red_pale']
        }
        # Ordering of the tables and when to start and end a column of tables
        # in the layout.
        self.vtkcnOrder = ['Whites', 'Greys', 'Blacks', 'Reds', 'Oranges', 'Browns', 'Yellows', 'Greens', 'Cyans',
                           'Blues',
                           'Magentas']
        self.vtkcnStartTable = ['Whites', 'Browns', 'Cyans']
        self.vtkcnEndTable = ['Oranges', 'Greens', 'Magentas']


class HTMLTableMaker:
    """
      This class creates HTML Tables displaying all the colors in
      the class vtkNamedColors grouped by various categories.
    """

    def __init__(self):
        self.cs = ColorStructures()
        self.nc = vtk.vtkNamedColors()
        self.htmlRGBA = HTMLToFromRGBAColor()

    @staticmethod
    def MakeHTMLStyle():
        s = '  <style>\n'
        s += '  \n'
        s += '  body {\n'
        s += '    background-color: snow\n'
        s += '  }\n'
        s += '  h1 {text-align:left;}\n'
        s += '  h2 {text-align:left;}\n'
        s += '  h3 {text-align:left;}\n'
        s += '  h4 {text-align:left;}\n'
        s += '  h5 {text-align:left;}\n'
        s += '  h6 {text-align:left;}\n'
        s += '  \n'
        s += '  p {text-align:left;}\n'
        s += '  \n'
        s += '  table {\n'
        s += '    font-family: arial, sans-serif;\n'
        s += '    border-collapse: collapse;\n'
        s += '    font-size: medium;\n'
        s += '    padding: 4px;\n'
        s += '  }\n'
        s += '\n'
        s += '  th[colspan]:not([colspan="1"]) {\n'
        s += '    background: LightSteelBlue;\n'
        s += '    font-size: x-large;\n'
        s += '    text-align : center;'
        s += '    vertical-align : top;\n'
        s += '  }\n'
        s += '  th {\n'
        s += '    background: LightSteelBlue;\n'
        s += '  }\n'
        s += '  td, th {\n'
        s += '    border: 1px solid #dddddd;\n'
        s += '    text-align: left;\n'
        s += '    padding: 8px;\n'
        s += '    font-family: monospace;\n'
        s += '    font-size: medium;\n'
        s += '    font-weight: bold;\n'
        s += '  }\n'
        s += '\n'
        s += '  tr {\n'
        s += '    background: WhiteSmoke;\n'
        s += '    vertical-align : top;\n'
        s += '  }\n'
        s += '\n'
        s += '  td[colspan]:not([colspan="1"]) {\n'
        s += '    background: MintCream;\n'
        s += '    font-size: large;\n'
        s += '    text-align : center;'
        s += '    vertical-align : top;\n'
        s += '  }\n'
        s += '  td {\n'
        s += '    background: WhiteSmoke;\n'
        s += '  }\n'
        s += '\n'
        s += '  .cour {\n'
        s += '    font-family: Courier;\n'
        s += '  }\n'
        s += '\n'
        s += '  html, body {\n'
        s += '    height: 100%;\n'
        s += '  }\n'
        s += '\n'
        s += '  html {\n'
        s += '    display: table;\n'
        s += '    margin: auto;\n'
        s += '  }\n'
        s += '\n'
        s += '  body {\n'
        s += '    display: table-cell;\n'
        s += '    vertical-align: middle;\n'
        s += '  }\n'
        s += '\n'
        s += '  thead {color: DarkGreen;}\n'
        s += '  tbody {color: MidnightBlue;}\n'
        s += '  tfoot {color: SaddleBrown;}\n'
        s += '\n'
        s += '  </style>\n'
        return s

    @staticmethod
    def MakeHTMLHeader():
        s = '<!DOCTYPE html>\n'
        s += '<html lang="en">\n'
        s += '<head>\n'
        s += '<meta charset="UTF-8" />\n'
        s += '<title>vtkNamedColors</title>\n'
        s += HTMLTableMaker.MakeHTMLStyle()
        s += '</head>\n'
        return s

    @staticmethod
    def MakeHTMLIndex():
        s = '<h2>Index</h2>\n'
        s += '<ul>\n'
        s += '\t<li><a href="#WebColorNames">Web color Names</a>'
        s += ' These colors correspond to those in'
        s += ' <a href="http://en.wikipedia.org/wiki/Web_colors"'
        s += ' title="Web Colors">Web Colors</a>.\n'
        s += '</li>\n'
        s += '\t<li><a href="#VTKColorNames">VTK color Names</a>\n'
        s += ' The colors correspond to additional colors commonly used in VTK.\n'
        s += '<br>The web colors take precedence over colors with\n'
        s += ' the same name (case insensitive) here.\n'
        s += '</li>\n'
        s += '\t<li><a href="#Synonyms">Synonyms</a></li>\n'
        s += '</ul>\n'
        return s

    @staticmethod
    def MakeTableHeader(title):
        s = '<tr>\n'
        s += '<th>'
        s += title
        s += '</th>\n'
        s += '<th>Decimal code<br>\n'
        s += '&#160;&#160;R'
        s += '&#160;&#160;&#160;&#160;G'
        s += '&#160;&#160;&#160;&#160;B</th>\n'
        s += '</tr>\n'
        return s

    @staticmethod
    def MakeTD(name):
        s = '<tr>\n'
        s += '<td colspan="2">'
        s += '<b>' + name + '</b>'
        s += '</td>\n'
        s += '</tr>\n'
        return s

    def MakeTR(self, name, rgb, textColor):
        """
          Use when the name is a color name known to the web browser.
        """
        s = '<tr>\n'
        s += '<td style="background:' + name + ';color:' + textColor
        s += '">' + name + '</td>\n'
        s += '<td style="background:' + name + ';color:' + textColor
        s += '">' + self.htmlRGBA.FormatRGBForHTML(rgb) + '</td>\n'
        s += '</tr>\n'
        return s

    def MakeTR_HTML(self, name, htmlColor, rgb, textColor):
        """
          Use when the name is not a color name known to the web browser.
        """
        s = '<tr>\n'
        s += '<td style="background:' + htmlColor + ';color:'
        s += textColor + '">' + name + '</td>\n'
        s += '<td style="background:' + htmlColor + ';color:'
        s += textColor + '">' + self.htmlRGBA.FormatRGBForHTML(rgb) + '</td>\n'
        s += '</tr>\n'
        return s

    def FindLongestColorName(self):
        """ Find the longest color name. """
        maxLength = -1
        for key, value in self.cs.cn.items():
            for val in value:
                if len(val) > maxLength:
                    maxLength = len(val)
        for key, value in self.cs.vtkcn.items():
            for val in value:
                if len(val) > maxLength:
                    maxLength = len(val)
        return maxLength

    def MakeWebColorTables(self):
        res = ''
        for key in self.cs.cnOrder:
            if key in self.cs.cnStartTable:
                res += '<td>\n'
                res += '<table>\n'
                res += self.MakeTableHeader('HTML name')
            # Add in the name of the group in the color table.
            res += self.MakeTD(key + ' colors')
            values = self.cs.cn[key]
            for name in values:
                rgb = self.nc.GetColor3ub(name)
                Y = self.htmlRGBA.RGBToLumaCCIR601(rgb)
                textColor = '#000000'  # Black
                if Y < 255 / 2.0:
                    textColor = '#ffffff'  # White
                # Make the row for each color in the group.
                # Here we use the name to set the background color
                #  as it is known to the web browser.
                res += self.MakeTR(name, rgb, textColor)
            if key in self.cs.cnEndTable:
                res += '</table>\n'
                res += '</td>\n'
        return res

    def MakeVTKColorTables(self):
        res = ''
        for key in self.cs.vtkcnOrder:
            if key in self.cs.vtkcnStartTable:
                res += '<td>\n'
                res += '<table>\n'
                res += self.MakeTableHeader('HTML name')
            # Add in the name of the group in the color table.
            res += self.MakeTD(key)
            values = self.cs.vtkcn[key]
            for name in values:
                rgb = self.nc.GetColor3ub(name)
                Y = self.htmlRGBA.RGBToLumaCCIR601(rgb)
                textColor = '#000000'  # Black
                if Y < 255 / 2.0:
                    textColor = '#ffffff'  # White
                # We must set the background color to a specific
                # HTML color as the color name may not be a standard
                # name known to the web browser.
                htmlColor = self.htmlRGBA.RGBToHTMLColor(rgb)
                # Make the row for each color in the group.
                res += self.MakeTR_HTML(name, htmlColor, rgb, textColor)
            if key in self.cs.vtkcnEndTable:
                res += '</table>\n'
                res += '</td>\n'
        return res

    def MakeSynonymColorTable(self):
        syn = self.nc.GetSynonyms()
        # Convert to a list where each element is a list of the
        #  color and its synonyms.
        syn = syn.split('\n\n')
        synonyms = []
        for ele in syn:
            synonyms.append(ele.split('\n'))
        cn = list()
        for key, value in self.cs.cn.items():
            cn = cn + value
        # Create a dictionary where the key is the lowercase name.
        d = dict()
        for n in cn:
            d.update({n.lower(): n})
        #  End point of first table.
        end1 = len(synonyms) // 2
        if end1 * 2 < len(synonyms):
            end1 += 1
        res = '<td>\n'
        res += '<table>\n'
        res += self.MakeTableHeader('Synonyms')
        count = 0
        for colorNames in synonyms:
            if count == end1:
                res += '</table>\n'
                res += '</td>\n'
                res += '<td>\n'
                res += '<table>\n'
                res += self.MakeTableHeader('Synonyms')
            for idx, name in enumerate(colorNames):
                if name in d:
                    colorNames[idx] = d[name]
            colorNames.sort()
            name = ", ".join(colorNames)
            rgb = self.nc.GetColor3ub(colorNames[0])
            Y = self.htmlRGBA.RGBToLumaCCIR601(rgb)
            textColor = '#000000'  # Black
            if Y < 255 / 2.0:
                textColor = '#ffffff'  # White
            # We must set the background color to a specific
            # HTML color  names is just a list of
            # synonyms for that particular color.
            htmlColor = self.htmlRGBA.RGBToHTMLColor(rgb)
            # Make the row for each color in the group.
            res += self.MakeTR_HTML(name, htmlColor, rgb, textColor)
            count += 1
        res += '</table>\n'
        res += '</td>\n'
        return res

    def MakeWebColorPage(self):
        res = self.MakeHTMLHeader()
        res += '<body>\n'
        res += '<h1>Colors available in vtkNamedColors</h1>\n'
        res += '<table>\n'
        res += '<tr>\n'
        res += '<th colspan="3">Web Color Names</th>\n'
        res += '</tr>\n'
        res += '<tr>\n'
        res += self.MakeWebColorTables()
        res += '</tr>\n'
        res += '</table>\n'
        res += '</body>\n'
        return res

    def MakeVTKColorPage(self):
        res = self.MakeHTMLHeader()
        res += '<body>\n'
        res += '<h1>Colors available in vtkNamedColors</h1>\n'
        res += 'The web colors take precedence over colors of the same'
        res += ' name in VTK Color Names.\n'
        res += '<table>\n'
        res += '<tr>\n'
        res += '<th colspan="3">VTK Color Names</th>\n'
        res += '</tr>\n'
        res += '<tr>\n'
        res += self.MakeVTKColorTables()
        res += '</tr>\n'
        res += '</table>\n'
        res += '</body>\n'
        return res

    def MakeSynonymColorPage(self):
        res = self.MakeHTMLHeader()
        res += '<body>\n'
        res += '<h1>Synonyms in vtkNamedColors</h1>\n'
        res += '<table>\n'
        res += '<tr>\n'
        res += '<th colspan="2">Synonyms</th>\n'
        res += '</tr>\n'
        res += '<tr>\n'
        res += self.MakeSynonymColorTable()
        res += '</tr>\n'
        res += '</table>\n'
        res += '</body>\n'
        return res

    def MakeCombinedColorPage(self):
        res = self.MakeHTMLHeader()
        res += '<body>\n'
        res += '<h1>Colors available in vtkNamedColors</h1>\n'
        res += 'The class vtkNamedColors provides color names and their'
        res += ' values for the convenience of the user.\n'
        res += '<br>The following tables show the available colors along with'
        res += ' their red, green and blue values.\n'
        res += self.MakeHTMLIndex()
        res += '<table>\n'
        res += '<tr>\n'
        res += '<th colspan="3"><a id="WebColorNames">Web color Names</a></th>\n'
        res += '</tr>\n'
        res += '<tr>\n'
        res += self.MakeWebColorTables()
        res += '</tr>\n'
        res += '</table>\n'
        res += '<br>\n'

        res += '<table>\n'
        res += '<tr>\n'
        res += '<th colspan="3"><a id="VTKColorNames">VTK color Names</a></th>\n'
        res += '</tr>\n'
        res += '<tr>\n'
        res += self.MakeVTKColorTables()
        res += '</tr>\n'
        res += '</table>\n'
        res += '<br>\n'

        res += '<table>\n'
        res += '<tr>\n'
        res += '<th colspan="2"><a id="Synonyms">Synonyms</a></th>\n'
        res += '</tr>\n'
        res += '<tr>\n'
        res += self.MakeSynonymColorTable()
        res += '</tr>\n'
        res += '</table>\n'
        res += '</body>\n'
        return res


if __name__ == "__main__":
    main()
