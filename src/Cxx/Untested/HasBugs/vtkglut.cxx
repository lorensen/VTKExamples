#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

vtkNew<vtkRenderer> ren;
vtkNew<vtkRenderWindow> renWin;

void Reshape(int width, int height) { renWin->SetSize(width, height); }

void Draw() {
  renWin->Render();
  ren->GetActiveCamera()->Azimuth(1);
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  // GLUT initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("VTK-GLUT Example");
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);

  // Creation of a simple VTK pipeline
  vtkNew<vtkConeSource> cone;

  vtkNew<vtkPolyDataMapper> coneMapper;
  coneMapper->SetInputConnection(cone->GetOutputPort());

  vtkNew<vtkActor> coneActor;
  coneActor->SetMapper(coneMapper.GetPointer());

  ren->AddActor(coneActor.GetPointer());
  renWin->AddRenderer(ren.GetPointer());

  // Here is the trick: we ask the RenderWindow to join the current OpenGL
  // context created by GLUT
  renWin->InitializeFromCurrentContext();

  // Let's start the main GLUT rendering loop
  glutMainLoop();

  return EXIT_SUCCESS;
}
