#include <vtkActor.h>
#include <vtkContourFilter.h>
#include <vtkImageData.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSampleFunction.h>
#include <vtkSmartPointer.h>
#include <vtkSphere.h>

#include <algorithm>
#include <array>

int main (int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color. Match those in VTKTextbook.pdf.
  auto SetColor = [&colors](std::array<double, 3>& v,
                            std::string const& colorName) {
    auto const scaleFactor = 255.0;
    std::transform(std::begin(v), std::end(v), std::begin(v),
                   [=](double const& n) { return n / scaleFactor; });
    colors->SetColor(colorName, v.data());
    return;
  };
  std::array<double, 3> bkg{{51, 77, 102}};
  SetColor(bkg, "BkgColor");

  vtkSmartPointer<vtkSphere> sphere = 
    vtkSmartPointer<vtkSphere>::New();
  
  // Sample the function
  vtkSmartPointer<vtkSampleFunction> sample = 
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(sphere);
  double value = 2.0;
  double xmin = -value, xmax = value,
    ymin = -value, ymax = value,
    zmin = -value, zmax = value;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
    
  // Create the 0 isosurface
  vtkSmartPointer<vtkContourFilter> contours = 
    vtkSmartPointer<vtkContourFilter>::New();
  contours->SetInputConnection(sample->GetOutputPort());
  contours->GenerateValues(1, 1, 1);
  
  // Map the contours to graphical primitives
  vtkSmartPointer<vtkPolyDataMapper> contourMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contours->GetOutputPort());
  contourMapper->ScalarVisibilityOff();
  
  // Create an actor for the contours
  vtkSmartPointer<vtkActor> contourActor = 
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
  
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  renderer->AddActor(contourActor);
  renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
  
  renderWindow->Render();
  interactor->Start();
    
  return EXIT_SUCCESS;
}
