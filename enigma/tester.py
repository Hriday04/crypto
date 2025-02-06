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
    import subprocess, os

    ## Make executable

    if os.path.isfile("enigma.out"):
        result = subprocess.run(["rm", "enigma.out"])
    result = subprocess.run(["gcc", "enigma.c", "-o", "enigma.out"])
    # check file exists
    if not os.path.isfile("enigma.out"):
        print("Compilation failed.")
        exit()
    result = subprocess.check_output(["head", "-c", "4", "enigma.out"])
    if not "ELF" in str(result)[1:]:
        print("Executable not valid.")
        exit()

    ## Check executable output

    sample = "MNBOASVTTB"
    secret = enigma(sample)
    result = subprocess.check_output(["./enigma.out", sample])
    if not "HELLOWORLD" in str(result):
        print("Sample input incorrectly/not descrypted.")
        exit()

    import random

    sample = "".join([chr(random.randint(ord('A'), ord('Z'))) for _ in range(0x10)])
    secret = enigma(sample)
    result = subprocess.check_output(["./enigma.out", sample])
    if secret in str(result):
        print("Perfect!")
    else:
        print("Not quite!")
