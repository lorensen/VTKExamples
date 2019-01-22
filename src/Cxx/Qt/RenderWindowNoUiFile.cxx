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

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  // 8.1.0+
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#else
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
#endif
  widget.SetRenderWindow(renderWindow);

  widget.resize( 256, 256 );

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkSphereSource> sphereSource;
#else
  vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
#endif

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkPolyDataMapper> sphereMapper;
#else
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#endif
  sphereMapper->SetInputConnection( sphereSource->GetOutputPort() );

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkActor> sphereActor;
#else
  vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
#endif
  sphereActor->SetMapper( sphereMapper );

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkRenderer> renderer;
#else
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
#endif
  renderer->AddActor( sphereActor );

  widget.GetRenderWindow()->AddRenderer( renderer );
  widget.show();

  app.exec();

  return EXIT_SUCCESS;
}
