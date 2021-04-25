# file: runme.py

import example

# Call average with a Python list...

print(example.average([1, 2, 3, 4]))

# ... or a wrapped std::vector<int>

v = example.IntVector(4)
for i in range(len(v)):
    v[i] = i + 1
print(example.average(v))


# half will return a Python list.
# Call it with a Python tuple...

print(example.half((1.0, 1.5, 2.0, 2.5, 3.0)))

# ... or a wrapped std::vector<double>

v = example.DoubleVector()
for i in [1, 2, 3, 4]:
    v.append(i)
print(example.half(v))

# now halve a wrapped std::vector<double> in place

example.halve_in_place(v)
print([i for i in v])

# play with points

v = example.PointVector()
for x in [1, 2, 3, 4]:
    p = example.point_t(x, x * 0.01)
    v.append(p)

for pp in v:
    print(pp)

v = example.point_array(5);
for i in range(5):
    v[i] = example.point_t(i,i)
u = example.point_array(5);
for i in range(5):
    u[i] = example.point_t(i*10, i*10)

print("example.add_in_place.__doc__:")
print(example.add_in_place.__doc__)

print(u[i] for i in range(5))
print(v[i] for i in range(5))

example.add_in_place(v, u, 5)
print(u[i] for i in range(5))
print(list(v[i] for i in range(5)))

# use PointVector
print("*************** use PointVector *****************")

v = example.PointVector(5);
for i in range(5):
    v[i] = example.point_t(i,i)
u = example.PointVector(5);
for i in range(5):
    u[i] = example.point_t(i*10, i*10)

print(u)
print(v)

example.add_in_place_vector(v, u)
print(u)
print(v)
print(u[0], u[1])

#import code
#code.interact(local=locals())