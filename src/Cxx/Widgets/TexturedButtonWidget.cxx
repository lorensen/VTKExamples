#include <vtkSmartPointer.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>

#include <vtkCoordinate.h>
#include <vtkSphereSource.h>
#include <vtkButtonWidget.h>
#include <vtkTexturedButtonRepresentation2D.h>

static void CreateImage(vtkSmartPointer<vtkImageData> image,
                        unsigned char *color1,
                        unsigned char *color2);

int main(int, char *[])
{
  // Create two images for texture
  vtkSmartPointer<vtkImageData> image1 =
    vtkSmartPointer<vtkImageData>::New();
  vtkSmartPointer<vtkImageData> image2 =
    vtkSmartPointer<vtkImageData>::New();
  unsigned char banana[3] = { 227, 207, 87 };
  unsigned char tomato[3] = { 255, 99, 71 };
  CreateImage(image1, banana, tomato);
  CreateImage(image2, tomato, banana);

  // Create some geometry
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

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

  // Create the widget and its representation
  vtkSmartPointer<vtkTexturedButtonRepresentation2D> buttonRepresentation =
    vtkSmartPointer<vtkTexturedButtonRepresentation2D>::New();
  buttonRepresentation->SetNumberOfStates(2);
  buttonRepresentation->SetButtonTexture(0, image1);
  buttonRepresentation->SetButtonTexture(1, image2);

  vtkSmartPointer<vtkButtonWidget> buttonWidget =
    vtkSmartPointer<vtkButtonWidget>::New();
  buttonWidget->SetInteractor(renderWindowInteractor);
  buttonWidget->SetRepresentation(buttonRepresentation);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .5);

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  // Place the widget. Must be done after a render so that the
  // viewport is defined.
  // Here the widget placement is in normalized display coordinates
  vtkSmartPointer<vtkCoordinate> upperRight =
    vtkSmartPointer<vtkCoordinate>::New();
  upperRight->SetCoordinateSystemToNormalizedDisplay();
  upperRight->SetValue(1.0, 1.0);

  double bds[6];
  double sz = 50.0;
  bds[0] = upperRight->GetComputedDisplayValue(renderer)[0] - sz;
  bds[1] = bds[0] + sz;
  bds[2] = upperRight->GetComputedDisplayValue(renderer)[1] - sz;
  bds[3] = bds[2] + sz;
  bds[4] = bds[5] = 0.0;

  // Scale to 1, default is .5
  buttonRepresentation->SetPlaceFactor(1);
  buttonRepresentation->PlaceWidget(bds);

  buttonWidget->On();

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CreateImage(vtkSmartPointer<vtkImageData> image,
                 unsigned char* color1,
                 unsigned char* color2)
{
  // Specify the size of the image data
  image->SetDimensions(10, 10, 1);
  image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

  int* dims = image->GetDimensions();

  // Fill the image with
  for (int y = 0; y < dims[1]; y++)
  {
    for (int x = 0; x < dims[0]; x++)
    {
      unsigned char* pixel =
        static_cast<unsigned char*>(image->GetScalarPointer(x, y, 0));
      if (x < 5)
      {
        pixel[0] = color1[0];
        pixel[1] = color1[1];
        pixel[2] = color1[2];
      }
      else
      {
        pixel[0] = color2[0];
        pixel[1] = color2[1];
        pixel[2] = color2[2];
      }
    }
  }
}
