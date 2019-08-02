#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkFeatureEdges.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtksys/SystemTools.hxx>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main(int argc, char *argv[])
{
  std::string fileName = "vtkSphereSource";
  if (argc > 1)
  {
    fileName = argv[1];
  }

  vtkSmartPointer<vtkPolyData> polyData =
    ReadPolyData(fileName.c_str());

  vtkSmartPointer<vtkFeatureEdges> featureEdges =
    vtkSmartPointer<vtkFeatureEdges>::New();
  featureEdges->FeatureEdgesOff();
  featureEdges->BoundaryEdgesOn();
  featureEdges->NonManifoldEdgesOn();
  featureEdges->ManifoldEdgesOff();
  featureEdges->SetInputData(polyData);
  featureEdges->Update();

  int numberOfOpenEdges = featureEdges->GetOutput()->GetNumberOfCells();

  if(numberOfOpenEdges > 0)
  {
    std::cout << fileName << ": Surface is not closed" << std::endl;
  }
  else
  {
    std::cout << fileName << ": Surface is closed" << std::endl;
  }

  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));
  if (extension == ".ply")
  {
    vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    vtkSmartPointer<vtkBYUReader> reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> source =
      vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
}
