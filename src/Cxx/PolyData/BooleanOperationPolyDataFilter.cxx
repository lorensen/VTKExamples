#include <vtkVersion.h>
#include <vtkBooleanOperationPolyDataFilter.h>

#include <vtkActor.h>
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> input1;
  vtkSmartPointer<vtkPolyData> input2;

  std::string operation("intersection");

  if (argc == 4)
  {
    vtkSmartPointer<vtkSTLReader> reader1 =
      vtkSmartPointer<vtkSTLReader>::New();
    reader1->SetFileName(argv[1]);
    reader1->Update();
    input1 = reader1->GetOutput();

    vtkSmartPointer<vtkSTLReader> reader2 =
      vtkSmartPointer<vtkSTLReader>::New();
    reader2->SetFileName(argv[3]);
    reader2->Update();
    input2 = reader2->GetOutput();

    operation = argv[2];
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource1 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource1->SetCenter(.25, 0, 0);
    sphereSource1->Update();
    input1 = sphereSource1->GetOutput();

    vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource2->Update();
    input2 = sphereSource2->GetOutput();

    if (argc == 2)
    {
      operation = argv[1];
    }
  }

  vtkSmartPointer<vtkPolyDataMapper> input1Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  input1Mapper->SetInputConnection( input1->GetProducerPort() );
#else
  input1Mapper->SetInputData( input1 );
#endif
  input1Mapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> input1Actor =
    vtkSmartPointer<vtkActor>::New();
  input1Actor->SetMapper( input1Mapper );
  input1Actor->GetProperty()->SetColor(1,0,0);
  input1Actor->SetPosition(
    input1->GetBounds()[1]-input1->GetBounds()[0],
    0, 0);
  vtkSmartPointer<vtkPolyDataMapper> input2Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  input2Mapper->SetInputConnection( input2->GetProducerPort() );
#else
  input2Mapper->SetInputData( input2 );
#endif
  input2Mapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> input2Actor =
    vtkSmartPointer<vtkActor>::New();
  input2Actor->SetMapper( input2Mapper );
  input2Actor->GetProperty()->SetColor(0,1,0);
  input2Actor->SetPosition(
    -2.0 * (input2->GetBounds()[1]-input2->GetBounds()[0]),
    0, 0);
  vtkSmartPointer<vtkBooleanOperationPolyDataFilter> booleanOperation =
    vtkSmartPointer<vtkBooleanOperationPolyDataFilter>::New();
  if (operation == "union")
  {
      booleanOperation->SetOperationToUnion();
  }
  else if (operation == "intersection")
  {
      booleanOperation->SetOperationToIntersection();
  }
  else if (operation == "difference")
  {
      booleanOperation->SetOperationToDifference();
  }
  else
  {
    std::cout << "Unknown operation: " << operation << std::endl;
    return EXIT_FAILURE;
  }
#if VTK_MAJOR_VERSION <= 5
  booleanOperation->SetInputConnection( 0, input1->GetProducerPort() );
  booleanOperation->SetInputConnection( 1, input2->GetProducerPort() );
#else
  booleanOperation->SetInputData( 0, input1 );
  booleanOperation->SetInputData( 1, input2 );
#endif
  vtkSmartPointer<vtkPolyDataMapper> booleanOperationMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  booleanOperationMapper->SetInputConnection( booleanOperation->GetOutputPort() );
  booleanOperationMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> booleanOperationActor =
    vtkSmartPointer<vtkActor>::New();
  booleanOperationActor->SetMapper( booleanOperationMapper );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
//  renderer->AddViewProp(input1Actor);
//  renderer->AddViewProp(input2Actor);
  renderer->AddViewProp(booleanOperationActor);
  renderer->SetBackground(.1, .2, .3);
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renWinInteractor->Start();

  return EXIT_SUCCESS;
}
