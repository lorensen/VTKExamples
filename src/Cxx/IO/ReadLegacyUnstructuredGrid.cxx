#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>

#include <vtkGenericCell.h>

#include <vtkExtractEdges.h>
#include <vtkTubeFilter.h>
#include <vtkPolyDataMapper.h>

#include <vtkGlyph3DMapper.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>

#include <vtkTextMapper.h>
#include <vtkShrinkFilter.h>

#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>

#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkCellIterator.h>
#include <vtkCellTypes.h>
#include <vtkLabeledDataMapper.h>

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create the reader for the data.
  std::string filename = argv[1];
  std::cout << "Loading " << filename.c_str() << std::endl;
  vtkSmartPointer<vtkUnstructuredGridReader> reader =
    vtkSmartPointer<vtkUnstructuredGridReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  vtkSmartPointer<vtkExtractEdges> extractEdges =
    vtkSmartPointer<vtkExtractEdges>::New();
  extractEdges->SetInputConnection(reader->GetOutputPort());

  vtkCellIterator *it = reader->GetOutput()->NewCellIterator();
  for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell())
  {
    vtkSmartPointer<vtkGenericCell> cell =
      vtkSmartPointer<vtkGenericCell>::New();
    it->GetCell(cell);
    std::string cellName = vtkCellTypes::GetClassNameFromTypeId(cell->GetCellType());
    std::cout << cellName
              << " NumberOfPoints: " << cell->GetNumberOfPoints()
              << " CellDimension: " << cell->GetCellDimension()
              << std::endl;
  }
  it->Delete();

  // Tube the edges
  vtkSmartPointer<vtkTubeFilter> tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection(extractEdges->GetOutputPort());
  tubes->SetRadius(.05);
  tubes->SetNumberOfSides(21);

  vtkSmartPointer<vtkPolyDataMapper> edgeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  edgeMapper->SetInputConnection(tubes->GetOutputPort());
  edgeMapper->SetScalarRange(0, 26);

  vtkSmartPointer<vtkActor> edgeActor =
    vtkSmartPointer<vtkActor>::New();
  edgeActor->SetMapper(edgeMapper);
  edgeActor->GetProperty()->SetSpecular(.6);
  edgeActor->GetProperty()->SetSpecularPower(30);
;

  // Glyph the points
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetPhiResolution(21);
  sphere->SetThetaResolution(21);
  sphere->SetRadius(.08);

  vtkSmartPointer<vtkGlyph3DMapper> pointMapper =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  pointMapper->SetInputConnection(reader->GetOutputPort());
  pointMapper->SetSourceConnection(sphere->GetOutputPort());
  pointMapper->ScalingOff();
  pointMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);
  pointActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
  pointActor->GetProperty()->SetSpecular(.6);
  pointActor->GetProperty()->SetSpecularColor(1.0,1.0,1.0);
  pointActor->GetProperty()->SetSpecularPower(100);
;

// Label the points
  vtkSmartPointer<vtkLabeledDataMapper> labelMapper = 
    vtkSmartPointer<vtkLabeledDataMapper>::New();
  labelMapper->SetInputConnection(reader->GetOutputPort());
  vtkSmartPointer<vtkActor2D> labelActor = 
    vtkSmartPointer<vtkActor2D>::New();
  labelActor->SetMapper(labelMapper);

// The geometry
  vtkSmartPointer<vtkShrinkFilter> geometryShrink = 
    vtkSmartPointer<vtkShrinkFilter>::New();
  geometryShrink->SetInputConnection(reader->GetOutputPort());
  geometryShrink->SetShrinkFactor(.8);

  vtkSmartPointer<vtkDataSetMapper> geometryMapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  geometryMapper->SetInputConnection(geometryShrink->GetOutputPort());
  geometryMapper->SetScalarModeToUseCellData();
  geometryMapper->SetScalarRange(0,11);
  vtkSmartPointer<vtkActor> geometryActor = 
    vtkSmartPointer<vtkActor>::New();
  geometryActor->SetMapper(geometryMapper);
  geometryActor->GetProperty()->SetLineWidth(3);  
  geometryActor->GetProperty()->EdgeVisibilityOn();
  geometryActor->GetProperty()->SetEdgeColor(0,0,0);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(geometryActor);
  renderer->AddActor(labelActor);
  renderer->AddActor(edgeActor);
  renderer->AddActor(pointActor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkCamera> aCamera =
    vtkSmartPointer<vtkCamera>::New();
  aCamera->Azimuth(-40.0);
  aCamera->Elevation(50.0);

  renderer->SetActiveCamera(aCamera);
  renderer->ResetCamera ();

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
