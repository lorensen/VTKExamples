### Description

The vtkDistanceWidget object is used to measure the distance between two points. 

The two end points can be positioned independently, and when they are released, a special PlacePointEvent is invoked so that special operations may be take to reposition the point (snap to grid, etc.) 

The widget has two different modes of interaction - when initially defined (i.e., placing the two points) and then a manipulate mode (adjusting the position of the two points).
