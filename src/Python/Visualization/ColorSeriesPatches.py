#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Produce a HTML page called VTKColorSeriesPatches.html showing the available
 color series in vtkColorSeries.

It also shows how to select the text color based on luminance.
In this case Digital CCIR601 is used which gives less weight to the
 red and blue components of a color.

"""

from __future__ import print_function

import vtk


def main():
    ncpt = HTMLTableMaker()
    res = ncpt.MakeHTMLTable()
    f = open("VTKColorSeriesPatches.html", "w", newline="\n")
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


class ColorStructures:
    """
    Holds the color series id, name and colors.
    """

    cs_colors = dict()
    max_colors = 0

    def __init__(self):
        cs = vtk.vtkColorSeries()
        sizes = list()
        for i in range(0, cs.GetNumberOfColorSchemes()):
            cs.SetColorScheme(i)
            sizes.append(cs.GetNumberOfColors())
            vc = list()
            for j in range(0, cs.GetNumberOfColors()):
                vc.append(cs.GetColor(j))
            self.cs_colors[i] = [cs.GetColorSchemeName(), vc]
        self.max_colors = max(sizes)


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
        s += '\n'
        s += '  body {\n'
        s += '    background-color: snow\n'
        s += '  }\n'
        s += '  h1 {text-align:left;}\n'
        s += '  h2 {text-align:left;}\n'
        s += '  h3 {text-align:left;}\n'
        s += '  h4 {text-align:left;}\n'
        s += '  h5 {text-align:left;}\n'
        s += '  h6 {text-align:left;}\n'
        s += '\n'
        s += '  p {text-align:left;}\n'
        s += '\n'
        s += '  table {\n'
        s += '    font-family: arial, sans-serif;\n'
        s += '    border-collapse: collapse;\n'
        s += '    font-size: medium;\n'
        s += '    padding: 4px;\n'
        s += '  }\n'
        s += '\n'
        s += '  th {\n'
        s += '    background: LightSteelBlue;\n'
        s += '    font-size: medium;\n'
        s += '  }\n'
        s += '\n'
        s += '  th[colspan]:not([colspan="1"]) {\n'
        s += '    background: LightSteelBlue;\n'
        s += '    font-size: medium;\n'
        s += '    text-align : center;\n'
        s += '    vertical-align : top;\n'
        s += '  }\n'
        s += '\n'
        s += '  tr {\n'
        s += '    background: MintCream;\n'
        s += '    vertical-align : top;\n'
        s += '  }\n'
        s += '\n'
        s += '  td {\n'
        s += '    background: MintCream;\n'
        s += '    border: 1px solid #dddddd;\n'
        s += '    text-align: left;\n'
        s += '    padding: 8px;\n'
        s += '    font-family: monospace;\n'
        s += '    font-size: medium;\n'
        s += '    font-weight: bold;\n'
        s += '  }\n'
        s += '\n'
        s += '  td[colspan]:not([colspan="1"]) {\n'
        s += '    text-align : center;\n'
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

    def MakeHTMLHeader(self):
        s = '<!DOCTYPE html>\n'
        s += '<html lang="en">\n'
        s += '<head>\n'
        s += '<meta charset="UTF-8" />\n'
        s += '<title>vtkColorSeries</title>\n'
        s += self.MakeHTMLStyle()
        s += '</head>\n'
        return s

    def MakeTableHeader(self):
        s = '<tr>\n'
        s += '<th>Index</th>\n'
        s += '<th colspan="' + str(self.cs.max_colors) + '">Name</th>\n'
        s += '</tr>\n'
        s += '<tr>\n'
        s += '<th></th>\n'
        s += '<th colspan="' + str(self.cs.max_colors) + '">Colors in the Series</th>\n'
        s += '</tr>\n'
        return s

    def MakeTD1(self, idx, name):
        s = '<tr>\n'
        s += '<td>'
        s += '<b>' + str(idx) + '</b>'
        s += '</td>\n'
        s += '<td colspan="' + str(self.cs.max_colors) + '">'
        s += '<b>' + name + '</b>'
        s += '</td>\n'
        s += '</tr>\n'
        return s

    def MakeTD2(self, rgbs):
        s = '<tr>\n'
        s += '<td></td>\n'

        cnt = 0
        for p in rgbs:
            ss = '{:3d}  '.format(cnt)
            ss = ss.replace(' ', '&#160;')
            y = self.htmlRGBA.RGBToLumaCCIR601(p)
            textColor = '#000000'  # Black
            if y < 255 / 2.0:
                textColor = '#ffffff'  # White
            s += '<td style="background:' + self.htmlRGBA.RGBToHTMLColor(p) + ';color:'
            s += textColor + '">' + ss + '</td>\n'
            cnt += 1
        if cnt < self.cs.max_colors:
            s += '<td colspan="' + str(self.cs.max_colors - cnt) + '"> &#160; </td>\n'
        s += '</tr>\n'
        return s

    def MakeTable(self):
        res = self.MakeTableHeader()
        for idx, v in self.cs.cs_colors.items():
            name = v[0]
            res += self.MakeTD1(idx, name)
            res += self.MakeTD2(v[1])

        return res

    def MakeHTMLTable(self):

        res = self.MakeHTMLHeader()
        res += '<body>\n'
        res += '<h1>Color series available in vtkColorSeries</h1>\n'
        res += '<table>\n'
        res += self.MakeTable()
        res += '</table>\n'
        res += '</body>\n'
        return res


if __name__ == "__main__":
    main()
