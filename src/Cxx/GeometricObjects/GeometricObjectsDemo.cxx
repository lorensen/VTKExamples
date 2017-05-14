#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkTextMapper.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkArrowSource.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkRegularPolygonSource.h>
#include <vtkSphereSource.h>

#include <vector>

int main(int, char *[])
{
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
  std::vector<vtkSmartPointer<vtkRenderer> > renderers;
  std::vector<vtkSmartPointer<vtkPolyDataMapper> > mappers;
  std::vector<vtkSmartPointer<vtkActor> > actors;
  std::vector<vtkSmartPointer<vtkTextMapper> > textmappers;
  std::vector<vtkSmartPointer<vtkActor2D> > textactors;
  
  // Create a mapper and actor for each object and the corresponding text label
  for( unsigned int i = 0; i < geometricObjectSources.size(); i++ )
  {
    geometricObjectSources[i]->Update();
    
    mappers.push_back( vtkSmartPointer<vtkPolyDataMapper>::New() );
    mappers[i]->SetInputConnection( geometricObjectSources[i]->GetOutputPort() );
    
    actors.push_back( vtkSmartPointer<vtkActor>::New() );
    actors[i]->SetMapper( mappers[i] );
    
    textmappers.push_back( vtkSmartPointer<vtkTextMapper>::New() );
    textmappers[i]->SetInput( geometricObjectSources[i]->GetClassName() ); // set text label to the name of the object source
    
    textactors.push_back( vtkSmartPointer<vtkActor2D>::New() );
    textactors[i]->SetMapper( textmappers[i] );
    textactors[i]->SetPosition( 10, 10); // Note: the position of an Actor2D is specified in display coordinates
  }
  
  // Define size of the grid that will hold the objects
  int gridCols = 3;
  int gridRows = 3;
  // Define side length (in pixels) of each renderer square
  int rendererSize = 200;
  
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(rendererSize*gridCols, rendererSize*gridRows);
  
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
  // Set up a grid of viewports for each renderer
  for( double row = 0; row < gridRows; row++ )
  {
    for( double col = 0; col < gridCols; col++ )
    {
      double index = row*gridCols + col;
      
      // Create a renderer for this grid cell
      vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
      renderer->SetBackground(.1, .2, .3);
      
      // Set the renderer's viewport dimensions (xmin, ymin, xmax, ymax) within the render window.
      // Note that for the Y values, we need to subtract the row index from gridRows
      // because the viewport Y axis points upwards, but we want to draw the grid from top to down
      double viewport[4] = {
        ((col    )              * rendererSize) / (gridCols * rendererSize),
        ((gridRows - (row + 1)) * rendererSize) / (gridRows * rendererSize),
        ((col + 1)              * rendererSize) / (gridCols * rendererSize),
        ((gridRows - (row    )) * rendererSize) / (gridRows * rendererSize) };
      renderer->SetViewport(viewport);
      
      // Add the corresponding actor and label for this grid cell, if they exist
      if( index < geometricObjectSources.size() )
      {
        renderer->AddActor(actors[index]);
        renderer->AddActor(textactors[index]);
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
