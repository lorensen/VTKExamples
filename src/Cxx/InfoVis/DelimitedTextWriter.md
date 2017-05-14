### Description
Is the output of
<source lang="cpp">
"","",""
0,1,2
3,4,5
6,7,8
</source>

expected? What is the first line indicating? Simply that there are 3 string fields?

With my prior edit, the first line is now "column-0","column-1","column-2" -- the first line is the names of the column arrays in the table. I added them to the example because the example was crashing on Windows builds, where streaming a NULL char* is no bueno. (David Cole)
