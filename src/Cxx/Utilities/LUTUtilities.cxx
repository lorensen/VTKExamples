#include <vtkColorSeries.h>
#include <vtkLookupTable.h>
#include <vtkVariantArray.h>
#include <vtkSmartPointer.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

//! Utilities for displaying and comparing lookup tables.
class LUTUtilities
{
  public:
    //-----------------------------------------------------------------------------
    //! Constructor.
    LUTUtilities(){};

    //-----------------------------------------------------------------------------
    //! Destructor.
    ~LUTUtilities(){};

    //-----------------------------------------------------------------------------
    //! Display the contents of the lookup table.
    /*!
     * @param lut - the lookup table.
     * @return a string containing the table data.
     */
    std::string DisplayLUTAsString(vtkLookupTable *lut)
    {
      vtkIdType tv = lut->GetNumberOfTableValues();
      double dR[2];
      lut->GetTableRange(dR);
      std::ostringstream os;
      if (lut->GetIndexedLookup())
      {
        vtkIdType av = lut->GetNumberOfAnnotatedValues();
        os << "Categorical Lookup Table\nNumber of annotated values: " << av
          << " Number of table values: " << tv
          << "\nTable Range: " << std::fixed
           << std::setw(8) << std::setprecision(6)
          << dR[0] << " to " << dR[1] << std::endl;
        if (av > 0)
        {
          for (vtkIdType i = 0; i < av; ++i)
          {
            double rgba[4];
            lut->GetAnnotationColor(lut->GetAnnotatedValue(i), rgba);
            os << std::setw(5) << lut->GetAnnotation(i) << ": ";
            os << this->AssembleRGBAString(rgba);
            os << std::endl;
          }
        }
        else
        {
          for (vtkIdType i = 0; i < tv; ++i)
          {
            double rgba[4];
            lut->GetTableValue(i, rgba);
            os << std::setw(5) << i << ": ";
            os << this->AssembleRGBAString(rgba);
            os << std::endl;
          }
        }
      }
      else
      {
        os << "Ordinal Lookup Table\nNumber of table values : " << tv
          << "\nTable Range: " << std::fixed
           << std::setw(8) << std::setprecision(6)
          << dR[0] << " to " << dR[1] << std::endl;
        std::vector<double> indices;
        for (int i = 0; i < tv; ++i)
        {
          indices.push_back((dR[1] - dR[0]) * i / tv + dR[0]);
        }
        for (std::vector<double>::const_iterator p = indices.begin();
            p != indices.end(); ++p)
        {
          double rgba[4];
          lut->GetColor(*p, rgba);
          rgba[3] = lut->GetOpacity(*p);
          os << std::fixed << std::setw(5) << std::setprecision(2)
             << *p << ": ";
          os << this->AssembleRGBAString(rgba);
          os << std::endl;
        }
      }
      return os.str();
    }

    //-----------------------------------------------------------------------------
    //! Compare two lookup tables.
    /*!
     * @param lut1 - the lookup table.
     * @param lut2 - the lookup table.
     * @return true if the tables are the same.
     */
    std::pair<bool, std::string> CompareLUTs(vtkLookupTable *lut1,
    vtkLookupTable *lut2)
    {
      std::pair<bool, std::string> res(true, "");
      if (lut1->GetIndexedLookup() != lut2->GetIndexedLookup())
      {
        res.first = false;
        res.second = "One table is ordinal and the other is categorical.";
        return res;
      }
      if (lut1->GetIndexedLookup() &&
          lut1->GetNumberOfAnnotatedValues()
          != lut2->GetNumberOfAnnotatedValues())
      {
        res.first = false;
        res.second = "The number of annotated values do not match.";
        return res;
      }
      if (lut1->GetNumberOfTableValues() != lut2->GetNumberOfTableValues())
      {
        res.first = false;
        res.second = "Table values do not match.";
        return res;
      }
      double dR1[2];
      lut1->GetTableRange(dR1);
      double dR2[2];
      lut2->GetTableRange(dR2);
      if (dR1[0] != dR2[0] && dR2[1] != dR1[1])
      {
        res.first = false;
        res.second = "Table ranges do not match.";
      }
      if (lut1->GetIndexedLookup())
      {
        vtkIdType av = lut1->GetNumberOfAnnotatedValues();
        if (av > 0)
        {
          for (vtkIdType i = 0; i < av; ++i)
          {
            if (lut1->GetAnnotation(i) != lut1->GetAnnotation(i))
            {
              res.first = false;
              res.second = "Annotations do not match.";
              return res;
            }
          }
          for (vtkIdType i = 0; i < av; ++i)
          {
            double rgba1[4];
            lut1->GetAnnotationColor(lut1->GetAnnotatedValue(i), rgba1);
            double rgba2[4];
            lut2->GetAnnotationColor(lut2->GetAnnotatedValue(i), rgba2);
            if (!this->CompareRGBA(rgba1, rgba2))
            {
              res.first = false;
              res.second = "Colors do not match.";
              return res;
            }
          }
        }
        else
        {
          for (vtkIdType i = 0; i < av; ++i)
          {
            double rgba1[4];
            lut1->GetTableValue(i, rgba1);
            double rgba2[4];
            lut2->GetTableValue(i, rgba2);
            if (!this->CompareRGBA(rgba1, rgba2))
            {
              res.first = false;
              res.second = "Colors do not match.";
              return res;
            }
          }
        }
      }
      else
      {
        vtkIdType tv = lut1->GetNumberOfTableValues();
        std::vector<double> indices;
        for (int i = 0; i < tv; ++i)
        {
          indices.push_back((dR1[1] - dR1[0]) * i / tv + dR1[0]);
        }
        for (std::vector<double>::const_iterator p = indices.begin();
          p != indices.end(); ++p)
        {
          double rgba1[4];
          lut1->GetColor(*p, rgba1);
          rgba1[3] = lut1->GetOpacity(*p);
          double rgba2[4];
          lut2->GetColor(*p, rgba2);
          rgba2[3] = lut2->GetOpacity(*p);
          if (!this->CompareRGBA(rgba1, rgba2))
          {
            res.first = false;
            res.second = "Colors do not match.";
            return res;
          }
        }
      }
      return res;
    }


  private:
    //-----------------------------------------------------------------------------
    //! Get a string of [R, G, B, A] as double.
    std::string RGBAToDoubleString(double *rgba)
    {
      std::ostringstream os;
      os << "[";
      for (int i = 0; i < 4; ++i)
      {
        if (i == 0)
        {
          os << std::fixed << std::setw(8) << std::setprecision(6) << rgba[i];
        }
        else
        {
          os << std::fixed << std::setw(9) << std::setprecision(6) << rgba[i];
        }
        if (i < 3)
        {
          os << ",";
        }
      }
      os << "]";
      return os.str();
    }

    //-----------------------------------------------------------------------------
    //! Get a string of [R, G, B, A] as unsigned char.
    std::string RGBAToCharString(double *rgba)
    {
      std::ostringstream os;
      os << "[";
      for (int i = 0; i < 4; ++i)
      {
        if (i == 0)
        {
          os << std::setw(3) << static_cast<int>(rgba[i] * 255);
        }
        else
        {
          os << std::setw(4) << static_cast<int>(rgba[i] * 255);
        }
        if (i < 3)
        {
          os << ",";
        }
      }
      os << "]";
      return os.str();
    }

    //-----------------------------------------------------------------------------
    //! Get a hexadecimal string of the RGB colors.
    std::string RGBToHexString(double *rgba)
    {
      std::ostringstream os;
      for (int i = 0; i < 3; ++i)
      {
        os << std::setw(2) << std::setfill('0') << std::hex
           << static_cast<int>(rgba[i] * 255);
      }
      return os.str();
    }

    //-----------------------------------------------------------------------------
    //! Get a string of [R, G, B, A] as double, unsigned char and hex.
    std::string AssembleRGBAString(double *rgba)
    {
      std::ostringstream os;
      os << this->RGBAToDoubleString(rgba);
      os << " ";
      os << this->RGBAToCharString(rgba);
      os << " 0x";
      os << this->RGBToHexString(rgba);
      return os.str();
    }

    //-----------------------------------------------------------------------------
    //! Compare two rgba colors.
    template <typename T>
    bool CompareRGBA(T *rgba1, T *rgba2)
    {
      bool areEquivalent = true;
      for (int i = 0; i < 4; ++i)
      {
        areEquivalent &= rgba1[i] == rgba2[i];
        if (!areEquivalent)
        {
          return false;
        }
      }
      return true;
    }
};

//-----------------------------------------------------------------------------
//! Get all the color scheme names.
/*!
 * @return a map of the names keyed on their index.
 */
std::map<int, std::string> GetAllColorSchemes()
{
  std::map<int, std::string> colorSchemes;
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  for (int i = 0; i < colorSeries->GetNumberOfColorSchemes(); ++i)
  {
    colorSeries->SetColorScheme(i);
    colorSchemes[i] = colorSeries->GetColorSchemeName();
  }
  return colorSchemes;
}

//-----------------------------------------------------------------------------
//! The available color scheme indexes and names.
/*!
  * @param colorSchemes - a map of the names keyed on their index.
  * @return a string if the indexes and names.
  */
std::string AvailableColorSchemes(std::map<int, std::string> & colorSchemes)
{
  std::ostringstream os;
  for (std::map<int, std::string>::const_iterator p = colorSchemes.begin();
       p != colorSchemes.end(); ++p)
  {
    os << std::setw(3) << p->first << "\t" << p->second << std::endl;
  }
  return os.str();
}

//-----------------------------------------------------------------------------
//! Display the available color schemes.
void DisplayAvailableColorSchemes()
{
  std::string line("-----------------------------------------------------------------------------\n");
  std::map<int, std::string> colorSchemes;
  colorSchemes = GetAllColorSchemes();
  std::cout << line << AvailableColorSchemes(colorSchemes) << line << std::endl;
}

//-----------------------------------------------------------------------------
//! Display the lookup tables and reason for failure.
/*!
 * @param reason - the reason.
 * @param lut1 - the first lookup table.
 * @param lut2 - the second lookup table.
 */
void DisplayResults(std::string & reason,
  vtkLookupTable *lut1, vtkLookupTable *lut2)
{
  LUTUtilities lutUtilities;
  std::string line("-----------------------------------------------------------------------------\n");
  std::cout << line;
  std::cout << reason << std::endl;
  std::cout << lutUtilities.DisplayLUTAsString(lut1) << std::endl;
  std::cout << lutUtilities.DisplayLUTAsString(lut2) << std::endl;
  std::cout << line;
}

//-----------------------------------------------------------------------------
//! Test pairs of lookup tables.
/*!
 * @param lut1 - the first lookup table.
 * @param lut2 - the second lookup table.
 * @param expected - if false a fail is expected.
 * @return true/false.
 */
bool TestTables(vtkLookupTable *lut1, vtkLookupTable *lut2,
                bool const expected = true)
{
  LUTUtilities lutUtilities;
  std::pair<bool, std::string> comparison = lutUtilities.CompareLUTs(lut1, lut2);
  if (comparison.first != expected)
  {
    DisplayResults(comparison.second, lut1, lut2);
  }
  return (expected) ? comparison.first : !comparison.first;
}

//-----------------------------------------------------------------------------
//! Test various combinations of lookup tables.
/*!
 * @param lutMode - if true the tables are ordinal, categorical otherwise.
 * @return true if all tests passed.
 */
bool TestLookupTables(bool const & lutMode)
{
  LUTUtilities lutUtilities;
  vtkSmartPointer<vtkLookupTable> lut1 = vtkSmartPointer<vtkLookupTable>::New();
  vtkSmartPointer<vtkLookupTable> lut2 = vtkSmartPointer<vtkLookupTable>::New();
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  int colorSeriesEnum = colorSeries->SPECTRUM;
  colorSeries->SetColorScheme(colorSeriesEnum);

  colorSeries->BuildLookupTable(lut1);
  colorSeries->BuildLookupTable(lut2);
  if (lutMode)
  {
    lut1->IndexedLookupOff();
    lut2->IndexedLookupOff();
  }
  lut1->SetNanColor(1, 0, 0, 1);
  lut2->SetNanColor(1, 0, 0, 1);

  if (!lutMode)
  {
    //  For the annotation just use a letter of the alphabet.
    vtkSmartPointer <vtkVariantArray> values1 =
      vtkSmartPointer <vtkVariantArray>::New();
    vtkSmartPointer <vtkVariantArray> values2 =
      vtkSmartPointer <vtkVariantArray>::New();
    std::string str = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < lut1->GetNumberOfTableValues(); ++i)
    {
      values1->InsertNextValue(vtkVariant(str.substr(i, 1)));
    }
    for (int i = 0; i < lut2->GetNumberOfTableValues(); ++i)
    {
      values2->InsertNextValue(vtkVariant(str.substr(i, 1)));
    }
    for (int i = 0; i < values1->GetNumberOfTuples(); ++i)
    {
      lut1->SetAnnotation(i, values1->GetValue(i).ToString());
    }
    for (int i = 0; i < values2->GetNumberOfTuples(); ++i)
    {
        lut2->SetAnnotation(i, values2->GetValue(i).ToString());
    }
  }

  // Are they the same?
  bool res = true;
  res &= TestTables(lut1, lut2);

  // Different size
  lut2->SetNumberOfTableValues(5);
  res &= TestTables(lut1, lut2, false);
  lut2->SetNumberOfTableValues(lut1->GetNumberOfTableValues());
  res &= TestTables(lut1, lut2);

  if (lutMode)
  {
    // Different range
    lut2->SetTableRange(1, 2);
    res &= TestTables(lut1, lut2, false);
    double tr[2];
    lut1->GetTableRange(tr);
    lut2->SetTableRange(tr);
    res &= TestTables(lut1, lut2);

    // Different color
    colorSeriesEnum = colorSeries->COOL;
    colorSeries->SetColorScheme(colorSeriesEnum);
    vtkSmartPointer<vtkLookupTable> lut3 = vtkSmartPointer<vtkLookupTable>::New();
    colorSeries->BuildLookupTable(lut3);
    lut3->IndexedLookupOff();
    res &= TestTables(lut1, lut3, false);

    // One indexed, the other ordinal.
    lut1->IndexedLookupOn();
    res &= TestTables(lut1, lut2, false);
  }
  else
  {
    // Different color
    colorSeriesEnum = colorSeries->COOL;
    colorSeries->SetColorScheme(colorSeriesEnum);
    vtkSmartPointer<vtkLookupTable> lut3 = vtkSmartPointer<vtkLookupTable>::New();
    //  For the annotation just use a letter of the alphabet.
    vtkSmartPointer <vtkVariantArray> values =
      vtkSmartPointer <vtkVariantArray>::New();
    std::string str = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < lut1->GetNumberOfTableValues(); ++i)
    {
      values->InsertNextValue(vtkVariant(str.substr(i, 1)));
    }
    for (int i = 0; i < values->GetNumberOfTuples(); ++i)
    {
      lut3->SetAnnotation(i, values->GetValue(i).ToString());
    }
    colorSeries->BuildLookupTable(lut3);
    res &= TestTables(lut1, lut3, false);

    // Different annotations.
    lut2->ResetAnnotations();
    for (int i = 0; i < values->GetNumberOfTuples(); ++i)
    {
      if (i % 3 == 0)
        continue;
      lut2->SetAnnotation(i, values->GetValue(i).ToString());
    }
    res &= TestTables(lut1, lut2, false);

    // No annotations.
    lut1->ResetAnnotations();
    lut2->ResetAnnotations();
    res &= TestTables(lut1, lut2);

    // One indexed, the other ordinal.
    lut1->IndexedLookupOff();
    res &= TestTables(lut1, lut2, false);
  }

  return res;
}

//-----------------------------------------------------------------------------
int main(int, char *[])
{
  //DisplayAvailableColorSchemes();
  // Test ordinal LUTS.
  bool res = TestLookupTables(true);
  // Test categorical LUTs.
  res &= TestLookupTables(false);
  return (res) ? EXIT_SUCCESS : EXIT_FAILURE;
}
