#include <vtkSmartPointer.h>
#include <vtkDelimitedTextReader.h>

#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkDoubleArray.h>
#include <vtkTable.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVersionMacros.h> // For version macros
#include <vtkVertexGlyphFilter.h>

#include <vtkNamedColors.h>
int main(int argc, char* argv[])
{
  // Verify input arguments
  if(argc != 2)
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.xyz)" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  vtkSmartPointer<vtkDelimitedTextReader> reader =
    vtkSmartPointer<vtkDelimitedTextReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->DetectNumericColumnsOn();
  reader->SetFieldDelimiterCharacters(" ");
  reader->Update();

  vtkTable* table = reader->GetOutput();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkDoubleArray> normals =
    vtkSmartPointer<vtkDoubleArray>::New();

  normals->SetNumberOfComponents(3); //3d normals (ie x,y,z)

  std::cout << "Table has " << table->GetNumberOfRows()
            << " rows." << std::endl;
  std::cout << "Table has " << table->GetNumberOfColumns()
            << " columns." << std::endl;

  for(vtkIdType i = 0; i < table->GetNumberOfRows(); i++)
  {
    std::cout << "x: " << (table->GetValue(i,0)).ToDouble()
              << " y: " << (table->GetValue(i,1)).ToDouble()
              << " z: " << (table->GetValue(i,2)).ToDouble();

    points->InsertNextPoint((table->GetValue(i,0)).ToDouble(),
                            (table->GetValue(i,1)).ToDouble(),
                            (table->GetValue(i,2)).ToDouble());

    double n[3];
    n[0] = (table->GetValue(i,3)).ToDouble();
    n[1] = (table->GetValue(i,4)).ToDouble();
    n[2] = (table->GetValue(i,5)).ToDouble();

    std::cout << " n: " << n[0] << " " << n[1] << " " << n[2] << std::endl;
    normals->InsertNextTuple(n);
  }

  std::cout << "There are " << points->GetNumberOfPoints()
            << " points." << std::endl;

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->SetNormals(normals);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  glyphFilter->SetInputData(polydata);
  glyphFilter->Update();

  // Visualize
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(30);
  actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Mint").GetData());

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
