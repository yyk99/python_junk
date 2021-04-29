# file: runme.py

import example

print("Loaded...")

print("Empty list is expected...")
layers, count = example.LoadedLayerList()

assert count == 0

print("Add some layers")
actual = example.LoadLayer('first.tif')
print('actual:', actual)

layers, count = example.LoadedLayerList()
assert count == 1

print ("Get layer info")
layers_arr = example.layer_handle_array_frompointer(layers)
for i in range(count):
	info = example.GetLayerInfo(layers_arr[i])
	print (i, info.description)


print("let's crash it")
for i in range(20):
	actual = example.LoadLayer('layer_%d.tif' % i)
	print(i, 'actual:', actual)


