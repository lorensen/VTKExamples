#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkDelimitedTextReader.h>
#include <vtkTable.h>
#include <vtkPointData.h>

#include <vtkParallelCoordinatesView.h>
#include <vtkParallelCoordinatesRepresentation.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkStringArray.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkIntArray.h>

#include <vtksys/SystemTools.hxx>

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();
  std::string title;

  if(argc > 1)
  {
    std::string inputFilename;
    inputFilename = argv[1];
    vtkSmartPointer<vtkDelimitedTextReader> reader =
      vtkSmartPointer<vtkDelimitedTextReader>::New();
    reader->SetFileName(inputFilename.c_str());
    reader->SetHaveHeaders(1);
    reader->DetectNumericColumnsOn();
    reader->SetFieldDelimiterCharacters(",");
    reader->Update();
    table = reader->GetOutput();
    title = vtksys::SystemTools::GetFilenameWithoutExtension(
      vtksys::SystemTools::GetFilenameName(inputFilename));
  }
  else
  {
    title = "Generated Data";
    vtkSmartPointer<vtkIntArray> array1 =
      vtkSmartPointer<vtkIntArray>::New();
    array1->SetName("Array1");
    array1->SetNumberOfComponents(1);
    array1->InsertNextValue(0);
    array1->InsertNextValue(1);
    array1->InsertNextValue(2);
    array1->InsertNextValue(3);
    array1->InsertNextValue(4);

    vtkSmartPointer<vtkFloatArray> array2 =
      vtkSmartPointer<vtkFloatArray>::New();
    array2->SetName("Array2");
    array2->SetNumberOfComponents(1);
    array2->InsertNextValue(-0);
    array2->InsertNextValue(-1);
    array2->InsertNextValue(-2);
    array2->InsertNextValue(-3);
    array2->InsertNextValue(-4);

    vtkSmartPointer<vtkDoubleArray> array3 =
      vtkSmartPointer<vtkDoubleArray>::New();
    array3->SetName("Array3");
    array3->SetNumberOfComponents(1);
    array3->InsertNextValue(0);
    array3->InsertNextValue(1);
    array3->InsertNextValue(4);
    array3->InsertNextValue(9);
    array3->InsertNextValue(16);

    table->AddColumn(array1);
    table->AddColumn(array2);
    table->AddColumn(array3);
  }

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();

  for (vtkIdType i = 0; i < table->GetNumberOfColumns(); ++i)
  {
    if (dynamic_cast<vtkStringArray*>(table->GetColumn(i)))
    {
      std::cout << i << " is "
                << "StringArray named ";
    }
    else if (dynamic_cast<vtkDoubleArray*>(table->GetColumn(i)))
    {
      std::cout << i << " is "
                << "DoubleArray named ";
    }
    else if (dynamic_cast<vtkFloatArray*>(table->GetColumn(i)))
    {
      std::cout << i << " is "
                << "DoubleArray named ";
    }
    else if (dynamic_cast<vtkIntArray*>(table->GetColumn(i)))
    {
      std::cout << i << " is "
                << "IntArray named ";
    }
    else
    {
      std::cout << i << " is "
                << "Unknown type named ";
    }
    std::cout << "\"" << table->GetColumn(i)->GetName() << "\"" << std::endl;

    polydata->GetPointData()->AddArray(table->GetColumn(i));

  }

  vtkSmartPointer<vtkParallelCoordinatesRepresentation> rep =
    vtkSmartPointer<vtkParallelCoordinatesRepresentation>::New();
  rep->SetInputData(polydata);

  // List all of the attribute arrays you want plotted in parallel coordinates
  // Set up the parallel coordinates Representation to be used in the View
  for (vtkIdType i = 0; i < table->GetNumberOfColumns(); ++i)
  {
    if (dynamic_cast<vtkStringArray*>(table->GetColumn(i)))
    {
      continue;
    }
    else
    {
      rep->SetInputArrayToProcess(i, 0, 0, 0, table->GetColumn(i)->GetName());
    }
  }
  rep->UseCurvesOn();
  rep->SetFontSize(.5);
  rep->SetPlotTitle(title.c_str());
  rep->SetLineOpacity(0.5);
  rep->SetLineColor(0.89, 0.81, 0.3);
  rep->SetAxisColor(1.0, 0.3882, 0.2784);
  rep->SetAxisLabelColor(1, 1, 1);

  // Set up the Parallel Coordinates View and hook in the Representation
  vtkSmartPointer<vtkParallelCoordinatesView> view =
    vtkSmartPointer<vtkParallelCoordinatesView>::New();
  view->SetRepresentation(rep);
  view->SetInspectMode(1);
  view->SetDisplayHoverText(1);

  // Brush Mode determines the type of interaction you perform to select data
  view->SetBrushModeToLasso();
  view->SetBrushOperatorToReplace();

  // Set up render window
  view->GetRenderWindow()->SetSize(600,300);
  view->ResetCamera();
  view->Render();

  // Start interaction event loop
  view->GetInteractor()->Start();
  return EXIT_SUCCESS;
}
