# ref: choice := (e and f) xor ((not e) and g)
# src: https://en.wikipedia.org/wiki/SHA-2

# We just tell Python the ints are bools
# We just use "!=" as xor

def _choice(e:bool, f:bool, g:bool) -> bool:
    return int(f if e else g)
    # return int((e and f) != ((not e) and g))

import itertools

tester = list(itertools.product([0, 1],repeat=3))

print(" === Boolean Choice === ")
[print('_choice'+str(test), '->', _choice(*test)) for test in tester]

arrays = (tuple(zip(*tester)))

def choice(e:tuple[bool], f:tuple[bool], g:tuple[bool]) -> tuple[bool]:
    return tuple(_choice(_e, _f, _g) for _e, _f, _g in zip(e,f,g))

# This was ugly
# print('choice'+str(arrays), '->', choice(*arrays))

# pretty print
bitstr = lambda bits : "".join([str(b) for b in bits])
bsstrs = lambda arrs : str(tuple(bitstr(bits) for bits in arrs))
print(" === Bitwise Choice === ")
print('choice'+bsstrs(arrays), '->', "'"+bitstr(choice(*arrays))+"'")

import numpy as np

def _median(e:bool, f:bool, g:bool) -> bool:
    return int(np.median([e,f,g]))

print(" === Boolean Median === ")
[print('_median'+str(test), '->', _median(*test)) for test in tester]

def median(e:tuple[bool], f:tuple[bool], g:tuple[bool]) -> tuple[bool]:
    return tuple(_median(_e, _f, _g) for _e, _f, _g in zip(e,f,g))

print(" === Bitwise Median === ")
print('median'+bsstrs(arrays), '->', "'"+bitstr(median(*arrays))+"'")

def rotleft(a:tuple[bool], n:int) -> tuple[bool]:
    return a[n:] + a[:n]

print(" === Bitwise Rotleft === ")
array = (0,0,1,0,1,1,0,1)
for n in range(len(arrays[0])+1):
    print('rotleft('+bitstr(array)+','+str(n)+') ->', bitstr(rotate(array,n)))