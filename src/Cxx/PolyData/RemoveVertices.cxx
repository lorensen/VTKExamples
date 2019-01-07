#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>

int main ( int argc, char *argv[] )
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename.vtp" << std::endl;
    return EXIT_FAILURE;
  }
  std::string filename = argv[1];

  // Read all the data from the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  vtkSmartPointer<vtkPolyData> output = vtkSmartPointer<vtkPolyData>::New();
  output->ShallowCopy(reader->GetOutput());
  //output->SetVerts(NULL);
  vtkSmartPointer<vtkCellArray> verts = vtkSmartPointer<vtkCellArray>::New();
  output->SetVerts(verts);
  //output->SetPoints(reader->GetOutput()->GetPoints());
  //output->SetPolys(reader->GetOutput()->GetPolys());

  vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("test.vtp");
  writer->SetInputData(output);
  writer->Write();

  return EXIT_SUCCESS;
}
