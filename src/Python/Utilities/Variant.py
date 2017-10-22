from __future__ import print_function
import vtk
import sys

# Unicode string for demonstration (etre with circumflex)
if sys.hexversion >= 0x03000000:
    unicodeEtre = '\xeatre'  # unicode in Python 3
else:
    unicodeEtre = unicode('\xeatre', 'latin1')  # noqa: F821

#
# Basic vtkVariant usage
#

# Default constructor
v = vtk.vtkVariant()
print("Invalid variant: %r, '%s'" % (v, v.GetTypeAsString()))

# Copy constructor
v = vtk.vtkVariant(vtk.vtkVariant("variant"))
print("Copied variant: %r, '%s'" % (v, v.GetTypeAsString()))

# Conversion constructors
v = vtk.vtkVariant(1)
print("Integer variant: %r, '%s'" % (v, v.GetTypeAsString()))
v = vtk.vtkVariant(1.0)
print("Float variant: %r, '%s'" % (v, v.GetTypeAsString()))
v = vtk.vtkVariant("hello")
print("String variant: %r, '%s'" % (v, v.GetTypeAsString()))
v = vtk.vtkVariant(unicodeEtre)
print("Unicode variant: %r, '%s'" % (v, v.GetTypeAsString()))
v = vtk.vtkVariant(vtk.vtkStringArray())
print("Object variant: %r, '%s'" % (v, v.GetTypeAsString()))

# Explicit type constructor
v1 = vtk.vtkVariant(1, vtk.VTK_UNSIGNED_SHORT)
v2 = vtk.vtkVariant(2, v1.GetType())
print("UShort variant: %r, '%s'" % (v2, v2.GetTypeAsString()))

# Type checking
if v2.IsUnsignedShort():
    print("v2 is UnsignedShort")
else:
    print("v2 is not UnsignedShort, it is", v2.GetTypeAsString())

# Explicit value extraction
s = v2.ToString()
print("String value: %s, %s" % (s, type(s)))
i = v2.ToInt()
print("Int value: %i, %s" % (i, type(i)))

# Automatic argument conversion
a = vtk.vtkVariantArray()
a.InsertNextValue(vtk.vtkVariant())
a.InsertNextValue(1)
a.InsertNextValue(2.0)
a.InsertNextValue("hello")
a.InsertNextValue(unicodeEtre)
a.InsertNextValue(vtk.vtkVariantArray())
print("Variant array:")
for i in range(a.GetNumberOfValues()):
    v = a.GetValue(i)
    print("%i: %r, '%s'" % (i, v, v.GetTypeAsString()))

# Comparison
if v2 == vtk.vtkVariant(2):
    print("v2 is equal to 2")
if v2 > vtk.vtkVariant(1):
    print("v2 is greater than 1")
if v2 < vtk.vtkVariant(3):
    print("v2 is less than 3")
if v2 == vtk.vtkVariant("2"):
    print("v2 is equal to '2'")

# Use as a dict key (hashed as a string)
d = {}
d[vtk.vtkVariant(1)] = 0
d[vtk.vtkVariant('1')] = 1
d[vtk.vtkVariant()] = 3
print("Index is %i" % d[vtk.vtkVariant(1.0)])

#
# Extra functionality from vtk.util.vtkVariant
#
# These are templated functions in C++, but in Python
# they take the template arg as a string instead,
# e.g. vtkVariantCreate<unsigned int>(1) becomes
#      vtkVariantCreate(1, 'unsigned int')

# Creation
v = vtk.vtkVariantCreate(1, 'unsigned int')

# Value extraction
v = vtk.vtkVariant(6.0)
f = vtk.vtkVariantExtract(v)

# Value extraction with type specified
f = vtk.vtkVariantExtract(v, 'double')

# Casting a variant
v = vtk.vtkVariant("10")
i = vtk.vtkVariantCast(v, 'int')
print("Valid cast result: %r" % i)

# A failed cast returns None
v = vtk.vtkVariant("hello")
i = vtk.vtkVariantCast(v, 'int')
print("Invalid cast result: %r" % i)

#
# Comparisons and sorting: See VTK docs for more info
#

# Special function vtk.vtkVariantStrictWeakOrder:
# Compare variants by type first, and then by value.  For Python 2, the
# return values are -1, 0, 1 like the Python 2 "cmp()" method.  This is
# in contrast with the Python 3 and C++ versions of this function, which
# check if (v1 < v2) and return True or False.
v1 = vtk.vtkVariant(10)
v2 = vtk.vtkVariant("10")
r = vtk.vtkVariantStrictWeakOrder(v1, v2)
print("Strict weak order (10, '10') ->", r)

# Sorting by strict weak order, using a key function:
unsorted = [1, 2.5, vtk.vtkVariant(), "0", unicodeEtre]
l = [vtk.vtkVariant(x) for x in unsorted]
l.sort(key=vtk.vtkVariantStrictWeakOrderKey)
print("Sort by weak order ->", l)

# Check two variants for strict equality of type and value.
b = vtk.vtkVariantStrictEquality(v1, v2)
print("Strict equality (10, '10') -> %s" % b)

# Two special-purpose methods.
# First is identical to (v1 < v2)
b = vtk.vtkVariantLessThan(v1, v2)
# Second is identical to (v1 == v2)
b = vtk.vtkVariantEqual(v1, v2)
