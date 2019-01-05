#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkDelaunay2D.h>
#include <vtkLookupTable.h>
#include <vtkMath.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataWriter.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int, char *[])
{
  // Create a grid of points (height/terrian map)
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  unsigned int GridSize = 20;
  double xx, yy, zz;
  for(unsigned int x = 0; x < GridSize; x++)
  {
    for(unsigned int y = 0; y < GridSize; y++)
    {
      xx = x + vtkMath::Random(-.2, .2);
      yy = y + vtkMath::Random(-.2, .2);
      zz = vtkMath::Random(-.5, .5);
      points->InsertNextPoint(xx, yy, zz);
    }
  }

  // Add the grid points to a polydata object
  vtkSmartPointer<vtkPolyData> inputPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  inputPolyData->SetPoints(points);

  // Triangulate the grid points
  vtkSmartPointer<vtkDelaunay2D> delaunay =
    vtkSmartPointer<vtkDelaunay2D>::New();
  delaunay->SetInputData(inputPolyData);
  delaunay->Update();
  vtkPolyData* outputPolyData = delaunay->GetOutput();

  double bounds[6];
  outputPolyData->GetBounds(bounds);

  // Find min and max z
  double minz = bounds[4];
  double maxz = bounds[5];

  std::cout << "minz: " << minz << std::endl;
  std::cout << "maxz: " << maxz << std::endl;

  // Create the color map
  vtkSmartPointer<vtkLookupTable> colorLookupTable =
    vtkSmartPointer<vtkLookupTable>::New();
  colorLookupTable->SetTableRange(minz, maxz);
  colorLookupTable->Build();

  // Generate the colors for each point based on the color map
  vtkSmartPointer<vtkUnsignedCharArray> colors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName("Colors");

  std::cout << "There are " << outputPolyData->GetNumberOfPoints()
            << " points." << std::endl;

  for(int i = 0; i < outputPolyData->GetNumberOfPoints(); i++)
  {
    double p[3];
    outputPolyData->GetPoint(i,p);

    double dcolor[3];
    colorLookupTable->GetColor(p[2], dcolor);
    std::cout << "dcolor: "
              << dcolor[0] << " "
              << dcolor[1] << " "
              << dcolor[2] << std::endl;
    unsigned char color[3];
    for(unsigned int j = 0; j < 3; j++)
    {
      color[j] = static_cast<unsigned char>(255.0 * dcolor[j]);
    }
    std::cout << "color: "
              << (int)color[0] << " "
              << (int)color[1] << " "
              << (int)color[2] << std::endl;

    colors->InsertNextTupleValue(color);
  }

  outputPolyData->GetPointData()->SetScalars(colors);

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(outputPolyData);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .3);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
