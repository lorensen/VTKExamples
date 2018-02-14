#include <vtkSmartPointer.h>
#include <vtkPCAStatistics.h>

#include <vtkLine.h>
#include <vtkLineSource.h>
#include <vtkTransform.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkMath.h>
#include <vtkDoubleArray.h>
#include <vtkTable.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>

#include <vtkNamedColors.h>

int main(int, char*[])
{
  vtkMath::RandomSeed(0);

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  for(unsigned int i = 0; i < 200; i++)
  {
    double x = vtkMath::Gaussian(0, 2);
    double y = vtkMath::Gaussian(0, 5);
    points->InsertNextPoint(x,y,0);
  }
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->RotateZ(30);

  vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformFilter->SetTransform(transform);
  transformFilter->SetInputData(polydata);
  transformFilter->Update();

  // These would be all of your "x" values.
  vtkSmartPointer<vtkDoubleArray> xArray =
    vtkSmartPointer<vtkDoubleArray>::New();
  xArray->SetNumberOfComponents(1);
  xArray->SetName("x");

  // These would be all of your "y" values.
  vtkSmartPointer<vtkDoubleArray> yArray =
    vtkSmartPointer<vtkDoubleArray>::New();
  yArray->SetNumberOfComponents(1);
  yArray->SetName("y");

  for(vtkIdType i = 0; i < polydata->GetNumberOfPoints(); i++)
  {
    double p[3];
    transformFilter->GetOutput()->GetPoint(i,p);
    xArray->InsertNextValue(p[0]);
    yArray->InsertNextValue(p[1]);
  }

  vtkSmartPointer<vtkTable> datasetTable =
    vtkSmartPointer<vtkTable>::New();
  datasetTable->AddColumn(xArray);
  datasetTable->AddColumn(yArray);

  vtkSmartPointer<vtkPCAStatistics> pcaStatistics =
    vtkSmartPointer<vtkPCAStatistics>::New();
  pcaStatistics->SetInputData( vtkStatisticsAlgorithm::INPUT_DATA, datasetTable );

  pcaStatistics->SetColumnStatus("x", 1 );
  pcaStatistics->SetColumnStatus("y", 1 );

  pcaStatistics->RequestSelectedColumns();
  pcaStatistics->SetDeriveOption(true);
  pcaStatistics->Update();

  ///////// Eigenvalues ////////////
  vtkSmartPointer<vtkDoubleArray> eigenvalues =
    vtkSmartPointer<vtkDoubleArray>::New();
  pcaStatistics->GetEigenvalues(eigenvalues);
  for(vtkIdType i = 0; i < eigenvalues->GetNumberOfTuples(); i++)
  {
    std::cout << "Eigenvalue " << i << " = " << eigenvalues->GetValue(i) << std::endl;
  }

  ///////// Eigenvectors ////////////
  vtkSmartPointer<vtkDoubleArray> eigenvectors =
    vtkSmartPointer<vtkDoubleArray>::New();

  pcaStatistics->GetEigenvectors(eigenvectors);

  vtkSmartPointer<vtkDoubleArray> evec1 =
    vtkSmartPointer<vtkDoubleArray>::New();
  pcaStatistics->GetEigenvector(0, evec1);

  vtkSmartPointer<vtkDoubleArray> evec2 =
    vtkSmartPointer<vtkDoubleArray>::New();
  pcaStatistics->GetEigenvector(1, evec2);

  double scale = 3.0;
  vtkSmartPointer<vtkLineSource> vector1Source =
    vtkSmartPointer<vtkLineSource>::New();
  vector1Source->SetPoint1(0,0,0);
  vector1Source->SetPoint1(scale * evec1->GetValue(0), scale* evec1->GetValue(1),0);

  vtkSmartPointer<vtkPolyDataMapper> vec1Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vec1Mapper->SetInputConnection(vector1Source->GetOutputPort());

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> vector1Actor =
    vtkSmartPointer<vtkActor>::New();
  vector1Actor->SetMapper(vec1Mapper);
  vector1Actor->GetProperty()->SetColor(colors->GetColor3d("LimeGreen").GetData());
  vector1Actor->GetProperty()->SetLineWidth(3);

  vtkSmartPointer<vtkLineSource> vector2Source =
    vtkSmartPointer<vtkLineSource>::New();
  vector2Source->SetPoint1(0,0,0);
  vector2Source->SetPoint1(scale* evec2->GetValue(0), scale*evec2->GetValue(1),0);


  vtkSmartPointer<vtkPolyDataMapper> vec2Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vec2Mapper->SetInputConnection(vector2Source->GetOutputPort());

  vtkSmartPointer<vtkActor> vector2Actor =
    vtkSmartPointer<vtkActor>::New();
  vector2Actor->SetMapper(vec2Mapper);
  vector2Actor->GetProperty()->SetColor(colors->GetColor3d("Crimson").GetData());
  vector2Actor->GetProperty()->SetLineWidth(3);

  // Project all of the points onto the eigenvector with
  // the largest eigenvalues
  double p0[3];
  p0[0] = -100*evec1->GetValue(0);
  p0[1] = -100*evec1->GetValue(1);
  p0[2] = 0;
  double p1[3];
  p1[0] = 100*evec1->GetValue(0);
  p1[1] = 100*evec1->GetValue(1);
  p1[2] = 0;

  vtkSmartPointer<vtkPoints> projectedPoints =
    vtkSmartPointer<vtkPoints>::New();
  for(vtkIdType i = 0; i < polydata->GetNumberOfPoints(); i++)
  {
    double p[3];
    transformFilter->GetOutput()->GetPoint(i,p);
    double t;
    double closestPoint[3];
    vtkLine::DistanceToLine(p, p0, p1, t, closestPoint);
    double newP[3];
    double v[3];
    vtkMath::Subtract(p1, p0, v);
    vtkMath::Normalize(v);
    vtkMath::MultiplyScalar(v, t);
    vtkMath::Add(p0, v, newP);
    projectedPoints->InsertNextPoint(t, 0, 0);
  }

  vtkSmartPointer<vtkPolyData> projectedPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  projectedPolyData->SetPoints(projectedPoints);

  vtkSmartPointer<vtkVertexGlyphFilter> projectedGlyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  projectedGlyphFilter->SetInputData(projectedPolyData);
  projectedGlyphFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> projectedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  projectedMapper->SetInputConnection(projectedGlyphFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> projectedActor =
    vtkSmartPointer<vtkActor>::New();
  projectedActor->SetMapper(projectedMapper);
  projectedActor->GetProperty()->SetPointSize(3);

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(colors->GetColor3d("burlywood").GetData());

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(colors->GetColor3d("slate_grey").GetData());

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  glyphFilter->SetInputConnection(transformFilter->GetOutputPort());
  glyphFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(glyphFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetPointSize(3);

  leftRenderer->AddActor(originalActor);
  leftRenderer->AddActor(vector1Actor);
  leftRenderer->AddActor(vector2Actor);

  rightRenderer->AddActor(projectedActor);

  leftRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
