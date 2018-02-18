#include <vtkActor.h>
#include <vtkAxes.h>
#include <vtkCamera.h>
#include <vtkDataObjectReader.h>
#include <vtkDataObjectToDataSetFilter.h>
#include <vtkFieldDataToAttributeDataFilter.h>
#include <vtkFollower.h>
#include <vtkGaussianSplatter.h>
#include <vtkImageData.h>
#include <vtkMarchingContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTubeFilter.h>
#include <vtkVectorText.h>

#include <vtkNamedColors.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " financial.vtk" << std::endl;
    return EXIT_FAILURE;
  }
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkDataObjectReader> reader =
    vtkSmartPointer<vtkDataObjectReader>::New();
  reader->SetFileName(argv[1]);

  int size = 3187;  // maximum number possible

  std::string xAxis = "INTEREST_RATE";
  std::string yAxis = "MONTHLY_PAYMENT";
  std::string zAxis = "MONTHLY_INCOME";
  std::string scalar = "TIME_LATE";

// extract data from field as a polydata (just points), then extract scalars
  vtkSmartPointer<vtkDataObjectToDataSetFilter> do2ds =
    vtkSmartPointer<vtkDataObjectToDataSetFilter>::New();
  do2ds->SetInputConnection(reader->GetOutputPort());
  do2ds->SetDataSetTypeToPolyData();
//format: component//, arrayname, arraycomp, minArrayId, maxArrayId, normalize
  do2ds->DefaultNormalizeOn();
  do2ds->SetPointComponent(0, const_cast<char *>(xAxis.c_str()), 0);
  do2ds->SetPointComponent(1, const_cast<char *>(yAxis.c_str()), 0, 0, size, 1);
  do2ds->SetPointComponent(2, const_cast<char *>(zAxis.c_str()), 0);
  do2ds->Update();
  vtkSmartPointer<vtkFieldDataToAttributeDataFilter> fd2ad =
    vtkSmartPointer<vtkFieldDataToAttributeDataFilter>::New();
  fd2ad->SetInputConnection(do2ds->GetOutputPort());
  fd2ad->SetInputFieldToDataObjectField();
  fd2ad->SetOutputAttributeDataToPointData();
  fd2ad->DefaultNormalizeOn();
  fd2ad->SetScalarComponent(0, scalar.c_str(), 0);

  // construct pipeline for original population
  vtkSmartPointer<vtkGaussianSplatter> popSplatter =
    vtkSmartPointer<vtkGaussianSplatter>::New();
  popSplatter->SetInputConnection(fd2ad->GetOutputPort());
  popSplatter->SetSampleDimensions(150, 150, 150);
  popSplatter->SetRadius(0.05);
  popSplatter->ScalarWarpingOff();

  vtkSmartPointer<vtkMarchingContourFilter> popSurface = 
    vtkSmartPointer<vtkMarchingContourFilter>::New();
  popSurface->SetInputConnection(popSplatter->GetOutputPort());
  popSurface->SetValue(0, 0.01);
  vtkSmartPointer<vtkPolyDataMapper> popMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  popMapper->SetInputConnection(popSurface->GetOutputPort());
  popMapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> popActor =
    vtkSmartPointer<vtkActor>::New();
  popActor->SetMapper(popMapper);
  popActor->GetProperty()->SetOpacity(0.3);
  popActor->GetProperty()->SetColor(colors->GetColor3d("Gold").GetData());

  // construct pipeline for delinquent population
  vtkSmartPointer<vtkGaussianSplatter> lateSplatter = 
    vtkSmartPointer<vtkGaussianSplatter>::New();
  lateSplatter->SetInputConnection(fd2ad->GetOutputPort());
  lateSplatter->SetSampleDimensions(150, 150, 150);
  lateSplatter->SetRadius(0.05);
  lateSplatter->SetScaleFactor(0.05);

  vtkSmartPointer<vtkMarchingContourFilter> lateSurface = 
    vtkSmartPointer<vtkMarchingContourFilter>::New();
  lateSurface->SetInputConnection(lateSplatter->GetOutputPort());
  lateSurface->SetValue(0, 0.01);
  vtkSmartPointer<vtkPolyDataMapper> lateMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lateMapper->SetInputConnection(lateSurface->GetOutputPort());
  lateMapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> lateActor =
    vtkSmartPointer<vtkActor>::New();
  lateActor->SetMapper(lateMapper);
  lateActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

  // create axes
  popSplatter->Update();
  double *bounds;
  bounds = popSplatter->GetOutput()->GetBounds();
  vtkSmartPointer<vtkAxes>  axes = 
    vtkSmartPointer<vtkAxes>::New();
  axes->SetOrigin(bounds[0], bounds[2], bounds[4]);
  axes->SetScaleFactor(popSplatter->GetOutput()->GetLength() / 5.0);
    vtkSmartPointer<vtkTubeFilter> axesTubes = 
      vtkSmartPointer<vtkTubeFilter>::New();
    axesTubes->SetInputConnection(axes->GetOutputPort());
    axesTubes->SetRadius(axes->GetScaleFactor() / 25.0);
    axesTubes->SetNumberOfSides(6);
    vtkSmartPointer<vtkPolyDataMapper> axesMapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
    axesMapper->SetInputConnection(axesTubes->GetOutputPort());
    vtkSmartPointer<vtkActor> axesActor =
      vtkSmartPointer<vtkActor>::New();
    axesActor->SetMapper(axesMapper);

    // label the axes
    vtkSmartPointer<vtkVectorText> XText = 
      vtkSmartPointer<vtkVectorText>::New();
    XText->SetText(const_cast<char *>(xAxis.c_str()));
    vtkSmartPointer<vtkPolyDataMapper> XTextMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    XTextMapper->SetInputConnection(XText->GetOutputPort());

    vtkSmartPointer<vtkFollower> XActor =
      vtkSmartPointer<vtkFollower>::New();
    XActor->SetMapper(XTextMapper);
    XActor->SetScale(0.02, .02, .02);
    XActor->SetPosition(0.35, -0.05, -0.05);
    XActor->GetProperty()->SetColor(0, 0, 0);

    vtkSmartPointer<vtkVectorText> YText = 
      vtkSmartPointer<vtkVectorText>::New();
    YText->SetText(const_cast<char *>(yAxis.c_str()));

    vtkSmartPointer<vtkPolyDataMapper> YTextMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    YTextMapper->SetInputConnection(YText->GetOutputPort());
    vtkSmartPointer<vtkFollower> YActor = 
      vtkSmartPointer<vtkFollower>::New();
    YActor->SetMapper(YTextMapper);
    YActor->SetScale(0.02, .02, .02);
    YActor->SetPosition(-0.05, 0.35, -0.05);
    YActor->GetProperty()->SetColor(0, 0, 0);

    vtkSmartPointer<vtkVectorText> ZText = 
      vtkSmartPointer<vtkVectorText>::New();
    ZText->SetText(const_cast<char *>(zAxis.c_str()));
    vtkSmartPointer <vtkPolyDataMapper> ZTextMapper =
      vtkSmartPointer <vtkPolyDataMapper>::New();
    ZTextMapper->SetInputConnection(ZText->GetOutputPort());
    vtkSmartPointer<vtkFollower> ZActor = 
      vtkSmartPointer<vtkFollower>::New();
    ZActor->SetMapper(ZTextMapper);
    ZActor->SetScale(0.02, .02, .02);
    ZActor->SetPosition(-0.05, -0.05, 0.35);
    ZActor->GetProperty()->SetColor(0, 0, 0);

    // Graphics stuff
    //
    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = 
      vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("vtk - Field.Data");

    // Add the actors to the renderer, set the background and size
    //
    renderer->AddActor(axesActor);
    renderer->AddActor(lateActor);
    renderer->AddActor(XActor);
    renderer->AddActor(YActor);
    renderer->AddActor(ZActor);
    renderer->AddActor(popActor);
    renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
    renderWindow->SetSize(650, 480);

    vtkSmartPointer<vtkCamera> camera =
      vtkSmartPointer<vtkCamera>::New();
    camera->SetClippingRange(.274, 13.72);
    camera->SetFocalPoint(0.433816, 0.333131, 0.449);
    camera->SetPosition(-1.96987, 1.15145, 1.49053);
    camera->SetViewUp(0.378927, 0.911821, 0.158107);
    renderer->SetActiveCamera(camera);
    XActor->SetCamera(camera);
    YActor->SetCamera(camera);
    ZActor->SetCamera(camera);

    // render and interact with data

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);
    renderWindow->Render();
    interactor->Start();
    return EXIT_SUCCESS;
}
