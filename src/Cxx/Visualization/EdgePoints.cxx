#include <vtkSmartPointer.h>
#include <vtkEdgePoints.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <array>
#include <string>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Usage: " << argv[0] << " file.mhd" << endl;
    return EXIT_FAILURE;
  }

  double isoValue = 0.0;
    if (argc > 2)
    {
      isoValue = std::stod(std::string(argv[2]));
    }
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  std::array<unsigned char , 4> isoColor{{255, 125, 64}};
    colors->SetColor("IsoColor", isoColor.data());
  std::array<unsigned char , 4> bkg{{51, 77, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

  vtkSmartPointer<vtkRenderer> aRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(aRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName (argv[1]);

  vtkSmartPointer<vtkEdgePoints> isoExtractor =
    vtkSmartPointer<vtkEdgePoints>::New();
  isoExtractor->SetInputConnection(reader->GetOutputPort());
  isoExtractor->SetValue(isoValue);

  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(isoExtractor->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> iso =
    vtkSmartPointer<vtkActor>::New();
  iso->SetMapper(isoMapper);
  iso->GetProperty()->SetDiffuseColor(colors->GetColor3d("IsoColor").GetData());

  // An outline provides context around the data.
  //
  vtkSmartPointer<vtkOutlineFilter> outlineData =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outlineData->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapOutline =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapOutline->SetInputConnection(outlineData->GetOutputPort());

  vtkSmartPointer<vtkActor> outline =
    vtkSmartPointer<vtkActor>::New();
  outline->SetMapper(mapOutline);
  outline->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

  // It is convenient to create an initial view of the data. The FocalPoint
  // and Position form a vector direction. Later on (ResetCamera() method)
  // this vector is used to position the camera to look at the data in
  // this direction.
  vtkSmartPointer<vtkCamera> aCamera =
    vtkSmartPointer<vtkCamera>::New();
  aCamera->SetViewUp (0, 0, -1);
  aCamera->SetPosition (0, -1, 0);
  aCamera->SetFocalPoint (0, 0, 0);
  aCamera->ComputeViewPlaneNormal();
  aCamera->Azimuth(30.0);
  aCamera->Elevation(30.0);

  // Actors are added to the renderer. An initial camera view is created.
  // The Dolly() method moves the camera towards the FocalPoint,
  // thereby enlarging the image.
  aRenderer->AddActor(outline);
  aRenderer->AddActor(iso);
  aRenderer->SetActiveCamera(aCamera);
  aRenderer->ResetCamera ();
  aCamera->Dolly(1.5);

  // Set a background color for the renderer and set the size of the
  // render window (expressed in pixels).
  aRenderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
  renWin->SetSize(640, 480);

  // Note that when camera movement occurs (as it does in the Dolly()
  // method), the clipping planes often need adjusting. Clipping planes
  // consist of two planes: near and far along the view direction. The
  // near plane clips out objects in front of the plane; the far plane
  // clips out objects behind the plane. This way only what is drawn
  // between the planes is actually rendered.
  aRenderer->ResetCameraClippingRange ();

  // Initialize the event loop and then start it.
  renWin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
