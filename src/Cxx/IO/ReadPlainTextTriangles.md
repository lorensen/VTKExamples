### Description

Here is an example of a custom file-format reader that produces a VTK XML PolyData file from a plain-text input format.  

#### Input Format
```
number_of_points
number_of_triangles
point[point[0]Y point[0](0]X)Z
point[point[1]Y point[1](1]X)Z
...
point[point[N]Y point[N](N]X)Z
triangle[triangle[0]B triangle[0](0]A)C
triangle[triangle[1]B triangle[1](1]A)C
...
triangle[triangle[M]B triangle[M](M]A)C
```

#### Example Input

```
3
1
0.0 0.0 0.0
0.0 0.0 1.0
0.0 1.0 0.0
0 1 2
```
