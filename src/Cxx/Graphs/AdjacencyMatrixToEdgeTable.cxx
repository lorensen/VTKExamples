/* The output is:

10 20 30
40 50 60
70 80 90

+-----------------+------------------+
|                 | value            |
+-----------------+------------------+
| 2               | 30               |
| 1               | 20               |
| 0               | 10               |
| 2               | 60               |
| 1               | 50               |
| 0               | 40               |
| 2               | 90               |
| 1               | 80               |
| 0               | 70               |
+-----------------+------------------+

The first column is the column index of the item in the 'value' column.
The row index is given by the number of times we've previously seen the column index.
For some reason, zeros in the matrix are not reported in the table.

For example, the first row says that the value '30' is in column 2 of the matrix (0-based indexing).
Since we have not previously seen an item in column 2, it is in row 0 of the matrix.

The fourth row says that the value '60' is also in column 2. We infer that '60' is row 1 of the
matrix because we have already seen one item (the '30') in column 2.
*/

#include <vtkSmartPointer.h>
#include <vtkDenseArray.h>
#include <vtkArrayToTable.h>
#include <vtkTable.h>
#include <vtkArrayData.h>
#include <vtkAdjacencyMatrixToEdgeTable.h>
#include <vtkArrayPrint.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array =
    vtkSmartPointer<vtkDenseArray<double> >::New();

  array->Resize(3,3);

  unsigned int counter = 1;
  for(vtkIdType i = 0; i < array->GetExtents()[0].GetEnd(); i++)
  {
    for(vtkIdType j = 0; j < array->GetExtents()[1].GetEnd(); j++)
    {
      array->SetValue(i, j, counter*10);
      counter++;
    }
  }

  vtkPrintMatrixFormat(std::cout, array.GetPointer());

  vtkSmartPointer<vtkArrayData> arrayData =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData->AddArray(array);

  vtkSmartPointer<vtkAdjacencyMatrixToEdgeTable> adjacencyMatrixToEdgeTable =
    vtkSmartPointer<vtkAdjacencyMatrixToEdgeTable>::New();
  adjacencyMatrixToEdgeTable->SetInputData(arrayData);
  adjacencyMatrixToEdgeTable->Update();

  adjacencyMatrixToEdgeTable->GetOutput()->Dump();

  return EXIT_SUCCESS;
}
