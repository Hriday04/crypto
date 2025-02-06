#!/usr/bin/env python3

# constants                       # constant
rs = [                            # rotors
    "BDFHJLCPRTXVZNYEIWGAKMUSQO", # fast
    "AJDKSIRUXBLHWTMCQGZNPYFVOE", # medium
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ", # slow
    "IXUHFEZDAOMTKQJWNSRLCYPBVG"  # reflect
]
A  = ord('A')                     # value of 'A'
NC = len(rs[0])                   # number of characters

# apply a cipher/rotor `r` to a letter `c`
rapply = lambda c, r : r[ord(c) - A]

# invert a cipher/rotor `r`
    # create a list of letters with their index
        # [(r[i],i) for i in range(NC)]
    # sort the list
        # for p in sorted
    # convert indexes to back to letters in the alphabet
        # chr(p[1]+A)
invert = lambda r : [chr(p[1]+A) for p in sorted([(r[i],i) for i in range(NC)])]

# extend the rotor set to include inverted ciphers
    # In reversed order, as well
    # fas med slo ref slo med fas
rs += [invert(r) for r in rs[2::-1]]

# encrypt letter `c` with rotors in default* positions
rotors = lambda c : [c := rapply(c,r) for r in rs][-1]

# default position a,b,c -> r,f,o, respectively
assert([
    rotors('A'),
    rotors('B'),
    rotors('C')
] == ['R','F','O'])

# shift letter `c` forward `n` letters in alphabet
nshift = lambda c, n : chr((ord(c) - A + n) % NC + A)

# allow rotor rotations
    # fast spins every letter
    # medi spins every time fast loops back NC->0
    # slow ""               medi ""
shifts = lambda l, n : [
    l % NC, l // NC % NC, l // (NC*NC) % NC,
    0,
    l // (NC*NC) % NC, l // NC % NC, l % NC
][n]

# combine shift apply? don't know what to call
shiply = lambda c, n, r : nshift(rapply(nshift(c,n),r),-n)
# or if you prefer
shiply = lambda c, n, r : chr((ord(r[(ord(c)-A+n)%NC])-A-n)%NC+A)

# single letter enigma, with number of previous letters `l`
letter = lambda c, l : [c := shiply(c,shifts(l,i),rs[i]) for i in range(len(rs))][-1]

# phrase
    # enigma starts with an single rotation before first encryption.
enigma = lambda s : "".join([letter(s[i],i+1) for i in range(len(s))])

# test
assert([
    enigma("AAA"),
    enigma("ABC"),
    enigma("ZLC")
] == ["ZLC","ZRA","AAA"])

if __name__ == "__main__":
    import sys
    print(enigma(sys.argv[1]))
