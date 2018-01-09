//
// This example demonstrates the creation of multiple actors and the
// manipulation of their properties and transformations. It is a
// derivative of Cone.tcl, see that example for more information.
//

// First include the required header files for the VTK classes we are using.
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>


int main(int, char* [])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  //
  // Next we create an instance of vtkConeSource and set some of its
  // properties. The instance of vtkConeSource "cone" is part of a
  // visualization pipeline (it is a source process object); it produces data
  // (output type is vtkPolyData) which other filters may process.
  //
  vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
  cone->SetHeight(3.0);
  cone->SetRadius(1.0);
  cone->SetResolution(10);

  //
  // In this example we terminate the pipeline with a mapper process object.
  // (Intermediate filters such as vtkShrinkPolyData could be inserted in
  // between the source and the mapper.)  We create an instance of
  // vtkPolyDataMapper to map the polygonal data into graphics primitives. We
  // connect the output of the cone source to the input of this mapper.
  //
  vtkSmartPointer<vtkPolyDataMapper> coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(cone->GetOutputPort());

  //
  // Create an actor to represent the first cone. The actor's properties are
  // modified to give it different surface properties. By default, an actor
  // is create with a property so the GetProperty() method can be used.
  //
  vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);
  coneActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());
  coneActor->GetProperty()->SetDiffuse(0.7);
  coneActor->GetProperty()->SetSpecular(0.4);
  coneActor->GetProperty()->SetSpecularPower(20);

  //
  // Create a property and directly manipulate it. Assign it to the
  // second actor.
  //
  vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
  property->SetColor(colors->GetColor3d("Tomato").GetData());
  property->SetDiffuse(0.7);
  property->SetSpecular(0.4);
  property->SetSpecularPower(20);

  //
  // Create a second actor and a property. The property is directly
  // manipulated and then assigned to the actor. In this way, a single
  // property can be shared among many actors. Note also that we use the
  // same mapper as the first actor did. This way we avoid duplicating
  // geometry, which may save lots of memory if the geoemtry is large.
  vtkSmartPointer<vtkActor> coneActor2 = vtkSmartPointer<vtkActor>::New();
  coneActor2->SetMapper(coneMapper);
  coneActor2->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());
  coneActor2->SetProperty(property);
  coneActor2->SetPosition(0, 2, 0);

  //
  // Create the Renderer and assign actors to it. A renderer is like a
  // viewport. It is part or all of a window on the screen and it is
  // responsible for drawing the actors it has.  We also set the background
  // color here.
  //
  vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
  ren1->AddActor(coneActor);
  ren1->AddActor(coneActor2);
  ren1->SetBackground(colors->GetColor3d("LightSlateGray").GetData());

  //
  // Finally we create the render window which will show up on the screen.
  // We put our renderer into the render window using AddRenderer. We also
  // set the size to be 300 pixels by 300.
  //
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  //
  // Now we loop over 60 degrees and render the cone each time.
  //
  ren1->GetActiveCamera()->Elevation(30);
  ren1->ResetCamera();
  for (int i = 0; i < 60; ++i)
  {
    // render the image
    renWin->Render();
    // rotate the active camera by one degree
    ren1->GetActiveCamera()->Azimuth(1);
  }

  iren->Start();

  return EXIT_SUCCESS;
}
