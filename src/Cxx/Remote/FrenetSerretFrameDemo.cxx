#include <vtkSplineWidget.h>
#include <vtkSmartPointer.h>

#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkGlyph3D.h>
#include <vtkArrowSource.h>
#include <vtkMaskPoints.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkFrenetSerretFrame.h>

#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

namespace
{
void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph);
}

struct Pipeline {
  vtkFrenetSerretFrame *frame;

  vtkGlyph3D           *glyph3DNormals;
  vtkGlyph3D           *glyph3DTangents;
  vtkGlyph3D           *glyph3DBinormals;

  vtkPolyDataMapper    *glyph3DNormalsMapper;
  vtkPolyDataMapper    *glyph3DTangentsMapper;
  vtkPolyDataMapper    *glyph3DBinormalsMapper;
};

static void SplineCallback(vtkObject *caller,
                           long unsigned int vtkNotUsed(eventId),
                           void *clientData,
                           void *vtkNotUsed(callData))
{
  vtkSplineWidget *splineWidget =
    static_cast<vtkSplineWidget *>(caller);
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  splineWidget->GetPolyData(polyData.GetPointer());

  Pipeline *pipeline =
    static_cast<Pipeline *>(clientData);

  pipeline->frame->SetInputData(polyData);

  vtkSmartPointer<vtkMaskPoints> maskPoints =
    vtkSmartPointer<vtkMaskPoints>::New();
  maskPoints->SetInputConnection(pipeline->frame->GetOutputPort());
  maskPoints->SetOnRatio(10);
  maskPoints->Update();

  // for each vector, create a Glyph3D and DeepCopy the output
  double radius = .1;
  maskPoints->GetOutput()->GetPointData()->SetActiveVectors("FSNormals");
  MakeGlyphs(maskPoints->GetOutput(), radius, pipeline->glyph3DNormals);
  vtkSmartPointer<vtkPolyData> normalsPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  normalsPolyData->DeepCopy(pipeline->glyph3DNormals->GetOutput());

  maskPoints->GetOutput()->GetPointData()->SetActiveVectors("FSTangents");
  MakeGlyphs(maskPoints->GetOutput(), radius, pipeline->glyph3DTangents);
  vtkSmartPointer<vtkPolyData> tangentsPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  tangentsPolyData->DeepCopy(pipeline->glyph3DTangents->GetOutput());

  maskPoints->GetOutput()->GetPointData()->SetActiveVectors("FSBinormals");
  MakeGlyphs(maskPoints->GetOutput(), radius, pipeline->glyph3DBinormals);
  vtkSmartPointer<vtkPolyData> binormalsPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  binormalsPolyData->DeepCopy(pipeline->glyph3DBinormals->GetOutput());

  pipeline->glyph3DNormalsMapper->SetInputData(normalsPolyData);
  pipeline->glyph3DTangentsMapper->SetInputData(tangentsPolyData);
  pipeline->glyph3DBinormalsMapper->SetInputData(binormalsPolyData);
}

int main(int, char *[])
{
  // Create the frame
  vtkSmartPointer<vtkFrenetSerretFrame> frame =
    vtkSmartPointer<vtkFrenetSerretFrame>::New();
  frame->ConsistentNormalsOn();

  // Define the glyph3D's
  vtkSmartPointer<vtkGlyph3D> glyph3DNormals =
    vtkSmartPointer<vtkGlyph3D>::New();
  vtkSmartPointer<vtkGlyph3D> glyph3DTangents =
    vtkSmartPointer<vtkGlyph3D>::New();
  vtkSmartPointer<vtkGlyph3D> glyph3DBinormals =
    vtkSmartPointer<vtkGlyph3D>::New();

  vtkSmartPointer<vtkPolyDataMapper> glyph3DNormalsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkPolyDataMapper> glyph3DTangentsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkPolyDataMapper> glyph3DBinormalsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();

  // Populate the pipeline object
  Pipeline pipeline;
  pipeline.glyph3DNormals = glyph3DNormals.GetPointer();
  pipeline.glyph3DTangents = glyph3DTangents.GetPointer();
  pipeline.glyph3DBinormals = glyph3DBinormals.GetPointer();
  pipeline.frame = frame.GetPointer();
  pipeline.glyph3DNormalsMapper = glyph3DNormalsMapper.GetPointer();
  pipeline.glyph3DTangentsMapper = glyph3DTangentsMapper.GetPointer();
  pipeline.glyph3DBinormalsMapper = glyph3DBinormalsMapper.GetPointer();

  // Define the actors
  vtkSmartPointer<vtkActor> glyph3DNormalsActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DNormalsActor->SetMapper(glyph3DNormalsMapper);
  glyph3DNormalsActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);

  vtkSmartPointer<vtkActor> glyph3DTangentsActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DTangentsActor->SetMapper(glyph3DTangentsMapper);
  glyph3DTangentsActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

  vtkSmartPointer<vtkActor> glyph3DBinormalsActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DBinormalsActor->SetMapper(glyph3DBinormalsMapper);
  glyph3DBinormalsActor->GetProperty()->SetColor(0.1804,0.5451,0.3412);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // The spline widget
  vtkSmartPointer<vtkSplineWidget> splineWidget = 
    vtkSmartPointer<vtkSplineWidget>::New();
  splineWidget->SetInteractor(renderWindowInteractor);

  // The callback does the work
  vtkSmartPointer<vtkCallbackCommand> splineCallback =
      vtkSmartPointer<vtkCallbackCommand>::New();
    splineCallback->SetCallback (SplineCallback);
    splineCallback->SetClientData(&pipeline);
    splineWidget->AddObserver(vtkCommand::StartInteractionEvent,splineCallback);
    splineWidget->AddObserver(vtkCommand::InteractionEvent,splineCallback);
    splineWidget->AddObserver(vtkCommand::EndInteractionEvent,splineCallback);

    // Add the actors
  renderer->AddActor(glyph3DNormalsActor);
  renderer->AddActor(glyph3DTangentsActor);
  renderer->AddActor(glyph3DBinormalsActor);

  renderWindowInteractor->Initialize();
  renderWindow->Render();

  // Prime the pipeline
  splineWidget->SetHandlePosition(2, 0, .5, 0);
  splineWidget->On();
  SplineCallback(splineWidget, 0, &pipeline, 0);

  renderWindow->Render();
  renderer->ResetCamera();
  renderer->SetBackground(.4, .5, .7);
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}

namespace
{
void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph)
{
  // Source for the glyph filter
  vtkSmartPointer<vtkArrowSource> arrow =
    vtkSmartPointer<vtkArrowSource>::New();
  arrow->SetTipResolution(16);
  arrow->SetTipLength(.3);
  arrow->SetTipRadius(.1);

  glyph->SetSourceConnection(arrow->GetOutputPort());
  glyph->SetInputData(src);
  glyph->SetVectorModeToUseVector();
  glyph->SetScaleModeToScaleByVector();
  glyph->SetScaleFactor(size);
  glyph->OrientOn();
  glyph->Update();
}
}
