#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkArrowSource.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRegularPolygonSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

#include <array>
#include <vector>
#include <vtkCamera.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char , 4> bkg{{51, 77, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

  // Create container to hold the 3D object generators (sources)
  std::vector<vtkSmartPointer<vtkPolyDataAlgorithm> > geometricObjectSources;
  
  // Populate the container with the various object sources to be demonstrated
  geometricObjectSources.push_back( vtkSmartPointer<vtkArrowSource>::New() );
  geometricObjectSources.push_back( vtkSmartPointer<vtkConeSource>::New() );
  geometricObjectSources.push_back( vtkSmartPointer<vtkCubeSource>::New() );
  geometricObjectSources.push_back( vtkSmartPointer<vtkCylinderSource>::New() );
  geometricObjectSources.push_back( vtkSmartPointer<vtkDiskSource>::New() );
  geometricObjectSources.push_back( vtkSmartPointer<vtkLineSource>::New() );
  geometricObjectSources.push_back( vtkSmartPointer<vtkRegularPolygonSource>::New() );
  geometricObjectSources.push_back( vtkSmartPointer<vtkSphereSource>::New() );
  
  // Create containers for the remaining nodes of each pipeline
  std::vector<vtkSmartPointer<vtkPolyDataMapper> > mappers;
  std::vector<vtkSmartPointer<vtkActor> > actors;
  std::vector<vtkSmartPointer<vtkTextMapper> > textmappers;
  std::vector<vtkSmartPointer<vtkActor2D> > textactors;
  
  // Create a common text property.
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(16);
  textProperty->SetJustificationToCentered();

  // Create a mapper and actor for each object and the corresponding text label
  for( unsigned int i = 0; i < geometricObjectSources.size(); i++ )
  {
    geometricObjectSources[i]->Update();
    
    mappers.push_back( vtkSmartPointer<vtkPolyDataMapper>::New() );
    mappers[i]->SetInputConnection( geometricObjectSources[i]->GetOutputPort() );
    
    actors.push_back( vtkSmartPointer<vtkActor>::New() );
    actors[i]->SetMapper( mappers[i] );
    actors[i]->GetProperty()->SetColor(
      colors->GetColor3d("Seashell").GetData());
    
    textmappers.push_back( vtkSmartPointer<vtkTextMapper>::New() );
    textmappers[i]->SetInput( geometricObjectSources[i]->GetClassName() ); // set text label to the name of the object source
    textmappers[i]->SetTextProperty(textProperty);
    
    textactors.push_back( vtkSmartPointer<vtkActor2D>::New() );
    textactors[i]->SetMapper( textmappers[i] );
    textactors[i]->SetPosition( 120, 16); // Note: the position of an Actor2D is specified in display coordinates
  }
  
  // Define size of the grid that will hold the objects
  int gridCols = 3;
  int gridRows = 3;
  // Define side length (in pixels) of each renderer square
  int rendererSize = 300;
  
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Geometric Objects Demo");
  renderWindow->SetSize(rendererSize*gridCols, rendererSize*gridRows);
  
  // Set up a grid of viewports for each renderer
  for( double row = 0; row < gridRows; row++ )
  {
    for( double col = 0; col < gridCols; col++ )
    {
      double index = row*gridCols + col;
      
      // Create a renderer for this grid cell
      vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
      renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
      
      // Set the renderer's viewport dimensions (xmin, ymin, xmax, ymax) within the render window.
      // Note that for the Y values, we need to subtract the row index from gridRows
      // because the viewport Y axis points upwards, but we want to draw the grid from top to down
      double viewport[4] = {
        static_cast<double>(col) / gridCols,
        static_cast<double>(gridRows - row - 1) / gridRows,
        static_cast<double>(col + 1) / gridCols,
        static_cast<double>(gridRows - row) / gridRows };
      renderer->SetViewport(viewport);
      
      // Add the corresponding actor and label for this grid cell, if they exist
      if( index < geometricObjectSources.size() )
      {
        renderer->AddActor(actors[index]);
        renderer->AddActor(textactors[index]);
        renderer->ResetCameraClippingRange();
      }
      
      renderWindow->AddRenderer(renderer);
    }
  }
  
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  renderWindow->Render();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
