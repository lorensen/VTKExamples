#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkElevationFilter.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkDeformPointSet.h>
#include <vtkCamera.h>
#include <vtkXMLPolyDataReader.h>

int main( int argc, char *argv[] )
{
  vtkSmartPointer<vtkPolyData> input =
    vtkSmartPointer<vtkPolyData>::New();
  double bounds[6];

  if(argc == 1)
  {
    // Create a sphere to warp
    vtkSmartPointer<vtkSphereSource> sphere =
      vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetThetaResolution(51);
    sphere->SetPhiResolution(17);
    sphere->Update();
    sphere->GetOutput()->GetBounds(bounds);

    // Generate some scalars on the polydata
    vtkSmartPointer<vtkElevationFilter> ele =
      vtkSmartPointer<vtkElevationFilter>::New();
    ele->SetInputConnection(sphere->GetOutputPort());
    ele->SetLowPoint(0,0,-0.5);
    ele->SetHighPoint(0,0,0.5);
    ele->SetLowPoint((bounds[1] + bounds[0]) / 2.0,
                     (bounds[3] + bounds[2]) / 2.0,
                     -bounds[5]);
    ele->SetHighPoint((bounds[1] + bounds[0]) / 2.0,
                      (bounds[3] + bounds[2]) / 2.0,
                      bounds[5]);

    ele->Update();
    input->ShallowCopy(ele->GetOutput());
  }
  else
  {
    std::string inputFilename = argv[1];

    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(inputFilename.c_str());
    reader->Update();

    input->ShallowCopy(reader->GetOutput());
    input->GetBounds(bounds);
  }

  // Now create a control mesh, in this case a octagon that encloses
  // the point set
  vtkSmartPointer<vtkPoints> pts =
    vtkSmartPointer<vtkPoints>::New();
  pts->SetNumberOfPoints(6);
  pts->SetPoint(0,
                bounds[0] - .1 * (bounds[1] - bounds[0]),
                (bounds[3] + bounds[2]) / 2.0,
                (bounds[5] + bounds[4]) / 2.0);
  pts->SetPoint(1,
                bounds[1] + .1 * (bounds[1] - bounds[0]),
                (bounds[3] + bounds[2]) / 2.0,
                (bounds[5] + bounds[4]) / 2.0);
  pts->SetPoint(2,
                (bounds[1] + bounds[0]) / 2.0,
                bounds[2] - .1 * (bounds[3] - bounds[2]),
                (bounds[5] + bounds[4]) / 2.0);
  pts->SetPoint(3,
                (bounds[1] + bounds[0]) / 2.0,
                bounds[3] + .1 * (bounds[3] - bounds[2]),
                (bounds[5] + bounds[4]) / 2.0);
  pts->SetPoint(4,
                (bounds[1] + bounds[0]) / 2.0,
                (bounds[3] + bounds[2]) / 2.0,
                bounds[4] - .1 * (bounds[5] - bounds[4]));
  pts->SetPoint(5,
                (bounds[1] + bounds[0]) / 2.0,
                (bounds[3] + bounds[2]) / 2.0,
                bounds[5] + .1 * (bounds[5] - bounds[4]));

  vtkSmartPointer<vtkCellArray> tris =
    vtkSmartPointer<vtkCellArray>::New();
  tris->InsertNextCell(3);
  tris->InsertCellPoint(2); tris->InsertCellPoint(0); tris->InsertCellPoint(4);
  tris->InsertNextCell(3);
  tris->InsertCellPoint(1); tris->InsertCellPoint(2); tris->InsertCellPoint(4);
  tris->InsertNextCell(3);
  tris->InsertCellPoint(3); tris->InsertCellPoint(1); tris->InsertCellPoint(4);
  tris->InsertNextCell(3);
  tris->InsertCellPoint(0); tris->InsertCellPoint(3); tris->InsertCellPoint(4);
  tris->InsertNextCell(3);
  tris->InsertCellPoint(0); tris->InsertCellPoint(2); tris->InsertCellPoint(5);
  tris->InsertNextCell(3);
  tris->InsertCellPoint(2); tris->InsertCellPoint(1); tris->InsertCellPoint(5);
  tris->InsertNextCell(3);
  tris->InsertCellPoint(1); tris->InsertCellPoint(3); tris->InsertCellPoint(5);
  tris->InsertNextCell(3);
  tris->InsertCellPoint(3); tris->InsertCellPoint(0); tris->InsertCellPoint(5);

  vtkSmartPointer<vtkPolyData> pd =
    vtkSmartPointer<vtkPolyData>::New();
  pd->SetPoints(pts);
  pd->SetPolys(tris);

  // Display the control mesh
  vtkSmartPointer<vtkPolyDataMapper> meshMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  meshMapper->SetInputData(pd);
  vtkSmartPointer<vtkActor> meshActor =
    vtkSmartPointer<vtkActor>::New();
  meshActor->SetMapper(meshMapper);
  meshActor->GetProperty()->SetRepresentationToWireframe();
  meshActor->GetProperty()->SetColor(0,0,0);

  // Do the intitial weight generation
  vtkSmartPointer<vtkDeformPointSet> deform =
    vtkSmartPointer<vtkDeformPointSet>::New();
    deform->SetInputData(input);
    deform->SetControlMeshData(pd);
    deform->Update(); // this creates the initial weights

  // Now move one point and deform
  double controlPoint[3];
  pts->GetPoint(5, controlPoint);
  pts->SetPoint(5, controlPoint[0],
                controlPoint[1],
                bounds[5] + .8 * (bounds[5] - bounds[4]));
  pts->Modified();

  // Display the warped polydata
  vtkSmartPointer<vtkPolyDataMapper> polyMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
    polyMapper->SetInputConnection(deform->GetOutputPort());
  vtkSmartPointer<vtkActor> polyActor =
    vtkSmartPointer<vtkActor>::New();
    polyActor->SetMapper(polyMapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  renderer->AddActor(polyActor);
  renderer->AddActor(meshActor);

  renderer->GetActiveCamera()->SetPosition(1,1,1);
  renderer->ResetCamera();
  renderer->SetBackground(.2, .3, .4);

  renWin->SetSize(300,300);
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
