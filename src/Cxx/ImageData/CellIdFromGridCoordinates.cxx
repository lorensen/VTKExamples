#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkStructuredData.h>

int main(int, char *[])
{

  vtkSmartPointer<vtkImageData> grid = vtkSmartPointer<vtkImageData>::New();
  grid->SetOrigin(0, 0, 0);

  unsigned int numVoxelsPerDimension = 2; //the number of voxels in each dimension
  grid->SetSpacing(1, 1, 1);

  int extent[6];
  extent[0] = 0;
  extent[1] = numVoxelsPerDimension;
  extent[2] = 0;
  extent[3] = numVoxelsPerDimension;
  extent[4] = 0;
  extent[5] = numVoxelsPerDimension;
  grid->SetExtent(extent);
  grid->AllocateScalars(VTK_INT,1);

  for(unsigned int i = 0; i < numVoxelsPerDimension; ++i)
  {
    for(unsigned int j = 0; j < numVoxelsPerDimension; ++j)
    {
      for(unsigned int k = 0; k < numVoxelsPerDimension; ++k)
      {
        int pos[3];
        pos[0] = i;
        pos[1] = j;
        pos[2] = k;

        vtkIdType id = vtkStructuredData::ComputeCellIdForExtent(extent, pos);
        std::cout << "Cell " << i << " " << j << " " << k << " has id : " << id << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}
