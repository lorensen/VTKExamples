#!/usr/bin/env python
import vtk
import vtkmath
def main():
    numRand = 3;
    #Generate numRand random numbers from a uniform distribution between 0.0 and 2.0
    for i in range(0,numRand):
    	i = vtkmath.random.uniform(0.0,2.0)
    	print(i)
		
if __name__ == '__main__':
    main()
