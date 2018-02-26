### Description
 This example modifies the shader to color based on model normal To do this we have to modify the vertex shader to pass the normal in model coordinates through to the fragment shader. By default the normal is converted to View coordinates and then passed on. We keep that, but add a varying for the original normal. Then we modify the fragment shader to set the diffuse color based on that normal.

!!! cite
    This example was inspired by the test [TestUserShader](https://gitlab.kitware.com/vtk/vtk/blob/master/Rendering/OpenGL2/Testing/Cxx/TestUserShader.cxx).
