// This example demonstrates the use of vtkXYPlotActor to display three
// probe lines using three different techniques.  In this example, we
// are loading data using the vtkPLOT3DReader.  We are using the
// vtkProbeFilter to extract the underlying point data along three
// probe lines.

#include <vtkSmartPointer.h>
#include <vtkXYPlotActor.h>

#include <vtkAppendPolyData.h>
#include <vtkLineSource.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkProbeFilter.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTubeFilter.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty2D.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTextProperty.h>
#include <vtkNamedColors.h>

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " combxyz.bin combq.bin" << std::endl;
    return EXIT_FAILURE;
  }

// Create a PLOT3D reader and load the data.
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  pl3d->SetXYZFileName(argv[1]);
  pl3d->SetQFileName(argv[2]);
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->Update();

  vtkStructuredGrid* pl3d_output =
    dynamic_cast<vtkStructuredGrid*>(pl3d->GetOutput()->GetBlock(0));

// Create three the line source to use for the probe lines.
  vtkSmartPointer<vtkLineSource> line =
    vtkSmartPointer<vtkLineSource>::New();
  line->SetResolution(30);

// Move the line into place and create the probe filter.  For
// vtkProbeFilter, the probe line is the input, and the underlying data
// set is the source.
  vtkSmartPointer<vtkTransform> transL1 =
    vtkSmartPointer<vtkTransform>::New();
  transL1->Translate(3.7, 0.0, 28.37);
  transL1->Scale(5, 5, 5);
  transL1->RotateY(90);

  vtkSmartPointer<vtkTransformPolyDataFilter> tf =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tf->SetInputConnection(line->GetOutputPort());
  tf->SetTransform(transL1);

  vtkSmartPointer<vtkProbeFilter> probe =
    vtkSmartPointer<vtkProbeFilter>::New();
  probe->SetInputConnection(tf->GetOutputPort());
  probe->SetSourceData(pl3d_output);

// Move the line again and create another probe filter.
  vtkSmartPointer<vtkTransform> transL2 =
    vtkSmartPointer<vtkTransform>::New();
  transL2->Translate(9.2, 0.0, 31.20);
  transL2->Scale(5, 5, 5);
  transL2->RotateY(90);

  vtkSmartPointer<vtkTransformPolyDataFilter>tf2 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tf2->SetInputConnection(line->GetOutputPort());
  tf2->SetTransform(transL2);
  vtkSmartPointer<vtkProbeFilter> probe2 =
    vtkSmartPointer<vtkProbeFilter>::New();
  probe2->SetInputConnection(tf2->GetOutputPort());
  probe2->SetSourceData(pl3d_output);

// Move the line again and create a third probe filter.
  vtkSmartPointer<vtkTransform> transL3 =
    vtkSmartPointer<vtkTransform>::New();
  transL3->Translate(13.27, 0.0, 33.40);
  transL3->Scale(4.5, 4.5, 4.5);
  transL3->RotateY(90);
  vtkSmartPointer<vtkTransformPolyDataFilter> tf3 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tf3->SetInputConnection(line->GetOutputPort());
  tf3->SetTransform(transL3);
  vtkSmartPointer<vtkProbeFilter> probe3 =
    vtkSmartPointer<vtkProbeFilter>::New();
  probe3->SetInputConnection(tf3->GetOutputPort());
  probe3->SetSourceData(pl3d_output);

// Create a vtkAppendPolyData to merge the output of the three probe
// filters into one data set.
  vtkSmartPointer<vtkAppendPolyData> appendF =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendF->AddInputConnection(probe->GetOutputPort());
  appendF->AddInputConnection(probe2->GetOutputPort());
  appendF->AddInputConnection(probe3->GetOutputPort());

// Create a tube filter to represent the lines as tubes.  Set up the
// associated mapper and actor.
  vtkSmartPointer<vtkTubeFilter> tuber =
    vtkSmartPointer<vtkTubeFilter>::New();
  tuber->SetInputConnection(appendF->GetOutputPort());
  tuber->SetRadius(0.1);
  vtkSmartPointer<vtkPolyDataMapper> lineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputConnection(tuber->GetOutputPort());
  vtkSmartPointer<vtkActor> lineActor =
    vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);

// Create an xy-plot using the output of the 3 probe filters as input.
// The x-values we are plotting are arc length.
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkXYPlotActor> xyplot =
    vtkSmartPointer<vtkXYPlotActor>::New();
  xyplot->AddDataSetInputConnection(probe->GetOutputPort());
  xyplot->AddDataSetInputConnection(probe2->GetOutputPort());
  xyplot->AddDataSetInputConnection(probe3->GetOutputPort());
  xyplot->GetPositionCoordinate()->SetValue(0.0, 0.67, 0);
  xyplot->GetPosition2Coordinate()->SetValue(1.0, 0.33, 0); //relative to Position;
  xyplot->SetXValuesToArcLength();
  xyplot->SetNumberOfXLabels(6);
  xyplot->SetTitle("Pressure vs. Arc Length (Zoomed View)");
  xyplot->SetXTitle("");
  xyplot->SetYTitle("P");
  xyplot->SetXRange(.1, .35);
  xyplot->SetYRange(.2, .4);
  xyplot->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());
  xyplot->GetProperty()->SetLineWidth(2);
// Set text prop color
// Assign same object to all text props
  vtkTextProperty *tprop = xyplot->GetTitleTextProperty();
  tprop->SetColor(xyplot->GetProperty()->GetColor());
  xyplot->SetAxisTitleTextProperty(tprop);
  xyplot->SetAxisLabelTextProperty(tprop);

// Create an xy-plot using the output of the 3 probe filters as input.
// The x-values we are plotting are normalized arc length.
  vtkSmartPointer<vtkXYPlotActor> xyplot2 =
    vtkSmartPointer<vtkXYPlotActor>::New();
  xyplot2->AddDataSetInputConnection(probe->GetOutputPort());
  xyplot2->AddDataSetInputConnection(probe2->GetOutputPort());
  xyplot2->AddDataSetInputConnection(probe3->GetOutputPort());
  xyplot2->GetPositionCoordinate()->SetValue(0.00, 0.33, 0);
  xyplot2->GetPosition2Coordinate()->SetValue(1.0, 0.33, 0); //relative to Position;
  xyplot2->SetXValuesToNormalizedArcLength();
  xyplot2->SetNumberOfXLabels(6);
  xyplot2->SetTitle("Pressure vs. Normalized Arc Length");
  xyplot2->SetXTitle("");
  xyplot2->SetYTitle("P");
  xyplot2->PlotPointsOn();
  xyplot2->PlotLinesOff();
  xyplot2->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  xyplot2->GetProperty()->SetPointSize(5);
// Set text prop color
// Assign same object to all text props
  tprop = xyplot2->GetTitleTextProperty();
  tprop->SetColor(xyplot2->GetProperty()->GetColor());
  xyplot2->SetAxisTitleTextProperty(tprop);
  xyplot2->SetAxisLabelTextProperty(tprop);

// Create an xy-plot using the output of the 3 probe filters as input.
// The x-values we are plotting are the underlying point data values.
  vtkSmartPointer<vtkXYPlotActor> xyplot3 =
    vtkSmartPointer<vtkXYPlotActor>::New();
  xyplot3->AddDataSetInputConnection(probe->GetOutputPort());
  xyplot3->AddDataSetInputConnection(probe2->GetOutputPort());
  xyplot3->AddDataSetInputConnection(probe3->GetOutputPort());
  xyplot3->GetPositionCoordinate()->SetValue(0.0, 0.0, 0);
  xyplot3->GetPosition2Coordinate()->SetValue(1.0, 0.33, 0); // relative to Position;
    xyplot3->SetXValuesToIndex();
  xyplot3->SetNumberOfXLabels(6);
  xyplot3->SetTitle("Pressure vs. Point Id");
  xyplot3->SetXTitle("Probe Length");
  xyplot3->SetYTitle("P");
  xyplot3->PlotPointsOn();
  xyplot3->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());
  xyplot3->GetProperty()->SetPointSize(3);
// Set text prop color
// Assign same object to all text props
  tprop = xyplot3->GetTitleTextProperty();
  tprop->SetColor(xyplot3->GetProperty()->GetColor());
  xyplot3->SetAxisTitleTextProperty(tprop);
  xyplot3->SetAxisLabelTextProperty(tprop);

// Draw an outline of the PLOT3D data set.
  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputData(pl3d_output);
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

// Create the Renderers, RenderWindow, and RenderWindowInteractor.
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderer> renderer2 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->AddRenderer(renderer2);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

// Set the background, viewport (necessary because we want to have the
// renderers draw to different parts of the render window) of the first
// renderer.  Add the outline and line actors to the renderer.
  renderer->SetBackground(colors->GetColor3d("blue_light").GetData());
  renderer->SetViewport(0, 0, .5, 1);
  renderer->AddActor(outlineActor);
  renderer->AddActor(lineActor);

// Set the background and viewport of the second renderer.  Add the
// xy-plot actors to the renderer.  Set the size of the render window.
  renderer2->SetBackground(colors->GetColor3d("silver").GetData());
  renderer2->SetViewport(0.5, 0.0, 1.0, 1.0);
  renderer2->AddActor2D(xyplot);
  renderer2->AddActor2D(xyplot2);
  renderer2->AddActor2D(xyplot3);
  renderWindow->SetSize(800, 600);

// Set up the camera parameters.
  vtkCamera *cam1 = renderer->GetActiveCamera();
  cam1->SetClippingRange(3.95297, 100);
  cam1->SetFocalPoint(8.88908, 0.595038, 29.3342);
  cam1->SetPosition(-12.3332, 31.7479, 41.2387);
  cam1->SetViewUp(0.060772, -0.319905, 0.945498);

  interactor->Initialize();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
