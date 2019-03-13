#include <QApplication>

#include <vtkActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>

#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

int main(int argc, char** argv)
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

  QApplication app(argc, argv);

  QVTKOpenGLNativeWidget widget;

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  widget.setRenderWindow(renderWindow);
#else
  widget.SetRenderWindow(renderWindow);
#endif

  widget.resize(600, 600);

  vtkNew<vtkSphereSource> sphereSource;

  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkNew<vtkActor> sphereActor;
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());

  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(sphereActor);
  renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  widget.renderWindow()->AddRenderer(renderer);
  widget.renderWindow()->SetWindowName("RenderWindowNoUIFile");
#else
  widget.GetRenderWindow()->AddRenderer(renderer);
  widget.GetRenderWindow()->SetWindowName("RenderWindowNoUIFile");
#endif
  widget.show();

  app.exec();

  return EXIT_SUCCESS;
}
