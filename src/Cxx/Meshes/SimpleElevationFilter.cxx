#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkDelaunay2D.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkLookupTable.h>
#include <vtkFloatArray.h>
#include <vtkSimpleElevationFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int, char *[])
{
  // Created a grid of points (heigh/terrian map)
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
	
  unsigned int GridSize = 10;
  for(unsigned int x = 0; x < GridSize; x++)
  {
    for(unsigned int y = 0; y < GridSize; y++)
    {
      points->InsertNextPoint(x, y, (x+y)/(y+1));
    }
  }

  double bounds[6];
  points->GetBounds(bounds);

  // Add the grid points to a polydata object
  vtkSmartPointer<vtkPolyData> inputPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  inputPolyData->SetPoints(points);
	
  // Triangulate the grid points
  vtkSmartPointer<vtkDelaunay2D> delaunay =
    vtkSmartPointer<vtkDelaunay2D>::New();
  delaunay->SetInputData(inputPolyData);
  delaunay->Update();

  vtkSmartPointer<vtkSimpleElevationFilter> elevationFilter =
    vtkSmartPointer<vtkSimpleElevationFilter>::New();
  elevationFilter->SetInputConnection(delaunay->GetOutputPort());
  elevationFilter->SetVector(0.0, 0.0, 1);
  elevationFilter->Update();

  vtkSmartPointer<vtkPolyData> output =
    vtkSmartPointer<vtkPolyData>::New();
  output->ShallowCopy(dynamic_cast<vtkPolyData*>(elevationFilter->GetOutput()));

  vtkFloatArray* elevation = dynamic_cast<vtkFloatArray*>(output->GetPointData()->GetArray("Elevation"));

  // Create the color map
  vtkSmartPointer<vtkLookupTable> colorLookupTable =
    vtkSmartPointer<vtkLookupTable>::New();
  colorLookupTable->SetTableRange(bounds[4], bounds[5]);
  colorLookupTable->Build();

  // Generate the colors for each point based on the color map
  vtkSmartPointer<vtkUnsignedCharArray> colors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName("Colors");

  for(vtkIdType i = 0; i < output->GetNumberOfPoints(); i++)
  {
    double val = elevation->GetValue(i);
    std::cout << "val: " << val << std::endl;

    double dcolor[3];
    colorLookupTable->GetColor(val, dcolor);
    std::cout << "dcolor: " << dcolor[0] << " " << dcolor[1] << " " << dcolor[2] << std::endl;
    unsigned char color[3];
    for(unsigned int j = 0; j < 3; j++)
    {
      color[j] = 255 * dcolor[j]/1.0;
    }
    std::cout << "color: " << (int)color[0] << " " << (int)color[1] << " " << (int)color[2] << std::endl;

    colors->InsertNextTupleValue(color);
  }

  output->GetPointData()->AddArray(colors);

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(output);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
