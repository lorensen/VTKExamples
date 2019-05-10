### Description
A word cloud is a visualization of word frequency in a given text as a weighted list. It is a variation of a [tag cloud](https://en.wikipedia.org/wiki/Tag_cloud).

This example creates a word cloud using vtkFreeTypeTools to render words into images. vtkImageBlend adds these images onto a final image. A vtkImageIterator compares pixels in the text image with those in the final image. If a non-background pixel exists in the final image, that word is not kept.

The example illustrates a number of std:: concepts including [random numbers](http://www.cplusplus.com/reference/random/), [regular expressions](http://www.cplusplus.com/reference/regex/) = and [multi_set](http://www.cplusplus.com/reference/set/multiset/).

Also, the [kwsys](https://gitlab.kitware.com/utils/kwsys) CommandLineArguments  used to process command line arguments.

Many parameters are exposed on the command line:
```bash
Usage: ./bin/WordCloud.app/Contents/MacOS/WordCloud
  textFileName 
  --backgroundColorName opt  Name of he color for the background(MignightBlue)
  --colorDistribution opt o  Distribution of random colors(.6 1.0)
  --colorScheme opt  Color scheme(constant)
  --dpi opt  Dots per inch(200)
  --fontFile opt  Font file name("")
  --fontMultiplier opt  Font multiplier(6)
  --gap opt  Space gap of words (2)
  --maxFontSize opt  Maximum font size(48)
  --minFontSize opt  Minimum font size(8)
  --orientationDistribution  Ranges of orientations(-20, 20)
  --size opt opt ...  Size of image(640 480)
  --wordColorName opt  Name of the color for the words (banana)
```
The example image was produced with these arguments:
```bash
WordCloud ${DATA}/Gettysburg.txt --dpi 150 --fontFile ${DATA}/Canterbury.ttf)
```
