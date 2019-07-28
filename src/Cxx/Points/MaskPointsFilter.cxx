#include <vtkSmartPointer.h>
#include <vtkMaskPointsFilter.h>
#include <vtkBoundedPointSource.h>
#include <vtkImageData.h>
#include <vtkCone.h>
#include <vtkSampleImplicitFunctionFilter.h>
#include <vtkImageThreshold.h>
#include <vtkBoundedPointSource.h>
#include <vtkMetaImageReader.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

static vtkSmartPointer<vtkImageData> CreatePoints();

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> imageMask;
  if (argc < 2)
  {
    imageMask = CreatePoints();
  }
  else
  {
    int upper = 1100;
    if (argc > 2)
    {
      upper = atoi(argv[2]);
    }
    // Read the volume data
    vtkSmartPointer<vtkMetaImageReader> reader =
      vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName (argv[1]);
    reader->Update();

    vtkSmartPointer<vtkImageThreshold> threshold =
      vtkSmartPointer<vtkImageThreshold>::New();
    threshold->SetInputConnection(reader->GetOutputPort());
    threshold->ThresholdByUpper(upper);
    threshold->SetOutputScalarTypeToUnsignedChar();
    threshold->ReplaceInOn();
    threshold->SetInValue(255);
    threshold->SetOutValue(0);
    threshold->ReplaceOutOn();
    threshold->Update();
    imageMask = dynamic_cast<vtkImageData*>(threshold->GetOutput());
  }
  vtkSmartPointer<vtkBoundedPointSource> pointSource =
    vtkSmartPointer<vtkBoundedPointSource>::New();
  pointSource->SetNumberOfPoints(100000);
  pointSource->SetBounds(imageMask->GetBounds());

  vtkSmartPointer<vtkMaskPointsFilter> maskPoints =
    vtkSmartPointer<vtkMaskPointsFilter>::New();
  maskPoints->SetInputConnection(pointSource->GetOutputPort());
  maskPoints->SetMaskData(imageMask);

  double radius = imageMask->GetSpacing()[0] * 4.0;
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(radius);

  vtkSmartPointer<vtkGlyph3D> glyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph->SetInputConnection(maskPoints->GetOutputPort());
  glyph->SetSourceConnection(sphereSource->GetOutputPort());
  glyph->ScalingOff();
  glyph->Update();

  vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyphMapper->SetInputConnection(glyph->GetOutputPort());
  glyphMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> glyphActor =
    vtkSmartPointer<vtkActor>::New();
  glyphActor->SetMapper(glyphMapper);
  glyphActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.3, .4, .6);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  
  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(glyphActor);

  // Generate an interesting view
  //
  ren1->GetActiveCamera()->SetPosition (1, 0, 0);
  ren1->GetActiveCamera()->SetFocalPoint (0, 1, 0);
  ren1->GetActiveCamera()->SetViewUp (0, 0, -1);
  ren1->GetActiveCamera()->Azimuth(30);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Dolly(1.0);
  ren1->ResetCameraClippingRange();

  renWin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

static vtkSmartPointer<vtkImageData> CreatePoints()
{
  vtkSmartPointer<vtkImageData> imageMask;

  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->SetDimensions(256,256,256);
  image->AllocateScalars(VTK_DOUBLE,1);
  image->SetSpacing(5.0/255.0, 5.0/255.0, 5.0/255.0);
  image->SetOrigin(-2.5, -2.5, -2.5);
  vtkSmartPointer<vtkCone> implicitFunction =
    vtkSmartPointer<vtkCone>::New();
  vtkSmartPointer<vtkSampleImplicitFunctionFilter> sample = 
    vtkSmartPointer<vtkSampleImplicitFunctionFilter>::New();
  sample->SetImplicitFunction(implicitFunction);
  sample->SetInputData(image);
  
  vtkSmartPointer<vtkImageThreshold> threshold =
    vtkSmartPointer<vtkImageThreshold>::New();
  threshold->SetInputConnection(sample->GetOutputPort());
  threshold->ThresholdByLower(.5);
  threshold->SetOutputScalarTypeToUnsignedChar();
  threshold->ReplaceInOn();
  threshold->SetInValue(255);
  threshold->SetOutValue(0);
  threshold->ReplaceOutOn();
  threshold->Update();
  imageMask = dynamic_cast<vtkImageData*>(threshold->GetOutput());
  return imageMask;
}
