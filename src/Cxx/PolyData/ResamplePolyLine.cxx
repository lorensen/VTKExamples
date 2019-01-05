#include <vtkActor.h>
#include <vtkCardinalSpline.h>
#include <vtkCellArray.h>
#include <vtkGlyph3D.h>
#include <vtkMath.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSplineFilter.h>
#include <vtkXMLPolyDataReader.h>

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  if (argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName ( argv[1] );
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkMath::RandomSeed(8775070);
    unsigned int numberOfPoints = 10;
    vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
    for (unsigned int i = 0; i < numberOfPoints; ++i)
    {
      double x = vtkMath::Random(-1, 1);
      double y = vtkMath::Random(-1, 1);
      double z = vtkMath::Random(-1, 1);
      points->InsertNextPoint(x, y, z);
    }
    vtkSmartPointer<vtkCellArray> lines =
      vtkSmartPointer<vtkCellArray>::New();
    lines->InsertNextCell(numberOfPoints);
    for (unsigned int i = 0; i < numberOfPoints; ++i)
    {
      lines->InsertCellPoint(i);
    }
    polyData->SetPoints(points);
    polyData->SetLines(lines);
  }

  vtkSmartPointer<vtkCardinalSpline> spline =
    vtkSmartPointer<vtkCardinalSpline>::New();
  spline->SetLeftConstraint(2);
  spline->SetLeftValue(0.0);
  spline->SetRightConstraint(2);
  spline->SetRightValue(0.0);

  vtkSmartPointer<vtkSplineFilter> splineFilter =
    vtkSmartPointer<vtkSplineFilter>::New();
  splineFilter->SetInputData(polyData);
  splineFilter->SetNumberOfSubdivisions(polyData->GetNumberOfPoints() * 10);
  splineFilter->SetSpline(spline);

  vtkSmartPointer<vtkPolyDataMapper> splineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  splineMapper->SetInputConnection(splineFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> splineActor =
    vtkSmartPointer<vtkActor>::New();
  splineActor->SetMapper(splineMapper);

  vtkSmartPointer<vtkSphereSource> originalNodes =
    vtkSmartPointer<vtkSphereSource>::New();
  originalNodes->SetRadius(.04);
  originalNodes->SetPhiResolution(10);
  originalNodes->SetThetaResolution(10);

  vtkSmartPointer<vtkGlyph3D> glyphOriginal =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyphOriginal->SetInputData(polyData);
  glyphOriginal->SetSourceConnection(originalNodes->GetOutputPort());

  vtkSmartPointer<vtkSphereSource> newNodes =
    vtkSmartPointer<vtkSphereSource>::New();
  newNodes->SetRadius(.02);
  newNodes->SetPhiResolution(10);
  newNodes->SetThetaResolution(10);

  vtkSmartPointer<vtkGlyph3D> glyphNew =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyphNew->SetInputConnection(splineFilter->GetOutputPort());
  glyphNew->SetSourceConnection(newNodes->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(glyphOriginal->GetOutputPort());

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);
  originalActor->GetProperty()->SetOpacity(.6);

  vtkSmartPointer<vtkPolyDataMapper> newMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  newMapper->SetInputConnection(glyphNew->GetOutputPort());

  vtkSmartPointer<vtkActor> newActor =
    vtkSmartPointer<vtkActor>::New();
  newActor->SetMapper(newMapper);
  newActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.1, .2, .4);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(originalActor);
  renderer->AddActor(newActor);
  renderer->AddActor(splineActor);

  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
