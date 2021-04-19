# file: runme.py

import example

# First create some objects using the pointer library.
print("Testing the pointer library")
a = example.new_intp()
b = example.new_intp()
c = example.new_intp()
example.intp_assign(a, 37)
example.intp_assign(b, 42)

print("     a = %s" % a)
print("     b = %s" % b)
print("     c = %s" % c)

# Call the add() function with some pointers
example.add(a, b, c)

# Now get the result
r = example.intp_value(c)
print("     37 + 42 = %s" % r)

# Clean up the pointers
example.delete_intp(a)
example.delete_intp(b)
example.delete_intp(c)

# Now try the typemap library
# This should be much easier. Now how it is no longer
# necessary to manufacture pointers.

print("Trying the typemap library")
r = example.sub(37, 42)
print("     37 - 42 = %s" % r)

# Now try the version with multiple return values

print("Testing multiple return values")
q, r = example.divide(42, 37)
print("     42/37 = %d remainder %d" % (q, r))

# more tests
# extern void foo(double x[10]);
# extern void bar(double a[4], double b[8]);

x = [i * 1.0 for i in range(10)]
print("x:", x)
example.foo(x)

example.bar([i * 2.0 for i in range(4)], [i * 0.1 for i in range(8)])

# 
example.parity("e\x09ffss\x00\x00\x01\nx", 0)

print("example.summer(x) = %f" % example.summer(x))
print("expected: %f" % sum(x))

print("cnt: ", example.count_chars(b"1a2a3a", 'a'))

p = example.Point()
p.x = 10
p.y = 20
print("p: ", p)
print ("p = (%d, %d)" % (p.x, p.y))

print ("Testing make_point() function")
p0 = example.make_point(0.5, 0.125)
print ("p0=", p0)
print ("p0=(%d,%d)" % (p0.x, p0.y))

print("Testing perimeter (...) function:")
points = [example.make_point(0,0), example.make_point(1,0), example.make_point(1,1), example.make_point(0,1) ]
print(example.perimeter(points))
# end of file
