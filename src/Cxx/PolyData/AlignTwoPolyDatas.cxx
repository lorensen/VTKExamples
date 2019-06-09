#include <vtkSmartPointer.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkLandmarkTransform.h>
#include <vtkPoints.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>
#include <vtkHausdorffDistancePointSetFilter.h>
#include <vtkFieldData.h>

#include <vtkOBBTree.h>
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>
#include <vtksys/SystemTools.hxx>

#include <string>
#include <algorithm>
#include <random>
#include <array>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
void AlignBoundingBoxes (vtkPolyData *, vtkPolyData *);
void BestBoundingBox (
  std::string axis,
  vtkPolyData *target,
  vtkPolyData *source,
  vtkPolyData *targetLandmarks,
  vtkPolyData *sourceLandmarks,
  double      &distance,
  vtkPoints   *bestPoints);
}

int main (int argc, char *argv[])
{
  // Vis Pipeline
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto renderer = vtkSmartPointer<vtkRenderer>::New();

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->SetBackground(colors->GetColor3d("sea_green_light").GetData());
  renderer->UseHiddenLineRemovalOn();

  std::cout << "Loading source: " << argv[1] << std::endl;
  auto sourcePolyData = ReadPolyData(argv[1]);

  // Save the source polydata in case the align does not improve
  // segmentation
  auto originalSourcePolyData = vtkSmartPointer<vtkPolyData>::New();
  originalSourcePolyData->DeepCopy(sourcePolyData);

  std::cout << "Loading target: " << argv[2] << std::endl;
  auto targetPolyData = ReadPolyData(argv[2]);

  auto distance =
    vtkSmartPointer<vtkHausdorffDistancePointSetFilter>::New();
  distance->SetInputData(0, targetPolyData);
  distance->SetInputData(1, sourcePolyData);
  distance->Update();

  double distanceBeforeAlign =
    static_cast<vtkPointSet*>(distance->GetOutput(0))->GetFieldData()->GetArray("HausdorffDistance")->GetComponent(0,0);

  // Get initial alignment using oriented bounding boxes
  AlignBoundingBoxes(sourcePolyData, targetPolyData);

  distance->SetInputData(0, targetPolyData);
  distance->SetInputData(1, sourcePolyData);
  distance->Modified();
  distance->Update();
  double distanceAfterAlign =
    static_cast<vtkPointSet*>(distance->GetOutput(0))->GetFieldData()->GetArray("HausdorffDistance")->GetComponent(0,0);

  double bestDistance = std::min(distanceBeforeAlign, distanceAfterAlign);

  if (distanceAfterAlign > distanceBeforeAlign)
  {
    sourcePolyData->DeepCopy(originalSourcePolyData);
  }

  // Refine the alignment using IterativeClosestPoint
  auto icp = vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
  icp->SetSource(sourcePolyData);
  icp->SetTarget(targetPolyData);
  icp->GetLandmarkTransform()->SetModeToRigidBody();
  icp->SetMaximumNumberOfLandmarks(100);
  icp->SetMaximumMeanDistance(.00001);
  icp->SetMaximumNumberOfIterations(500);
  icp->CheckMeanDistanceOn();
  icp->StartByMatchingCentroidsOn();
  icp->Update();

//  icp->Print(std::cout);

  auto lmTransform = icp->GetLandmarkTransform();
  auto transform = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transform->SetInputData(sourcePolyData);
  transform->SetTransform(lmTransform);
  transform->SetTransform(icp);
  transform->Update();

  distance->SetInputData(0, targetPolyData);
  distance->SetInputData(1, transform->GetOutput());
  distance->Update();

  double distanceAfterICP =
    static_cast<vtkPointSet*>(distance->GetOutput(0))->GetFieldData()->GetArray("HausdorffDistance")->GetComponent(0,0);

  if (distanceAfterICP < bestDistance)
  {
    bestDistance = distanceAfterICP;
  }

  std::cout << "Distance before, after align, after ICP, min: "
            << distanceBeforeAlign << ", "
            << distanceAfterAlign << ", "
            << distanceAfterICP << ", "
            << bestDistance << std::endl;

  // Select
  auto sourceMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  if (bestDistance == distanceBeforeAlign)
  {
    sourceMapper->SetInputData(originalSourcePolyData);
    std::cout << "Using original alignment" << std::endl;
  }
  else if (bestDistance == distanceAfterAlign)
  {
    sourceMapper->SetInputData(sourcePolyData);
    std::cout << "Using alignment by OBB" << std::endl;
  }
  else
  {
    sourceMapper->SetInputConnection(transform->GetOutputPort());
    std::cout << "Using alignment by ICP" << std::endl;
  }
  sourceMapper->ScalarVisibilityOff();

  auto sourceActor = vtkSmartPointer<vtkActor>::New();
  sourceActor->SetMapper(sourceMapper);
  sourceActor->GetProperty()->SetOpacity(.6);
  sourceActor->GetProperty()->SetDiffuseColor(
    colors->GetColor3d("White").GetData());
  renderer->AddActor(sourceActor);

  auto targetMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  targetMapper->SetInputData(targetPolyData);
  targetMapper->ScalarVisibilityOff();

  auto targetActor = vtkSmartPointer<vtkActor>::New();
  targetActor->SetMapper(targetMapper);
  targetActor->GetProperty()->SetDiffuseColor(
    colors->GetColor3d("Tomato").GetData());
  renderer->AddActor(targetActor);

  renderWindow->AddRenderer(renderer);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension =
    vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));

  // Drop the case of the extension
  std::transform(extension.begin(), extension.end(),
                 extension.begin(), ::tolower);

  if (extension == ".ply")
  {
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader = vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}

void AlignBoundingBoxes (vtkPolyData *source, vtkPolyData *target)
{
  // Use OBBTree to create an oriented bounding box for target and source
  auto sourceOBBTree = vtkSmartPointer<vtkOBBTree>::New();
  sourceOBBTree->SetDataSet(source);
  sourceOBBTree->SetMaxLevel(1);
  sourceOBBTree->BuildLocator();

  auto targetOBBTree = vtkSmartPointer<vtkOBBTree>::New();
  targetOBBTree->SetDataSet(target);
  targetOBBTree->SetMaxLevel(1);
  targetOBBTree->BuildLocator();

  auto sourceLandmarks = vtkSmartPointer<vtkPolyData>::New();
  sourceOBBTree->GenerateRepresentation(0, sourceLandmarks);

  auto targetLandmarks = vtkSmartPointer<vtkPolyData>::New();
  targetOBBTree->GenerateRepresentation(0, targetLandmarks);

  auto lmTransform = vtkSmartPointer<vtkLandmarkTransform>::New();
  lmTransform->SetModeToSimilarity();
  lmTransform->SetTargetLandmarks(targetLandmarks->GetPoints());
  auto lmTransformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  double bestDistance = VTK_DOUBLE_MAX;
  auto bestPoints = vtkSmartPointer<vtkPoints>::New();
  BestBoundingBox(
    "X",
    target,
    source,
    targetLandmarks,
    sourceLandmarks,
    bestDistance,
    bestPoints);
  BestBoundingBox(
    "Y",
    target,
    source,
    targetLandmarks,
    sourceLandmarks,
    bestDistance,
    bestPoints);
  BestBoundingBox(
    "Z",
    target,
    source,
    targetLandmarks,
    sourceLandmarks,
    bestDistance,
    bestPoints);

  lmTransform->SetSourceLandmarks(bestPoints);
  lmTransform->Modified();
  
  auto transformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformPD->SetInputData(source);
  transformPD->SetTransform(lmTransform);
  transformPD->Update();

  source->DeepCopy(transformPD->GetOutput());

}
void BestBoundingBox (
  std::string axis,
  vtkPolyData *target,
  vtkPolyData *source,
  vtkPolyData *targetLandmarks,
  vtkPolyData *sourceLandmarks,
  double      &bestDistance,
  vtkPoints   *bestPoints)
{
  auto distance =
    vtkSmartPointer<vtkHausdorffDistancePointSetFilter>::New();
  auto testTransform = vtkSmartPointer<vtkTransform>::New();
  auto testTransformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  auto lmTransform = vtkSmartPointer<vtkLandmarkTransform>::New();
  auto lmTransformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();

  lmTransform->SetModeToSimilarity();
  lmTransform->SetTargetLandmarks(targetLandmarks->GetPoints());

  double sourceCenter[3];
  sourceLandmarks->GetCenter(sourceCenter);

  auto delta = 90.0;
  for (auto i = 0; i < 4; ++i)
  {
    auto angle = delta * i;
    // Rotate about center
    testTransform->Identity();
    testTransform->Translate(
      sourceCenter[0], sourceCenter[1], sourceCenter[2]);
    if (axis == "X")
    {
      testTransform->RotateX(angle);
    }
    else if (axis == "Y")
    {
      testTransform->RotateY(angle);
    }
    else
    {
      testTransform->RotateZ(angle);
    }
    testTransform->Translate(
      -sourceCenter[0], -sourceCenter[1], -sourceCenter[2]);

    testTransformPD->SetTransform(testTransform);
    testTransformPD->SetInputData(sourceLandmarks);
    testTransformPD->Update();

    lmTransform->SetSourceLandmarks(testTransformPD->GetOutput()->GetPoints());
    lmTransform->Modified();

    lmTransformPD->SetInputData(source);
    lmTransformPD->SetTransform(lmTransform);
    lmTransformPD->Update();

    distance->SetInputData(0, target);
    distance->SetInputData(1, lmTransformPD->GetOutput());
    distance->Update();
  
    double testDistance =
      static_cast<vtkPointSet*>(distance->GetOutput(0))->GetFieldData()->GetArray("HausdorffDistance")->GetComponent(0,0);
    if (testDistance < bestDistance)
    {
      bestDistance = testDistance;
      bestPoints->DeepCopy(testTransformPD->GetOutput()->GetPoints());
    }
  }
  return;
}

}

