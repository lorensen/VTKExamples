#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkThreshold.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkMeshQuality.h>
#include <vtkSphereSource.h>
#include <vtkTriangleFilter.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
      vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(sphereSource->GetOutputPort());
  triangleFilter->Update();

    //Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> sphereMapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
  sphereMapper->SetInputConnection(triangleFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
      vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  vtkPolyData* mesh = triangleFilter->GetOutput();
  cout << "There are " << mesh->GetNumberOfCells() << " cells." << endl;

  vtkSmartPointer<vtkMeshQuality> qualityFilter =
      vtkSmartPointer<vtkMeshQuality>::New();
  qualityFilter->SetInputData(mesh);
  qualityFilter->SetTriangleQualityMeasureToArea();
  qualityFilter->Update();

  vtkDataSet* qualityMesh = qualityFilter->GetOutput();
  vtkSmartPointer<vtkDoubleArray> qualityArray =
    dynamic_cast<vtkDoubleArray*>(qualityMesh->GetCellData()->GetArray("Quality"));

  cout << "There are " << qualityArray->GetNumberOfTuples() << " values." << endl;

  for(vtkIdType i = 0; i < qualityArray->GetNumberOfTuples(); i++)
  {
    double val = qualityArray->GetValue(i);
    cout << "value " << i << " : " << val << endl;
  }

  vtkSmartPointer<vtkThreshold> selectCells =
    vtkSmartPointer<vtkThreshold>::New();
  selectCells->ThresholdByLower(.02);
  selectCells->SetInputArrayToProcess( 0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS,
              vtkDataSetAttributes::SCALARS );
  selectCells->SetInputData(qualityMesh);
  selectCells->Update();

  vtkUnstructuredGrid* ug = selectCells->GetOutput();

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(ug);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
  actor->GetProperty()->SetRepresentationToWireframe();
  actor->GetProperty()->SetLineWidth(5);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->AddActor(sphereActor);
  renderer->SetBackground(1,1,1); // Background color white

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
