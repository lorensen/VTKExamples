### Description

This example demonstrates how to select and highlight cells using vtkInteractorStyleRubberBandPick. Press 'r' to enter selection mode.

vtkExtractPolyDataGeometry selects all cells within the selected area. The cells include those on the visible surface as well as those that exist within the view frustum returned by the interactor.

The example accepts a geometry file as the first argument. Without an argument a vtkSphereSource will be used as the vtkPolyData.

