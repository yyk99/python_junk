# file: runme.py

import example

q_info =  example.layer_info_query_t ()
print(1, q_info)
print(2, q_info.m_list)
print(3, q_info.m_list_size)

arr = example.layer_handle_array(1)
print(10, type(arr))

arr[0] = 42
print(20, arr[0])
print(30, type(arr[0]))

q_info.m_list = arr.cast()
q_info.m_list_size = 1

parr = example.point_array(2)
parr[0] = example.point_t(1, 2)
parr[1].x = 10
parr[1].y = 20

q_info.m_point_list = parr
q_info.m_point_list_size = 2

res = example.RunInfoQuery(q_info)
assert type(res) is str
print (40, res)
