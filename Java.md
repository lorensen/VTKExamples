Click [hear](http://www.vtk.org/Wiki/VTK/Tutorials/JavaEnvironmentSetup) for a tutorial on setting up your Java environment.

It would be appreciated if there are any Python VTK experts who could convert any of the [c++ examples](Cxx) to Java!

[TOC]

#Input and Output
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Read a polydata(.vtp) file](/Java/IO/ReadPolyData) | [vtkXMLPolyDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html) | IO
[Write a polygonal data (.vtp) file](/Java/IO/WritePolyData) | [vtkXMLPolyDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html) | IO

#Implicit Functions and Iso-surfaces
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ImplicitSphere](/Java/ImplicitFunctions/ImplicitSphere) | [vtkSphere](http://www.vtk.org/doc/nightly/html/classvtkSphere.html) [vtkAppendPolyData](http://www.vtk.org/doc/nightly/html/classvtkAppendPolyData.html) [vtkTubeFilter](http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html)  | ImplicitFunctions, Append poly data, tube filter, sphere

#Data Structures
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[VisualizeKDTree](/Java/DataStructures/VisualizeKDTree)| [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html) |

#Image Processing
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ImageTest](/Java/Imaging/ImageTest) | [vtkImageReader2Factory](http://www.vtk.org/doc/nightly/html/classvtkImageReader2Factory.html) | use Java File Dialog to select Image File to Display

#Miscellaneous
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Cutter](/Java/Miscellaneous/Cutter) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html) |
[Screenshot](/Java/Miscellaneous/Screenshot) | [vtkWindowToImageFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html) |
[Cone6](/Java/Miscellaneous/Cone6) || The missing Step 6 Java example from Examples/Tutorial

#Visualization
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Animation](/Java/Visualization/Animation)  || Move a sphere across a scene
[Follower](/Java/Visualization/Follower) | [vtkFollower](http://www.vtk.org/doc/nightly/html/classvtkFollower.html) | Draw text that stays right side up
[AnimDataCone](/Java/Visualization/AnimDataCone)  | [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html) | Animate a cone by modifying the polydata points - uses Interaction M key (Motion) to toggle animation.
[ColorAnActor](/Java/Visualization/ColorAnActor) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html::GetProperty)::SetColor | Animate a cone by modifying the polydata points - uses Interaction M key (Motion) to toggle animation.
[VectorField](/Java/Visualization/VectorField) |    |

#Interaction
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[SphereInteractionPanel](/Java/Interaction/SphereInteractionPanel) | [vtkInteractorStyleSwitch](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleSwitch.html) [vtkCanvas](http://www.vtk.org/doc/nightly/html/classvtkCanvas.html)  | Switch style interaction adds C and A key actions for selecting Camera or Actor interaction, and T and J key actions for Trackball or Joystick interaction mode. Adds charEvent observer callback to restore the missing E and Q events to quit.

#Graphs
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[SelectGraphVertices](/Java/Graphs/SelectGraphVertices)  | [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html) | Select Edges and vertices in a graph

#Swing Integration
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[JFrameRender](/Java/SwingIntegration/JFrameRenderer)  | [vtkRenderWindowPanel](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowPanel.html) | Render a scene in a JFrame using a vtkRenderWindowPanel
[SwingHandleMouseEvent](/Java/SwingIntegration/SwingHandleMouseEvent)  | [vtkRenderWindowPanel](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowPanel.html) | Display in a JLabel the point the mouse is hovering over using a mouse listener
