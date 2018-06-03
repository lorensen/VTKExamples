@echo off
lualatex VTKTextBook
makeglossaries VTKTextBook
biber VTKTextBook
makeindex VTKTextBook
lualatex VTKTextBook
lualatex VTKTextBook
