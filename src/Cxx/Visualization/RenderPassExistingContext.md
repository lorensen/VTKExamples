This example illustrates how VTK can/could be used to render into an existing non-VTK render window (OpenGL context).
The existing render window creates the OpenGL context, creates lights and a camera and controls the user interaction.
VTK is only used to render in a callback function, which is controlled by the existing render window.


In order to simulate this scenario, this example actually creates a first vtkRenderWindow with its own vtkRenderer and vtkRenderWindowInteractor. This render window could have also been created using direct OpenGL calls inside e.g. an MFC or Qt window.
This could be useful for software projects, which would like to use VTK in an existing rendering framework, without handing over 100% of control to the VTK render window / interactor.


The callback here is implemented as a vtkCommand, which calls render after the Render process has ended in the existing render window (vtkCommand::EndEvent, see [http://www.vtk.org/pipermail/vtkusers/2003-July/068584.html this post]). The actual rendering done in the callback is the most important part. It calls different render passes using the [http://www.vtk.org/Wiki/VTK/MultiPass_Rendering Multipass Framework in VTK].


Note that it is not necessary to perform a lighting or camera pass IFF the camera of the second renderer "ren2" is synchronized correctly with the camera of the first "pre-existing" renderer. In addition the render window size must be updated.

If you have any comments, please contact me at lloyd at itis.ethz.ch

I found these packages or discussions helpful:
 - [http://code.google.com/p/omegalib/ omegalib / ovtk]


Thanks!
Bryn Lloyd
