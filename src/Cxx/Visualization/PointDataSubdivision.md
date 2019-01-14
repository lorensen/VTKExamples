### Description

#### Introduction

This example demonstrates the use of the vtkLinearSubdivisionFilter and vtkButterflySubdivisionFilter.

In order to see the effects of these filters a triptych is created that demonstrates the effect of applying the filter.

The user can select from a list of sources to render, specify whether normals are displayed, what type of shading to use and the number of normals to glyph.

A representative set of sources to render are provided in the class called **Sources**. The user is encouraged to experiment with different sources to see the effect of the filters.

#### Adding more sources.
If you add more sources, you may need to provide one or all of these filters:
 - A vtkTriangleFilter
 - A vtkPolyDataNormals filter
 - A vtkElevationFilter.
 - A vtkCleanPolyData filter.
 - For parametric sources, you may need to apply one of both of **JoinUOff()** or **JoinVOff()**.

The representative sources provided in the class **Sources** should provide good templates.
