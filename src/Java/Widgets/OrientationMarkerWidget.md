### Description

vtkOrientationMarkerWidget object provides support for interactively manipulating the position, size, and apparent orientation of a prop that represents an orientation marker. 

This class works by adding its internal renderer to an external "parent" renderer on a different layer. The input orientation marker is rendered as an overlay on the parent renderer and, thus, appears superposed over all props in the parent's scene. 

The camera view of the orientation the marker is made to match that of the parent's by means of an observer mechanism, giving the illusion that the orientation of the marker reflects that of the prop(s) in the parent's scene.

The widget listens to left mouse button and mouse movement events. It will change the cursor shape based on its location. If the cursor is over the overlay renderer, it will change the cursor shape to a SIZEALL shape or to a resize corner shape (e.g., SIZENW) if the cursor is near a corner. If the left mouse button is pressed and held down while moving, the overlay renderer, and hence, the orientation marker, is resized or moved. In the case of a resize operation, releasing the left mouse button causes the widget to enforce its renderer to be square. The diagonally opposite corner to the one moved is repositioned such that all edges of the renderer have the same length: the minimum.
