### Description

Click on a sphere to highlight it. vtkPolyDataSilhoutte creates a silhouette of the picked vtkActor. The example subclasses vtkInteractorStyleTrackballCamera with a local class called **MouseInteractorHighLightActor**. The new interactor overrides the *OnLeftButtonDown* of vtkInteractorStyleTrackballCamera.

[Watch this video](https://www.youtube.com/watch?v=ATjYDzk9llk) showing the picking of several spheres.

!!! seealso
    **HighlightPickedActor** [C++](/Cxx/Picking/HighlightPickedActor) or [Python](/Python/Picking/HighlightPickedActor) where  the color and edge visibility of the picked actor is changed.
