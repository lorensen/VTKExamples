### Description
In this example we are coloring the surface by partitioning the elevation
into bands and using arrows to display the normals on the surface.

Rather beautiful surfaces are generated.

The banded contour filter and an indexed lookup table are used along with 
the elevation filter to generate the banding on the surface.
To further enhance the surface the surface normals are
glyphed and colored by elevation using the default lookup table. 

The example also demonstrates partitioning the pipelines into functions.

For generating surfaces, the trick here is to return [vtkPolydata](http://www.vtk.org/doc/nightly/html/classvtkPolydata.html) for surfaces
thereby hiding the particular surface properties in the implementation of the
function. This allows us to specify multiple surface types and, in this code,
to use the name of the surface to pick the one we want.

The process is as follows:

1. Use an enum to select your surface.

2. Use [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html) to make an indexed lookup table.

3. Then we use the number of colors in the lookup table and the scalar range of the surface to create a list/vector of bands.

4. This list is then used to define the labels for the scalar bar using the midpoints of the ranges in the bands as the labels.

5. Once this is done, we annotate the lookup table and then create a reversed lookup table. This will be used by the scalar bar actor.

6. The maximum values in the ranges in the bands are used to set the bands in the banded contour filter.

7. Glyphs are then created for the normals.

8. Then everything is put together for the rendering in the usual actor/mapper pipeline. The reversed lookup table is used by the scalar bar actor so that the maximum value is at the top if the actor is placed in its default orientation/position.

9. The function Display() pulls together all the components and returns a [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html) so that you can interact with the image.

Feel free to experiment with different color schemes and/or the other
sources from the parametric function group or a cone etc.

For versions of VTK older than VTK 8.0:

In the function `MakeParametricHills()` you may have to set `ClockwiseOrderingOff()` when using [vtkParametricRandomHills](http://www.vtk.org/doc/nightly/html/classvtkParametricRandomHills.html) as a source, this ensures that the normals face in the expected direction, the default is `ClockwiseOrderingOn()`.
As an alternative, in `MakeGlyphs()`, you can set reverseNormals to True thereby invoking [vtkReverseSense](http://www.vtk.org/doc/nightly/html/classvtkReverseSense.html) to achieve the same effect.

You will usually need to adjust the parameters for maskPts,
arrow and glyph for a nice appearance.
Do this in the function `MakeGlyphs()`.

You may also need to add an elevation filter to generate the scalars
as demonstrated in `MakePlane()` and `MakeSphere()`.

`PrintBands()` and `PrintFrequencies()` allow you to inspect the bands and
the number of scalars in each band. These are useful if you want to
get an idea of the distribution of the scalars in each band.
