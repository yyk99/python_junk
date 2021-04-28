# file: runme.py

import example

def part1():
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

def part20():
	# more tests
	# extern void foo(double x[10]);
	# extern void bar(double a[4], double b[8]);

	x = [i * 1.0 for i in range(10)]
	print("x:", x)
	example.foo(x)

	example.bar([i * 2.0 for i in range(4)], [i * 0.1 for i in range(8)])

	print("example.summer(x) = %f" % example.summer(x))
	print("expected: %f" % sum(x))

def part21():
	# 
	example.parity("e\x09ffss\x00\x00\x01\nx", 0)
	print("cnt: ", example.count_chars(b"1a2a3a", 'a'))

def part3():

	p = example.Point()
	p.x = 10
	p.y = 20
	print("p: ", p)
	print ("p = (%g, %g)" % (p.x, p.y))

	p2 = example.make_point2(0.75, 7.62)
	print("p2: ", p2)
	print ("p2 = (%g, %g)" % (p2.x, p2.y))

	print ("Testing make_point() function")
	p0 = example.make_point(0.5, 0.125)
	print ("p0=", p0)
	print ("p0=(%g, %g)" % (p0.x, p0.y))

	print("Testing perimeter (...) function:")
	points = [example.make_point(0,0), example.make_point(1,0), example.make_point(1,1), example.make_point(0,1) ]
	print(example.perimeter(points))

	print("Testing add_points(...) function")
	res = example.add_points(p0, p2)
	print ("res = (%g, %g)" % (res.x, res.y))

def part4():
	print ("---------------- part4: ---------------- ")
	print ("example.generate_points.__doc__: ", example.generate_points.__doc__)
	point_arr, point_arr_size = example.generate_points();
	print(point_arr)
	print(point_arr_size)

	# IMPORTANT: construct Point_array object from the returned pointer
	the_array = example.Point_array_frompointer(point_arr)

	for i in range(point_arr_size):
		print (i, the_array[i].x, the_array[i].y)

	return

part1()
part20()
part21()
part3()
part4()

# end of file
