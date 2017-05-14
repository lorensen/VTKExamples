[VTKExamples](/index/)/[Cxx](/Cxx)/InfoVis/TreeMapView

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/InfoVis/TestTreeMapView.png?raw=true" width="256" />

### Description
Fix: use a much simpler tree and generate the tree in the code instead of reading files.

**TreeMapView.cxx**
```c++
#include <vtkDataRepresentation.h>
#include <vtkRenderWindow.h>
#include <vtkRegressionTestImage.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTestUtilities.h>
#include <vtkTreeMapView.h>
#include <vtkViewTheme.h>
#include <vtkXMLTreeReader.h>
#include <vtkSmartPointer.h>
#include <vtkTesting.h>

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkTesting> testHelper =
    vtkSmartPointer<vtkTesting>::New();
  testHelper->AddArguments(argc,const_cast<const char **>(argv));
  std::string dataRoot = testHelper->GetDataRoot();
  std::string treeFileName = dataRoot + "/Data/Infovis/XML/vtkclasses.xml";
  std::string graphFileName = dataRoot + "/Data/Infovis/XML/vtklibrary.xml";

  if (argc > 2)
  {
    treeFileName = argv[1];  // vtkclasses.xml
    graphFileName = argv[2]; // vtklibrary.xml
  }

  // We need to put the graph and tree edges in different domains.
  vtkSmartPointer<vtkXMLTreeReader> reader1 =
    vtkSmartPointer<vtkXMLTreeReader>::New();
  reader1->SetFileName(treeFileName.c_str());
  reader1->SetEdgePedigreeIdArrayName("tree edge");
  reader1->GenerateVertexPedigreeIdsOff();
  reader1->SetVertexPedigreeIdArrayName("id");

  vtkSmartPointer<vtkXMLTreeReader> reader2 =
    vtkSmartPointer<vtkXMLTreeReader>::New();
  reader2->SetFileName(graphFileName.c_str());
  reader2->SetEdgePedigreeIdArrayName("graph edge");
  reader2->GenerateVertexPedigreeIdsOff();
  reader2->SetVertexPedigreeIdArrayName("id");

  reader1->Update();
  reader2->Update();

  vtkSmartPointer<vtkTreeMapView> view =
    vtkSmartPointer<vtkTreeMapView>::New();
  view->DisplayHoverTextOff();
  view->SetTreeFromInputConnection(reader2->GetOutputPort());
  view->SetGraphFromInputConnection(reader1->GetOutputPort());

  view->SetAreaColorArrayName("level");
  view->SetEdgeColorToSplineFraction();
  view->SetColorEdges(true);
  view->SetAreaLabelArrayName("id");
  view->SetAreaHoverArrayName("id");
  view->SetAreaLabelVisibility(true);
  view->SetAreaSizeArrayName("VertexDegree");

  // Apply a theme to the views
  vtkViewTheme* const theme = vtkViewTheme::CreateMellowTheme();
  view->ApplyViewTheme(theme);
  theme->Delete();

  view->GetRenderWindow()->SetMultiSamples(0);
  view->GetRenderWindow()->SetAlphaBitPlanes(1);
  view->Update();
  view->ResetCamera();

  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TreeMapView)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TreeMapView MACOSX_BUNDLE TreeMapView.cxx)
 
target_link_libraries(TreeMapView ${VTK_LIBRARIES})
```

**Download and Build TreeMapView**

Click [here to download TreeMapView](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TreeMapView.tar) and its *CMakeLists.txt* file.
Once the *tarball TreeMapView.tar* has been downloaded and extracted,
```
cd TreeMapView/build 
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
./TreeMapView
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

