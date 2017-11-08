#include <vtkSmartPointer.h>
#include <vtkCellIterator.h>
#include <vtkGenericDataSet.h>
#include <vtkGenericCell.h>
#include <vtkXMLGenericDataObjectReader.h>
#include <vtkPointSet.h>
#include <vtkCellTypes.h>

#include <map>

int main (int argc, char *argv[])
{
  std::map<std::string, int> cellMap;

  for (int arg = 1; arg < argc; ++arg)
  {
    vtkSmartPointer<vtkXMLGenericDataObjectReader> reader =
      vtkSmartPointer<vtkXMLGenericDataObjectReader>::New();
    reader->SetFileName(argv[arg]);
    reader->Update();

    vtkPointSet *pointSet = vtkPointSet::SafeDownCast(reader->GetOutput());
    vtkCellIterator *it = pointSet->NewCellIterator();
    for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell())
    {
      vtkSmartPointer<vtkGenericCell> cell =
        vtkSmartPointer<vtkGenericCell>::New();
      it->GetCell(cell);
      std::string cellName = vtkCellTypes::GetClassNameFromTypeId(cell->GetCellType());
      if (cellMap.count(cellName) == 0)
      {
        int numFaces = cell->GetNumberOfFaces();
        std::cout << "Type: " << cellName
                  << " has " << cell->GetNumberOfFaces() << " faces" << std::endl;
      }
      cellMap[cellName]++;
    }
}
  std::map <std::string, int>::iterator itm = cellMap.begin();

  for (itm = cellMap.begin(); itm != cellMap.end(); ++itm)
  {
    std::cout << itm->first << " occurs " << itm->second << " times" << std::endl;
  }

  return EXIT_SUCCESS;
}
