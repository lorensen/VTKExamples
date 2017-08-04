#include <vtkSmartPointer.h>
#include <vtkContourFilter.h>

#include <vtkInteractorStyleUser.h>
#include <vtkProperty.h>
#include <vtkOutlineFilter.h>
#include <vtkCommand.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkImageData.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkNamedColors.h>


namespace
{
void CreateData(vtkImageData* data);

class vtkSliderCallback : public vtkCommand
{
public:
  static vtkSliderCallback *New()
  {
    return new vtkSliderCallback;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue();
    this->ContourFilter->GenerateValues(1, value, value);

  }
  vtkSliderCallback():ContourFilter(NULL) {}
  vtkContourFilter* ContourFilter;
};
}

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkImageData> data =
    vtkSmartPointer<vtkImageData>::New();
  CreateData(data);

  // Create an isosurface
  vtkSmartPointer<vtkContourFilter> contourFilter =
    vtkSmartPointer<vtkContourFilter>::New();
  contourFilter->SetInputData(data);
  contourFilter->GenerateValues(1, 10, 10); // (numContours, rangeStart, rangeEnd)

  // Map the contours to graphical primitives
  vtkSmartPointer<vtkPolyDataMapper> contourMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contourFilter->GetOutputPort());

  // Create an actor for the contours
  vtkSmartPointer<vtkActor> contourActor =
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
  contourActor->GetProperty()->SetLineWidth(5);

  // Create the outline
  vtkSmartPointer<vtkOutlineFilter> outlineFilter =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outlineFilter->SetInputData(data);

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outlineFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Gray").GetData());
  outlineActor->GetProperty()->SetLineWidth(3);

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
  renderer->AddActor(outlineActor);
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());

  vtkSmartPointer<vtkSliderRepresentation3D> sliderRep =
    vtkSmartPointer<vtkSliderRepresentation3D>::New();
  sliderRep->SetMinimumValue(0.0);
  sliderRep->SetMaximumValue(30.0);
  sliderRep->SetValue(10.0);
  sliderRep->SetTitleText("Contour value");
  sliderRep->SetPoint1InWorldCoordinates(-20, -40, 0);
  sliderRep->SetPoint2InWorldCoordinates(0, -40, 0);
  sliderRep->SetSliderWidth(.2);
  sliderRep->SetLabelHeight(.1);

  vtkSmartPointer<vtkSliderWidget> sliderWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidget->SetInteractor(interactor);
  sliderWidget->SetRepresentation(sliderRep);
  sliderWidget->SetAnimationModeToAnimate();
  sliderWidget->EnabledOn();

  vtkSmartPointer<vtkSliderCallback> callback =
    vtkSmartPointer<vtkSliderCallback>::New();
  callback->ContourFilter = contourFilter;

  sliderWidget->AddObserver(vtkCommand::InteractionEvent,callback);

  vtkSmartPointer<vtkInteractorStyleUser> style =
    vtkSmartPointer<vtkInteractorStyleUser>::New();
  interactor->SetInteractorStyle(style);

  renderWindow->SetSize(500,500);
  renderWindow->Render();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
namespace
{
void CreateData(vtkImageData* data)
{
  data->SetExtent(-25,25,-25,25,0,0);
  data->AllocateScalars(VTK_DOUBLE,1);
  int* extent = data->GetExtent();

  for (int y = extent[2]; y <= extent[3]; y++)
  {
    for (int x = extent[0]; x <= extent[1]; x++)
    {
      double* pixel = static_cast<double*>(data->GetScalarPointer(x,y,0));
      pixel[0] = sqrt(pow(x,2.0) + pow(y,2.0));
    }
  }

  vtkSmartPointer<vtkXMLImageDataWriter> writer =
    vtkSmartPointer<vtkXMLImageDataWriter>::New();
  writer->SetFileName("data.vti");
  writer->SetInputData(data);
  writer->Write();
}
}
