#include <vtkActor.h>
#include <vtkContourFilter.h>
#include <vtkCutter.h>
#include <vtkExtractGrid.h>
#include <vtkLookupTable.h>
#include <vtkStripper.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkPlane.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkTubeFilter.h>
#include <vtkNamedColors.h>

// Perform psuedo volume rendering in a structured grid by compositing
// translucent cut planes. This same trick can be used for unstructured
// grids. Note that for better results, more planes can be created. Also,
// if your data is vtkImageData, there are much faster methods for volume
// rendering.

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " combxyz.bin combq.bin" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

// Create pipeline. Read structured grid data.
//
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->SetXYZFileName(argv[1]);
  pl3d->SetQFileName(argv[2]);
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->Update();

  vtkStructuredGrid *pl3dOutput =
    dynamic_cast<vtkStructuredGrid*>(pl3d->GetOutput()->GetBlock(0));

// A convenience, use this filter to limit data for experimentation.
  vtkSmartPointer<vtkExtractGrid> extract =
    vtkSmartPointer<vtkExtractGrid>::New();
  extract->SetVOI(1, 55, -1000, 1000, -1000, 1000);
  extract->SetInputData(pl3dOutput);

// The (implicit) plane is used to do the cutting
  vtkSmartPointer<vtkPlane> plane =
    vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(0, 4, 2);
  plane->SetNormal(0, 1, 0);

// The cutter is set up to process each contour value over all cells
// (SetSortByToSortByCell). This results in an ordered output of polygons
// which is key to the compositing.
  vtkSmartPointer<vtkCutter> cutter =
    vtkSmartPointer<vtkCutter>::New();
  cutter->SetInputConnection(extract->GetOutputPort());
  cutter->SetCutFunction(plane);
  cutter->GenerateCutScalarsOff();
  cutter->SetSortByToSortByCell();

  vtkSmartPointer<vtkLookupTable> clut =
    vtkSmartPointer<vtkLookupTable>::New();
  clut->SetHueRange(0, .67);
  clut->Build();

  vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cutterMapper->SetInputConnection(cutter->GetOutputPort());
  cutterMapper->SetScalarRange(.18, .7);
  cutterMapper->SetLookupTable(clut);

  vtkSmartPointer<vtkActor> cut =
    vtkSmartPointer<vtkActor>::New();
  cut->SetMapper(cutterMapper);

// Add in some surface geometry for interest.
  vtkSmartPointer<vtkContourFilter> iso =
    vtkSmartPointer<vtkContourFilter>::New();
  iso->SetInputData(pl3dOutput);
  iso->SetValue(0, .22);
  
  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(iso->GetOutputPort());
  normals->SetFeatureAngle(60);

  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(normals->GetOutputPort());
  isoMapper->ScalarVisibilityOff();
  
  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Tomato").GetData());
  isoActor->GetProperty()->SetSpecularColor(colors->GetColor3d("White").GetData());
  isoActor->GetProperty()->SetDiffuse(.8);
  isoActor->GetProperty()->SetSpecular(.5);
  isoActor->GetProperty()->SetSpecularPower(30);

  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputData(pl3dOutput);

  vtkSmartPointer<vtkStripper> outlineStrip =
    vtkSmartPointer<vtkStripper>::New();
  outlineStrip->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkTubeFilter> outlineTubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  outlineTubes->SetInputConnection(outline->GetOutputPort());
  outlineTubes->SetInputConnection(outlineStrip->GetOutputPort());
  outlineTubes->SetRadius(.1);

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outlineTubes->GetOutputPort());
  
  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);

// Create the RenderWindow, Renderer and Interactor
//
    vtkSmartPointer<vtkRenderer> ren1 =
      vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren1);
    vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();

    iren->SetRenderWindow(renWin);

// Add the actors to the renderer, set the background and size
//
    ren1->AddActor(outlineActor);
    outlineActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
    ren1->AddActor(isoActor);
    isoActor->VisibilityOn();
    ren1->AddActor(cut);

    unsigned int n = 20;
    double opacity = 1.0 / (static_cast<double>(n)) * 5.0;
    cut->GetProperty()->SetOpacity(1);
    ren1->SetBackground(colors->GetColor3d("Slategray").GetData());
    renWin->SetSize(640, 480);

  ren1->GetActiveCamera()->SetClippingRange(3.95297, 50);
  ren1->GetActiveCamera()->SetFocalPoint(9.71821, 0.458166, 29.3999);
  ren1->GetActiveCamera()->SetPosition(2.7439, -37.3196, 38.7167);
  ren1->GetActiveCamera()->ComputeViewPlaneNormal();
  ren1->GetActiveCamera()->SetViewUp(-0.16123, 0.264271, 0.950876);

// Cut: generates n cut planes normal to camera's view plane
//
    plane->SetNormal(ren1->GetActiveCamera()->GetViewPlaneNormal());
    plane->SetOrigin(ren1->GetActiveCamera()->GetFocalPoint());
    cutter->GenerateValues(n, -5, 5);
    clut->SetAlphaRange(opacity, opacity);
    renWin->Render();

    iren->Start();

    return EXIT_SUCCESS;
}
