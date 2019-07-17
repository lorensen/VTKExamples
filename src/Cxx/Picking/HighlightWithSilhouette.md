### Description

Click on a sphere to highlight it. vtkPolyDataSilhoutte creates a silhouette of the picked vtkActor. The example subclasses vtkInteractorStyleTrackballCamera with a local class called **MouseInteractorHighLightActor**. The new interactor overrides the *OnLeftButtonDown* of vtkInteractorStyleTrackballCamera.

!!! seealso
    [HighlightPickedActor](/Cxx/Picking/HighlightPickedActor) changes the color and edge visibility of the picked actor.
