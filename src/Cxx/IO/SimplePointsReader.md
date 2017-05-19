### Description
A file of XYZ coordinates is a very easy format that can be used for
simple storage from many applications. This example demonstrates how
to read this type of file into a polydata object. An example file of
three points would look like this:

`
 0.0 0.0 0.0
 1.0 0.0 0.0
 0.0 1.0 0.0
`

As a demo, save the above three lines to a file called simple.xyz and
call the executable resulting from the code below with

`
 ./SimplePointsReader simple.xyz
`

from the build directory.

!!! seealso
    For the reverse operation, writing a points file, see the [SimplePointsWriter](SimplePointsWriter) example.
