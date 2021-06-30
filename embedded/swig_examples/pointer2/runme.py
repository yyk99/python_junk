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

print ("type(layers)", type(layers))

print ("Get layer info")
layers_arr = example.layer_handle_array_frompointer(layers)
for i in range(count):
	info = example.GetLayerInfo(layers_arr[i])
	print (i, info.description)

try:
	print("let's crash it")
	for i in range(20):
		actual = example.LoadLayer('layer_%d.tif' % i)
		print(i, 'actual:', actual)
except Exception as e:
	print("Aha!", e)

q_info =  example.layer_info_query_t ()
print(20, type(q_info))
print(30, q_info)

res = example.RunInfoQuery(q_info)
assert type(res) is str
print (40, res)

q_info =  example.layer_info_query_t ()

arr = example.layer_handle_array(10)
for i in range(10) : arr[i] = (i + 1) * 0x10000
q_info.m_list = arr
q_info.m_list_size = 10

res = example.RunInfoQuery(q_info)
assert type(res) is str
print (40, res)

