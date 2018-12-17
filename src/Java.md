# Java Examples

Click [here](http://www.vtk.org/Wiki/VTK/Tutorials/JavaEnvironmentSetup) for a tutorial on setting up your Java environment.

It would be appreciated if there are any Java VTK experts who could convert any of the [c++ examples](/Cxx) to Java!

!!! info
    [This table](/Coverage/JavaVTKClassesUsed.md) shows the VTK classes covered by the examples.

!!! info
    [This table](/Coverage/JavaVTKClassesNotUsed.md) shows VTK classes that do not have an example. Please add examples in your area of expertise!

## GeometricObjects

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Arrow](/Java/GeometricObjects/Arrow) | vtkArrow | Arrow Visualization
[Circle](/Java/GeometricObjects/Circle) | vtkCircle |Circle Visualization
[Cone](/Java/GeometricObjects/Cone) | vtkCone | Cone Visualization
[Cylinder](/Java/GeometricObjects/Cylinder) | vtkCylinder | Cylinder Visualization
[Frustum](/Java/GeometricObjects/Frustum) | vtkFrustum | Frustum Visualization
[Cube](/Java/GeometricObjects/Cube) | vtkCube | Cube Visualization
[Disk](/Java/GeometricObjects/Disk) | vtkDisk | Disk Visualization
[Line](/Java/GeometricObjects/Line) | vtkLine | Line Visualization
[LongLine](/Java/GeometricObjects/LongLine) | vtkLine | A visualization of a long line
[OrientedCylinder](/Java/GeometricObjects/OrientedCylinder) | vtkOrientedCylinder |Oriented Cylinder visualization
[OrientedArrow](/Java/GeometricObjects/OrientedArrow) | vtkOrientedArrow | Oriented Arrow visualization 
[Polygon](/Java/GeometricObjects/Polygon) | vtkPolygon | Polygon Visualization
[PlanesIntersection](/Java/GeometricObjects/PlanesIntersection) | vtkPlanesIntersection | PlanesIntersection
[RegularPolygonSource](/Java/GeometricObjects/RegularPolygonSource) | vtkRegularPolygonSource| RegularPolygon Visualization
[ParametricObjects](/Java/GeometricObjects/ParametricObjects) | vtkParametricObjects| ParametricObjects Visualization
[Pyramid](/Java/GeometricObjects/Pyramid) | vtkPyramid | Pyramid Visualization
[Quad](/Java/GeometricObjects/Quad) | vtkQuad | Quad Visualization
[Vertex](/Java/GeometricObjects/Vertex) | vtkVertex | Vertex Visualization
[TextActor](/Java/GeometricObjects/TextActor) | vtkTextActor | TextActor Demonstration
[Triangle](/Java/GeometricObjects/Triangle) | vtkTriangle | Triangle Visualization
[TriangleStrip](/Java/GeometricObjects/TriangleStrip) | vtkTriangleStrip | Triangle Strip Visualization


## Geovis

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[EarthSource](/Java/Geovis/EarthSource) | vtkEarthSource | Earth Source Visualization |


## Input and Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Read a polydata(.vtp) file](/Java/IO/ReadPolyData) | vtkXMLPolyDataReader | IO
[Write a polygonal data (.vtp) file](/Java/IO/WritePolyData) | vtkXMLPolyDataWriter | IO

## Implicit Functions and Iso-surfaces

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImplicitSphere](/Java/ImplicitFunctions/ImplicitSphere) | vtkSphere vtkAppendPolyData vtkTubeFilter | ImplicitFunctions, Append poly data, tube filter, sphere

## Data Structures

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[VisualizeKDTree](/Java/DataStructures/VisualizeKDTree) | vtkKdTreePointLocator |

## Image Processing

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImageTest](/Java/Imaging/ImageTest) | vtkImageReader2Factory | use Java File Dialog to select Image File to Display

## Lighting

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[SpotLight](/Java/Lighting/SpotLight) | vtkSpotLight | vtkSpotLight Demonstration
[LightActor](/Java/Lighting/LightActor) | vtkLightActor| vtkLightActor Demonstration


## Miscellaneous

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Cone6](/Java/Miscellaneous/Cone6) |  | The missing Step 6 Java example from Examples/Tutorial
[Cutter](/Java/Miscellaneous/Cutter) | vtkCutter |
[Screenshot](/Java/Miscellaneous/Screenshot) | vtkWindowToImageFilter |

## Visualization

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AnimDataCone](/Java/Visualization/AnimDataCone) | vtkRenderWindowInteractor | Animate a cone by modifying the polydata points - uses Interaction M key (Motion) to toggle animation.
[Animation](/Java/Visualization/Animation) |  | Move a sphere across a scene
[ColorAnActor](/Java/Visualization/ColorAnActor) | vtkActor vtkCanvas | Switch style interaction adds C and A key actions for selecting Camera or Actor interaction, and T and J key actions for Trackball or Joystick interaction mode. Adds charEvent observer callback to restore the missing E and Q events to quit.
[Follower](/Java/Visualization/Follower) | vtkFollower | Draw text that stays right side up 
[WireframeSphere](/Java/Visualization/WireframeSphere) | vtkSphere | A Wireframe Sphere Visualization 

## Graphs

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[SelectGraphVertices](/Java/Graphs/SelectGraphVertices) | vtkAnnotationLink | Select Edges and vertices in a graph

## Swing Integration

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[JFrameRender](/Java/SwingIntegration/JFrameRenderer) | vtkRenderWindowPanel | Render a scene in a JFrame using a vtkRenderWindowPanel
[SwingHandleMouseEvent](/Java/SwingIntegration/SwingHandleMouseEvent) | vtkRenderWindowPanel | Display in a JLabel the point the mouse is hovering over using a mouse listener
