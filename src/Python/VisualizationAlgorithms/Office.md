### Description

Using random point seeds to create streamlines.

This example demonstrates the use of **vtkPointSource** to generate streamlines.
The dataset is a structured grid representation of a CFD simulation of flow in a small office with flow velocity and a scalar pressure field.
As this picture shows, there are a couple of bookcases, desks, a window, and an inlet and outlet for the ventilation system.
On one of the desks is a small, intense heat source (e.g., a cigarette).

We generate 25 streamlines that are started near the inlet using a **vtkPointSource** point generator.
By adjusting a single parameter (e.g., the center of the point source) it is possible to quickly explore our simulation data.

This program provides you with an optional parameter to select from one of several point source centers.
