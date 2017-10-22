#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function
import sys
import vtk


class LUTUtilities(object):
    '''
    Utilities for displaying and comparing lookup tables.
    '''

    def __init__(self):
        pass

    def DisplayLUTAsString(self, lut):
        '''
        Display the contents of the lookup table.
        :param: lut - the lookup table.
        :return: a string containing the table data.
        '''
        str = ''
        tv = lut.GetNumberOfTableValues()
        dR = lut.GetTableRange()
        if lut.GetIndexedLookup():
            av = lut.GetNumberOfAnnotatedValues()
            str = "Categorical Lookup Table\n" +\
                "Number of annotated values: {:d}".format(av) +\
                " Number of table values: {:d}".format(tv) +\
                "\nTable Range: {:8.6f} to {:8.6f}\n".format(dR[0], dR[1])
            if av > 0:
                for i in range(av):
                    rgba = [0.0, 0.0, 0.0, 0.0]
                    lut.GetAnnotationColor(lut.GetAnnotatedValue(i), rgba)
                    str += "{:>5}: ".format(lut.GetAnnotation(i))
                    str += self.AssembleRGBAString(rgba)
            else:
                for i in range(tv):
                    rgba = [0.0, 0.0, 0.0, 0.0]
                    rgba = lut.GetTableValue(i)
                    str += "{:5d}: ".format(i)
                    str += self.AssembleRGBAString(rgba)
        else:
            str = "Ordinal Lookup Table\n" +\
                " Number of table values: {:d}".format(tv) +\
                "\nTable Range: {:8.6f} to {:8.6f}\n".format(dR[0], dR[1])
            indices = [(dR[1] - dR[0]) *
                       float(x) / tv + dR[0] for x in range(0, tv)]
            for i, v in enumerate(indices):
                rgb = [0.0, 0.0, 0.0]
                lut.GetColor(v, rgb)
                rgba = rgb + [lut.GetOpacity(v)]
                str += "{:5.2f}: ".format(v)
                str += self.AssembleRGBAString(rgba)
        return str

    def AssembleRGBAString(self, rgba):
        '''
        Display the contents of the rgba as a series of strings:
        decimal [r g b a], integer [r g b a] where r,g ,b a are
        in the range 0..255 and 0xrrggba .
        :param: The rgba string.
        :return: A string in the above format.
        '''
        s = '[' + ', '.join(['{:0.6f}'.format(x) for x in rgba]) + ']'
        ucrgb = [int(x * 255) for x in rgba]
        t = '[' + ', '.join(['{:3d}'.format(x) for x in ucrgb]) + ']'
        # u = '0x'+''.join(map(lambda x: '{:02X}'.format(x),ucrgb[:3]))
        u = '0x' + ''.join(['{:02x}'.format(x) for x in ucrgb])
        res = '{:s} {:s} {:s}\n'.format(s, t, u)
        return res

    def CompareLUTs(self, lut1, lut2):
        '''
        Compare two lookup tables.
        :param: lut1 - the lookup table.
        :param: lut2 - the lookup table.
        :return: True if the tables are the same.
        '''
        res = [True, '']
        if lut1.GetIndexedLookup() != lut2.GetIndexedLookup():
            res[0] = False
            res[1] = "One table is ordinal and the other is categorical."
            return res
        if lut1.GetIndexedLookup() and\
                lut1.GetNumberOfAnnotatedValues() !=\
                lut2.GetNumberOfAnnotatedValues():
            res[0] = False
            res[1] = "The number of annotated values do not match."
            return res
        if lut1.GetNumberOfTableValues() != lut2.GetNumberOfTableValues():
            res[0] = False
            res[1] = "Table values do not match."
            return res
        dR1 = lut1.GetTableRange()
        dR2 = lut2.GetTableRange()
        if dR1[0] != dR2[0] and dR1[1] != dR2[1]:
            res[0] = False
            res[1] = "Table ranges do not match."
            return res
        if lut1.GetIndexedLookup():
            av = lut1.GetNumberOfAnnotatedValues()
            if av > 0:
                for i in range(av):
                    if lut1.GetAnnotation(i) != lut1.GetAnnotation(i):
                        res[0] = False
                        res[1] = "Annotations do not match."
                        return res
                for i in range(av):
                    rgba1 = [0.0, 0.0, 0.0, 0.0]
                    lut1.GetAnnotationColor(lut1.GetAnnotatedValue(i), rgba1)
                    rgba2 = [0.0, 0.0, 0.0, 0.0]
                    lut2.GetAnnotationColor(lut2.GetAnnotatedValue(i), rgba2)
                    if not self.CompareRGBA(rgba1, rgba2):
                        res[0] = False
                        res[1] = "Colors do not match."
                        return res
            else:
                tv = lut1.GetNumberOfTableValues()
                for i in range(tv):
                    rgba1 = lut1.GetTableValue(i)
                    rgba2 = lut2.GetTableValue(i)
                    if not self.CompareRGBA(rgba1, rgba2):
                        res[0] = False
                        res[1] = "Colors do not match."
                        return res
        else:
            tv = lut1.GetNumberOfTableValues()
            indices = [(dR1[1] - dR1[0]) *
                       float(x) / tv + dR1[0] for x in range(0, tv)]
            for i, v in enumerate(indices):
                rgb1 = [0.0, 0.0, 0.0]
                lut1.GetColor(v, rgb1)
                rgba1 = rgb1 + [lut1.GetOpacity(v)]
                rgb2 = [0.0, 0.0, 0.0]
                lut2.GetColor(v, rgb2)
                rgba2 = rgb2 + [lut2.GetOpacity(v)]
                if not self.CompareRGBA(rgba1, rgba2):
                    res[0] = False
                    res[1] = "Colors do not match."
                    return res

        return res

    def CompareRGBA(self, rgba1, rgba2):
        '''
        Compare two rgba lists.
        rgba can be a hexadecimal string, or a
        list of rgb or rgba colors.
        :param: rgba1 - the color.
        :param: rgba2 - the color.
        :return: True if the colors are the same.
        '''
        if len(rgba1) != len(rgba2):
            return False
        if isinstance(rgba1, str):
            return rgba1 == rgba2
        if len(rgba1) == 3 or len(rgba1) == 4:
            for i in range(0, len(rgba1)):
                if rgba1[i] != rgba2[i]:
                    return False
            return True
        return False


def GetAllColorSchemes():
    '''
    Get all the color scheme names.
    :return: a map of the names keyed on their index.
    '''
    colorSchemes = dict()
    colorSeries = vtk.vtkColorSeries()
    for i in range(colorSeries.GetNumberOfColorSchemes()):
        colorSeries.SetColorScheme(i)
        colorSchemes[i] = colorSeries.GetColorSchemeName()
    return colorSchemes


def AvailableColorSchemes(colorSchemes):
    '''
    The available color scheme indexes and names.
    :param: colorSchemes - a map of the names keyed on their index.
    :return:  a string if the indexes and names.
    '''
    str = ''
    for k, v in colorSchemes.items():
        str += '{:3d}\t{:s}\n'.format(k, v)
    return str


def DisplayAvailableColorSchemes():
    '''
    Display the available color schemes.
    '''
    line = "-----------------------------------------------------------------------------\n"
    colorSchemes = GetAllColorSchemes()
    print(line + AvailableColorSchemes(colorSchemes) + line)


def DisplayResults(reason, lut1, lut2):
    '''
    Display the lookup tables and reason for failure.
    :param: reason - the reason.
    :param: lut1 - the first lookup table.
    :param: lut2 - the second lookup table.
    '''
    lutUtilities = LUTUtilities()
    line = "-----------------------------------------------------------------------------\n"
    print(line + reason + "\n")
    print(lutUtilities.DisplayLUTAsString(lut1))
    print(lutUtilities.DisplayLUTAsString(lut2))
    print(line)


def TestTables(lut1, lut2, expected=True):
    '''
    Test pairs of lookup tables.
    :param: lut1 - the first lookup table.
    :param: lut2 - the second lookup table.
    :param: expected - if False a fail is expected.
    :return: True/False.
    '''
    lutUtilities = LUTUtilities()
    comparison = lutUtilities.CompareLUTs(lut1, lut2)
    if comparison[0] != expected:
        DisplayResults(comparison[1], lut1, lut2)
    if expected:
        return comparison[0]
    return not comparison[0]


def TestLookupTables(lutMode):
    '''
    Test various combinations of lookup tables.
    :param: lutMode - if True the tables are ordinal, categorical otherwise.
    :return: True if all tests passed.
    '''
    lut1 = vtk.vtkLookupTable()
    lut2 = vtk.vtkLookupTable()
    colorSeries = vtk.vtkColorSeries()
    colorSeriesEnum = colorSeries.SPECTRUM
    colorSeries.SetColorScheme(colorSeriesEnum)

    colorSeries.BuildLookupTable(lut1)
    colorSeries.BuildLookupTable(lut2)
    if lutMode:
        lut1.IndexedLookupOff()
        lut2.IndexedLookupOff()
    lut1.SetNanColor(1, 0, 0, 1)
    lut2.SetNanColor(1, 0, 0, 1)
    if not lutMode:
        # For the annotation just use a letter of the alphabet.
        values1 = vtk.vtkVariantArray()
        values2 = vtk.vtkVariantArray()
        str = "abcdefghijklmnopqrstuvwxyz"
        for i in range(lut1.GetNumberOfTableValues()):
            values1.InsertNextValue(vtk.vtkVariant(str[i]))
        for i in range(lut2.GetNumberOfTableValues()):
            values2.InsertNextValue(vtk.vtkVariant(str[i]))
        for i in range(values1.GetNumberOfTuples()):
            lut1.SetAnnotation(i, values1.GetValue(i).ToString())
        for i in range(values2.GetNumberOfTuples()):
            lut2.SetAnnotation(i, values2.GetValue(i).ToString())
    # Are they the same?
    res = True
    res &= TestTables(lut1, lut2)

    # Different size
    lut2.SetNumberOfTableValues(5)
    res &= TestTables(lut1, lut2, False)
    lut2.SetNumberOfTableValues(lut1.GetNumberOfTableValues())
    res &= TestTables(lut1, lut2)

    if lutMode:
        # Different range
        lut2.SetTableRange(1, 2)
        res &= TestTables(lut1, lut2, False)
        tr = lut1.GetTableRange()
        lut2.SetTableRange(tr)
        res &= TestTables(lut1, lut2)

        # Different color
        colorSeriesEnum = colorSeries.COOL
        colorSeries.SetColorScheme(colorSeriesEnum)
        lut3 = vtk.vtkLookupTable()
        colorSeries.BuildLookupTable(lut3)
        lut3.IndexedLookupOff()
        res &= TestTables(lut1, lut3, False)

        # One indexed, the other ordinal.
        lut1.IndexedLookupOn()
        res &= TestTables(lut1, lut2, False)

    else:
        # Different color
        colorSeriesEnum = colorSeries.COOL
        colorSeries.SetColorScheme(colorSeriesEnum)
        lut3 = vtk.vtkLookupTable()
        colorSeries.BuildLookupTable(lut3)
        values = vtk.vtkVariantArray()
        str = "abcdefghijklmnopqrstuvwxyz"
        for i in range(lut3.GetNumberOfTableValues()):
            values.InsertNextValue(vtk.vtkVariant(str[i]))
        for i in range(values.GetNumberOfTuples()):
            lut3.SetAnnotation(i, values.GetValue(i).ToString())
        colorSeries.BuildLookupTable(lut3)
        res &= TestTables(lut1, lut3, False)

        # Different annotations.
        lut2.ResetAnnotations()
        for i in range(values.GetNumberOfTuples()):
            if i % 3 == 0:
                continue
            lut2.SetAnnotation(i, values.GetValue(i).ToString())
        res &= TestTables(lut1, lut2, False)

        # No annotations
        lut1.ResetAnnotations()
        lut2.ResetAnnotations()
        res &= TestTables(lut1, lut2)

        # One indexed, the other ordinal.
        lut1.IndexedLookupOff()
        res &= TestTables(lut1, lut2, False)

    return res


def main():
    # DisplayAvailableColorSchemes()
    # Test ordinal LUTS.
    res = TestLookupTables(True)
    # Test categorical LUTs.
    res &= TestLookupTables(False)
    return res


if __name__ == '__main__':
    res = main()
    if res:
        sys.exit(0)
    else:
        print('Ordinal or Categorical LookupTable tests failed.')
        sys.exit(1)
