/*
 * This example shows how to combine data from both the imaging
 *  and graphics pipelines. The vtkMergeData filter is used to
 *  merge the data from each together.
*/
#include <vtkActor.h>
#include <vtkBMPReader.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkImageLuminance.h>
#include <vtkMergeFilter.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkWarpScalar.h>

#include <array>
#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{

  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " fileName" << std::endl;
    std::cout << "where: fileName is the masonry.bmp file." << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argv[1];

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char , 4> bkg{{60, 93, 144, 255}};
    colors->SetColor("BkgColor", bkg.data());

  // Read in an image and compute a luminance value-> The image is extracted
  // as a set of polygons (vtkImageDataGeometryFilter). We then will
  // warp the plane using the scalar (luminance) values.
  //
  vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
  reader->SetFileName(fileName.c_str());
  // Convert the image to a grey scale.
  vtkSmartPointer<vtkImageLuminance> luminance =
    vtkSmartPointer<vtkImageLuminance>::New();
  luminance->SetInputConnection(reader->GetOutputPort());
  // Pass the data to the pipeline as polygons.
  vtkSmartPointer<vtkImageDataGeometryFilter> geometry =
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  geometry->SetInputConnection(luminance->GetOutputPort());
  // Warp the data in a direction perpendicular to the image plane.
  vtkSmartPointer<vtkWarpScalar> warp = vtkSmartPointer<vtkWarpScalar>::New();
  warp->SetInputConnection(geometry->GetOutputPort());
  warp->SetScaleFactor(-0.1);

  // Use vtkMergeFilter to combine the original image with the warped geometry.
  vtkSmartPointer<vtkMergeFilter> merge =
    vtkSmartPointer<vtkMergeFilter>::New();
  merge->SetGeometryConnection(warp->GetOutputPort());
  merge->SetScalarsConnection(reader->GetOutputPort());
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(merge->GetOutputPort());
  mapper->SetScalarRange(0, 255);
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create the rendering window, renderer, and interactive renderer.
  //
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size.
  ren->AddActor(actor);
  ren->ResetCamera();
  ren->SetBackground(colors->GetColor3d("BkgColor").GetData());
  // ren->GetActiveCamera()->Azimuth(20);
  // ren->GetActiveCamera()->Elevation(30);
  // ren->ResetCameraClippingRange();
  // ren->GetActiveCamera()->Zoom(1.3);
  ren->GetActiveCamera()->SetPosition(-100, -130, 325);
  ren->GetActiveCamera()->SetFocalPoint(105, 114, -29);
  ren->GetActiveCamera()->SetViewUp(0.51, 0.54, 0.67);
  ren->ResetCameraClippingRange();

  renWin->SetSize(512, 512);

  // Render the image.
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
