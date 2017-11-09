### Description
This example uses vtkMassProperties to compute the volume of a closed mesh. vtkMassProperties requires triangles with consistent ordering. This example uses vtkFillHolesFilter and vtkTriangleFilter to ensure a closed, triangulated mesh. vtkPolyDataNormals enforces consistent normals.

If run with no arguments, a vtkSphereSource generates the vtkPolyData. Of given a file containing vtkPolyData, it computes that data's volume and surface area.

!!! cite
   [(Alyassin A.M. et al, "Evaluation of new algorithms for the interactive measurement of surface area and volume", Med Phys 21(6) 1994.)](https://www.researchgate.net/profile/Abdalmajeid_Alyassin/publication/15264446_Evaluation_of_new_algorithms_for_the_interactive_measurement_of_surface_area_and_volume/links/5497dff10cf29b944826369a.pdf)

