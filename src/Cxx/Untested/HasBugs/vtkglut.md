### Description

This page illustrates how to use the new method '''vtkRenderWindow::InitializeFromCurrentContext()''' to associate a vtkRenderWindow instance to an existing window and activated OpenGL context.

By using this method, VTK does not create the rendering container nor the OpenGL context but inherits from the one created somewhere else.
This allows a vtkRenderWindow and thus VTK to be easily embedded in an existing graphical application.

The following code shows how to embed a VTK RenderWindow in a very simple GLUT based application which shows a vtkCone in rotation.

The interaction part is not shown here but it works as usual, you just need to pass the GLUT events to your VTK interactor.
