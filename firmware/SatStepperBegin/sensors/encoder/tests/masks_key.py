masks = [
     0b00001101,
     0b00001011,
     0b00000010,
     0b00000100,

     0b00000001,
     0b00001000,
     0b00001110,
     0b00000111,

     0b00000000,
     0b00001111,
     0b00000101,
     0b00001010,

     0b00001100,
     0b00000011,
     0b00000110,
     0b00001001 ]


for m in masks:
    print('{} : {}'.format(hex(m), m))

if len(masks) != len(set(masks)):
    print("WARNING: masks is not uniqued!")
else:
    print("Uniq test passed: masks is uniqued")

