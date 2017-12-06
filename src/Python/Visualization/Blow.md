### Description

Extrusion blow molding process.

In the extrusion blow molding process, a material is extruded through an annular die to form
a hollow cylinder. This cylinder is called a parison. Two mold halves are then closed on the parison, while at the same time the parison is inflated with air.
Some of the parison material remains within the mold while some becomes waste material.
The material is typically a polymer plastic softened with heat, but blow molding has been used to form metal parts. Plastic bottles are often manufactured using a blow molding process.

In this example the polymer was molded using an isothermal, nonlinear-elastic, incompressible (rubber-like) material. Triangular membrane finite elements were used to model the parison, while a combination of triangular and quadrilateral finite elements were used to model the mold. The mold surface is assumed to be rigid, and the parison is
assumed to attach to the mold upon contact. Thus the thinning of the parison is controlled by its stretching during inflation and the sequence in which it contacts the mold.

Ten steps of the analysis are illustrated. The color of the parison indicates its thickness. Using a rainbow scale, red areas are thinnest while blue regions are thickest. Our visualization shows clearly one problem with the analysis technique we are using. Note that while the nodes (i.e., points) of the finite element mesh are prevented from passing through the mold, the interior of the
triangular elements are not. This is apparent from the occlusion of the mold wireframe by the parison mesh.

You can also view the individual steps.
