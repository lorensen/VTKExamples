### Description
* Contributed by: Lars Friedrich, Peter Gruber

This example generates a sphere, cuts it with a plane and, therefore, generates a circlular contour (vtkPolyData). Subsequently a binary image representation (vtkImageData) is extracted from it. Internally vtkPolyDataToImageStencil and vtkLinearExtrusionFilter are utilized.
Both the circular poly data (circle.vtp) and the resultant image (labelImage.mhd) are saved to disk.

!!! note
    Similarily to example [PolyDataToImageStencil](/Python/PolyData/PolyDataToImageDataStencil), I am not really sure whether or not the image origin needs to be adjusted as the sphere-image-overlay shows some offset in paraview visualization (at least I think ...). Maybe someone could verify that. Thanks!
