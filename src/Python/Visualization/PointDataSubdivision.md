### Description

#### Introduction

This example demonstrates the use of the [vtkLinearSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearSubdivisionFilter.html) and [vtkButterflySubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html) .

In order to see the effects of these filters a triptych is created that demonstrates the effect of applying the filter.

The user can select from a list of sources to render, specify whether normals are displayed, what type of shading to use and the number of normals to glyph.

A representative set of sources to render are provided in the class called **Sources**. The user is encouraged to experiment with different sources to see the effect of the filters.

#### Adding more sources.
If you add more sources, you may need to provide one or all of these filters:
 - A Triangle filter
 - A Normal filter
 - An elevation filter.
 - A CleanPolyData filter.
 - For parametric sources, you may need to apply one of both of **JoinUOff()** or **JoinVOff()**.

The representative sources provided in the class **Sources** should provide good templates.
