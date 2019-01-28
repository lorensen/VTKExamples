vtkGeoGraticle generates polydata to illustrate the distortions introduced by a map projection. 
The level parameter specifies the number of lines to be drawn. Poles are treated differently than other regions; hence the use of a Level parameter instead of a NumberOfLines parameter. The latitude and longitude are specified as half-open intervals with units of degrees. 
By default the latitude bounds are (-90,90) and the longitude bounds are (0,180).
