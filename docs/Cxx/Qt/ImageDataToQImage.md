[VTKExamples](/index/)/[Cxx](/Cxx)/Qt/ImageDataToQImage

### Description
This example shows how a vtkImageData can be converted into a [QImage](http://doc.qt.io/qt-5/qimage.html).

See also the [QImageToImageSource](Cxx/Qt/QImageToImageSource) example.

**ImageDataToQImage.cxx**
```c++
#include <vtkVersion.h>

#include <vtkImageData.h>
#include <vtkSmartPointer.h>

#include <QImage>
#include <QColor>
#include <QApplication>

// Create a green 50x50 imageData for demonstration purposes
vtkSmartPointer<vtkImageData> createDemoImageData()
{
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
  image->SetDimensions( 50, 50, 1 );
#if VTK_MAJOR_VERSION <= 5
  #pragma message( VTK_MAJOR_VERSION )
  image->SetNumberOfScalarComponents( 3 );
  image->SetScalarTypeToUnsignedChar();
  image->AllocateScalars();
#else
  image->AllocateScalars( VTK_UNSIGNED_CHAR, 3 );
#endif

  int width = image->GetDimensions()[0];
  int height = image->GetDimensions()[1];

  for ( int y = 0; y < height; y++ )
  {
    for ( int x = 0; x < width; x++ )
    {
      unsigned char *pixel =
        static_cast<unsigned char *>( image->GetScalarPointer( x, y, 0 ) );
      pixel[0] = 0;
      pixel[1] = 255;
      pixel[2] = 0;
    }
  }

  return image;
}

// The actual conversion code
QImage vtkImageDataToQImage( vtkSmartPointer<vtkImageData> imageData )
{
  if ( !imageData ) { return QImage(); }

  /// \todo retrieve just the UpdateExtent
  int width = imageData->GetDimensions()[0];
  int height = imageData->GetDimensions()[1];
  QImage image( width, height, QImage::Format_RGB32 );
  QRgb *rgbPtr =
    reinterpret_cast<QRgb *>( image.bits() ) + width * ( height - 1 );
  unsigned char *colorsPtr =
    reinterpret_cast<unsigned char *>( imageData->GetScalarPointer() );

  // Loop over the vtkImageData contents.
  for ( int row = 0; row < height; row++ )
  {
    for ( int col = 0; col < width; col++ )
    {
      // Swap the vtkImageData RGB values with an equivalent QColor
      *( rgbPtr++ ) = QColor( colorsPtr[0], colorsPtr[1], colorsPtr[2] ).rgb();
      colorsPtr += imageData->GetNumberOfScalarComponents();
    }

    rgbPtr -= width * 2;
  }

  return image;
}

int main( int argc, char *argv[] )
{
  QApplication app( argc, argv );

  QImage qimage = vtkImageDataToQImage( createDemoImageData() );
  qimage.save( "qimage.png" );

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageDataToQImage)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageDataToQImage MACOSX_BUNDLE ImageDataToQImage.cxx)
 
target_link_libraries(ImageDataToQImage ${VTK_LIBRARIES})
```

**Download and Build ImageDataToQImage**

Click [here to download ImageDataToQImage](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageDataToQImage.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageDataToQImage.tar* has been downloaded and extracted,
```
cd ImageDataToQImage/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./ImageDataToQImage
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

