### Description

*Contributed by: Lars Friedrich*

A simple example that shows how to use vtkTupleInterpolator for the
purpose of interpolating 1D functions. Internally the program
investigates two functions: *sine* and *Runge* function with sparsely
distributed supporting points. The application uses different
interpolation modes: '''linear''', '''cardinal spline''' and
'''Kochanek spline'''. Moreover, the example offers the "--csv-output"
(or "-co") option which causes the program to generate CSV-sheets
reflecting the interpolated data. In order to demonstrate the spline
interpolation behavior at the edge regions, we use the '''open''' and
'''closed''' interval spline options as well. For example, a
Kochanek-interpolation of the Runge function:

<img style="float:middle" src="http://www.vtk.org/Wiki/images/a/aa/Tuple1D_Kochanek_interpolation.png">

### Program Usage

``` bash
./1DTupleInterpolation [](options)

  -h or --help ... print this short help
  -nv or --no-verbose ... no verbose messages to std::cout
  -co or --csv-output ... CSV (comma separated values) file outputs
```

!!! note
    optional arguments are case-sensitive!
