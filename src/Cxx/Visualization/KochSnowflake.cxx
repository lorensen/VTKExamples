#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkMath.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkIntArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkLookupTable.h>
#include <vtkTriangle.h>
#include <vtkPolyLine.h>
#include <vtkCellData.h>

# define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

# define LEVEL 6

/*----------------------------------------------------------------------------*
 *                       Koch Snowflake as vtkPolyLine                        *
 *----------------------------------------------------------------------------*/
vtkSmartPointer<vtkPolyData> as_polyline(vtkSmartPointer<vtkPoints> points, int level)
{
  // Use the points from the previous iteration to create the points of the
  // next level. There is an assumption on my part that the curve is traversed
  // in a counterclockwise fashion. If the initial triangle above is written to
  // describe clockwise motion, the points will face inward instead of outward.
  for (int i = 0; i < level; i++)
  {
    // We're going to make the next set of points from the old one and swap
    // them at the end. The vtkSmartPointer will go out of scope and be
    // deleted.
    VTK_CREATE(vtkPoints, temp);
    double v0[3];
    double v1[3];

    // The first point of the previous vtkPoints is the first point of the next vtkPoints.
    points->GetPoint(0, v0);
    temp->InsertNextPoint(v0);

    // Iterate over "edges" in the vtkPoints
    for (int ii = 1; ii < points->GetNumberOfPoints(); ii++)
    {
      points->GetPoint(ii - 1, v0);
      points->GetPoint(ii, v1);
      double t = sqrt(vtkMath::Distance2BetweenPoints(v0, v1));
      double nx = (v1[0] - v0[0])/t; // x-component of edge unit tangent
      double ny = (v1[1] - v0[1])/t; // y-component of edge unit tangent

      v1[0] = v0[0] + nx*t/3.;
      v1[1] = v0[1] + ny*t/3.;
      v1[2] = 0.;
      temp->InsertNextPoint(v1);

      v1[0] = v0[0] + t*(nx/2. + ny*sqrt(3.)/6.);
      v1[1] = v0[1] + t*(ny/2. - nx*sqrt(3.)/6.);
      v1[2] = 0.;
      temp->InsertNextPoint(v1);

      v1[0] = v0[0] + 2./3.*nx*t;
      v1[1] = v0[1] + 2./3.*ny*t;
      v1[2] = 0.;
      temp->InsertNextPoint(v1);

      v1[0] = v0[0] + nx*t;
      v1[1] = v0[1] + ny*t;
      v1[2] = 0.;
      temp->InsertNextPoint(v1);
    }
    points = temp;
  }

  // draw the outline
  VTK_CREATE(vtkCellArray, lines);
  VTK_CREATE(vtkPolyLine, pl);
  pl->GetPointIds()->SetNumberOfIds(points->GetNumberOfPoints());
  for (int i = 0; i < points->GetNumberOfPoints(); i++)
  {
    pl->GetPointIds()->SetId(i, i);
  }
  lines->InsertNextCell(pl);

  // complete the polydata
  VTK_CREATE(vtkPolyData, polydata);
  polydata->SetLines(lines);
  polydata->SetPoints(points);

  return polydata;
}

/*----------------------------------------------------------------------------*
 *                Koch Snowflake as collection of vtkTriangles                *
 *----------------------------------------------------------------------------*/
void as_triangles(int start, int end, vtkCellArray *cells, int level, vtkIntArray *data)
{
  if (end - start >= 3)
  {
    int stride = (end - start + 1)/4;

    VTK_CREATE(vtkTriangle, triangle);
    triangle->GetPointIds()->SetId(0, start +   stride);
    triangle->GetPointIds()->SetId(1, start + 2*stride);
    triangle->GetPointIds()->SetId(2, start + 3*stride);

    cells->InsertNextCell(triangle);
    data->InsertNextValue(level);

    as_triangles(start,            start +   stride, cells, level + 1, data);
    as_triangles(start +   stride, start + 2*stride, cells, level + 1, data);
    as_triangles(start + 2*stride, start + 3*stride, cells, level + 1, data);
    as_triangles(start + 3*stride, start + 4*stride, cells, level + 1, data);
  }
}

/*----------------------------------------------------------------------------*
 *                                Main Method                                 *
 *----------------------------------------------------------------------------*/
int main(int, char *[]) {

  // Initially, set up the points to be an equilateral triangle. Note that the
  // first point is the same as the last point to make this a closed curve when
  // I create the vtkPolyLine.
  VTK_CREATE(vtkPoints, points);
  for (int i = 0; i < 4; i++) {
    points->InsertNextPoint(cos(2.*vtkMath::Pi()*i/3), sin(2*vtkMath::Pi()*i/3.), 0.);
  }

  vtkSmartPointer<vtkPolyData> outline_pd  = as_polyline(points, LEVEL);
  // You have already gone through the trouble of putting the points in the
  // right places - so "all" you need to do now is to create polygons from the
  // points that are in the vtkPoints.

  // The points that are passed in, have an overlap of the beginning and the end.


  // Set this up for each of the initial sides, then call the recursive function.
  VTK_CREATE(vtkCellArray, triangles);
  int stride = outline_pd->GetPoints()->GetNumberOfPoints()/3;

  // The cell data will allow us to color the triangles based on the level of
  // the iteration of the Koch snowflake.
  VTK_CREATE(vtkIntArray, data);
  data->SetNumberOfComponents(0);
  data->SetName("Iteration Level");

  // This is the starting triangle.
  VTK_CREATE(vtkTriangle, t);
  t->GetPointIds()->SetId(0,        0);
  t->GetPointIds()->SetId(1,   stride);
  t->GetPointIds()->SetId(2, 2*stride);
  triangles->InsertNextCell(t);
  data->InsertNextValue(0);

  as_triangles(       0,   stride, triangles, 1, data);
  as_triangles(  stride, 2*stride, triangles, 1, data);
  as_triangles(2*stride, 3*stride, triangles, 1, data);

  VTK_CREATE(vtkPolyData, triangle_pd);
  triangle_pd->SetPoints(outline_pd->GetPoints());
  triangle_pd->SetPolys(triangles);
  triangle_pd->GetCellData()->SetScalars(data);

  //-----------------//
  // rendering stuff //
  //-----------------//
  VTK_CREATE(vtkPolyDataMapper, outline_mapper);
  outline_mapper->SetInputData(outline_pd);

  VTK_CREATE(vtkLookupTable, lut);
  lut->SetNumberOfTableValues(256);
  lut->SetHueRange(0.6, 0.6);
  lut->SetSaturationRange(0., 1.);
  lut->Build();

  VTK_CREATE(vtkPolyDataMapper, triangle_mapper);
  triangle_mapper->SetInputData(triangle_pd);
  triangle_mapper->SetScalarRange(0.0, LEVEL);
  triangle_mapper->SetLookupTable(lut);

  VTK_CREATE(vtkActor, outline_actor);
  outline_actor->SetMapper(outline_mapper);

  VTK_CREATE(vtkActor, triangle_actor);
  triangle_actor->SetMapper(triangle_mapper);

  VTK_CREATE(vtkRenderer, outline_ren);
  outline_ren->AddActor(outline_actor);
  outline_ren->SetViewport(0.0, 0.0, 0.5, 1.0);

  VTK_CREATE(vtkRenderer, triangle_ren);
  triangle_ren->AddActor(triangle_actor);
  triangle_ren->SetViewport(0.5, 0.0, 1.0, 1.0);
  triangle_ren->SetActiveCamera(outline_ren->GetActiveCamera());

  VTK_CREATE(vtkRenderWindow, renw);
  renw->SetMultiSamples(0);
  renw->AddRenderer(outline_ren);
  renw->AddRenderer(triangle_ren);
  renw->SetSize(800, 400);

  VTK_CREATE(vtkRenderWindowInteractor, iren);
  iren->SetRenderWindow(renw);

  outline_ren->ResetCamera();
  renw->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
