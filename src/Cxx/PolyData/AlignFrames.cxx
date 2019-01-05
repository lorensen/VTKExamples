#include <vtkLandmarkTransform.h>
#include <vtkMath.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkTransformFilter.h>

struct Frame
{
  Frame(float o[3], float x[3], float y[3], float z[3])
  {
    this->SetOrigin(o);
    this->SetXDirection(x);
    this->SetYDirection(y);
    this->SetZDirection(z);

    std::cout << "Origin: " << this->origin[0] << " " << this->origin[1] << " " << this->origin[2] << std::endl;
    std::cout << "xDirection: "<< this->xDirection[0] << " " << this->xDirection[1] << " " << this->xDirection[2] << std::endl;
    std::cout << "yDirection: "<< this->yDirection[0] << " " << this->yDirection[1] << " " << this->yDirection[2] << std::endl;
    std::cout << "zDirection: "<< this->zDirection[0] << " " << this->zDirection[1] << " " << this->zDirection[2] << std::endl;
  }

  void ApplyTransform(vtkTransform* transform, std::string filename)
  {
    vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
    CreatePolydata(polydata);
    
    vtkSmartPointer<vtkTransformFilter> transformFilter =
      vtkSmartPointer<vtkTransformFilter>::New();
    transformFilter->SetInputData(polydata);
    transformFilter->SetTransform(transform);
    transformFilter->Update();

    vtkSmartPointer<vtkXMLPolyDataWriter> writer =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName(filename.c_str());
    writer->SetInputConnection(transformFilter->GetOutputPort());
    writer->Write();
  }

  void CreatePolydata(vtkPolyData* polydata)
  {
    vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();

    points->InsertNextPoint(this->origin);
    float x[3];
    vtkMath::Add(this->origin, this->xDirection, x);
    points->InsertNextPoint(x);
    float y[3];
    vtkMath::Add(this->origin, this->yDirection, y);
    points->InsertNextPoint(y);
    float z[3];
    vtkMath::Add(this->origin, this->zDirection, z);
    points->InsertNextPoint(z);

    polydata->SetPoints(points);

    vtkSmartPointer<vtkVertexGlyphFilter> vertexGlyphFilter =
      vtkSmartPointer<vtkVertexGlyphFilter>::New();
    vertexGlyphFilter->AddInputData(polydata);
    vertexGlyphFilter->Update();

    polydata->ShallowCopy(vertexGlyphFilter->GetOutput());
  }
  
  void Write(std::string filename)
  {
    vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
    CreatePolydata(polydata);

    vtkSmartPointer<vtkXMLPolyDataWriter> writer =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName(filename.c_str());
    writer->SetInputData(polydata);
    writer->Write();
  }
  
  float origin[3];
  float xDirection[3];
  float yDirection[3];
  float zDirection[3];

  void SetOrigin(float o[3])
  {
    this->origin[0] = o[0];
    this->origin[1] = o[1];
    this->origin[2] = o[2];
  }
  
  void SetXDirection(float direction[3])
  {
    vtkMath::Normalize(direction);
    this->xDirection[0] = direction[0];
    this->xDirection[1] = direction[1];
    this->xDirection[2] = direction[2];
  }
  
  void SetYDirection(float direction[3])
  {
    vtkMath::Normalize(direction);
    this->yDirection[0] = direction[0];
    this->yDirection[1] = direction[1];
    this->yDirection[2] = direction[2];
  }
  
  void SetZDirection(float direction[3])
  {
    vtkMath::Normalize(direction);
    this->zDirection[0] = direction[0];
    this->zDirection[1] = direction[1];
    this->zDirection[2] = direction[2];
  }

};

void AlignFrames(Frame sourceFrame, Frame destinationFrame, vtkTransform* transform);

int main(int, char *[])
{
  float frame1origin[3] = {0,0,0};
  float frame1XDirection[3] = {1,0,0};
  float frame1YDirection[3] = {0,1,0};
  std::cout << frame1YDirection[0] << " " << frame1YDirection[1] << " " << frame1YDirection[2] << std::endl;
  float frame1ZDirection[3] = {0,0,1};
  Frame frame1(frame1origin, frame1XDirection, frame1YDirection, frame1ZDirection);
  frame1.Write("frame1.vtp");
  
  float frame2origin[3] = {0,0,0};
  float frame2XDirection[3] = {.707f,.707f,0};
  float frame2YDirection[3] = {-.707f,.707f,0};
  float frame2ZDirection[3] = {0,0,1};
  Frame frame2(frame2origin, frame2XDirection, frame2YDirection, frame2ZDirection);
  frame2.Write("frame2.vtp");
  
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  AlignFrames(frame2, frame1, transform); // Brings frame2 to frame1

  //std::cout << *transform << std::endl;

  frame2.ApplyTransform(transform, "transformed.vtp");
    
  return EXIT_SUCCESS;
}

void AlignFrames(Frame sourceFrame, Frame targetFrame, vtkTransform* transform)
{
  // This function takes two frames and finds the matrix M between them.
  
  vtkSmartPointer<vtkLandmarkTransform> landmarkTransform =
    vtkSmartPointer<vtkLandmarkTransform>::New();
    
  // Setup source points
  vtkSmartPointer<vtkPoints> sourcePoints =
    vtkSmartPointer<vtkPoints>::New();
    
  sourcePoints->InsertNextPoint(sourceFrame.origin);
  float sourceX[3];
  vtkMath::Add(sourceFrame.origin, sourceFrame.xDirection, sourceX);
  sourcePoints->InsertNextPoint(sourceX);
  float sourceY[3];
  vtkMath::Add(sourceFrame.origin, sourceFrame.yDirection, sourceY);
  sourcePoints->InsertNextPoint(sourceY);
  float sourceZ[3];
  vtkMath::Add(sourceFrame.origin, sourceFrame.zDirection, sourceZ);
  sourcePoints->InsertNextPoint(sourceZ);

  // Setup target points
  vtkSmartPointer<vtkPoints> targetPoints =
    vtkSmartPointer<vtkPoints>::New();
    
  targetPoints->InsertNextPoint(targetFrame.origin);
  float targetX[3];
  vtkMath::Add(targetFrame.origin, targetFrame.xDirection, targetX);
  targetPoints->InsertNextPoint(targetX);
  float targetY[3];
  vtkMath::Add(targetFrame.origin, targetFrame.yDirection, targetY);
  targetPoints->InsertNextPoint(targetY);
  float targetZ[3];
  vtkMath::Add(targetFrame.origin, targetFrame.zDirection, targetZ);
  targetPoints->InsertNextPoint(targetZ);

  landmarkTransform->SetSourceLandmarks(sourcePoints);
  landmarkTransform->SetTargetLandmarks(targetPoints);
  landmarkTransform->SetModeToRigidBody();
  landmarkTransform->Update();

  vtkMatrix4x4* M = landmarkTransform->GetMatrix();

  transform->SetMatrix(M);
}
