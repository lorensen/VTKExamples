#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkDistancePolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataReader.h>
#include <vtkCleanPolyData.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkScalarBarActor.h>
#include <vtkSphereSource.h>

#include <vtkNamedColors.h>

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkPolyData> input1;
  vtkSmartPointer<vtkPolyData> input2;
  if (argc == 3)
  {
//     std::cerr << "Usage: " << argv[0]
//               << " filename1.vtk"
//               << " filename2.vtk" << std::endl;
    vtkSmartPointer<vtkPolyDataReader> reader1 =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader1->SetFileName(argv[1]);
    reader1->Update();
    input1 = reader1->GetOutput();

    vtkSmartPointer<vtkPolyDataReader> reader2 =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader2->SetFileName(argv[2]);
    reader2->Update();
    input2 = reader2->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource1 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource1->SetCenter(1, 0, 0);
    sphereSource1->SetPhiResolution(21);
    sphereSource1->SetThetaResolution(21);
    sphereSource1->Update();
    input1 = sphereSource1->GetOutput();

    vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource2->SetPhiResolution(21);
    sphereSource2->SetThetaResolution(21);
    sphereSource2->Update();
    input2 = sphereSource2->GetOutput();
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkCleanPolyData> clean1 =
    vtkSmartPointer<vtkCleanPolyData>::New();
  clean1->SetInputData( input1);

  vtkSmartPointer<vtkCleanPolyData> clean2 =
    vtkSmartPointer<vtkCleanPolyData>::New();
  clean2->SetInputData( input2);

  vtkSmartPointer<vtkDistancePolyDataFilter> distanceFilter =
    vtkSmartPointer<vtkDistancePolyDataFilter>::New();

  distanceFilter->SetInputConnection( 0, clean1->GetOutputPort() );
  distanceFilter->SetInputConnection( 1, clean2->GetOutputPort() );
  distanceFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection( distanceFilter->GetOutputPort() );
  mapper->SetScalarRange(
    distanceFilter->GetOutput()->GetPointData()->GetScalars()->GetRange()[0],
    distanceFilter->GetOutput()->GetPointData()->GetScalars()->GetRange()[1]);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );

  vtkSmartPointer<vtkScalarBarActor> scalarBar =
    vtkSmartPointer<vtkScalarBarActor>::New();
  scalarBar->SetLookupTable(mapper->GetLookupTable());
  scalarBar->SetTitle("Distance");
  scalarBar->SetNumberOfLabels(4);
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderer->SetBackground2(colors->GetColor3d("Gold").GetData());
  renderer->GradientBackgroundOn();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renWin );

  renderer->AddActor( actor );
  renderer->AddActor2D(scalarBar);

  renWin->Render();
  renWinInteractor->Start();

  return EXIT_SUCCESS;
}
