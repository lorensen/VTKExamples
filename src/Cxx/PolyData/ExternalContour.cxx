#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkWindowToImageFilter.h>
#include <vtkContourFilter.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkVersion.h>

#include <vtkXMLPolyDataReader.h>


int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> data3d;

  if ( argc > 1 )
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (argv[1]);
    reader->Update();

    data3d = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> source =
      vtkSmartPointer<vtkSphereSource>::New();
    source->SetCenter(0.0, 0.0, 5.0);
    source->SetRadius(2.0);
    source->SetPhiResolution(20.);
    source->SetThetaResolution(20.);
    source->Update();

    data3d = source->GetOutput();
  }

  double bounds_data[6], center_data[3];
  data3d->GetBounds(bounds_data);
  data3d->GetCenter(center_data);

  // Black and white scene with the data in order to print the view
  vtkSmartPointer<vtkPolyDataMapper> mapper_data =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper_data->SetInputData(data3d);	

  vtkSmartPointer<vtkActor> actor_data =
    vtkSmartPointer<vtkActor>::New();
  actor_data->SetMapper(mapper_data);
  actor_data->GetProperty()->SetColor(0,0,0);

  vtkSmartPointer<vtkRenderer> tmp_rend =
    vtkSmartPointer<vtkRenderer>::New();
  tmp_rend->SetBackground(1,1,1);

  tmp_rend->AddActor(actor_data);
  tmp_rend->ResetCamera();
  tmp_rend->GetActiveCamera()->SetParallelProjection(1);

  vtkSmartPointer<vtkRenderWindow> tmp_rW =
    vtkSmartPointer<vtkRenderWindow>::New();
  tmp_rW->SetOffScreenRendering( 1 );
  tmp_rW->AddRenderer(tmp_rend);

  tmp_rW->Render();

  // Get a print of the window
  vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
    vtkSmartPointer<vtkWindowToImageFilter>::New();
  windowToImageFilter->SetInput(tmp_rW);
#if VTK_MAJOR_VERSION >= 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  windowToImageFilter->SetScale(2); // image quality
#else
  windowToImageFilter->SetMagnification(2); //image quality
#endif
  windowToImageFilter->Update();

  // Extract the silhouette corresponding to the black limit of the image
  vtkSmartPointer<vtkContourFilter> ContFilter = vtkSmartPointer<vtkContourFilter>::New();
  ContFilter->SetInputConnection(windowToImageFilter->GetOutputPort());
  ContFilter->SetValue(0,255);
  ContFilter->Update();

  // Make the contour coincide with the data.
  vtkSmartPointer<vtkPolyData> contour = ContFilter->GetOutput();

  double bounds_contour[6], center_contour[3];
  double trans_x=0., trans_y=0., trans_z=0., ratio_x=0., ratio_y=0.;
  contour->GetBounds(bounds_contour);

  ratio_x = (bounds_data[1]-bounds_data[0])/(bounds_contour[1]-bounds_contour[0]);
  ratio_y = (bounds_data[3]-bounds_data[2])/(bounds_contour[3]-bounds_contour[2]);

  // Rescale the contour so that it shares the same bounds as the
  // input data
  vtkSmartPointer<vtkTransform>transform1 =
    vtkSmartPointer<vtkTransform>::New();
  transform1->Scale( ratio_x, ratio_y, 1.);

  vtkSmartPointer<vtkTransformPolyDataFilter> tfilter1 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tfilter1->SetInputData(contour);
  tfilter1->SetTransform(transform1);
  tfilter1->Update();

  contour = tfilter1->GetOutput();

  // Translate the contour so that it shares the same center as the
  // input data
  contour->GetCenter(center_contour);
  trans_x = center_data[0]-center_contour[0];
  trans_y = center_data[1]-center_contour[1];
  trans_z = center_data[2]-center_contour[2];

  vtkSmartPointer<vtkTransform> transform2 =
    vtkSmartPointer<vtkTransform>::New();
  transform2->Translate( trans_x, trans_y, trans_z);

  vtkSmartPointer<vtkTransformPolyDataFilter> tfilter2 =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  tfilter2->SetInputData(contour);
  tfilter2->SetTransform(transform2);
  tfilter2->Update();

  contour = tfilter2->GetOutput();

  // Render the result : Input data + resulting silhouette

  // Updating the color of the data
  actor_data->GetProperty()->SetColor(0.9,0.9,0.8);

  // Create a mapper and actor of the silhouette
  vtkSmartPointer<vtkPolyDataMapper> mapper_contour =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper_contour->SetInputData(contour);

  vtkSmartPointer<vtkActor> actor_contour =
    vtkSmartPointer<vtkActor>::New();
  actor_contour->SetMapper(mapper_contour);
  actor_contour->GetProperty()->SetLineWidth(2.);

  // 2 renderers and a render window
  vtkSmartPointer<vtkRenderer> renderer1 =
    vtkSmartPointer<vtkRenderer>::New();
  renderer1->AddActor(actor_data);

  vtkSmartPointer<vtkRenderer> renderer2 =
    vtkSmartPointer<vtkRenderer>::New();
  renderer2->AddActor(actor_contour);

  vtkSmartPointer<vtkRenderWindow> renderwindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderwindow->SetSize(400,400);

  renderwindow->AddRenderer(renderer1);
  renderer1->SetViewport(0., 0., 0.5, 1.);

  renderwindow->AddRenderer(renderer2);
  renderer2->SetViewport(0.5, 0., 1., 1.);

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  iren->SetRenderWindow( renderwindow);
  iren->SetInteractorStyle(style);

  renderwindow->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
