#
#
#

color = (0, 0, 0)

def SetColor (aColor):
	global color
	assert type(aColor) is tuple
	assert len(aColor) == 3
	color = aColor

def GetColor ():
	return color

if __name__ == "__main__":
	print ("import me")
