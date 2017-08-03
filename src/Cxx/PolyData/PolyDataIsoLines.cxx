#include <vtkSmartPointer.h>
#include <vtkBandedPolyDataContourFilter.h>

#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cout << "Required arguments: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  //float range[2];
  double range[2];
  reader->GetOutput()->GetPointData()->GetScalars()->GetRange(range);
  //std::cout << "Range: " << range[0] << " , " << range[1] << std::endl;

  vtkSmartPointer<vtkBandedPolyDataContourFilter> bf =
    vtkSmartPointer<vtkBandedPolyDataContourFilter>::New();
  bf->SetInputConnection(reader->GetOutputPort());
  int numContours = 30;
  bf->GenerateValues(numContours, range);
  bf->GenerateContourEdgesOn();
  bf->Update();

  // Color the contours
  bf->GetOutput(1)->GetPointData()->SetScalars(bf->GetOutput()->GetPointData()->GetScalars());

  // Make sure the mapper uses the new colors
  bf->GetOutput(0)->GetPointData()->SetActiveScalars("Scalars");

  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(bf->GetOutputPort());
  writer->SetFileName("output.vtp");
  writer->Update();
  }

  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(bf->GetOutputPort(1));
  writer->SetFileName("ContourEdges.vtp");
  writer->Update();
  }

  /*
  // See which isocontours are being generated
  double values[10];
  bf->GetValues(values);
  for(unsigned int i = 0; i < 10; i++)
    {
    cout << values[i] << " ";
    }
  cout << endl;
  */


  // Color actor
  vtkSmartPointer<vtkPolyDataMapper> colorMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  colorMapper->SetInputConnection(bf->GetOutputPort(0));
  colorMapper->SetScalarRange(range);

  vtkSmartPointer<vtkActor> colorActor =
    vtkSmartPointer<vtkActor>::New();
  colorActor->SetMapper(colorMapper);

  // Edge actor
  vtkSmartPointer<vtkPolyDataMapper> edgeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  edgeMapper->SetInputConnection(bf->GetOutputPort(1));
  edgeMapper->SetScalarRange(range);

  vtkSmartPointer<vtkActor> edgeActor =
      vtkSmartPointer<vtkActor>::New();
  edgeActor->SetMapper(edgeMapper);
  edgeActor->GetProperty()->SetLineWidth(5);

  // Create the RenderWindow, Renderer and both Actors

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer
  renderer->AddActor(colorActor);
  renderer->AddActor(edgeActor);

  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
