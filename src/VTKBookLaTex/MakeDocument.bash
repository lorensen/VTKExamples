#!/bin/bash
lualatex VTKTextBook
makeglossaries VTKTextBook
biber VTKTextBook
lualatex VTKTextBook
lualatex VTKTextBook
