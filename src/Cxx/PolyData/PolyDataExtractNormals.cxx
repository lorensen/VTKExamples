#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>

void TestPointNormals(vtkPolyData* polydata);
void TestCellNormals(vtkPolyData* polydata);

bool GetPointNormals(vtkPolyData* polydata);
bool GetCellNormals(vtkPolyData* polydata);

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();

  // If a file is provided, read it. Else, create a sphere.
  if(argc == 2)
  {

    // Read File
    std::string filename = argv[1]; //first command line argument
    std::cout << "Reading file " << filename << "..." << std::endl;

    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    std::cout << "Reading " << filename << std::endl;
    reader->SetFileName(filename.c_str());
    reader->Update();
    polydata->DeepCopy(reader->GetOutput());
  }
  else
  {
    std::cout << "Creating a sphere..." << std::endl;
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();
    std::cout << "In main: " << sphereSource->GetOutput()->GetNumberOfPoints() << std::endl;
    polydata->DeepCopy(sphereSource->GetOutput());
  }

  std::cout << "PolyData address: " << polydata << std::endl;

  TestPointNormals(polydata);

  TestCellNormals(polydata);

  return EXIT_SUCCESS;
}

void TestPointNormals(vtkPolyData* polydata)
{
  std::cout << "In TestPointNormals: " << polydata->GetNumberOfPoints() << std::endl;
  // Try to read normals directly
  bool hasPointNormals = GetPointNormals(polydata);

  if(!hasPointNormals)
  {
    std::cout << "No point normals were found. Computing normals..." << std::endl;

    // Generate normals
    vtkSmartPointer<vtkPolyDataNormals> normalGenerator =
      vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputData(polydata);
    normalGenerator->ComputePointNormalsOn();
    normalGenerator->ComputeCellNormalsOff();
    normalGenerator->Update();
    /*
    // Optional settings
    normalGenerator->SetFeatureAngle(0.1);
    normalGenerator->SetSplitting(1);
    normalGenerator->SetConsistency(0);
    normalGenerator->SetAutoOrientNormals(0);
    normalGenerator->SetComputePointNormals(1);
    normalGenerator->SetComputeCellNormals(0);
    normalGenerator->SetFlipNormals(0);
    normalGenerator->SetNonManifoldTraversal(1);
    */

    polydata = normalGenerator->GetOutput();

    // Try to read normals again
    hasPointNormals = GetPointNormals(polydata);

    std::cout << "On the second try, has point normals? " << hasPointNormals << std::endl;

  }
  else
  {
    std::cout << "Point normals were found!" << std::endl;
  }
}

void TestCellNormals(vtkPolyData* polydata)
{
  // Try to read normals directly
  bool hasCellNormals = GetCellNormals(polydata);

  if(!hasCellNormals)
  {
    std::cout << "No cell normals were found. Computing normals..." << std::endl;

    // Generate normals
    vtkSmartPointer<vtkPolyDataNormals> normalGenerator =
      vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputData(polydata);
    normalGenerator->ComputePointNormalsOff();
    normalGenerator->ComputeCellNormalsOn();
    normalGenerator->Update();
    /*
    // Optional settings
    normalGenerator->SetFeatureAngle(0.1);
    normalGenerator->SetSplitting(1);
    normalGenerator->SetConsistency(0);
    normalGenerator->SetAutoOrientNormals(0);
    normalGenerator->SetComputePointNormals(1);
    normalGenerator->SetComputeCellNormals(0);
    normalGenerator->SetFlipNormals(0);
    normalGenerator->SetNonManifoldTraversal(1);
    */

    polydata = normalGenerator->GetOutput();

    // Try to read normals again
    hasCellNormals = GetCellNormals(polydata);

    std::cout << "On the second try, has cell normals? " << hasCellNormals << std::endl;

  }
  else
  {
    std::cout << "Cell normals were found!" << std::endl;
  }
}



bool GetPointNormals(vtkPolyData* polydata)
{
  std::cout << "In GetPointNormals: " << polydata->GetNumberOfPoints() << std::endl;
  std::cout << "Looking for point normals..." << std::endl;

  // Count points
  vtkIdType numPoints = polydata->GetNumberOfPoints();
  std::cout << "There are " << numPoints << " points." << std::endl;

  // Count triangles
  vtkIdType numPolys = polydata->GetNumberOfPolys();
  std::cout << "There are " << numPolys << " polys." << std::endl;

  ////////////////////////////////////////////////////////////////
  // Double normals in an array
  vtkDoubleArray* normalDataDouble =
    dynamic_cast<vtkDoubleArray*>(polydata->GetPointData()->GetArray("Normals"));

  if(normalDataDouble)
  {
    int nc = normalDataDouble->GetNumberOfTuples();
    std::cout << "There are " << nc
            << " components in normalDataDouble" << std::endl;
    return true;
  }

  ////////////////////////////////////////////////////////////////
  // Double normals in an array
  vtkFloatArray* normalDataFloat =
    dynamic_cast<vtkFloatArray*>(polydata->GetPointData()->GetArray("Normals"));

  if(normalDataFloat)
  {
    int nc = normalDataFloat->GetNumberOfTuples();
    std::cout << "There are " << nc
            << " components in normalDataFloat" << std::endl;
    return true;
  }

  ////////////////////////////////////////////////////////////////
  // Point normals
  vtkDoubleArray* normalsDouble =
    dynamic_cast<vtkDoubleArray*>(polydata->GetPointData()->GetNormals());

  if(normalsDouble)
  {
    std::cout << "There are " << normalsDouble->GetNumberOfComponents()
              << " components in normalsDouble" << std::endl;
    return true;
  }

  ////////////////////////////////////////////////////////////////
  // Point normals
  vtkFloatArray* normalsFloat =
    dynamic_cast<vtkFloatArray*>(polydata->GetPointData()->GetNormals());

  if(normalsFloat)
  {
    std::cout << "There are " << normalsFloat->GetNumberOfComponents()
              << " components in normalsFloat" << std::endl;
    return true;
  }

  /////////////////////////////////////////////////////////////////////
  // Generic type point normals
  vtkDataArray* normalsGeneric = polydata->GetPointData()->GetNormals(); //works
  if(normalsGeneric)
  {
    std::cout << "There are " << normalsGeneric->GetNumberOfTuples()
              << " normals in normalsGeneric" << std::endl;

    double testDouble[3];
    normalsGeneric->GetTuple(0, testDouble);

    std::cout << "Double: " << testDouble[0] << " "
              << testDouble[1] << " " << testDouble[2] << std::endl;

    // Can't do this:
    /*
    float testFloat[3];
    normalsGeneric->GetTuple(0, testFloat);

    std::cout << "Float: " << testFloat[0] << " "
              << testFloat[1] << " " << testFloat[2] << std::endl;
    */
    return true;
  }


  // If the function has not yet quit, there were none of these types of normals
  std::cout << "Normals not found!" << std::endl;
  return false;

}


bool GetCellNormals(vtkPolyData* polydata)
{
  std::cout << "Looking for cell normals..." << std::endl;

  // Count points
  vtkIdType numCells = polydata->GetNumberOfCells();
  std::cout << "There are " << numCells << " cells." << std::endl;

  // Count triangles
  vtkIdType numPolys = polydata->GetNumberOfPolys();
  std::cout << "There are " << numPolys << " polys." << std::endl;

  ////////////////////////////////////////////////////////////////
  // Double normals in an array
  vtkDoubleArray* normalDataDouble =
    dynamic_cast<vtkDoubleArray*>(polydata->GetCellData()->GetArray("Normals"));

  if(normalDataDouble)
  {
    int nc = normalDataDouble->GetNumberOfTuples();
    std::cout << "There are " << nc
            << " components in normalDataDouble" << std::endl;
    return true;
  }

  ////////////////////////////////////////////////////////////////
  // Double normals in an array
  vtkFloatArray* normalDataFloat =
    dynamic_cast<vtkFloatArray*>(polydata->GetCellData()->GetArray("Normals"));

  if(normalDataFloat)
  {
    int nc = normalDataFloat->GetNumberOfTuples();
    std::cout << "There are " << nc
            << " components in normalDataFloat" << std::endl;
    return true;
  }

  ////////////////////////////////////////////////////////////////
  // Point normals
  vtkDoubleArray* normalsDouble =
    dynamic_cast<vtkDoubleArray*>(polydata->GetCellData()->GetNormals());

  if(normalsDouble)
  {
    std::cout << "There are " << normalsDouble->GetNumberOfComponents()
              << " components in normalsDouble" << std::endl;
    return true;
  }

  ////////////////////////////////////////////////////////////////
  // Point normals
  vtkFloatArray* normalsFloat =
    dynamic_cast<vtkFloatArray*>(polydata->GetCellData()->GetNormals());

  if(normalsFloat)
  {
    std::cout << "There are " << normalsFloat->GetNumberOfComponents()
              << " components in normalsFloat" << std::endl;
    return true;
  }

  /////////////////////////////////////////////////////////////////////
  // Generic type point normals
  vtkDataArray* normalsGeneric = polydata->GetCellData()->GetNormals(); //works
  if(normalsGeneric)
  {
    std::cout << "There are " << normalsGeneric->GetNumberOfTuples()
              << " normals in normalsGeneric" << std::endl;

    double testDouble[3];
    normalsGeneric->GetTuple(0, testDouble);

    std::cout << "Double: " << testDouble[0] << " "
              << testDouble[1] << " " << testDouble[2] << std::endl;

    // Can't do this:
    /*
    float testFloat[3];
    normalsGeneric->GetTuple(0, testFloat);

    std::cout << "Float: " << testFloat[0] << " "
              << testFloat[1] << " " << testFloat[2] << std::endl;
    */
    return true;
  }


  // If the function has not yet quit, there were none of these types of normals
  std::cout << "Normals not found!" << std::endl;
  return false;

}
