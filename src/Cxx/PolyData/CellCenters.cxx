#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkProperty.h>
#include <vtkCellCenters.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(3,3,2);
  imageData->SetSpacing(1.0, 1.0, 1.0);
  imageData->SetOrigin(0.0, 0.0, 0.0);

  vtkSmartPointer<vtkCellCenters> cellCentersFilter =
    vtkSmartPointer<vtkCellCenters>::New();
  cellCentersFilter->SetInputData(imageData);
  cellCentersFilter->VertexCellsOn();
  cellCentersFilter->Update();

  // Access the cell centers
  for(vtkIdType i = 0; i < cellCentersFilter->GetOutput()->GetNumberOfPoints(); i++)
  {
    double p[3];
    cellCentersFilter->GetOutput()->GetPoint(i, p);
    cout << "Point " << i << " : " << p[0] << " , " << p[1] << " , " << p[2] << endl;
  }

  // Display the cell centers
  vtkSmartPointer<vtkDataSetMapper> centerMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  centerMapper->SetInputConnection(cellCentersFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> centerActor =
    vtkSmartPointer<vtkActor>::New();
  centerActor->SetMapper(centerMapper);

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(imageData);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  renderWindow->AddRenderer(renderer);

  renderer->AddActor(actor);
  renderer->AddActor(centerActor);

  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
