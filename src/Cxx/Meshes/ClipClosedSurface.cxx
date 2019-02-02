#include <vtkSmartPointer.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkClipClosedSurface.h>
#include <vtkPlane.h>
#include <vtkPlaneCollection.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkSphereSource.h>

//
// Demonstrate the use of clipping of polygonal data
//

int main (int argc, char *argv[])
{
  // PolyData to process
  vtkSmartPointer<vtkPolyData> polyData;

  if (argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    // Create a sphere
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(20);
    sphereSource->SetPhiResolution(11);
    sphereSource->Update();

    polyData = sphereSource->GetOutput();
  }

  double *center = polyData->GetCenter();
  vtkSmartPointer<vtkPlane> plane1 =
    vtkSmartPointer<vtkPlane>::New();
  plane1->SetOrigin(center[0], center[1], center[2]);
  plane1->SetNormal(0.0, -1.0, 0.0);
  vtkSmartPointer<vtkPlane> plane2 =
    vtkSmartPointer<vtkPlane>::New();
  plane2->SetOrigin(center[0], center[1], center[2]);
  plane2->SetNormal(0.0, 0.0, 1.0);
  vtkSmartPointer<vtkPlane> plane3 =
    vtkSmartPointer<vtkPlane>::New();
  plane3->SetOrigin(center[0], center[1], center[2]);
  plane3->SetNormal(-1.0, 0.0, 0.0);

  vtkSmartPointer<vtkPlaneCollection> planes =
    vtkSmartPointer<vtkPlaneCollection>::New();
  planes->AddItem(plane1);
  planes->AddItem(plane2);
  planes->AddItem(plane3);

  vtkSmartPointer<vtkClipClosedSurface> clipper =
    vtkSmartPointer<vtkClipClosedSurface>::New();
  clipper->SetInputData(polyData);
  clipper->SetClippingPlanes(planes);
  clipper->SetActivePlaneId(2);
  clipper->SetScalarModeToColors();
  clipper->SetClipColor(0.8900, 0.8100, 0.3400); // banana
  clipper->SetBaseColor(1.0000, 0.3882, 0.2784); // tomato
  clipper->SetActivePlaneColor(0.6400, 0.5800, 0.5000); // beige

  vtkSmartPointer<vtkDataSetMapper> clipMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  clipMapper->SetInputConnection(clipper->GetOutputPort());

  vtkSmartPointer<vtkActor> clipActor =
    vtkSmartPointer<vtkActor>::New();
  clipActor->SetMapper(clipMapper);
  clipActor->GetProperty()->SetColor(1.0000,0.3882,0.2784);
  clipActor->GetProperty()->SetInterpolationToFlat();

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
  ren1->AddActor(clipActor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(120);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.0);
  ren1->ResetCameraClippingRange();

  renWin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
