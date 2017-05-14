#include <vtkSphereSource.h>
#include <vtkMath.h>
#include <vtkDoubleArray.h>
#include <vtkFieldData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXYPlotActor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkXYPlotActor> plot =
      vtkSmartPointer<vtkXYPlotActor>::New();
  plot->ExchangeAxesOff();
  plot->SetLabelFormat( "%g" );
  plot->SetXTitle( "Level" );
  plot->SetYTitle( "Frequency" );
  plot->SetXValuesToIndex();

  for (unsigned int i = 0 ; i < 2 ; i++)
  {
    vtkSmartPointer<vtkDoubleArray> array_s =
        vtkSmartPointer<vtkDoubleArray>::New();
    vtkSmartPointer<vtkFieldData> field =
        vtkSmartPointer<vtkFieldData>::New();
    vtkSmartPointer<vtkDataObject> data =
        vtkSmartPointer<vtkDataObject>::New();

    for (int b = 0; b < 30; b++)   /// Assuming an array of 30 elements
    {
      double val = vtkMath::Random(0.0,2.0);
      array_s->InsertValue(b,val);
    }
    field->AddArray(array_s);
    data->SetFieldData(field);
    plot->AddDataObjectInput(data);
  }

  plot->SetPlotColor(0,1,0,0);
  plot->SetPlotColor(1,0,1,0);

  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(plot);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );
  renderWindow->SetSize(500,500);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( renderWindow );

  // Initialize the event loop and then start it
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
