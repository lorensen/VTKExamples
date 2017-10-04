#include <QApplication>

#include <vtkActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

#include <QVTKOpenGLWidget.h>
#include <QSurfaceFormat>

int main(int argc, char** argv)
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

  QApplication app(argc, argv);

  QVTKOpenGLWidget widget;
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  widget.SetRenderWindow(renderWindow);

  widget.resize( 256, 256 );

  vtkNew<vtkSphereSource> sphereSource;

  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection( sphereSource->GetOutputPort() );

  vtkNew<vtkActor> sphereActor;
  sphereActor->SetMapper( sphereMapper );

  vtkNew<vtkRenderer> renderer;
  renderer->AddActor( sphereActor );

  widget.GetRenderWindow()->AddRenderer( renderer );
  widget.show();

  app.exec();

  return EXIT_SUCCESS;
}
