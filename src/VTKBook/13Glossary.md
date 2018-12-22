# Glossary

**3D Widget.** An interaction paradigm enabling manipulation of scene objects (e.g., lights, camera, actors, and so on). The 3D widget typically provides a visible representation that can be intuitively and interactively manipulated.

**API.** An acronym for application programmer's interface.

**Abstract Class.** A class that provides methods and data members for the express purpose of deriving subclasses. Such objects are used to define a common interface and attributes for their subclasses.

**Abstraction.** A mental process that extracts the essential form or unifying properties of a concept.

**Alpha.** A specification of opacity (or transparency). An alpha value of one indicates that the object is opaque. An alpha value of zero indicates that the object is completely transparent.

**Ambient Lighting.** The background lighting of unlit surfaces.

**Animation.** A sequence of images displayed in rapid succession. The images may vary due to changes in geometry, color, lighting, camera position, or other graphics parameters. Animations are used to display the variation of one or more variables.

**Antialiasing.** The process of reducing aliasing artifacts. These artifacts typically result from undersampling the data. A common use of antialiasing is to draw straight lines that don't have the jagged edges found in many systems without antialiasing.

**Azimuth.** A rotation of a camera about the vertical (or view up) axis.

**Attribute.** A named member of a class that captures some
characteristic of the class. Attributes have a name, a data type, and
a data value. This is the same as a data member or instance variable.

**Base Class.** A superclass in C++.

**Binocular Parallax.** The effect of viewing the same object with two
slightly different viewpoints to develop depth information.

**Boolean Texture.** A texture map consisting of distinct regions used
to "cut" or accentuate features of data. For example, a texture map
may consist of regions of zero opacity. When such a texture is mapped
onto the surface of an object, portions of its interior becomes
visible. Generally used in conjunction with a quadric (or other
implicit function) to generate texture coordinates.

**C++.** A compiled programming language with roots in the C
programming language. C++ is an extension of C that incorporates
objectoriented principles.

**CT (Computed Tomography).** A data acquisition technique based on
Xrays. Data is acquired in a 3D volume as a series of slice planes
(i.e., a stack of *n^2^* points).

**Cell.** The atoms of visualization datasets. Cells define a topology
(e.g., polygon, triangle) in terms of a list of point coordinates.

**Cell Attributes.** Dataset attributes associated with a cell. See
also *point attributes* .

**Class.** An object that defines the characteristics of a subset of
objects. Typically, it defines methods and data members. All objects
instantiated from a class share that class's methods and data
members.

**Clipping Plane.** A plane that restricts the rendering or processing
of data. Front and back clipping planes are commonly used to restrict
the rendering of primitives to those lying between the two planes.

**Color Mapping.** A scalar visualization technique that maps scalar
values into color. Generally used to display the variation of data on
a surface or through a volume.

**Compiled System.** A compiled system requires that a program be
compiled (or translated into a lower level language) before it is
executed. Contrast with *interpreted systems* .

**Composite Cell.** A cell consisting of one or more primary cells.

**Concrete Class.** A class that can be instantiated. Typically,
abstract classes are not instantiated but concrete classes are.

**Connectivity.** A technique to extract connected cells. Cells are
connected when they share common features such as points, edges, or
faces.

**Contouring.** A scalar visualization technique that creates lines
(in 2D) or surfaces (in 3D) representing a constant scalar value
across a scalar field. Contour lines are called isovalue lines or
iso-lines. Contour surfaces are called isovalue surfaces or
isosurfaces.

**Constructor.** A class method that is invoked when an instance of
that class is created. Typically the constructor sets any default
values and allocates any memory that the instance needs. See also
*destructor* .

**Critical Points.** Locations in a vector field where the local
vector magnitude goes to zero and the direction becomes undefined.

**Cutting.** A visualization technique to slice through or cut data.
The cutting surface is typically described with an implicit function,
and data attributes are mapped onto the cut surface. See also *boolean
texture* .

**Dataset.** The general term used to describe visualization data. Datasets consist of structure   (geometry and topology) and dataset attributes (scalars, vectors, tensors, etc.).
**Dataset Attributes.** The information associated with the structure
of a dataset. This can be scalars, vectors, tensors, normals, and
texture coordinates, or arbitrary data arrays that may be contained in
the field.

**Data Extraction.** The process of selecting a portion of data based
on characteristics of the data. These characteristics may be based on
geometric or topological constraints or constraints on data attribute
values.

**Data Flow Diagram.** A diagram that shows the information flow and
operations on that information as it moves throughout a program or
process.

**Data Object.** An object that is an abstraction of data. For
example, a patient's file in a hospital could be a data object.
Typical visualization objects include structured grids and volumes.
See also *process object* .

**Data Member.** A named member of a class that captures some
characteristic of the class. Data members have a name, a data type,
and a data value. This is the same as an attribute or instance
variable.

**Data Visualization.** The process of transforming data into sensory
stimuli, usually visual images. Data visualization is a general term,
encompassing data from engineering and science, as well as information
from business, finance, sociology, geography, information management,
and other fields. Data visualization also includes elements of data
analysis, such as statistical analysis. Contrast with *scientific
visualization* and *information visualization* .

**Decimation.** A type of polygon reduction technique that deletes
points in a polygonal mesh that satisfies a co-planar or co-linear
condition and replaces the resulting hole with a new triangulation.

**Delaunay Triangulation.** A triangulation that satisfies the
Delaunay circumsphere criterion. This criterion states that a
circumsphere of each simplex in the triangulation contains only the
points defining the simplex.

**Delegation.** The process of assigning an object to handle the
execution of another object's methods. Sometimes it is said that one
object forwards certain methods to another object for execution.

**Demand-driven.** A method of visualization pipeline update where the
update occurs only when data is requested and occurs only in the
portion of the network required to generate the data.

**Derived Class.** A class that is more specific or complete than its
superclass. The derived class, which is also known as the subclass,
inherits all the members of its superclass. Usually a derived class
adds new functionality or fills in what was defined by its superclass.
See also *subclass* .

**Destructor.** A class method that is invoked when an instance of
that class is deleted. Typically the destructor frees memory that the
instance was using. See also *constructor* .

**Device Mapper.** A mapper that interfaces data to a graphics library
or subsystem.

**Diffuse Lighting.** Reflected light from a matte surface. Diffuse
lighting is a function of the relative angle between the incoming
light and surface normal of the object.

**Displacement Plots.** A vector visualization technique that shows
the displacement of the surface of an object. The method generates
scalar values by computing the dot product between the surface normal
and vector displacement of the surface. The scalars are visualized
using color mapping.

**Display Coordinate System.** A coordinate system that is the result
of mapping the view coordinate system onto the display hardware.

**Divergence.** In numerical computation: the tendency of computation
to move away from the solution. In fluid flow: the rapid motion of fluid particles away from one
another.

**Dividing Cubes.** A contour algorithm that represents isosurfaces as
a dense cloud of points.

**Dolly.** A camera operation that moves the camera position towards (

from the camera focal point.

*dolly in* ) or away (

*dolly out* )

**Double Buffering.** A display technique that is used to display
animations more smoothly. It consists of using two buffers in the
rendering process. While one buffer is being displayed, the next frame
in the animation is being drawn on the other buffer. Once the drawing
is complete the two buffers are swapped and the new image is
displayed.

**Dynamic Memory Model.** A data flow network that does not retain
intermediate results as it executes. Each time the network executes,
it must recompute any data required as input to another process
object. A dynamic memory model reduces system memory requirements but
places greater demands on computational requirements.

**Dynamic Model.** A description of a system concerned with
synchronizing events and objects.

**Effective Stress.** A mathematical combination of the normal and
shear stress components that provide a measure of the stress at a
point. Effective stress is a scalar value, while stress is represented
with a tensor value. See *stress* .

**Eigenfields.** Vector fields defined by the eigenvectors of a
tensor.

**Eigenvalue.** A characteristic value of a matrix. Eigenvalues often
correspond to physical phenomena, such as frequency of vibration or
magnitude of principal components of stress.

**Eigenvector.** A vector associated with each eigenvalue. The
eigenvector spans the space of the matrix. Eigenvectors are orthogonal
to one another. Eigenvectors often correspond to physical phenomena
such as mode shapes of vibration.

**Elevation.** A rotation of a camera about the horizontal axis.

**Entity.** Something within a system that has identity. Chairs,
airplanes, and cameras are things that correspond to physical entities
in the real world. A database and isosurface algorithm are examples of
nonphysical entities.

**Event-driven.** A method of visualization pipeline update where
updates occur when an event

affects the pipeline, e.g., when an object instance variable is set or
modified. See also *demand-driven*.

**Execution.** The process of updating a visualization network.

**Explicit Execution.** Controlling network updates by performing
explicit dependency analysis.

**Exporter.** An object that saves a VTK scene definition to a file or
other program. (A scene consists of lights, cameras, actors, geometry,
properties, texture, and other pertinent data.) See also *importer* .

**Fan-in.** The flow of multiple pieces of data into a single filter.

**Fan-out.** The flow of data from a filter's output to other objects.

**Feature Angle.** The angle between surface normal vectors, e.g., the
angle between the normal vectors on two adjacent polygons.

**Filter.** A process object that takes at least one input and
generates at least one output.

**Finite Element Method (FEM).** A numerical technique for the
solution of partial differential equations. FEM is based on
discretizing a domain into elements (and nodes) and constructing basis
(or interpolation) functions across the elements. From these functions
a system of linear equations is generated and solved on the computer.
Typical applications include stress, heat transfer, and vibration
analysis.

**Finite Difference Method.** A numerical technique for the solution
of partial differential equations (PDEs). Finite difference methods
replace the PDEs with truncated Taylor series approximations. This
results in a system of equations that is solved on a computer. Typical
applications include fluid flow, combustion, and heat transfer.

**Flat Shading.** A shading technique where the lighting equation for
a geometric primitive is calculated once, and then used to fill in
the entire area of the primitive. This is also known as faceted
shading. See also *gouraud shading* and *phong shading* .

**Functional Model.** The description of a system based on what it
does.

**Generalization.** The abstraction of a subset of classes to a common
superclass. Generalization extracts the common members or methods from
a group of classes to create a common superclass. See also
*specialization* and *inheritance* .

**Geometry.** Used generally to mean the characteristic position,
shape, and topology of an object.

Used specifically (in tandem with topology) to mean the position and
shape of an object.

**Glyph.** A general visualization technique used to represent data
using a meaningful shape or pictorial representation. Each glyph is
generally a function of its input data and may change size,
orientation, and shape; or modify graphics properties in response to
changes in input.

**Gouraud Shading.** A shading technique that applies the lighting
equations for a geometric primitive at each vertex. The resulting
colors are then interpolated over the areas between the vertices. See
also *flat shading* and *Phong shading* .

**Hedgehog.** A vector visualization technique that represents vector
direction and magnitude with oriented lines.

**Height Field.** A set of altitude or height samples in a rectangular
grid. Height fields are typically used to represent terrain.

**Hexahedron.** A type of primary 3D cell. The hexahedron looks like a
"brick." It has six faces, 12 edges, and eight vertices. The faces of
the hexahedron are not necessarily planar.

**Homogeneous Coordinates.** An alternate coordinate representation
that provides more flexibility than traditional Cartesian coordinates.
This includes perspective transformation and combined translation,
scaling, and rotation.

**Hyperstreamline.** A tensor visualization technique.
Hyperstreamlines are created by treating the eigenvectors as three
separate vectors. The maximum eigenvalue/eigenvector is used as a
vector field in which particle integration is performed (like streamlines).
The other two vectors control the cross-sectional shape of an ellipse
that is swept along the integration path. See also *streampolygon* .

**Image Data.** A dataset whose structure is both geometrically and
topologically regular. Both geometry and topology are implicit. A 3D
image dataset is known as a volume. A 2D image dataset is known as a
pixmap.

**Image-Order Techniques.** Rendering techniques that determine for
each pixel in the image plane which data samples contribute to it.
Image-order techniques are implemented using ray casting. Contrast
with *object-order techniques* .

**Implicit Execution.** Controlling network updates by distributing
network dependency throughout the visualization process objects. Each
process object requests that its input be updated before it executes.
This results in a recursive update/execution process throughout the
network.

**Implicit Function.** A mathematical function of the form ,
whereFxyz(),, c is a constant=.

**Implicit Modelling.** A modelling technique that represents geometry
as a scalar field. Usually the scalar is a distance function or
implicit function distributed through a volume.

**Importer.** An object that interfaces to external data or programs
to define a complete scene in VTK. (The scene consists of lights,
cameras, actors, geometry, properties, texture, and other pertinent
data.) See also *exporter* .

**Information Visualization.** The process of transforming information
into sensory stimuli, usually visual images. Information visualization
is used to describe the process of visualizing data without structure,
such as information on the World Wide Web; or abstract data
structures, like computer file systems or documents. Contrast with
*scientific visualization* and *data visualization* .

**Inheritance.** A process where the attributes and methods of a
superclass are bestowed upon all sub-classes derived from that
superclass. It is said that the subclasses inherit their superclasses'
methods and attributes.

**Instance.** An object that is defined by a class and used by a
program or application. There may be many instances of a specific
class.

**Instance Variable.** A named member of a class that captures a
characteristic of the class. Instance variables have a name, a data
type, and a data value. The phrase, instance variable, is often
abbreviated as ivar. This is the same as an attribute or data member.

**Intensity.** The light energy transferred per unit time across a
unit plane perpendicular to the light rays.

**Interpolate.**

that bracket

Estimate a value of a function at a point *p*.

*p*, given known function values and points

**Interpolation Functions.** Functions continuous in value and
derivatives used to interpolate data from known points and function
values. Cells use interpolation functions to compute data values
interior to or on the boundary of the cell.

**Interpreted System.** An interpreted system can execute programs
without going through a separate compilation stage. Interpreted
systems often allow the user to interact and modify the program as it
is running. Contrast with *compiled systems* .

**Irregular Data.** Data in which the relationship of one data item to
the other data items in the dataset is arbitrary. Irregular data is
also known as unstructured data.

**Iso-parametric.** A form of interpolation in which interpolation for
data values is the same as for the local geometry. Compare with
*sub-parametric* and *super-parametric* .

**Isosurface.** A surface representing a constant valued scalar
function. See *contouring* .

**Isovalue.** The scalar value used to generate an isosurface.

**Jacobian.** A matrix that relates one coordinate system to another.

**Line.** A cell defined by two points.

**MRI (Magnetic Resonance Imaging).** A data acquisition technique
based on measuring variation in magnetic field in response to
radio-wave pulses. The data is acquired in a 3D region as a series of
slice planes (i.e., a stack of $n^2$ points).

**Mapper.** A process object that terminates the visualization
network. It maps input data into graphics libraries (or other
devices) or writes data to disk (or a communication device).

**Manifold Topology.** A domain is manifold at a point *p* in a
topological space of dimension *n* if the

neighborhood around *p* is homeomorphic to an *n*-dimensional sphere.
Homeomorphic means that the mapping is one to one without tearing
(i.e., like mapping a rubber sheet from a square to a disk). We
generally refer to an object's topology as manifold if every point in
the object is manifold. Contrast with *nonmanifold topology* .

**Marching Cubes.** A contouring algorithm to create surfaces of
constant scalar value in 3D. Marching cubes is described for volume
datasets, but has been extended to datasets consisting of other cell
types.

**Member Function.** A member function is a function or transformation
that can be applied to an object. It is the functional equivalent to a
data member. Member functions define the behavior of an object.
Methods, operations, and member functions are essentially the same.

**Method.** A function or transformation that can be applied to an
object. Methods define the behavior of an object. Methods,
operations, and member functions are essentially the same.

**Modal Lines.** Lines on the surface of a vibrating object that
separate regions of positive and negative displacement.

**Mode Shape.** The motion of an object vibrating at a natural
frequency. See also *eigenvalues* and

*eigenvectors* .

**Model Coordinate System.** The coordinate system that a model or
geometric entity is defined in.

There may be many different model coordinate systems defined for one
scene.

**Motion Blur.** An artifact of the shutter speed of a camera. Since
the camera's shutter stays open for a finite amount of time, changes
in the scene that occur during that time can result in blurring of the
resulting image.

**Morph.** A progressive transformation of one object into another.
Generally used to transform images (2D morphing) and in some cases
geometry (3D morphing).

**Multiple Input.** Process objects that accept more than one input.

**Multiple Output.** Process objects that generate more than one
output.

**Multidimensional Visualization.** Visualizing data of four or more
variables. Generally requires a mapping of many dimensions into three
or fewer dimensions so that standard visualization techniques can be
applied.

**Nonmanifold Topology.** Topology that is not manifold. Examples
include polygonal meshes, where an edge is used by more than two
polygons, or polygons connected to each other at their vertices
(i.e., do not share an edge). Contrast with *manifold topology* .

**Normal.** A unit vector that indicates perpendicular direction to a
surface. Normals are a common type of data attribute.

**Object.** An abstraction that models the state and behavior of
entities in a system. Instances and classes are both objects.

**Object Model.** The description of a system in terms of the
components that make up the system, including the relationship of the
components one to another.

**Object-Order Techniques.** Rendering techniques that project object
data (e.g., polygons or voxels) onto the image plane. Example
techniques include ordered compositing and splatting.

**Object-Oriented.** A software development technique that uses
objects to represent the state and behavior of entities in a system.

**Octree Decomposition.** A technique to decompose a cubical region of
three-dimensional space into smaller cubes. The cubes, or octants, are
related in tree fashion. The root octant is the cubical region. Each
octant may have eight children created by dividing the parent in half
in the x, y, and z directions.

**Object Factory.** An object used to construct or instantiate other
objects. In VTK, object factories are implemented using the class
method New().

**OMT.** *Object Modelling Technique* . An object-oriented design
technique that models software systems with object, dynamic, and
functional diagrams.

**Operation.** A function or transformation that can be applied to an
object. Operations define the behavior of an object. Methods and
member functions implement operations.

**Overloading.** Having multiple methods with the same name. Some
methods are overloaded because there are different versions of the
same method. These differences are based on argument types, while the
underlying algorithm remains the same. Contrast with *polymorphic* .

**Painter's Algorithm.** An object-order rendering technique that
sorts rendering primitives from back to front and then draws them.

**Parametric Coordinates.** A coordinate system natural to the
geometry of a geometric object. For example, a line may be described
by the single coordinate *s* even though the line may lie in three or
higher dimensions.

**Parallel Projection.** A mapping of world coordinates into view
coordinates that preserves all parallel lines. In a parallel
projection an object will appear the same size regardless of how far
away it is from the viewer. This is equivalent to having a center of
projection that is infinitely far away. Contrast with *perspective
projection* .

**Particle Trace.** The trajectory that particles trace over time in
fluid flow. Particle traces are everywhere tangent to the velocity
field. Unlike streamlines, particle lines are time-dependent.

**Pathline.** The trajectory that a particle follows in fluid flow.

**Perspective Projection.** A mapping of world coordinates into view
coordinates that roughly approximates a camera lens. Specifically, the
center of projection must be a finite distance from the

view plane. As a result closer, objects will appear larger than
distant objects. Contrast with *parallel* *projection* .

**Phong Shading.** A shading technique that applies the lighting
equations for a geometric primitive at each pixel. See also *flat
shading* and *Gouraud shading* .

**Pitch.** A rotation of a camera's position about the horizontal
axis, centered at its viewpoint. See also *yaw* and *roll*. Contrast
with *elevation* .

**Pixel.** Short for picture element. Constant valued elements in an
image. In VTK, a two-dimensional cell defined by an ordered list of
four points.

**Point.** A geometric specification of position in 3D space.

**Point Attributes.** Data attributes associates with the points of a
dataset.

**Polygon.** A cell consisting of three or more co-planar points
defining a polygon. The polygon can be concave but without imbedded
loops.

**Polygonal Data.** A dataset type consisting of arbitrary
combinations of vertices, polyvertices, lines, polylines, polygons,
and triangle strips. Polygonal data is an intermediate data form that
can be easily rendered by graphics libraries, and yet can represent
many types of visualization data.

**Polygon Reduction.** A family of techniques to reduce the size of
large polygonal meshes. The goal is to reduce the number of polygons,
while preserving a "good" approximation to the original geometry. In
most techniques topology is preserved as well.

**Polyline.**

A composite cell consisting of one or more lines.

**Polymorphic.** Having many forms. Some methods are polymorphic
because the same method in

different classes may implement a different algorithm. The semantics
of the method are typically

the same, even though the implementation may differ. Contrast with
*overloading* .

**Polyvertex.**

A composite cell consisting of one or more vertices.

**Primary Cell.**

A cell that is not defined in terms of other cells.

**Probing.** Also known as sampling or resampling. A data selection
technique that selects data at a

set of points.

**Process Object.** A visualization object that is an abstraction of a
process or algorithm. For example, the isosurfacing algorithm marching cubes is implemented as a process object. See also *data object*.

**Progressive Mesh.** A representation of a triangle mesh that enables
incremental refinement and

derefinement. The data representation is compact and is useful for
transmission of 3D triangle

meshes across a network. See also *polygon reduction* .

**Properties.** A general term used to describe the rendered
properties of an actor. This includes lighting terms such as ambient,
diffuse, and specular coefficients; color and opacity; shading
techniques such as flat and Gouraud; and the actor's geometric
representation (wireframe, points, or surface).

**Pyramid.** A type of primary 3D cell. The pyramid has a
quadrilateral base connected to a single apex point. It has five
faces, eight edges, and five vertices. The base face of the pyramid is
not necessarily planar.


**Quadric.** A function of the form

$$
f(x,y,z) = a_0x^2 + a_1y^2 + a_2z^2 + a_3xy + a_4yz + a_5xz + a_6 x + a_7 y + a_8 z + a_9
$$

The quadric equation can represent many useful 3D objects such as spheres,
ellipsoids, cylinders, and cones.

**Quadratic Edge.** A type of primary 1D cell with a quadratic
interpolation function. The quadratic edge is defined by three points:
two end points and a mid-edge node.

**Quadratic Triangle.** A type of primary 2D cell with quadratic
interpolation functions. The quadratic triangle is defined by six
points: three corner points and three mid-edge nodes.

**Quadratic Quadrilateral.** A type of primary 2D cell with quadratic
interpolation functions. The quadratic quadrilateral is defined by
eight points: four corner points and four mid-edge nodes.

**Quadratic Tetrahedron.** A type of primary 3D cell with quadratic
interpolation functions. The quadratic tetrahedron is defined by ten
points: four corner points and six mid-edge nodes.

**Quadratic Hexahedron.** A type of primary 3D cell with quadratic
interpolation functions. The quadratic edge is defined by twenty
points: eight corner points and twelve mid-edge nodes.

**Quadrilateral (Quad).** A type of primary 2D cell. The quadrilateral
is four sided with four vertices. The quadrilateral must be convex.

**Reader.** A source object that reads a file or files and produces a
data object.

**Reference Counting.** A memory management technique used to reduce
memory requirements. Portions of memory (in this case objects) may be
referenced by more than one other object. The referenced object keeps
a count of references to it. If the count returns to zero, the object
deletes itself, returning memory back to the system. This technique
avoids making copies of memory.

**Region of Interest.** A portion of a dataset that the user is
interested in visualizing. Sometimes abbreviated ROI.

**Regular Data.** Data in which one data item is related (either
geometrically or topologically) to other data items. Also referred to
as structured data.

**Rendering.** The process of converting object geometry (i.e.,
geometric primitives), object properties, and a specification of
lights and camera into an image. The primitives may take many forms
including surface primitives (points, lines, polygons, splines),
implicit functions, or volumes.

**Resonant Frequency.** A frequency at which an object vibrates.

**Roll.** A rotation of a camera about its direction of projection.
See also *azimuth* , *elevation* , *pitch*, and *yaw*.

**Sampling.** Selective acquisition or sampling of data, usually at a
regular interval. See also *probing* .

**Scalar.** A single value or function value. May also be used to
represent a field of such values.

**Scalar Range.** The minimum and maximum scalar values of a scalar
field.

**Scalar Generation.** Creating scalar values from other data such as
vectors or tensors. One example is computing vector norm.

**Scene.** A complete representation of the components required to
generate an image or animation including lights, cameras, actors.
properties, transformations, geometry, texture, and other pertinent
information.

**Scene Graph.** A hierarchical, acyclic, directed tree representation
of a scene. The graph order (depth first) controls when objects are
processed by the graphics system.

**Scientific Visualization.** The process of transforming data into
sensory stimuli, usually visual images. Generally used to denote the
application of visualization to the sciences and engineering. Contrast
with *data visualization* and *information visualization* .

**Searching.** The process of locating data. Usually the search is
based on spatial criteria such as position or being inside a cell.

**Segmentation.** Identification and demarcation of tissue types.
Segmentation is generally applied to CT and MRI data to associate soft
tissue with a particular body organ or anatomical structure.

**Simplex.** The convex combination of *n* independent vectors in
*n*-space forms an *n*-dimensional simplex. Points, lines, triangles,
and tetrahedra are examples of simplices in 0D, 1D, 2D, and 3D.

**Source.** A process object that produces at least one output.
Contrast with *filter* .

**Specialization.** The creation of subclasses that are more refined
or specialized than their super-class. See also *generalization* and
*inheritance* .

**Specular Lighting.** Reflected lighting from a shiny surface.
Specular lighting is a function of the relative angle between the
incoming light, the surface normal of the object, and the view angle
of the observer.

**Splatting.** A method to distribute data values across a region. The
distribution functions are often based on Gaussian functions.

**State Diagram.** A diagram that relates states and events. Used to
describe behavior in a software system.

**Static Memory Model.** A data flow network that retains intermediate
results as it executes. A static memory model minimizes computational
requirements, but places greater demands on memory requirements.

**Strain.** A nondimensional quantity expressed as the ratio of the
displacement of an object to its length (normal strain), or angular
displacement (shear strain). Strain is a tensor quantity. See also
*stress* .

**Stress.** A measure of force per unit area. Normal stress is stress
normal to a given surface, and is either compressive (a negative
value) or tensile (a positive value). Shear stress acts tangentially
to a given surface. Stress is related to strain through the linear
proportionality constants (theE modulus of elasticity), (Poisson's
ratio), and (modulusG of elasticity in shear). Stress is a tensor
quantity. See also *strain* .

**Streakline.** The set of particles that have previously passed
through a particular point.

**Streamline.** Curves that are everywhere tangent to the velocity
field. A streamline satisfies the integral curve $\frac{\text{d}\overrightarrow{x}}{\text{d}s} = \overrightarrow{v}(x,t')$ at sonme time $t'$.

**Streampolygon.** A vector and tensor visualization technique that
represents flow with tubes that have polygonal cross sections. The
method is based on integrating through the vector field and then
sweeping a regular polygon along the streamline. The radius, number of
sides, shape, and rotation of the polygon are allowed to change in
response to data values. See also *hyperstreamline* .

**Streamribbon.** A vector visualization technique that represents
vectors with ribbons that are everywhere tangent to the vector field

**Streamsurface** . A surface that is everywhere tangent to a vector
field. Can be approximated by generating a series of streamlines along
a curve and connecting the lines with a surface.

**Streamwise Vorticity.** A measure of the rotation of flow around a
streamline.

**Structured Data.** Data in which one data item is related (either
geometrically or topologically) to other data items. Also referred to
as regular data.

**Structured Grid.** A dataset whose structure is topologically
regular but whose geometry is irregular. Geometry is explicit and
topology is implicit. Typically, structured grids consist of
hexahedral cells.

**Structured Points.** *Preferred term is* Image Data *.* A dataset
whose structure is both geometrically and topologically regular. Both
geometry and topology are implicit. A 3D structured point dataset is
known as a volume. A 2D structured point dataset is known as a pixmap.

**Subclass.** A class that is more specific or complete than its
superclass. The subclass, which is also known as the derived class,
inherits all the members of its superclass. Usually a subclass will
add some new functionality or fill in what was defined by its
superclass. See also *derived class* .

**Sub-parametric.** A form of interpolation in which interpolation for
data values is of higher order than that for the local geometry.
Compare with *iso-parametric* and *super-parametric* .

**Subsampling.** Sampling data at a resolution at less than final
display resolution.

**Superclass.** A class from which other classes are derived. See also
*base class* .

**Super-parametric.** A form of interpolation in which interpolation
for data values is of lower order than that for the local geometry.
Compare with *iso-parametric* and *sub-parametric* .

**Surface Rendering.** Rendering techniques based on geometric surface
primitives such as points, lines, polygons, and splines. Contrast with
*volume rendering* .

**Swept Surface.**

The surface that an object creates as it is swept through space.

**Swept Volume.**

The volume enclosed by a swept surface.

**Tcl.**

An interpreted language developed by John Ousterhout in the early 1980s.

**Tk.**

A graphical user-interface toolkit based on Tcl.

**Tensor.** A mathematical generalization of vectors and matrices. A
tensor of rank *k* can be considered a *k*-dimensional table. Tensor visualization algorithms treat 3 x 3 real symmetric matrix tensors (rank 2 tensors).

**Tensor Ellipsoid.** A type of glyph used to visualize tensors. The
major, medium, and minor eigenvalues of a tensor define an
ellipsoid. The eigenvalues are used to scale along the axes.

**Tetrahedron.** A 3D primary cell that is a simplex with four
triangular faces, six edges, and four vertices.

**Texture Animation.** Rapid application of texture maps to visualize
data. A useful example maps a 1D texture map of varying intensity
along a set of lines to simulate particle flow.

**Texture Coordinate.** Specification of position within texture map.
Texture coordinates are used to map data from Cartesian system into 2D
or 3D texture map.

**Texture Map.** A specification of object properties in a canonical
region. These properties are most often intensity, color, and alpha,
or combinations of these. The region is typically a structured array
of data in a pixmap (2D) or in a volume (3D).

**Texture Mapping.** A rendering technique to add detail to objects
without requiring extensive geometric modelling. One common example
is to paste a picture on the surface of an object.

**Texture Thresholding.** Using texture mapping to display selected
data. Often makes use of alpha opacity to conceal regions of minimal
interest.

**Thresholding.** A data selection technique that selects data that
lies within a range of data. Typically scalar thresholding selects
data whose scalar values meet a scalar criterion.

**Topology.** A subset of the information about the structure of a
dataset. Topology is a set of properties invariant under certain
geometric transformation such as scaling, rotation, and translation.

**Topological Dimension.** The dimension or number of parametric
coordinates required to address the domain of an object. For example,
a line in 3D space is of topological dimension one because the line
can be parametrized with a single parameter.

**Transformation Matrix.** A matrix of values used to control the
position, orientation, and scale of objects.

**Triangle Strip.** A composite 2D cell consisting of triangles. The
triangle strip is an efficient representation scheme for triangles where points $n + 2$ can represent $n$ triangles.

**Triangle.** A primary 2D cell. The triangle is a simplex with three
edges and three vertices.

**Triangular Irregular Network (TIN).** An unstructured triangulation
consisting of triangles. Often used to represent terrain data.

**Triangulation.** A set of nonintersecting simplices sharing common
vertices, edges, and/or faces.

**Type Converter** . A type of filter used to convert from one dataset
type to another.

**Type Checking.** The process of enforcing compatibility between
objects.

**Uniform Grid.** A synonym for image data.

**Unstructured Data.** Data in which one data item is unrelated
(either geometrically or topologically) to other data items. Also
referred to as irregular data.

**Unstructured Grid.** A general dataset form consisting of arbitrary
combinations of cells and points. Both the geometry and topology are
explicitly defined.

**Unstructured Points.** A dataset consisting of vertex cells that are
positioned irregularly in space, with no implicit or explicit
topology.

**Visualization.** The process of converting data to images (or other
sensory stimuli). Alternatively, the end result of the visualization
process.

**Vector.** A specification of direction and magnitude. Vectors can be
used to describe fluid velocity, structural displacement, or object
motion.

**Vector Field Topology.** Vector fields are characterized by regions
flow diverges, converges, and/or rotates. The relationship of these
regions one to another is the topology of the flow.

**Vertex.** A primary 0D cell. Is sometimes used synonymously with
point or node.

**View Coordinate System.** The projection of the world coordinate
system into the camera's viewing frustrum.

**View Frustrum.** The viewing region of a camera defined by six
planes: the front and back clipping planes, and the four sides of a
pyramid defined by the camera position, focal point, and view angle
(or image viewport if viewing in parallel projection).

**Visual Programming.** A programming model that enables the
construction and manipulation of visualization applications. A typical
implementation is the construction of a visualization pipeline by
connecting execution modules into a network.

**Visualization Network.** A series of process objects and data
objects joined together into a dataflow network.

**Volume.** A regular array of points in 3D space. Volumes are often
defined as a series of 2D images arranged along the *z*-axis.

**Volume Rendering.** The process of directly viewing volume data
without converting the data to intermediate surface primitives.
Contrast with *surface rendering* .

**Vorticity.** A measure of the rotation of fluid flow.

**Voxel.** Short for volume element. In VTK, a primary
three-dimensional cell with six faces. Each face is perpendicular to
one of the coordinate axes.

**Warping.** A scalar and vector visualization technique that distorts
an object to magnify the effects of data value. Warping may be used on
vector data to display displacement or velocity, or on scalar data to
show relative scalar values.

**Wedge.** A type of primary 3D cell. The wedge has two triangular
faces connected with three quadrilateral faces. It has five faces,
nine edges, and six vertices. The quadrilateral faces of the wedge are
not necessarily planar.

**World Coordinate System.** A three-dimensional Cartesian coordinate
system in which the main elements of a rendering scene are positioned.

**Writer.** A type of mapper object that writes data to disk or other
I/O device.

**Yaw.** A rotation of a camera's position about the vertical axis,
centered at its viewpoint. See also *pitch* and *roll*. Contrast with
*azimuth* .

**Z-Buffer.** Memory that contains the depth (along the view plane
normal) of a corresponding element in a frame buffer.

**Z-Buffering.** A technique for performing hidden line (point,
surface) removal by keeping track of the current depth, or *z* value
for each pixel. These values are stored in the *z*-buffer.

**Zoom.** A camera operation that changes the field of view of the
camera. Contrast with *dolly*.
