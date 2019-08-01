#include <vtkCellIterator.h>
#include <vtkCellTypes.h>
#include <vtkGenericCell.h>
#include <vtkGenericDataSet.h>
#include <vtkPointSet.h>
#include <vtkSmartPointer.h>
#include <vtkXMLGenericDataObjectReader.h>

#include <map>

int main(int argc, char* argv[])
{
  std::map<std::string, int> cellMap;

  for (int arg = 1; arg < argc; ++arg)
  {
    auto reader =
      vtkSmartPointer<vtkXMLGenericDataObjectReader>::New();
    reader->SetFileName(argv[arg]);
    reader->Update();

    //    vtkPointSet *pointSet =
    //    vtkPointSet::SafeDownCast(reader->GetOutput());;
    vtkPointSet* pointSet = dynamic_cast<vtkPointSet*>(reader->GetOutput());
    ;
    auto it = pointSet->NewCellIterator();
    for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell())
    {
      auto cell = vtkSmartPointer<vtkGenericCell>::New();
      it->GetCell(cell);
      std::string cellName =
          vtkCellTypes::GetClassNameFromTypeId(cell->GetCellType());
      if (cellMap.count(cellName) == 0)
      {
        std::cout << "Type: " << cellName << " has " << cell->GetNumberOfFaces()
                  << " faces" << std::endl;
      }
      cellMap[cellName]++;
    }
    it->Delete();
  }
  for (auto itm = cellMap.begin(); itm != cellMap.end(); ++itm)
  {
    std::cout << itm->first << " occurs " << itm->second << " times"
              << std::endl;
  }

  return EXIT_SUCCESS;
}
