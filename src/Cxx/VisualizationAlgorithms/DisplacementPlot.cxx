// Translated from dispPlot.tcl
/*
Produce figure 6-15(b) from the VTK Textbook.
Surface plot of a vibrating plane.

The color_scheme option allows you to select a series of colour schemes.
0: The default:- cool maximum negative motion,
                 warm maximum positive motion, white at the nodes.
1: Alternate choice:- green maximum negative motion,
                      purple maximum positive motion, white at the nodes.
2: The original:- white at maximum motion, black at the nodes.

*/

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkColorTransferFunction.h>
#include <vtkDataSetMapper.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkVectorDot.h>
#include <vtkWarpVector.h>

namespace
{
//! Create a lookup table.
/*!
@param lut - An indexed lookup table.
*/
void MakeLUT(int const& colorScheme, vtkLookupTable* lut);
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename [colorScheme]" << std::endl;
    std::cout << "where: filename is the file plate.vtk." << std::endl;
    std::cout << "       colorScheme is 0, 1, or 2, default 0" << std::endl;
    std::cout << "Produces figure 6-15(b) Surface plot of vibrating plane from "
                 "the VTK Textbook."
              << std::endl;
    return EXIT_FAILURE;
  }

  int colorScheme = 0;
  std::string fileName = argv[1];

  if (argc == 3)
  {
    colorScheme = std::abs(atoi(argv[2]));
    colorScheme = (colorScheme > 2) ? 0 : colorScheme;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Read a vtk file
  //
  vtkSmartPointer<vtkPolyDataReader> plate =
    vtkSmartPointer<vtkPolyDataReader>::New();
  plate->SetFileName(fileName.c_str());
  plate->SetVectorsName("mode8");
  plate->Update();

  vtkSmartPointer<vtkWarpVector> warp = vtkSmartPointer<vtkWarpVector>::New();
  warp->SetInputConnection(plate->GetOutputPort());
  warp->SetScaleFactor(0.5);

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(warp->GetOutputPort());

  vtkSmartPointer<vtkVectorDot> color = vtkSmartPointer<vtkVectorDot>::New();
  color->SetInputConnection(normals->GetOutputPort());

  vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
  MakeLUT(colorScheme, lut);

  vtkSmartPointer<vtkDataSetMapper> plateMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  plateMapper->SetInputConnection(color->GetOutputPort());
  plateMapper->SetLookupTable(lut);
  plateMapper->SetScalarRange(-1, 1);

  vtkSmartPointer<vtkActor> plateActor = vtkSmartPointer<vtkActor>::New();
  plateActor->SetMapper(plateMapper);

  // Create the RenderWindow, Renderer and both Actors
  //
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size
  //
  ren->AddActor(plateActor);
  ren->SetBackground(colors->GetColor3d("Wheat").GetData());
  renWin->SetSize(512, 512);

  ren->GetActiveCamera()->SetPosition(13.3991, 14.0764, 9.97787);
  ren->GetActiveCamera()->SetFocalPoint(1.50437, 0.481517, 4.52992);
  ren->GetActiveCamera()->SetViewAngle(30);
  ren->GetActiveCamera()->SetViewUp(-0.120861, 0.458556, -0.880408);
  ren->GetActiveCamera()->SetClippingRange(12.5724, 26.8374);
  // Render the image.
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}

namespace
{
void MakeLUT(int const& colorScheme, vtkLookupTable* lut)
{
  // See: [Diverging Color Maps for Scientific Visualization]
  //      (http://www.kennethmoreland.com/color-maps/)
  auto nc = 256;
  vtkSmartPointer<vtkColorTransferFunction> ctf =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  switch (colorScheme)
  {
    case 0:
    default:
      // Cool to warm diverging.
      ctf->SetColorSpaceToDiverging();
      ctf->AddRGBPoint(0.0, 0.230, 0.299, 0.754);
      ctf->AddRGBPoint(1.0, 0.706, 0.016, 0.150);
      lut->SetNumberOfTableValues(nc);
      lut->Build();
      for (auto i = 0; i < nc; ++i)
      {
        double rgb[4] = {0.0, 0.0, 0.0, 1.0};
        ctf->GetColor(static_cast<double>(i) / nc, rgb);
        lut->SetTableValue(i, rgb);
      }
      break;
    case 1:
      // Green to purple diverging.
      ctf->SetColorSpaceToDiverging();
      ctf->AddRGBPoint(0.0, 0.085, 0.532, 0.201);
      ctf->AddRGBPoint(1.0, 0.436, 0.308, 0.631);
      lut->SetNumberOfTableValues(nc);
      lut->Build();
      for (auto i = 0; i < nc; ++i)
      {
        double rgb[4] = {0.0, 0.0, 0.0, 1.0};
        ctf->GetColor(static_cast<double>(i) / nc, rgb);
        lut->SetTableValue(i, rgb);
      }
      break;
    case 2:
    {
      // Make a lookup table, black in the centre with bright areas
      //   at the beginning and end of the table.
      // This is from the original code.
      auto nc2 = nc / 2;
      lut->SetNumberOfColors(nc);
      lut->Build();
      for (auto i = 0; i < nc2; ++i)
      {
        // White to black.
        auto v = (double(nc2) - i) / double(nc2);
        lut->SetTableValue(i, v, v, v, 1);
      }
      for (auto i = nc2; i < nc; ++i)
      {
        // Black to white.
        auto v = (i - double(nc2)) / double(nc2);
        lut->SetTableValue(i, v, v, v, 1);
      }
      break;
    }
  }
}
}
