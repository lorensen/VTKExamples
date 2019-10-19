### Description

Demonstrates physically based rendering, image based lighting and a skybox.

Physically based rendering sets color, metallicity and roughness of the object, sliders are provided for:
- metallicity
- roughness

Image based lighting uses a cubemap texture to specify the environment.

A Skybox is used to create the illusion of distant three-dimensional surroundings.

Textures for the image based lighting and the skymap are supplied from a cubemap.

You can select different cubemaps and different surfaces to visualise.

For more information, see [Introducing Physically Based Rendering with VTK](https://blog.kitware.com/vtk-pbr/).

!!! note
Physically Based Rendering (PBR) will be available in VTK 9.0 and is already available on the current master branch of VTK.

!!! note
The cubemap/skybox files are found in `VTKExamples/Testing/Data/skyboxes/`.
