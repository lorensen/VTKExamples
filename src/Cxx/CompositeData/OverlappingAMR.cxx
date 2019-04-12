// Demonstrates how to create and populate a VTK's Overlapping AMR Grid
// type Data

#include <vtkAMRBox.h>
#include <vtkAMRUtilities.h>
#include <vtkContourFilter.h>
#include <vtkFloatArray.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkOverlappingAMR.h>
#include <vtkOutlineFilter.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphere.h>
#include <vtkUniformGrid.h>

namespace
{
  void MakeScalars(int dims[3], double origin[3], double spacing[3],
      vtkFloatArray* scalars)
  {
    // Implicit function used to compute scalars
    vtkSmartPointer<vtkSphere> sphere =
      vtkSmartPointer<vtkSphere>::New();
    sphere->SetRadius(3);
    sphere->SetCenter(5, 5, 5);
  
    scalars->SetNumberOfTuples(dims[0]*dims[1]*dims[2]);
    for (int k=0; k<dims[2]; k++)
    {
      double z = origin[2] + spacing[2]*k;
      for (int j=0; j<dims[1]; j++)
      {
        double y = origin[1] + spacing[1]*j;
        for (int i=0; i<dims[0]; i++)
        {
          double x = origin[0] + spacing[0]*i;
          scalars->SetValue(
              k*dims[0]*dims[1] + j*dims[0] + i, 
              sphere->EvaluateFunction(x, y, z));
        }
      }
    }
  }
}

int main (int, char *[])
{  
  // Create and populate the AMR dataset
  // The dataset should look like
  // Level 0
  //   uniform grid, dimensions 11, 11, 11, AMR box (0, 0, 0) - (9, 9, 9) 
  // Level 1 - refinement ratio : 2
  //   uniform grid, dimensions 11, 11, 11, AMR box (0, 0, 0) - (9, 9, 9)
  //   uniform grid, dimensions 11, 11, 11, AMR box (10, 10, 10) - (19, 19, 19)
  // Use MakeScalars() above to fill the scalar arrays

  vtkSmartPointer<vtkOverlappingAMR> amr = 
    vtkSmartPointer<vtkOverlappingAMR>::New();
  int blocksPerLevel[] = { 1, 2 };
  amr->Initialize(2, blocksPerLevel);
    
  double origin[3] = {0.0, 0.0, 0.0};
  double spacing[3] = {1.0, 1.0, 1.0};
  int dims[3] = {11, 11, 11};

  vtkSmartPointer<vtkUniformGrid> ug1 =
    vtkSmartPointer<vtkUniformGrid>::New();
  // Geometry
  ug1->SetOrigin(origin);
  ug1->SetSpacing(spacing);
  ug1->SetDimensions(dims);
  
  // Data
  vtkSmartPointer<vtkFloatArray> scalars = 
    vtkSmartPointer<vtkFloatArray>::New(); 
  ug1->GetPointData()->SetScalars(scalars);
  MakeScalars(dims, origin, spacing, scalars);

  int lo[3] = {0, 0, 0};
  int hi[3] = {9, 9, 9};
  vtkAMRBox box1(lo, hi);
  amr->SetAMRBox(0, 0, box1);
  amr->SetDataSet(0, 0, ug1);

  double spacing2[3] = {0.5, 0.5, 0.5};

  vtkSmartPointer<vtkUniformGrid> ug2 =
    vtkSmartPointer<vtkUniformGrid>::New();
  // Geometry
  ug2->SetOrigin(origin);
  ug2->SetSpacing(spacing2);
  ug2->SetDimensions(dims);
  
  // Data
  scalars = vtkSmartPointer<vtkFloatArray>::New(); 
  ug2->GetPointData()->SetScalars(scalars);
  MakeScalars(dims, origin, spacing2, scalars);

  int lo2[3] = {0, 0, 0};
  int hi2[3] = {9, 9, 9};
  vtkAMRBox box2(lo2, hi2);
  amr->SetAMRBox(1, 0, box2);
  amr->SetDataSet(1, 0, ug2);

  double origin3[3] = {5, 5, 5};

  vtkSmartPointer<vtkUniformGrid> ug3 =
    vtkSmartPointer<vtkUniformGrid>::New();
  // Geometry
  ug3->SetOrigin(origin3);
  ug3->SetSpacing(spacing2);
  ug3->SetDimensions(dims);
  
  // Data
  scalars = vtkSmartPointer<vtkFloatArray>::New(); 
  ug3->GetPointData()->SetScalars(scalars);
  MakeScalars(dims, origin3, spacing2, scalars);

  int lo3[3] = {10, 10, 10};
  int hi3[3] = {19, 19, 19};
  vtkAMRBox box3(lo3, hi3);
  amr->SetAMRBox(1, 1, box3);
  amr->SetDataSet(1, 1, ug3);
  
  amr->SetRefinementRatio(0, 2);

  vtkAMRUtilities::BlankCells(amr);
  
  vtkSmartPointer<vtkOutlineFilter> of = 
    vtkSmartPointer<vtkOutlineFilter>::New();
  of->SetInputData(amr);
  
  vtkSmartPointer<vtkCompositeDataGeometryFilter> geomFilter =
    vtkSmartPointer<vtkCompositeDataGeometryFilter>::New();
  geomFilter->SetInputConnection(of->GetOutputPort());

  // Create an iso-surface - at 10
  vtkSmartPointer<vtkContourFilter> cf = 
    vtkSmartPointer<vtkContourFilter>::New();
  cf->SetInputData(amr);
  cf->SetNumberOfContours(1);
  cf->SetValue(0, 10.0);

  vtkSmartPointer<vtkCompositeDataGeometryFilter> geomFilter2 =
    vtkSmartPointer<vtkCompositeDataGeometryFilter>::New();
  geomFilter2->SetInputConnection(cf->GetOutputPort());

  // create the render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> aren =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin  = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(aren);
  
  vtkSmartPointer<vtkRenderWindowInteractor> iren = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  
  // associate the geometry with a mapper and the mapper to an actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  
  mapper->SetInputConnection(of->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor1 =
    vtkSmartPointer<vtkActor>::New();
     
  actor1->SetMapper(mapper);

  // associate the geometry with a mapper and the mapper to an actor
  vtkSmartPointer<vtkPolyDataMapper> mapper2 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  
  mapper2->SetInputConnection(geomFilter2->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);

  // add the actor to the renderer and start handling events
  aren->AddActor(actor1);
  aren->AddActor(actor2);
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
