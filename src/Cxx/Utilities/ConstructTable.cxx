#include <vtkTable.h>
#include <vtkVariant.h>
#include <vtkVariantArray.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  //construct an empty table
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  for ( unsigned int i = 0; i < 3; i++ )
  {
    vtkSmartPointer<vtkVariantArray> col =
      vtkSmartPointer<vtkVariantArray>::New();

    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    table->AddColumn ( col );
  }

  //fill the table with values
  unsigned int counter = 0;
  for(vtkIdType r = 0; r < table->GetNumberOfRows(); r++ )
  {
    for(vtkIdType c = 0; c < table->GetNumberOfColumns(); c++ )
    {
      table->SetValue ( r,c, vtkVariant ( counter ) );
      counter++;
    }
  }

  //print information about the table
  std::cout << "NumRows: " << table->GetNumberOfRows() << std::endl;
  std::cout << "NumCols: " << table->GetNumberOfColumns() << std::endl;

  //display the table
  table->Dump ( 3 );

  //access elements of the table
  for(vtkIdType r = 0; r < table->GetNumberOfRows(); r++ )
  {
    for(vtkIdType c = 0; c < table->GetNumberOfColumns(); c++ )
    {
    vtkVariant v = table->GetValue( r,c);
    std::cout << "(r,c) = (" << r << "," << c << ") = " << v << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
