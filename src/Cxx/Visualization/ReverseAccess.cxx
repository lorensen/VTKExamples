//
// This example demonstrates how to access the source object
// (e.g. vtkSphereSource) from the actor reversely.
//
// some standard vtk headers
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkMath.h>

// additionally needed vtk header for this example
#include <vtkAlgorithmOutput.h>

int main(int, char *[])
{
  // source
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetRadius( 0.5 );
  // mapper
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection( sphere->GetOutputPort() );
  // actor
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper( sphereMapper );
  //renderer
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground( 0.1, 0.2, 0.4 );
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer( ren1 );
  renWin->SetSize( 300, 300 );
  // add actor to the renderer
  ren1->AddActor( sphereActor );

  //
  // Now we retrieve the source object from vtkActor reversely,
  // meaning we don't use the spheresource object we instantiated
  // above directly,
  // instead we retrieve a reference to the spheresource through the
  // actor.
  // An advantage of this concept might be that we don't need to
  // maintain the source object anymore
  // in a more complex application.
  // To demonstrate that we can modify properties of the spheresource
  // through this reference
  // beside changing some properties of the actor (in this example we
  // change actor's x-position),
  // we change the radius of the spheresource as well.
  //
  // next two lines are the core lines for reverse access
  //
  vtkSmartPointer<vtkAlgorithm> algorithm =
    sphereActor->GetMapper()->GetInputConnection(0, 0)->GetProducer();
  vtkSmartPointer<vtkSphereSource> srcReference =
    dynamic_cast<vtkSphereSource*>(algorithm.GetPointer());;

  float origRadius = srcReference->GetRadius();
  for (int i = 0; i < 360; ++i)
  {
    // change radius of the spheresource
    srcReference->SetRadius(origRadius * (1 + sin((float)i/180.0 * vtkMath::Pi())));
    // change x-position of the actor
    sphereActor->SetPosition(sin((float)i/45.0 * vtkMath::Pi())*0.5, 0, 0);
    renWin->Render();
  }

  //
  // Thanks to the usage of vtkSmartPointer there is no explicit need
  // to free any objects at this point.
  //
  return EXIT_SUCCESS;
}
