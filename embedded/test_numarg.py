#
# https://docs.python.org/3/extending/embedding.html#pure-embedding
#

import emb

def test(*args):
	print("Number of arguments", emb.numargs())
	return 0