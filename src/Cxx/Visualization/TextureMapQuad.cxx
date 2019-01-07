#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkCellArray.h>
#include <vtkJPEGReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkTexture.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkFloatArray.h>
#include <vtkPolygon.h>
#include <string>

int main ( int argc, char *argv[] )
{
  // Parse command line arguments
  if ( argc != 2 )
  {
    std::cerr << "Usage:" << argv[0] << " Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  // Read the image which will be the texture
  vtkSmartPointer<vtkJPEGReader> jPEGReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader->SetFileName ( inputFilename.c_str() );

  // Create a plane
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 2.0, 0.0);

  vtkSmartPointer<vtkCellArray> polygons =
    vtkSmartPointer<vtkCellArray>::New();
  vtkSmartPointer<vtkPolygon> polygon =
    vtkSmartPointer<vtkPolygon>::New();
  polygon->GetPointIds()->SetNumberOfIds(4); //make a quad
  polygon->GetPointIds()->SetId(0, 0);
  polygon->GetPointIds()->SetId(1, 1);
  polygon->GetPointIds()->SetId(2, 2);
  polygon->GetPointIds()->SetId(3, 3);

  polygons->InsertNextCell(polygon);

  vtkSmartPointer<vtkPolyData> quad =
    vtkSmartPointer<vtkPolyData>::New();
  quad->SetPoints(points);
  quad->SetPolys(polygons);

  vtkSmartPointer<vtkFloatArray> textureCoordinates =
    vtkSmartPointer<vtkFloatArray>::New();
  textureCoordinates->SetNumberOfComponents(2);
  textureCoordinates->SetName("TextureCoordinates");

  float tuple[2] = {0.0, 0.0};
  textureCoordinates->InsertNextTuple(tuple);
  tuple[0] = 1.0; tuple[1] = 0.0;
  textureCoordinates->InsertNextTuple(tuple);
  tuple[0] = 1.0; tuple[1] = 1.0;
  textureCoordinates->InsertNextTuple(tuple);
  tuple[0] = 0.0; tuple[1] = 2.0;
  textureCoordinates->InsertNextTuple(tuple);

  quad->GetPointData()->SetTCoords(textureCoordinates);

  // Apply the texture
  vtkSmartPointer<vtkTexture> texture =
    vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(jPEGReader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(quad);

  vtkSmartPointer<vtkActor> texturedQuad =
    vtkSmartPointer<vtkActor>::New();
  texturedQuad->SetMapper(mapper);
  texturedQuad->SetTexture(texture);

  // Visualize the textured plane
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(texturedQuad);
  renderer->SetBackground (0.4392,0.5020,0.5647);
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
