[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/CaptionActor2D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestCaptionActor2D.png?raw=true" width="256" />

**CaptionActor2D.cxx**
```c++
#include <vtkAbstractPicker.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCaptionActor2D.h>
#include <vtkCoordinate.h>
#include <vtkFollower.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkCoordinate.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkMath.h>
#include <vtkObjectFactory.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkVectorText.h>

#include <sstream>

class MyStyle : public vtkInteractorStyleImage
{
  public:
    static MyStyle* New();
    vtkTypeMacro(MyStyle, vtkInteractorStyleImage);

    std::vector<vtkActor2D*> Numbers;

    void OnLeftButtonDown()
    {
      //std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
      this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
              this->Interactor->GetEventPosition()[1],
              0,  // always zero.
              //this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
              this->CurrentRenderer );
      double picked[3];
      this->Interactor->GetPicker()->GetPickPosition(picked);
      //std::cout << "Picked point with coordinate: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

      this->AddNumber(picked);

      // Forward events
      vtkInteractorStyleImage::OnLeftButtonDown();

      //this->Interactor->GetRenderWindow()->Render();
      this->Interactor->Render();
    }

    void AddNumber(double p[3])
    {
      std::cout << "Adding marker at " << p[0] << " " << p[1] ;//<< std::endl;

      // normally, with an image you would do
      // double* s = image->GetSpacing();
      // double* o = image->GetOrigin();
      // p[0] = static_cast<int>( (p[0] - o[0]) / s[0] + 0.5 );
      p[0] = static_cast<int>( p[0] + 0.5 );
      p[1] = static_cast<int>( p[1] + 0.5 );

      std::cout << " -> " << p[0] << " " << p[1] << std::endl;

      // Convert the current number to a string
      std::stringstream ss;
      ss << Numbers.size();
      std::cout << "Adding number: " << ss.str() << std::endl;

      // Create an actor for the text
      vtkSmartPointer<vtkCaptionActor2D> captionActor = vtkSmartPointer<vtkCaptionActor2D>::New();
      captionActor->SetCaption( ss.str().c_str() );
      captionActor->SetAttachmentPoint(p);
      captionActor->BorderOff();
      captionActor->GetCaptionTextProperty()->BoldOff();
      captionActor->GetCaptionTextProperty()->ItalicOff();
      captionActor->GetCaptionTextProperty()->ShadowOff();
      captionActor->ThreeDimensionalLeaderOff();
      
      this->CurrentRenderer->AddViewProp( captionActor );

      this->Numbers.push_back(captionActor);
    }
};

vtkStandardNewMacro(MyStyle);

int main (int, char *[])
{
  // Create a blank, black image
  vtkSmartPointer<vtkImageCanvasSource2D> drawing = vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0, 20, 0, 50, 0, 0);
  drawing->FillBox(0,20,0,50);

  // Draw a red circle of radius 5 centered at (9,10)
  drawing->SetDrawColor(255, 0, 0, 0);
  drawing->DrawCircle(9, 10, 5);
  drawing->Update();

  vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(drawing->GetOutputPort());
  actor->InterpolateOff();

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  renderer->GradientBackgroundOn();
  renderer->SetBackground2(0,0,1); // Background 2 color blue

  renderWindow->Render();

  vtkSmartPointer<MyStyle> style = vtkSmartPointer<MyStyle>::New();

  renderWindowInteractor->SetInteractorStyle( style );
  style->SetDefaultRenderer( renderer );
  style->SetCurrentRenderer( renderer );
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CaptionActor2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CaptionActor2D MACOSX_BUNDLE CaptionActor2D.cxx)
 
target_link_libraries(CaptionActor2D ${VTK_LIBRARIES})
```

**Download and Build CaptionActor2D**

Click [here to download CaptionActor2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CaptionActor2D.tar) and its *CMakeLists.txt* file.
Once the *tarball CaptionActor2D.tar* has been downloaded and extracted,
```
cd CaptionActor2D/build 
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
./CaptionActor2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

