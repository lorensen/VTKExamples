### Description
This example takes a plain text file of coordinates and normals (x y z nx ny nz) and reads them into a vtkPolyData and displays them on the screen. This can be easily changed to reading a file with any delimiter by changing the argument of <source lang="cpp">Reader->SetFieldDelimiterCharacters(" ");</source>

Here is an example file:

 0.0 0.0 0.0 1.0 2.0 3.0
 1.0 0.0 0.0 4.0 5.0 6.1
 0.0 1.0 0.0 7.2 8.3 9.4
