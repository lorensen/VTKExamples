### Description
This page illustrates how to use the new method '''vtkRenderWindow::InitializeFromCurrentContext()''' to associate a vtkRenderWindow instance to an existing window and activated OpenGL context.

By using this method, VTK do not create the rendering container nor the OpenGL context but inherit from the one created somewhere else.
This allows a vtkRenderWindow and thus VTK to be easily embedded in an existing graphical application.


The following code shows how to embed a VTK RenderWindow in a very simple GLUT based application which shows a vtkCone in rotation.

It has been successfully tested under Linux, Windows & MacOS X.

The interaction part is not shown here but it works as usual, you just need to pass the GLUT events to your VTK interactor.
