### Description
With vtkAxesActor, a hybrid object with 3D axes and 2D label props, it is not possible to move the labels along with the axes with vtkInteractorStyleTrackballActor. Here we create new axes labels using a different 3D prop: vtkFollower, and update their positions with a custom callback command. 
