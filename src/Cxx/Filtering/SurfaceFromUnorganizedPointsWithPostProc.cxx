#include <vtkVersion.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkSmartPointer.h>

#include <vtkNamedColors.h>
#include <vtkProgrammableSource.h>
#include <vtkContourFilter.h>
#include <vtkReverseSense.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>
#include <cmath>

#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

static void readPoints(vtkPoints* points);

static vtkSmartPointer<vtkPolyData> transform_back(vtkSmartPointer<vtkPoints> pt, vtkSmartPointer<vtkPolyData> pd);

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Read some points
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

  readPoints(points);

  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Construct the surface and create isosurface.	
  vtkSmartPointer<vtkSurfaceReconstructionFilter> surf =
    vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();

#if VTK_MAJOR_VERSION <= 5
  surf->SetInput(polydata);
#else
  surf->SetInputData(polydata);
#endif

  vtkSmartPointer<vtkContourFilter> contourFilter = vtkSmartPointer<vtkContourFilter>::New();
  contourFilter->SetInputConnection(surf->GetOutputPort());
  contourFilter->SetValue(0, 0.0);


  // Sometimes the contouring algorithm can create a volume whose gradient
  // vector and ordering of polygon (using the right hand rule) are
  // inconsistent. vtkReverseSense cures this problem.
  vtkSmartPointer<vtkReverseSense> reverse = vtkSmartPointer<vtkReverseSense>::New();
  reverse->SetInputConnection(contourFilter->GetOutputPort());
  reverse->ReverseCellsOn();
  reverse->ReverseNormalsOn();
  reverse->Update();

  vtkSmartPointer<vtkPolyData> newSurf = transform_back( points, reverse->GetOutput());

  vtkSmartPointer<vtkPolyDataMapper> map = vtkSmartPointer<vtkPolyDataMapper>::New();
  map->SetInputConnection(reverse->GetOutputPort());
  map->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> surfaceActor = vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper(map);
  surfaceActor->GetProperty()->SetDiffuseColor(
    namedColors->GetColor3d("Tomato").GetData());
  surfaceActor->GetProperty()->SetSpecularColor(namedColors->GetColor3d("Seashell").GetData());
  surfaceActor->GetProperty()->SetSpecular(.4);
  surfaceActor->GetProperty()->SetSpecularPower(50);

  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size
  ren->AddActor(surfaceActor);
  ren->SetBackground(namedColors->GetColor3d("Burlywood").GetData());
  renWin->SetSize(400, 400);
  ren->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  ren->GetActiveCamera()->SetPosition(1, 0, 0);
  ren->GetActiveCamera()->SetViewUp(0, 0, 1);
  ren->ResetCamera();
  ren->GetActiveCamera()->Azimuth(20);
  ren->GetActiveCamera()->Elevation(30);
  ren->GetActiveCamera()->Dolly(1.2);
  ren->ResetCameraClippingRange();

  iren->Initialize();
  renWin->Render();
  iren->Start();

  return 0;
}

vtkSmartPointer<vtkPolyData> transform_back(vtkSmartPointer<vtkPoints> pt, vtkSmartPointer<vtkPolyData> pd)
{
  // The reconstructed surface is transformed back to where the
  // original points are. (Hopefully) it is only a similarity
  // transformation.

  // 1. Get bounding box of pt, get its minimum corner (left, bottom, least-z), at c0, pt_bounds

  // 2. Get bounding box of surface pd, get its minimum corner (left, bottom, least-z), at c1, pd_bounds

  // 3. compute scale as:
  //       scale = (pt_bounds[1] - pt_bounds[0])/(pd_bounds[1] - pd_bounds[0]);

  // 4. transform the surface by T := T(pt_bounds[0], [2], [4]).S(scale).T(-pd_bounds[0], -[2], -[4])



  // 1.
  double pt_bounds[6];  // (xmin,xmax, ymin,ymax, zmin,zmax)
  pt->GetBounds(pt_bounds);


  // 2.
  double pd_bounds[6];  // (xmin,xmax, ymin,ymax, zmin,zmax)
  pd->GetBounds(pd_bounds);

//   // test, make sure it is isotropic
//   std::cout<<(pt_bounds[1] - pt_bounds[0])/(pd_bounds[1] - pd_bounds[0])<<std::endl;
//   std::cout<<(pt_bounds[3] - pt_bounds[2])/(pd_bounds[3] - pd_bounds[2])<<std::endl;
//   std::cout<<(pt_bounds[5] - pt_bounds[4])/(pd_bounds[5] - pd_bounds[4])<<std::endl;
//   // TEST


  // 3
  double scale = (pt_bounds[1] - pt_bounds[0])/(pd_bounds[1] - pd_bounds[0]);


  // 4.
  vtkSmartPointer<vtkTransform> transp = vtkSmartPointer<vtkTransform>::New();
  transp->Translate(pt_bounds[0], pt_bounds[2], pt_bounds[4]);
  transp->Scale(scale, scale, scale);
  transp->Translate(- pd_bounds[0], - pd_bounds[2], - pd_bounds[4]);

  vtkSmartPointer<vtkTransformPolyDataFilter> tpd = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  tpd->SetInput(pd);
#else
  tpd->SetInputData(pd);
#endif
  tpd->SetTransform(transp);
  tpd->Update();


  return tpd->GetOutput();
}


void readPoints(vtkPoints* points)
{

  float x, y, z;
  // generate random points on unit sphere
  for(int i=0; i<5000; i++)
  {

      double u = vtkMath::Random(0.0,1.0);
      double v = vtkMath::Random(0.0,1.0);
      double phi = 2.0*3.14159265*u;
      double theta = acos(2.0*v-1.0);

      x = std::cos(phi)*std::sin(theta);
      y = std::sin(phi)*std::sin(theta);
      z = std::cos(theta);

      points->InsertNextPoint(x, y, z);
  }

  return;
}
