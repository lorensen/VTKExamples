#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkDelimitedTextWriter.h>
#include <vtkSphereSource.h>
#include <vtkVariantArray.h>
#include <vtkTable.h>

#include <sstream>
#include <string>

int main(int argc, char *argv[])
{
  std::string outputFilename = "output.txt";

  // Use the specified filename if it is provided
  if(argc == 2)
  {
    outputFilename = argv[1];
  }

  // Construct an empty table
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  for(unsigned int i = 0; i < 3; i++)
  {
    vtkSmartPointer<vtkVariantArray> col =
      vtkSmartPointer<vtkVariantArray>::New();

    std::ostringstream oss;
    oss << "column-" << i;
    std::string colName = oss.str();
    col->SetName(colName.c_str());

    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    table->AddColumn ( col );
  }

  // Fill the table with values
  unsigned int counter = 0;
  for(vtkIdType r = 0; r < table->GetNumberOfRows(); r++ )
  {
    for(vtkIdType c = 0; c < table->GetNumberOfColumns(); c++ )
    {
      table->SetValue ( r,c, vtkVariant ( counter ) );
      counter++;
    }
  }

  vtkSmartPointer<vtkDelimitedTextWriter> writer =
    vtkSmartPointer<vtkDelimitedTextWriter>::New();
  writer->SetFileName(outputFilename.c_str());
  writer->SetInputData(table);
  writer->Write();

  return EXIT_SUCCESS;
}
