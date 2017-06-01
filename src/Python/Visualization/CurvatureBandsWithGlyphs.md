### Description
In this example we are coloring the surface by partitioning the gaussian curvature into bands and using arrows to display the normals on the surface.

Rather beautiful surfaces are generated.

The banded contour filter and an indexed lookup table are used along with 
the gaussian curvature filter to generate the banding on the surface.
To further enhance the surface the surface normals are
glyphed and colored by elevation using the default lookup table. 

The example also demonstrates partitioning the pipelines into functions and how
to generate a custom lookup table to handle irregular distributions of data.

For generating surfaces, the trick here is to return [vtkPolydata](http://www.vtk.org/doc/nightly/html/classvtkPolydata.html) for surfaces
thereby hiding the particular surface properties in the implementation of the
function. This allows us to specify multiple surface types and, in this code,
to use an enum to pick the one we want.

The surface selected is the parametric random hills surface. The problem with
the random hills surface is that most of the gaussian curvatures will lie in the range -1 to 0.2 (say) with a few large values say 20 to 40 at the peaks of the hills. Thus we need to manually allocate the color banding, this is done in the function MakeCustomBands(). The ranges selected in this function were determined by generating a frequency table for 20 bands and seeing where the values lie in the table. Then from this the distribution of the bands was made to best show the nature of the surface. The edges of the random hills surface have large irregular values so these are clipped.

The process is as follows:

1. Use an enum to select your surface generating elevations and curvatures and clipping is needed.

2. Use [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html) to make an indexed lookup table.

3. Then we use the number of colors in the lookup table and the scalar range of the surface to create a list/vector of bands. If need be we generate manual bands.

4. This list is then used to define the labels for the scalar bar using the midpoints of the ranges in the bands as the labels.

5. Once this is done, we annotate the lookup table and then create a reversed lookup table. This will be used by the scalar bar actor.

6. The maximum values in the ranges in the bands are used to set the bands in the banded contour filter.

7. Glyphs are then created for the normals.

8. Then everything is put together for the rendering in the usual actor/mapper pipeline. The reversed lookup table is used by the scalar bar actor so that the maximum value is at the top if the actor is placed in its default orientation/position.

9. The function Display() pulls together all the components and returns a [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html) so that you can interact with the image.

Feel free to experiment with different color schemes and/or the other
sources from the parametric function group or the torus etc.

or versions of VTK older than VTK 8.0:

In the function `MakeParametricHills()` you may have to set `ClockwiseOrderingOff()` when using [vtkParametricRandomHills](http://www.vtk.org/doc/nightly/html/classvtkParametricRandomHills.html) as a source,
this ensures that the normals face in the expected direction, the default is `ClockwiseOrderingOn()`.
As an alternative, in `MakeGlyphs()`, you can set reverseNormals to True thereby invoking [vtkReverseSense](http://www.vtk.org/doc/nightly/html/classvtkReverseSense.html) to achieve the same effect.

You will usually need to adjust the parameters for maskPts,
arrow and glyph for a nice appearance.
Do this in the function `MakeGlyphs()`.

`PrintBands()` and `PrintFrequencies()` allow you to inspect the bands and
the number of scalars in each band. These are useful if you want to
get an idea of the distribution of the scalars in each band.
