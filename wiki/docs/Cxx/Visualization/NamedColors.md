[VTKExamples](Home)/[Cxx](Cxx)/Visualization/NamedColors

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestNamedColors.png" width="256" />

### Description
This example demonstrates the usage of the vtkNamedColors class. Some helper functions are also implemented.

A cone is created and contoured using the BandedPolyDataContourFilter, it is then colored using a LookupTable where the colors have been assigned using color names.

A list of available color names and any synonyms are also output.

**NamedColors.cxx**
```c++
/*
This example demonstrates the usage of the vtNamedColor class.
*/
#include <vtkNamedColors.h>

#include <vtkConeSource.h>
#include <vtkAlgorithm.h>
#include <vtkElevationFilter.h>
#include <vtkBandedPolyDataContourFilter.h>
#include <vtkLookupTable.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <cstdlib>

// In C++0x there is a utility function std::next, however compilers
// not implementing C++0x will need this equivalent.
template <typename ForwardIt>
  ForwardIt myNext(ForwardIt iter,
            typename std::iterator_traits<ForwardIt>::difference_type n = 1);

// Test if an iterator points to the last item.
template <typename Iter, typename Cont>
  bool IsLast(Iter iter, const Cont & cont);

// Parse the color names returning a std::vector<std::string>
// colorNames is a string formatted with each name separated
// with a linefeed.
std::vector<vtkStdString> ParseColorNames(const vtkStdString & colorNames);

// Parse the synonyms returning a std::vector<std::vector<std::string> >
// synonyms is a string of synonyms separated by a double linefeed where
// each synonym is two or more color names separated by a linefeed.
std::vector<std::vector<vtkStdString> > ParseSynonyms(
  const vtkStdString & synonyms);

// Print out the colors.
void PrintColors(vtkNamedColors *namedColors);

// Print out the synonyms.
void PrintSynonyms(vtkNamedColors *namedColors);

// Find any synonyms for a specified color.
void FindSynonyms(const vtkStdString & color, vtkNamedColors *namedColors,
  vtkStringArray *synonyms);

//-----------------------------------------------------------------------------
template <typename ForwardIt>
  ForwardIt myNext(ForwardIt iter,
            typename std::iterator_traits<ForwardIt>::difference_type n)
{
    std::advance(iter, n);
    return iter;
}

//-----------------------------------------------------------------------------
template <typename Iter, typename Cont>
  bool IsLast(Iter iter, const Cont & cont)
{
  return (iter != cont.end()) && (myNext(iter) == cont.end());
}

//-----------------------------------------------------------------------------
std::vector<vtkStdString> ParseColorNames(const vtkStdString & colorNames)
{
  // The delimiter for a color.
  const std::string colorDelimiter = "\n";
  std::vector<vtkStdString> cn;
  size_t start = 0;
  size_t end = colorNames.find(colorDelimiter);
  while(end != std::string::npos)
  {
    cn.push_back(colorNames.substr(start,end - start));
    start = end + 1;
    end = colorNames.find(colorDelimiter,start);
  }
  // Get the last color.
  if (!colorNames.empty())
  {
    cn.push_back(colorNames.substr(start,colorNames.size() - start));
  }
  return cn;
}

//-----------------------------------------------------------------------------
std::vector<std::vector<vtkStdString> > ParseSynonyms(
  const vtkStdString & synonyms)
{
  // The delimiter for a string of synonyms.
  const std::string synonymDelimiter = "\n\n";
  size_t start = 0;
  size_t end = synonyms.find("\n\n"); // The delimiter for a string of synonyms.
  std::vector<vtkStdString> cn;
  std::vector<std::vector<vtkStdString> > syn;
  vtkStdString str;
  while(end != std::string::npos)
  {
    str = synonyms.substr(start,end - start);
    cn = ParseColorNames(str);
    syn.push_back(cn);
    start = end + 2;
    end = synonyms.find(synonymDelimiter,start);
  }
  // Get the last set of synonyms.
  if(!synonyms.empty())
  {
    str = synonyms.substr(start,end - start);
    cn = ParseColorNames(str);
    syn.push_back(cn);
  }
  return syn;
}

//-----------------------------------------------------------------------------
void FindSynonyms(const vtkStdString & color, vtkNamedColors *namedColors,
  vtkStringArray *synonyms)
{
  vtkSmartPointer<vtkStringArray> availableColors =
    vtkSmartPointer<vtkStringArray>::New();
  namedColors->GetColorNames(availableColors);
  // We will be matching on RGB only.
  vtkColor3ub myColor = namedColors->GetColor3ub(color);
  // Colors are all stored as lower case, so convert color to lower case.
  vtkStdString lcColor;
  std::transform(color.begin(),color.end(),std::back_inserter(lcColor),
                   (int (*)(int))std::tolower);
  for(vtkIdType i = 0; i < availableColors->GetNumberOfValues(); ++i)
  {
    vtkStdString n = availableColors->GetValue(i);
    vtkColor3ub c = namedColors->GetColor3ub(n);
    if (myColor.Compare(c,1) /*&& n != lcColor*/)
    {
      synonyms->InsertNextValue(availableColors->GetValue(i));
    }
  }
}

//-----------------------------------------------------------------------------
void PrintColors(vtkNamedColors *namedColors)
{
  // Get the available colors:
  std::vector<vtkStdString> colors =
    ParseColorNames(namedColors->GetColorNames());
  std::cout << "There are " << namedColors->GetNumberOfColors()
    << " colors:" << std::endl;
  int n = 0;
  for(std::vector<vtkStdString>::const_iterator p =
    colors.begin(); p!= colors.end(); ++p)
  {
    ++n;
    if ( n % 5 == 0 )
    {
      std::cout << std::endl;
    }
    std::cout << *p;
    if(!IsLast(p,colors))
    {
      std::cout << ",";
    }
  }
  std::cout << std::endl;
}

//-----------------------------------------------------------------------------
void PrintSynonyms(vtkNamedColors *namedColors)
{
  // Get the synonyms:
  std::vector<std::vector<vtkStdString> > synonyms =
    ParseSynonyms(namedColors->GetSynonyms());
  std::cout << "There are " << synonyms.size()
    << " synonyms:" << std::endl;
  for(std::vector<std::vector<vtkStdString> >::const_iterator p =
    synonyms.begin(); p != synonyms.end(); ++p)
  {
      for(std::vector<vtkStdString>::const_iterator q =
        p->begin(); q != p->end(); ++q)
      {
       std::cout << *q;
       if(!IsLast(q,*p))
       {
        std::cout << ",";
       }
      }
      std::cout << std::endl;
  }
}

//-----------------------------------------------------------------------------
// Create a cone, contour it using the banded contour filter and
// color it with the primary additive and subtractive colors.
int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  // We can print out the variables
  //namedColors->PrintSelf(std::cout,vtkIndent(2));

  // Here we just print out the colors and any
  // synonyms.
  PrintColors(namedColors);
  PrintSynonyms(namedColors);

  // Create a cone
  vtkSmartPointer<vtkConeSource> coneSource =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->SetCenter(0.0, 0.0, 0.0);
  coneSource->SetRadius(5.0);
  coneSource->SetHeight(10);
  coneSource->SetDirection(0,1,0);
  coneSource->Update();

  double bounds[6];
  coneSource->GetOutput()->GetBounds(bounds);

  vtkSmartPointer<vtkElevationFilter> elevation =
    vtkSmartPointer<vtkElevationFilter>::New();
  elevation->SetInputConnection(coneSource->GetOutputPort());
  elevation->SetLowPoint(0,bounds[2],0);
  elevation->SetHighPoint(0,bounds[3],0);

  vtkSmartPointer<vtkBandedPolyDataContourFilter> bcf =
    vtkSmartPointer<vtkBandedPolyDataContourFilter>::New();
  bcf->SetInputConnection(elevation->GetOutputPort());
  bcf->SetScalarModeToValue();
  bcf->GenerateContourEdgesOn();
  bcf->GenerateValues(7,elevation->GetScalarRange());

  // Build a simple lookup table of
  // primary additive and subtractive colors.
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetNumberOfTableValues(7);
  double rgba[4];
  // Test setting and getting colors here.
  // We are also modifying alpha.
  namedColors->GetColor("Red",rgba);
  rgba[3] = 0.5;
  namedColors->SetColor("My Red",rgba);
  namedColors->GetColor("My Red",rgba);
  lut->SetTableValue(0,rgba);
  // Does "My Red" match anything?
  vtkSmartPointer<vtkStringArray> matchingColors =
    vtkSmartPointer<vtkStringArray>::New();
  // Demonstrates how to find synonyms.
  FindSynonyms("My Red", namedColors, matchingColors);
  if(matchingColors->GetNumberOfValues() != 0 )
  {
    std::cout << "Matching colors to My Red: ";
    for(vtkIdType i = 0; i < matchingColors->GetNumberOfValues(); ++i)
    {
      std::cout << matchingColors->GetValue(i);
      if (i != matchingColors->GetNumberOfValues() - 1 )
      {
         std::cout << ",";
      }
    }
    std::cout << std::endl;
  }
  namedColors->GetColor("DarkGreen",rgba);
  rgba[3] = 0.3;
  lut->SetTableValue(1,rgba);
  // Alternatively we can use tuple methods here:
  lut->SetTableValue(2,namedColors->GetColor4d("Blue").GetData());
  lut->SetTableValue(3,namedColors->GetColor4d("Cyan").GetData());
  lut->SetTableValue(4,namedColors->GetColor4d("Magenta").GetData());
  lut->SetTableValue(5,namedColors->GetColor4d("Yellow").GetData());
  lut->SetTableValue(6,namedColors->GetColor4d("White").GetData());
  lut->SetTableRange(elevation->GetScalarRange());
  lut->Build();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(bcf->GetOutputPort());
  mapper->SetScalarRange(elevation->GetScalarRange());
  mapper->SetLookupTable(lut);
  mapper->SetScalarModeToUseCellData();

  vtkSmartPointer<vtkPolyDataMapper> contourLineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourLineMapper->SetInputData(bcf->GetContourEdgesOutput());
  contourLineMapper->SetScalarRange(elevation->GetScalarRange());
  contourLineMapper->SetResolveCoincidentTopologyToPolygonOffset();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkActor> contourLineActor =
    vtkSmartPointer<vtkActor>::New();
  contourLineActor->SetMapper(contourLineMapper);
  contourLineActor->GetProperty()->SetColor(
    namedColors->GetColor3d("Black").GetData()
    );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->AddActor(contourLineActor);
  renderer->SetBackground(
    namedColors->GetColor3d("SteelBlue").GetData()
    );
  renderWindow->Render();
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(NamedColors)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(NamedColors MACOSX_BUNDLE NamedColors.cxx)
 
target_link_libraries(NamedColors ${VTK_LIBRARIES})
```

**Download and Build NamedColors**

Click [here to download NamedColors](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/NamedColors.tar) and its *CMakeLists.txt* file.
Once the *tarball NamedColors.tar* has been downloaded and extracted,
```
cd NamedColors/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./NamedColors
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

