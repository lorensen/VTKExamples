[VTKExamples](Home)/[Cxx](Cxx)/Visualization/Arbitrary3DCursor

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestArbitrary3DCursor.png" width="256" />

**Arbitrary3DCursor.cxx**
```c++
#include <vtkVersion.h>
#include "vtkSmartPointer.h"

#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
#include "vtkPointWidget.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkProbeFilter.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkXMLPolyDataReader.h"

#include <sstream>

// This does the actual work: updates the probe.
// Callback for the interaction
class vtkmyPWCallback : public vtkCommand
{
public:
  static vtkmyPWCallback *New()
  {
    return new vtkmyPWCallback;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkPointWidget *pointWidget = reinterpret_cast<vtkPointWidget*>(caller);
    pointWidget->GetPolyData(this->PolyData);
    double position[3];
    pointWidget->GetPosition(position);
    std::ostringstream text;
    text << "cursor: "
         << std::fixed << std::setprecision(4)
         << position[0] << ", " << position[1] << ", " << position[2];
    this->PositionActor->SetInput(text.str().c_str());
    this->CursorActor->VisibilityOn();
  }
  vtkmyPWCallback():PolyData(0),CursorActor(0) {}
  vtkPolyData  *PolyData;
  vtkActor     *CursorActor;
  vtkTextActor *PositionActor;
};

int main( int argc, char *argv[] )
{
  vtkSmartPointer<vtkPolyData> inputPolyData;

  if(argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    inputPolyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetPhiResolution(15);
    sphereSource->SetThetaResolution(15);
    sphereSource->Update();
    inputPolyData = sphereSource->GetOutput();
  }

  vtkSmartPointer<vtkPolyData> point =
    vtkSmartPointer<vtkPolyData>::New();

  vtkSmartPointer<vtkProbeFilter> probe =
    vtkSmartPointer<vtkProbeFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  probe->SetInput(point);
  probe->SetSource(inputPolyData);
#else
  probe->SetInputData(point);
  probe->SetSourceData(inputPolyData);
#endif

  // create glyph
  vtkSmartPointer<vtkConeSource> cone =
    vtkSmartPointer<vtkConeSource>::New();
  cone->SetResolution(16);

  vtkSmartPointer<vtkGlyph3D> glyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph->SetInputConnection(probe->GetOutputPort());
  glyph->SetSourceConnection(cone->GetOutputPort());
  glyph->SetVectorModeToUseVector();
  glyph->SetScaleModeToDataScalingOff();
  glyph->SetScaleFactor(inputPolyData->GetLength() * 0.1);

  vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyphMapper->SetInputConnection(glyph->GetOutputPort());

  vtkSmartPointer<vtkActor> glyphActor =
    vtkSmartPointer<vtkActor>::New();
  glyphActor->SetMapper(glyphMapper);
  glyphActor->VisibilityOn();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput(inputPolyData);
#else
  mapper->SetInputData(inputPolyData);
#endif
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();
  actor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400 );

  vtkSmartPointer<vtkTextActor> textActor =
    vtkSmartPointer<vtkTextActor>::New();
  textActor->GetTextProperty()->SetFontSize ( 12 );
  textActor->SetPosition ( 10, 20 );
  textActor->SetInput ( "cursor:" );
  textActor->GetTextProperty()->SetColor ( 1.0,0.0,0.0 );

  // Create the RenderWindow, Render1er and both Actors
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // The SetInteractor method is how 3D widgets are associated with the render
  // window interactor. Internally, SetInteractor sets up a bunch of callbacks
  // using the Command/Observer mechanism (AddObserver()).
  vtkSmartPointer<vtkmyPWCallback> myCallback =
    vtkSmartPointer<vtkmyPWCallback>::New();
  myCallback->PolyData = point;
  myCallback->CursorActor = glyphActor;
  myCallback->PositionActor = textActor;

  // The point widget is used probe the dataset.
  //
  vtkSmartPointer<vtkPointWidget> pointWidget =
    vtkSmartPointer<vtkPointWidget>::New();
  pointWidget->SetInteractor(iren);
#if VTK_MAJOR_VERSION <= 5
  pointWidget->SetInput(inputPolyData);
#else
  pointWidget->SetInputData(inputPolyData);
#endif
  pointWidget->AllOff();
  pointWidget->PlaceWidget();
  pointWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  ren1->AddActor(glyphActor);
  ren1->AddActor(actor);
  ren1->AddActor2D ( textActor );

  // Add the actors to the renderer, set the background and size
  //
  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(300, 300);
  renWin->Render();
  pointWidget->On();
  // render the image
  //
  iren->Initialize();
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Arbitrary3DCursor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Arbitrary3DCursor MACOSX_BUNDLE Arbitrary3DCursor.cxx)
 
target_link_libraries(Arbitrary3DCursor ${VTK_LIBRARIES})
```

**Download and Build Arbitrary3DCursor**

Click [here to download Arbitrary3DCursor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Arbitrary3DCursor.tar) and its *CMakeLists.txt* file.
Once the *tarball Arbitrary3DCursor.tar* has been downloaded and extracted,
```
cd Arbitrary3DCursor/build 
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
./Arbitrary3DCursor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

