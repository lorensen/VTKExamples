#include <vtkSmartPointer.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkLandmarkTransform.h>
#include <vtkMath.h>
#include <vtkMatrix4x4.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char *argv[])
{
  // Ensure a filename was specified
  if ( argc != 4 )
  {
    std::cout << "Required arguments: source.vtp target.vtp output.vtp" << std::endl;
    return EXIT_FAILURE;
  }

  std::string strSource = argv[1];
  std::string strTarget = argv[2];
  std::string strOutput = argv[3];
  vtkSmartPointer<vtkXMLPolyDataReader> sourceReader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  sourceReader->SetFileName(strSource.c_str());
  sourceReader->Update();

  vtkSmartPointer<vtkXMLPolyDataReader> targetReader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  targetReader->SetFileName(strTarget.c_str());
  targetReader->Update();

  //setup ICP transform
  vtkSmartPointer<vtkIterativeClosestPointTransform> icp =
    vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
  icp->SetSource(sourceReader->GetOutput());
  icp->SetTarget(targetReader->GetOutput());
  icp->GetLandmarkTransform()->SetModeToRigidBody();
  //icp->DebugOn();
  icp->SetMaximumNumberOfIterations(20);
  icp->StartByMatchingCentroidsOn();
  icp->Modified();
  icp->Update();

  //get the resulting transformation matrix (this matrix takes the source points to the target points)
  vtkSmartPointer<vtkMatrix4x4> M = icp->GetMatrix();
  std::cout << "The resulting matrix is: " << *M << std::cout;

  //transform the source points by the ICP solution
  vtkSmartPointer<vtkTransformPolyDataFilter> iCPTransFilter =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  iCPTransFilter->SetInput(sourceReader->GetOutput());
  iCPTransFilter->SetTransform(icp);
  iCPTransFilter->Update();

  vtkSmartPointer<vtkPolyData> resultPolydata = iCPTransFilter->GetOutput();
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName(strOutput.c_str());
  writer->SetInput(resultPolydata);
  writer->Write();

  /*
  //if you need to take the target points to the source points, the matrix is:
  icp->Inverse();
  vtkSmartPointer<vtkMatrix4x4> minv = icp->GetMatrix();
  std::cout << "The resulting inverse matrix is: " << *minv << std::cout;
  */

  return EXIT_SUCCESS;
}
