"""
Converts string into c/c++ array in readable form
used to convert tetriminos into binary shapes
"""

file = open("CodeMake/output.txt", "w")

def write_block(s):
    for i in range(4):
        file.write("\t")
        if i==0: file.write(" {")
        else: file.write("  ")
        
        file.write("{")
        for j in range(4):
            file.write(s[4*i+j])
            if j<3: file.write(", ")

        file.write("}")
        
        if i==3: file.write("},\n")
        else: file.write(",\n")

ss = ["1100011000000000", "0010011001000000", "0000110001100000", "0100110010000000"]
for s in ss:
    write_block(s)
    
file.close()