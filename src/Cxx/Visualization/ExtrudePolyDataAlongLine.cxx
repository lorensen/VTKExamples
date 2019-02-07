#include <vtkSmartPointer.h>
#include <vtkRuledSurfaceFilter.h>

#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>
#include <vtkFrenetSerretFrame.h>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataNormals.h>

#include <vtkFeatureEdges.h>
#include <vtkStripper.h>
#include <vtkPolyDataConnectivityFilter.h>

#include <vtkMath.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkMatrix4x4.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>

#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtksys/SystemTools.hxx>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main(int argc, char *argv[])
{
  // For testing
  vtkMath::RandomSeed(7859821);
  // Read a polydata
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;
  
  int numberOfContours = polyData->GetNumberOfLines();
  std::cout << "Number of contours: " << numberOfContours << std::endl;

  // Generate  some random points
  int numberOfPoints = 10 ;
  vtkSmartPointer<vtkPointSource> pointSource = 
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(numberOfPoints);
  pointSource->Update();
  
  vtkPoints* points = pointSource->GetOutput()->GetPoints();
    
  vtkSmartPointer<vtkParametricSpline> spline = 
    vtkSmartPointer<vtkParametricSpline>::New();
  spline->SetPoints(points);

  vtkSmartPointer<vtkParametricFunctionSource> functionSource = 
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  functionSource->SetParametricFunction(spline);
  functionSource->SetUResolution(50 * numberOfPoints);
  functionSource->SetVResolution(50 * numberOfPoints);
  functionSource->SetWResolution(50 * numberOfPoints);

  // Create the frame
  vtkSmartPointer<vtkFrenetSerretFrame> frame =
    vtkSmartPointer<vtkFrenetSerretFrame>::New();
  frame->SetInputConnection(functionSource->GetOutputPort());
  frame->ConsistentNormalsOn();
  frame->Update();

  frame->GetOutput()->GetPointData()->SetActiveVectors("FSNormals");
  frame->GetOutput()->GetPointData()->SetActiveVectors("FSTangents");
  frame->GetOutput()->GetPointData()->SetActiveVectors("FSBinormals");

  vtkPoints *linePoints = frame->GetOutput()->GetPoints();

  std::vector<vtkSmartPointer<vtkAppendPolyData> >skeletons;
  for (int i = 0; i < numberOfContours; ++i)
  {
    skeletons.push_back(vtkSmartPointer<vtkAppendPolyData>::New());
  }

  for (int i = 0; i < linePoints->GetNumberOfPoints(); ++i)
  {
    vtkSmartPointer<vtkTransform> transform =
      vtkSmartPointer<vtkTransform>::New();

    // Compute a basis
    double normalizedX[3];
    frame->GetOutput()->GetPointData()->SetActiveVectors("FSNormals");
    frame->GetOutput()->GetPointData()->GetVectors()->GetTuple(i, normalizedX);
    double normalizedY[3];
    frame->GetOutput()->GetPointData()->SetActiveVectors("FSBinormals");
    frame->GetOutput()->GetPointData()->GetVectors()->GetTuple(i, normalizedY);
    double normalizedZ[3];
    frame->GetOutput()->GetPointData()->SetActiveVectors("FSTangents");
    frame->GetOutput()->GetPointData()->GetVectors()->GetTuple(i, normalizedZ);

    // Create the direction cosine matrix
    vtkSmartPointer<vtkMatrix4x4> matrix =
      vtkSmartPointer<vtkMatrix4x4>::New();
    matrix->Identity();
    for (unsigned int j = 0; j < 3; ++j)
    {
      matrix->SetElement(j, 0, normalizedX[j]);
      matrix->SetElement(j, 1, normalizedY[j]);
      matrix->SetElement(j, 2, normalizedZ[j]);
    }

    transform->Translate(linePoints->GetPoint(i)[0],
                         linePoints->GetPoint(i)[1],
                         linePoints->GetPoint(i)[2]);
    transform->Scale(.02, .02, .02);
    transform->Concatenate(matrix);

    vtkSmartPointer<vtkTransformPolyDataFilter> transformPD =
      vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    vtkSmartPointer<vtkPolyData> polyDataCopy =
      vtkSmartPointer<vtkPolyData>::New();
    polyDataCopy->DeepCopy(polyData);

    transformPD->SetTransform(transform);
    transformPD->SetInputData(polyDataCopy);
    transformPD->Update();

    vtkSmartPointer<vtkPolyDataConnectivityFilter> contours =
      vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
    contours->SetInputConnection(transformPD->GetOutputPort());
    contours->Update();
    for (int r = 0; r < contours->GetNumberOfExtractedRegions(); ++r)
    {
      contours->SetExtractionModeToSpecifiedRegions();
      contours->InitializeSpecifiedRegionList();
      contours->AddSpecifiedRegion(r);
      contours->Update();
      vtkSmartPointer<vtkPolyData> skeleton =
        vtkSmartPointer<vtkPolyData>::New();
      skeleton->DeepCopy(contours->GetOutput());
      skeletons[r]->AddInputData(skeleton);
    }
  }
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();

  for (int i = 0; i < numberOfContours; ++i)
  {
    vtkSmartPointer<vtkRuledSurfaceFilter> ruled = 
      vtkSmartPointer<vtkRuledSurfaceFilter>::New();
    ruled->SetRuledModeToPointWalk();
    ruled->CloseSurfaceOff();
    ruled->SetOnRatio(1);
    ruled->SetDistanceFactor(10000000);
    ruled->SetInputConnection(skeletons[i]->GetOutputPort());

    vtkSmartPointer<vtkPolyDataNormals> normals = 
      vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetInputConnection(ruled->GetOutputPort());
    vtkSmartPointer<vtkPolyDataMapper> mapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(normals->GetOutputPort());
    vtkSmartPointer<vtkProperty> backProp = 
      vtkSmartPointer<vtkProperty>::New();
    backProp->SetColor(1.0, 0.3882, 0.278);
    vtkSmartPointer<vtkActor> actor = 
      vtkSmartPointer<vtkActor>::New();
    actor->SetBackfaceProperty(backProp);
    actor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
  }  
  
  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->SetBackground(.4, .5, .7);

  // Pick a good view
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(120);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.1);
  renderer->ResetCameraClippingRange();

  renderWindow->SetSize(512, 512);
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameExtension(std::string(fileName));
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

    // Center the data
    vtkSmartPointer<vtkTransform> transform =
      vtkSmartPointer<vtkTransform>::New();
    std::cout << reader->GetOutput()->GetCenter()[0] << ", "
              << reader->GetOutput()->GetCenter()[1] << ", "
              << reader->GetOutput()->GetCenter()[2] << std::endl;
    transform->Translate(-reader->GetOutput()->GetCenter()[0],
                         -reader->GetOutput()->GetCenter()[1],
                         -reader->GetOutput()->GetCenter()[2]);
    vtkSmartPointer<vtkTransformPolyDataFilter> transformPD =
      vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    transformPD->SetTransform(transform);
    transformPD->SetInputData(reader->GetOutput());
    transformPD->Update();

    polyData = transformPD->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
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
  else
  {
    vtkSmartPointer<vtkDiskSource> diskSource = 
      vtkSmartPointer<vtkDiskSource>::New();
    diskSource->SetCircumferentialResolution(3);

    vtkSmartPointer<vtkCleanPolyData> clean = 
      vtkSmartPointer<vtkCleanPolyData>::New();
    clean->SetInputConnection(diskSource->GetOutputPort());

    vtkSmartPointer<vtkFeatureEdges> edges =
      vtkSmartPointer<vtkFeatureEdges>::New();
    edges->SetInputConnection(clean->GetOutputPort());
    edges->NonManifoldEdgesOff();
    edges->ManifoldEdgesOff();
    edges->BoundaryEdgesOn();
    edges->FeatureEdgesOff();

    vtkSmartPointer<vtkStripper> stripper =
      vtkSmartPointer<vtkStripper>::New();
    stripper->SetInputConnection(edges->GetOutputPort());
    stripper->Update();
    polyData = stripper->GetOutput();

#if 0
    vtkSmartPointer<vtkLineSource> lineSource = 
      vtkSmartPointer<vtkLineSource>::New();
    lineSource->SetResolution(10);
    lineSource->Update();
    
    polyData = lineSource->GetOutput();
#endif
  }
  return polyData;
}
}
