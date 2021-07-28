import GM

GM.SetColor((1,2,3))

print('color', GM.gm.color)

assert GM.GetColor() == (1,2,3)
