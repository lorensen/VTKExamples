[VTKExamples](/home/)/[Python](/Python)/GeometricObjects/Display/OrientedArrow

### Description
This example illustrates how to create and display an arrow that passes through two points.

It demonstrates two different ways to apply the transform:
# Use [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html) to create a new transformed polydata. This method is useful if the transformed polydata is needed later in the pipeline, e.g. vtkGlyph3DFilter.
# Apply the transform directly to the actor using [vtkProp3D's SetUserMatrix](http://www.vtk.org/doc/nightly/html/classvtkProp3D.html#a950378fc70405a58bd998c00f84a39a3). No new data is produced.

Switch between the two methods by setting USER_MATRIX to either <math>True</math> or <math>False</math> as documented in the script.

**OrientedArrow.py**
```python
#!/usr/bin/env python

import vtk
import random


'''
There are two alternative ways to apply the transform.
 1) Use vtkTransformPolyDataFilter to create a new transformed polydata. 
    This method is useful if the transformed polydata is needed
      later in the pipeline
    To do this, set USER_MATRIX = True
 2) Apply the transform directly to the actor using vtkProp3D's SetUserMatrix. 
    No new data is produced.
    To do this, set USER_MATRIX = False
'''
USER_MATRIX = False

#Create an arrow.
arrowSource = vtk.vtkArrowSource()

# Generate a random start and end point
random.seed(8775070)
startPoint = [0 for i in range(3)]
startPoint[0] = random.uniform(-10,10)
startPoint[1] = random.uniform(-10,10)
startPoint[2] = random.uniform(-10,10)
endPoint = [0 for i in range(3)]
endPoint[0] = random.uniform(-10,10)
endPoint[1] = random.uniform(-10,10)
endPoint[2] = random.uniform(-10,10)

# Compute a basis
normalizedX = [0 for i in range(3)]
normalizedY = [0 for i in range(3)]
normalizedZ = [0 for i in range(3)]

# The X axis is a vector from start to end
math = vtk.vtkMath()
math.Subtract(endPoint, startPoint, normalizedX)
length = math.Norm(normalizedX)
math.Normalize(normalizedX)

# The Z axis is an arbitrary vector cross X
arbitrary = [0 for i in range(3)]
arbitrary[0] = random.uniform(-10,10)
arbitrary[1] = random.uniform(-10,10)
arbitrary[2] = random.uniform(-10,10)
math.Cross(normalizedX, arbitrary, normalizedZ)
math.Normalize(normalizedZ)

# The Y axis is Z cross X
math.Cross(normalizedZ, normalizedX, normalizedY)
matrix = vtk.vtkMatrix4x4()

# Create the direction cosine matrix
matrix.Identity()
for i in range(3):
  matrix.SetElement(i, 0, normalizedX[i])
  matrix.SetElement(i, 1, normalizedY[i])
  matrix.SetElement(i, 2, normalizedZ[i])

# Apply the transforms
transform = vtk.vtkTransform()
transform.Translate(startPoint)
transform.Concatenate(matrix)
transform.Scale(length, length, length)

# Transform the polydata
transformPD = vtk.vtkTransformPolyDataFilter()
transformPD.SetTransform(transform)
transformPD.SetInputConnection(arrowSource.GetOutputPort())

#Create a mapper and actor for the arrow
mapper = vtk.vtkPolyDataMapper()
actor = vtk.vtkActor()

if USER_MATRIX:
    mapper.SetInputConnection(arrowSource.GetOutputPort())
    actor.SetUserMatrix(transform.GetMatrix())
else:
    mapper.SetInputConnection(transformPD.GetOutputPort())

actor.SetMapper(mapper)

# Create spheres for start and end point
sphereStartSource = vtk.vtkSphereSource()
sphereStartSource.SetCenter(startPoint)
sphereStartMapper = vtk.vtkPolyDataMapper()
sphereStartMapper.SetInputConnection(sphereStartSource.GetOutputPort())
sphereStart = vtk.vtkActor()
sphereStart.SetMapper(sphereStartMapper)
sphereStart.GetProperty().SetColor(1.0, 1.0, .3)

sphereEndSource = vtk.vtkSphereSource()
sphereEndSource.SetCenter(endPoint)
sphereEndMapper = vtk.vtkPolyDataMapper()
sphereEndMapper.SetInputConnection(sphereEndSource.GetOutputPort())
sphereEnd = vtk.vtkActor()
sphereEnd.SetMapper(sphereEndMapper)
sphereEnd.GetProperty().SetColor(1.0, .3, .3)

#Create a renderer, render window, and interactor
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

#Add the actor to the scene
renderer.AddActor(actor)
renderer.AddActor(sphereStart)
renderer.AddActor(sphereEnd)
renderer.SetBackground(.1, .2, .3) # Background color dark blue


#Render and interact
renderWindow.Render()
renderWindowInteractor.Start()
```
