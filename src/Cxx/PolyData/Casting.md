### Description
This example creates a polydata object with 3 points and attaches a distance value to each point. To retrieve the array from the polydata, we have to use a SafeDownCast to the type that we want. This is necessary because to keep things as general as possible the polydata will return an abstract array class.
