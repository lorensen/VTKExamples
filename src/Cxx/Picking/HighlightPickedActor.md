### Description
Click on a sphere to highlight it. The picked sphere color changes to red, and its EdgeVisibity is On. The example subclasses vtkInteractorStyleTrackballCamera with a local class called **MouseInteractorHighLightActor**. The new interactor overrides the *OnLeftButtonDown* of vtkInteractorStyleTrackballCamera.

!!! seealso
    [HighlightWithSilhouette](/Cxx/Picking/HighlightWithSilhouette) generates a silhouette of the picked actor.
