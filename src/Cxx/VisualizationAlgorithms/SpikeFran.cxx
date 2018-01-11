#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkGlyph3D.h>
#include <vtkMaskPoints.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

// This example demonstrates the use of glyphing. We also use a mask filter
// to select a subset of points to glyph.

// Read a data file. This originally was a Cyberware laser digitizer scan
// of Fran J.'s face. Surface normals are generated based on local geometry
// (i.e., the polygon normals surrounding each point are averaged). We flip
// the normals because we want them to point out from Fran's face.
//
int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " fran_cut.vtk" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataReader> fran =
    vtkSmartPointer<vtkPolyDataReader>::New();
  fran->SetFileName(argv[1]);

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(fran->GetOutputPort());
  normals->FlipNormalsOn();

  vtkSmartPointer<vtkPolyDataMapper> franMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  franMapper->SetInputConnection(normals->GetOutputPort());

  vtkSmartPointer<vtkActor> franActor =
    vtkSmartPointer<vtkActor>::New();
  franActor->SetMapper(franMapper);
  franActor->GetProperty()->SetColor(colors->GetColor3d("Flesh").GetData());

// We subsample the dataset because we want to glyph just a subset of
// the points. Otherwise the display is cluttered and cannot be easily
// read. The RandomModeOn and SetOnRatio combine to random select one out
// of every 10 points in the dataset.
//
  vtkSmartPointer<vtkMaskPoints> ptMask =
    vtkSmartPointer<vtkMaskPoints>::New();
  ptMask->SetInputConnection(normals->GetOutputPort());
  ptMask->SetOnRatio(10);
  ptMask->RandomModeOn();

// In this case we are using a cone as a glyph. We transform the cone so
// its base is at 0,0,0. This is the point where glyph rotation occurs.
  vtkSmartPointer<vtkConeSource> cone =
    vtkSmartPointer<vtkConeSource>::New();
  cone->SetResolution(6);

  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Translate(0.5, 0.0, 0.0);

  vtkSmartPointer<vtkTransformPolyDataFilter> transformF =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformF->SetInputConnection(cone->GetOutputPort());
  transformF->SetTransform(transform);

// vtkGlyph3D takes two inputs: the input point set (SetInputConnection)
// which can be any vtkDataSet; and the glyph (SetSourceConnection) which
// must be a vtkPolyData.  We are interested in orienting the glyphs by the
// surface normals that we previously generated.
  vtkSmartPointer<vtkGlyph3D> glyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph->SetInputConnection(ptMask->GetOutputPort());
  glyph->SetSourceConnection(transformF->GetOutputPort());
  glyph->SetVectorModeToUseNormal();
  glyph->SetScaleModeToScaleByVector();
  glyph->SetScaleFactor(0.004);

  vtkSmartPointer<vtkPolyDataMapper> spikeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  spikeMapper->SetInputConnection(glyph->GetOutputPort());

  vtkSmartPointer<vtkActor> spikeActor =
    vtkSmartPointer<vtkActor>::New();
  spikeActor->SetMapper(spikeMapper);
  spikeActor->GetProperty()->SetColor(colors->GetColor3d("Emerald_Green").GetData());

// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(franActor);
  ren1->AddActor(spikeActor);

  renWin->SetSize(640, 480);
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());

// render the image
//
  renWin->Render();

  ren1->GetActiveCamera()->Zoom(1.4);
  ren1->GetActiveCamera()->Azimuth(110);
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
