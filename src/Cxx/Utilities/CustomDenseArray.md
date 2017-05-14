### Description
The only thing you have to do to enable your class to work with vtkDenseArray is add a single line:   

<source lang="cpp">
operator vtkVariant() const { return vtkVariant(); }
</source>
