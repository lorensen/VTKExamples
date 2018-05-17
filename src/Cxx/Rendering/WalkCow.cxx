// Translated from walkCow.tcl

#include <vtkActor.h>
#include <vtkAxes.h>
#include <vtkBYUReader.h>
#include <vtkCallbackCommand.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkPNGWriter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkVersionMacros.h>
#include <vtkWindowToImageFilter.h>

#include <array>

namespace
{
/*
These Rotate* and Walk functions create a scene where multiple
   views of the object exist.

  They all operate in a similar manner, namely:
  1) Accept vtkActor, vtkRenderer, vtkRenderWindow as parameters.
  2) Position the object.
  3) Position the observer with the focal point sent to the centre
      of the object.
  4) Render and set EraseOff() in the render window.
     Note that:
      EraseOff() has to be called after a Render() call
       to work in the desired way.
  5) Then rotate or walk the object around the scene.
  6) Write out the scene using Screenshot().
  6) Set EraseOff() in the render window.
  7) Reset the object position.

*/
void Rotate_X(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin);
void Rotate_Y(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin);
void Rotate_Z(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin);
void Rotate_XY(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin);
void Rotate_V_0(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin);
void Rotate_V_V(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin);
void Walk(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin);

/*
// Used to estimate positions similar to the book illustrations.
static void CameraModifiedCallback(vtkObject* caller,
                                   long unsigned int vtkNotUsed(eventId),
                                   void* vtkNotUsed(clientData),
                                   void* vtkNotUsed(callData));
*/

// Save a screenshot.
void Screenshot(std::string fileName, vtkRenderWindow* renWin);
}

int main(int argc, char* argv[])
{
  int figure = 0;
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename [figure]" << std::endl;
    std::cout << "where: filename is the file cow.g" << std::endl;
    std::cout << "       figure is 0, 1, or 2, default 0" << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argv[1];
  if (argc == 3)
  {
    figure = std::abs(atoi(argv[2]));
    figure = (figure > 2) ? 0 : figure;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char , 4> bkg1{{60, 93, 144, 255}};
    colors->SetColor("BkgColor1", bkg1.data());
  std::array<unsigned char , 4> bkg2{{26, 51, 102, 255}};
    colors->SetColor("BkgColor2", bkg2.data());

  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // The cow pipeline.
  vtkSmartPointer<vtkBYUReader> cow = vtkSmartPointer<vtkBYUReader>::New();
  cow->SetGeometryFileName(fileName.c_str());
  cow->Update();

  vtkSmartPointer<vtkPolyDataMapper> cowMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cowMapper->SetInputConnection(cow->GetOutputPort());
  cowMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> cowActor = vtkSmartPointer<vtkActor>::New();
  cowActor->SetMapper(cowMapper);
  cowActor->GetProperty()->SetColor(colors->GetColor3d("Wheat").GetData());

  ren->AddActor(cowActor);

  // Axes pipeline.
  vtkSmartPointer<vtkAxes> cowAxesSource = vtkSmartPointer<vtkAxes>::New();
  cowAxesSource->SetScaleFactor(10.0);
  cowAxesSource->SetOrigin(0, 0, 0);

  vtkSmartPointer<vtkPolyDataMapper> cowAxesMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cowAxesMapper->SetInputConnection(cowAxesSource->GetOutputPort());

  vtkSmartPointer<vtkActor> cowAxes = vtkSmartPointer<vtkActor>::New();
  cowAxes->SetMapper(cowAxesMapper);
  cowAxes->VisibilityOff();

  ren->AddActor(cowAxes);

  ren->SetBackground(colors->GetColor3d("BkgColor1").GetData());
  renWin->SetSize(600, 480);

  iren->Initialize();
  cowAxes->VisibilityOn();
  renWin->Render();

  // Activate this if you want to see the Position and Focal point.
  // vtkSmartPointer<vtkCallbackCommand> modifiedCallback =
  // vtkSmartPointer<vtkCallbackCommand>::New();
  // modifiedCallback->SetCallback(CameraModifiedCallback);
  // ren->GetActiveCamera()->AddObserver(vtkCommand::ModifiedEvent,
  // modifiedCallback);

  // These four rotations use the same camera position.
  Rotate_X(cowActor, ren, renWin);
  Rotate_Y(cowActor, ren, renWin);
  Rotate_Z(cowActor, ren, renWin);
  Rotate_XY(cowActor, ren, renWin);

  ren->SetBackground(colors->GetColor3d("BkgColor2").GetData());
  switch (figure)
  {
    default:
    case 0:
      Rotate_V_0(cowActor, ren, renWin);
      Rotate_V_V(cowActor, ren, renWin);
      // Walk() needs to go after Rotate_V_0() or Rotate_V_V().
      Walk(cowActor, ren, renWin);
      break;
    case 1:
      Rotate_V_0(cowActor, ren, renWin);
      break;
    case 2:
      Rotate_V_V(cowActor, ren, renWin);
      break;
  }

  // Interact with data.
  // Keep the last rendered image.
  renWin->EraseOff();
  iren->Start();
  return EXIT_SUCCESS;
}

namespace
{

void Rotate_X(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin)
{
  // Six rotations about the x axis.
  ren->ResetCamera();
  ren->ResetCameraClippingRange();
  cowActor->SetOrientation(0.0, 0.0, 0.0);
  cowActor->SetOrigin(0.0, 0.0, 0);
  cowActor->SetPosition(0, 0, 0);
  // Get the focal point.
  double* bounds = cowActor->GetBounds();
  double fp[3];
  for (int i = 0; i < 3; ++i)
  {
    fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0;
  }
  // This closely matches the original illustration.
  ren->GetActiveCamera()->SetPosition(2, 25, 0);
  ren->GetActiveCamera()->SetFocalPoint(fp);
  ren->GetActiveCamera()->SetViewUp(0, 0, -1);
  ren->ResetCameraClippingRange();
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();
  for (int idx = 0; idx < 6; idx++)
  {
    cowActor->RotateX(60);
    renWin->Render();
    renWin->Render();
  }
  Screenshot("Fig3-31a.png", renWin);
  renWin->EraseOn();
}

void Rotate_Y(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin)
{
  // Six rotations about the y axis.
  ren->ResetCamera();
  ren->ResetCameraClippingRange();
  cowActor->SetOrientation(0.0, 0.0, 0.0);
  cowActor->SetOrigin(0.0, 0.0, 0);
  cowActor->SetPosition(0, 0, 0);
  // Get the focal point.
  double* bounds = cowActor->GetBounds();
  double fp[3];
  for (int i = 0; i < 3; ++i)
  {
    fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0;
  }
  // This closely matches the original illustration.
  ren->GetActiveCamera()->SetPosition(2, 0, 25);
  ren->GetActiveCamera()->SetFocalPoint(fp);
  ren->GetActiveCamera()->SetViewUp(0, 1, 0);
  ren->ResetCameraClippingRange();
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();
  for (int idx = 0; idx < 6; idx++)
  {
    cowActor->RotateY(60);
    renWin->Render();
    renWin->Render();
  }
  Screenshot("Fig3-31b.png", renWin);
  renWin->EraseOn();
}

void Rotate_Z(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin)
{
  // Six rotations about the z axis.
  ren->ResetCamera();
  ren->ResetCameraClippingRange();
  cowActor->SetOrientation(0.0, 0.0, 0.0);
  cowActor->SetOrigin(0.0, 0.0, 0);
  cowActor->SetPosition(0, 0, 0);
  // Get the focal point.
  double* bounds = cowActor->GetBounds();
  double fp[3];
  for (int i = 0; i < 3; ++i)
  {
    fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0;
  }
  // This closely matches the original illustration.
  ren->GetActiveCamera()->SetPosition(2, 0, 25);
  ren->GetActiveCamera()->SetFocalPoint(fp);
  ren->GetActiveCamera()->SetViewUp(0, 1, 0);
  ren->ResetCameraClippingRange();
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();
  for (int idx = 0; idx < 6; idx++)
  {
    cowActor->RotateZ(60);
    renWin->Render();
    renWin->Render();
  }
  Screenshot("Fig3-31c.png", renWin);
  renWin->EraseOn();
}

void Rotate_XY(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin)
{
  // First a rotation about the x axis, then six rotations about the y axis.
  ren->ResetCamera();
  ren->ResetCameraClippingRange();
  cowActor->SetOrientation(0.0, 0.0, 0.0);
  cowActor->SetOrigin(0.0, 0.0, 0);
  cowActor->SetPosition(0, 0, 0);
  // Get the focal point.
  double* bounds = cowActor->GetBounds();
  double fp[3];
  for (int i = 0; i < 3; ++i)
  {
    fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0;
  }
  // This closely matches the original illustration.
  ren->GetActiveCamera()->SetPosition(2, 0, 25);
  ren->GetActiveCamera()->SetFocalPoint(fp);
  ren->GetActiveCamera()->SetViewUp(0, 1, 0);
  ren->ResetCameraClippingRange();
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();
  cowActor->RotateX(60);
  for (int idx = 0; idx < 6; idx++)
  {
    cowActor->RotateY(60);
    renWin->Render();
    renWin->Render();
  }
  cowActor->RotateX(-60);
  Screenshot("Fig3-31d.png", renWin);
  renWin->EraseOn();
}

void Rotate_V_0(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin)
{
  // The cow rotating about a vector passing through her nose.
  // With the origin at (0, 0, 0).
  ren->ResetCamera();
  ren->ResetCameraClippingRange();
  cowActor->SetOrientation(0.0, 0.0, 0.0);
  cowActor->SetOrigin(0.0, 0.0, 0);
  cowActor->SetPosition(0, 0, 0);
  // Get the focal point.
  double* bounds = cowActor->GetBounds();
  double fp[3];
  for (int i = 0; i < 3; ++i)
  {
    fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0;
  }
  vtkSmartPointer<vtkTransform> cowPos = vtkSmartPointer<vtkTransform>::New();
  cowPos->Identity();
  cowPos->SetMatrix(cowActor->GetMatrix());
  vtkSmartPointer<vtkTransform> cowTransform =
    vtkSmartPointer<vtkTransform>::New();
  cowTransform->Identity();
  cowActor->SetUserMatrix(cowTransform->GetMatrix());
  // This closely matches the original illustration.
  ren->GetActiveCamera()->SetPosition(16, 9, -12);
  ren->GetActiveCamera()->SetFocalPoint(fp);
  ren->ResetCameraClippingRange();
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();
  for (int idx = 0; idx < 6; idx++)
  {
    cowActor->RotateWXYZ(60, 2.19574, -1.42455, -0.0331036);
    renWin->Render();
    renWin->Render();
  }
  Screenshot("Fig3-33a.png", renWin);
  renWin->EraseOn();
  // Put the cow back on the origin.
  // for (int idx = 0; idx < 6; idx++)
  //{
  //  cowActor->RotateWXYZ(-60, 2.19574, -1.42455, -0.0331036);
  //}
  // cowActor->SetUserMatrix(cowPos->GetMatrix());
  // ren->GetActiveCamera()->SetPosition(0, 0, 1);
  // ren->GetActiveCamera()->SetViewUp(0, 1, 0);
  // ren->ResetCamera();
}

void Rotate_V_V(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin)
{
  // The cow rotating about a vector passing through her nose.
  // With the origin at (6.11414, 1.27386, 0.015175).
  ren->ResetCamera();
  ren->ResetCameraClippingRange();
  cowActor->SetOrientation(0.0, 0.0, 0.0);
  cowActor->SetOrigin(0.0, 0.0, 0);
  cowActor->SetPosition(0, 0, 0);
  // Get the focal point.
  double* bounds = cowActor->GetBounds();
  double fp[3];
  for (int i = 0; i < 3; ++i)
  {
    fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0;
  }
  vtkSmartPointer<vtkTransform> cowPos = vtkSmartPointer<vtkTransform>::New();
  cowPos->Identity();
  cowPos->SetMatrix(cowActor->GetMatrix());
  cowActor->SetOrigin(6.11414, 1.27386, 0.015175); // The cow's nose
  vtkSmartPointer<vtkTransform> cowTransform =
    vtkSmartPointer<vtkTransform>::New();
  cowTransform->Identity();
  cowActor->SetUserMatrix(cowTransform->GetMatrix());
  // This closely matches the original illustration.
  ren->GetActiveCamera()->SetPosition(31, 23, -21);
  ren->GetActiveCamera()->SetFocalPoint(fp);
  ren->ResetCameraClippingRange();
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();
  for (int idx = 0; idx < 6; idx++)
  {
    cowActor->RotateWXYZ(60, 2.19574, -1.42455, -0.0331036);
    renWin->Render();
    renWin->Render();
  }
  Screenshot("Fig3-33b.png", renWin);
  renWin->EraseOn();
  // Put the cow back on the origin.
  // for (int idx = 0; idx < 6; idx++)
  //{
  //  cowActor->RotateWXYZ(-60, 2.19574, -1.42455, -0.0331036);
  //}
  // cowActor->SetUserMatrix(cowPos->GetMatrix());
}

void Walk(vtkActor* cowActor, vtkRenderer* ren, vtkRenderWindow* renWin)
{
  // The cow "walking" around the global origin
  vtkSmartPointer<vtkTransform> cowPos = vtkSmartPointer<vtkTransform>::New();
  cowPos->Identity();
  cowPos->SetMatrix(cowActor->GetMatrix());
  cowActor->SetOrientation(0.0, 0.0, 0.0);
  cowActor->SetOrigin(0.0, 0.0, 0.0);
  // Get the focal point.
  double* bounds = cowActor->GetBounds();
  double fp[3];
  for (int i = 0; i < 3; ++i)
  {
    fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0;
  }
  vtkSmartPointer<vtkTransform> cowTransform =
    vtkSmartPointer<vtkTransform>::New();
  cowTransform->Identity();
  cowTransform->Translate(0, 0, 5);
  cowActor->SetUserMatrix(cowTransform->GetMatrix());
  // This closely matches the original illustration.
  ren->GetActiveCamera()->SetPosition(1, 24, 16);
  ren->GetActiveCamera()->SetFocalPoint(fp);
  ren->GetActiveCamera()->SetViewUp(0, 0, -1);
  ren->ResetCameraClippingRange();
  renWin->Render();
  renWin->Render();
  renWin->EraseOff();
  for (int idx = 0; idx < 6; idx++)
  {
    cowTransform->Identity();
    cowTransform->RotateY(idx * 60);
    cowTransform->Translate(0, 0, 5);
    cowActor->SetUserMatrix(cowTransform->GetMatrix());
    renWin->Render();
    renWin->Render();
  }
  Screenshot("Fig3-32.png", renWin);
  renWin->EraseOn();
  // Walkies are over, put the cow back on the origin.
  // cowActor->SetUserMatrix(cowPos->GetMatrix());
}

/*
static void CameraModifiedCallback(vtkObject* caller,
                                   long unsigned int vtkNotUsed(eventId),
                                   void* vtkNotUsed(clientData),
                                   void* vtkNotUsed(callData))
{
  std::cout << caller->GetClassName() << " modified" << std::endl;
  vtkCamera* camera = static_cast<vtkCamera*>(caller);
  // Print the interesting stuff.
  std::cout << "\tPosition: " << camera->GetPosition()[0] << ", "
            << camera->GetPosition()[1] << ", " << camera->GetPosition()[2]
            << std::endl;
  std::cout << "\tFocal point: " << camera->GetFocalPoint()[0] << ", "
            << camera->GetFocalPoint()[1] << ", " << camera->GetFocalPoint()[2]
            << std::endl;
}
*/

void Screenshot(std::string fileName, vtkRenderWindow* renWin)
{
  vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
    vtkSmartPointer<vtkWindowToImageFilter>::New();
  windowToImageFilter->SetInput(renWin);
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 1
  windowToImageFilter->SetScale(1); // image quality
#else
  windowToImageFilter->SetMagnification(1); // image quality
#endif
  // We are not recording the alpha (transparency) channel.
  // windowToImageFilter->SetInputBufferTypeToRGBA();
  windowToImageFilter->SetInputBufferTypeToRGB();
  // Read from the front buffer.
  windowToImageFilter->ReadFrontBufferOff();
  windowToImageFilter->Update();

  vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName(fileName.c_str());
  writer->SetInputConnection(windowToImageFilter->GetOutputPort());
  writer->Write();
}
}
