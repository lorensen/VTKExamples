### Description

This example demonstrates how to generate a [box plot](https://en.wikipedia.org/wiki/Box_plot).

The example uses data from [the Michelson Morley experiment](https://en.wikipedia.org/wiki/Michelson%E2%80%93Morley_experiment). Compare the wiki example output with the [Wikipedia results](https://upload.wikimedia.org/wikipedia/commons/f/fa/Michelsonmorley-boxplot.svg)

!!! warning
    The ChartBox expects an input table with exactly 5 rows per column. The 5 rows are minimum, 1st quartile, median, 3rd quartile and maximum. [vtkComputeQuartiles](http://www.vtk.org/doc/nightly/html/classvtkComputeQuartiles.html) is used to create a valid input table from the original data.
