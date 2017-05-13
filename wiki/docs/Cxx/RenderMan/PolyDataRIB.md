[VTKExamples](/home/)/[Cxx](/Cxx)/RenderMan/PolyDataRIB

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/RenderMan/TestPolyDataRIB.png?raw=true" width="256" />

### Description
To see the RenderMan results for this example, download and install the [non-commercial version of RenderMan](http://renderman.pixar.com/view/non-commercial-renderman).

**PolyDataRIB.cxx**
```c++
#include <vtkXMLPolyDataReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include "vtkRIBExporter.h"
#include "vtkRIBProperty.h"

#include <vtksys/SystemTools.hxx>

static vtkSmartPointer<vtkRIBProperty> spatter(const char *sizes,
                                               const char *specksize,
                                               const char *spattercolor,
                                               const char *basecolor);
static vtkSmartPointer<vtkRIBProperty> rmarble(const char *veining);

int main ( int argc, char *argv[] )
{
  // Parse command line arguments
  if(argc < 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " Filename(.vtp) [freqency]" << std::endl;
    return EXIT_FAILURE;
  }
  const char *freq = "1";
  if (argc > 2)
  {
    freq = argv[2];
  }

  std::string filename = argv[1];
  std::string prefix = vtksys::SystemTools::GetFilenameWithoutExtension(filename);

  // Read all the data from the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(reader->GetOutputPort());

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(normals->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->SetProperty(rmarble(freq));

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.1, .3, .5); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  prefix = prefix + "_" + freq;
  vtkSmartPointer<vtkRIBExporter> aRib =
    vtkSmartPointer<vtkRIBExporter>::New();
  aRib->BackgroundOn();
  aRib->SetInput(renderWindow);
  aRib->SetFilePrefix(prefix.c_str());
  aRib->Write();
  std::cout << "Exported RIB file is: " << prefix << ".rib" << std::endl;
  if (getenv("RMANTREE") == NULL)
  {
    std::cout << "To render the generated rib file, set the environment variable RMANTREE to the base of your RenderMan install" << std::endl;
  }
  else
  {
    std::string rmantree = getenv("RMANTREE");
    std::cout << "To create a tif file run: " << std::endl;
    std::cout << rmantree << "bin/prman " << prefix << ".rib " << std::endl;
  }
  return EXIT_SUCCESS;
}

vtkSmartPointer<vtkRIBProperty> spatter(const char *sizes,
                                        const char *specksize,
                                        const char *spattercolor,
                                        const char *basecolor)
{
  vtkSmartPointer<vtkRIBProperty> spatterProp =
    vtkSmartPointer<vtkRIBProperty>::New ();
  spatterProp->SetVariable("sizes", "float");
  spatterProp->AddVariable("specksize", "float");
  spatterProp->AddVariable("spattercolor", "color");
  spatterProp->AddVariable("basecolor", "color");

  spatterProp->SetSurfaceShaderParameter("sizes", sizes);
  spatterProp->AddSurfaceShaderParameter("specksize", specksize);
  spatterProp->AddSurfaceShaderParameter("spattercolor", spattercolor);
  spatterProp->AddSurfaceShaderParameter("basecolor", basecolor);
  spatterProp->SetSurfaceShader("spatter");

  return spatterProp;
}

vtkSmartPointer<vtkRIBProperty> rmarble(const char *veining)
{
  vtkSmartPointer<vtkRIBProperty> rmarbleProp =
    vtkSmartPointer<vtkRIBProperty>::New ();
  rmarbleProp->SetVariable("veining", "float");
  rmarbleProp->SetSurfaceShaderParameter("veining", veining);
  rmarbleProp->SetSurfaceShader("rmarble");

  return rmarbleProp;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolyDataRIB)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataRIB MACOSX_BUNDLE PolyDataRIB.cxx)
 
target_link_libraries(PolyDataRIB ${VTK_LIBRARIES})
```

**Download and Build PolyDataRIB**

Click [here to download PolyDataRIB](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataRIB.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataRIB.tar* has been downloaded and extracted,
```
cd PolyDataRIB/build 
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
./PolyDataRIB
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

