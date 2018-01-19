### Description
This example demonstrates how to extract "computational planes" from a structured dataset. Structured data has a natural, logical coordinate system based on i-j-k indices. Specifying imin,imax, jmin,jmax, kmin,kmax pairs can indicate a point, line, plane, or volume of data.

In this example, we extract three planes and warp them using scalar values in the direction of the local normal at each point. This gives a sort of "velocity profile" that indicates the nature of the flow.
