/*
This code is based on the VTK file: /IO/Geometry/Testing/Python/motor.py.
*/

#include <vtkActor.h>
#include <vtkBYUReader.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkFloatArray.h>
#include <vtkImplicitTextureCoords.h>
#include <vtkNamedColors.h>
#include <vtkPlanes.h>
#include <vtkPoints.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkTexture.h>

#include <string>
#include <vector>

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " textureFile motorFile" << std::endl;
    std::cout << "where: textureFile is the texture file: texThres2.vtk."
              << std::endl;
    std::cout << "       motorFile is ihe motor file: motor.g." << std::endl;
    return EXIT_FAILURE;
  }

  std::string textureFile = argv[1];
  std::string motorFile = argv[2];

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create the Renderer, RenderWindow and RenderWindowInteractor.
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Create the cutting planes.
  vtkSmartPointer<vtkPlanes> planes = vtkSmartPointer<vtkPlanes>::New();
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkFloatArray> norms = vtkSmartPointer<vtkFloatArray>::New();

  norms->SetNumberOfComponents(3);
  points->InsertPoint(0, 0.0, 0.0, 0.0);
  norms->InsertTuple3(0, 0.0, 0.0, 1.0);
  points->InsertPoint(1, 0.0, 0.0, 0.0);
  norms->InsertTuple3(1, -1.0, 0.0, 0.0);
  planes->SetPoints(points);
  planes->SetNormals(norms);

  // Get the texture.
  vtkSmartPointer<vtkStructuredPointsReader> texReader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  texReader->SetFileName(textureFile.c_str());
  vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(texReader->GetOutputPort());
  texture->InterpolateOff();
  texture->RepeatOff();

  // Set up the pipelines for the parts of the motor.
  // We will use lists of pipeline objects.
  auto numberOfParts = 5;
  std::vector<vtkSmartPointer<vtkBYUReader>> byu;
  std::vector<vtkSmartPointer<vtkPolyDataNormals>> normals;
  std::vector<vtkSmartPointer<vtkImplicitTextureCoords>> tex;
  std::vector<vtkSmartPointer<vtkDataSetMapper>> byuMapper;
  std::vector<vtkSmartPointer<vtkActor>> byuActor;
  std::vector<std::string> partColours{"cold_grey", "peacock", "raw_sienna",
                                       "banana", "peach_puff"};
  // Use this to control which parts to display.
  std::vector<bool> displayParts(numberOfParts, true);
  // If displayParts[2] = false; then an image like that in the VTK tests is
  // produced.

  for (auto i = 0; i < numberOfParts; ++i)
  {
    byu.push_back(vtkSmartPointer<vtkBYUReader>::New());
    byu[i]->SetGeometryFileName(motorFile.c_str());
    byu[i]->SetPartNumber(i + 1);

    normals.push_back(vtkSmartPointer<vtkPolyDataNormals>::New());
    normals[i]->SetInputConnection(byu[i]->GetOutputPort());

    tex.push_back(vtkSmartPointer<vtkImplicitTextureCoords>::New());
    tex[i]->SetInputConnection(normals[i]->GetOutputPort());
    tex[i]->SetRFunction(planes);
    // tex[i]->FlipTextureOn();

    byuMapper.push_back(vtkSmartPointer<vtkDataSetMapper>::New());
    byuMapper[i]->SetInputConnection(tex[i]->GetOutputPort());

    byuActor.push_back(vtkSmartPointer<vtkActor>::New());
    byuActor[i]->SetMapper(byuMapper[i]);
    byuActor[i]->SetTexture(texture);
    byuActor[i]->GetProperty()->SetColor(
      colors->GetColor3d(partColours[i]).GetData());

    ren->AddActor(byuActor[i]);
    if (displayParts[i])
    {
      byuActor[i]->VisibilityOn();
    }
    else
    {
      byuActor[i]->VisibilityOff();
    }
  }

  ren->SetBackground(colors->GetColor3d("AliceBlue").GetData());

  renWin->SetSize(512, 512);

  vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
  camera->SetFocalPoint(0.0286334, 0.0362996, 0.0379685);
  camera->SetPosition(1.37067, 1.08629, -1.30349);
  camera->SetViewAngle(17.673);
  camera->SetClippingRange(1, 10);
  camera->SetViewUp(-0.376306, -0.5085, -0.774482);
  ren->SetActiveCamera(camera);

  // Render the image.
  renWin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
