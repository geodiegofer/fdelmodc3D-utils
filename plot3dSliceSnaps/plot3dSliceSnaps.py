import sys
import os
import fileinput
import re
import datetime
import numpy as np

from functools import wraps
from time import time

# Get console dimensions for pretty print
thei,twid = list(map(int, os.popen('stty size','r').read().split() ) )

# Timing decorator
def timing(f):
    @wraps(f)
    def wrapper(*args, **kwargs):
        start = time()
        result = f(*args, **kwargs)
        end = time()
        print(f"Took {end-start:7.3}s".rjust(twid,' '))
        return result
    return wrapper

# Shell calling function
@timing
def wos(formstr: str):
	formstr = eval(f'f"""{formstr}"""')

	print(f">>{sys.argv[0]}:\n\t",end='')
	print(formstr)
	os.system(formstr) 

def strfrac2float(frac_str):
    try:
        return float(frac_str)
    except ValueError:
        num, denom = frac_str.split('/')
        try:
            leading, num = num.split(' ')
            whole = float(leading)
        except ValueError:
            whole = 0
        frac = float(num) / float(denom)
        return whole - frac if whole < 0 else whole + frac

#######################################################################################################################
# START
#######################################################################################################################
print('='*twid)
print(f'START {sys.argv[0]}'.center(twid,'='))
print('='*twid)

print(f"{sys.argv[0]} How to use:")
print(f"py {sys.argv[0]} slicedim fac snaps.su")
print(f"Ex:\n py {sys.argv[0]} y 2/3 snap_sp.su")
print(f"fac: use fractions or decimal numbers. Cannot be >1.\n")
print(f"Ex:\n py {sys.argv[0]} y 1/2 snap_sp.su\n If ny=201, it will give snaps of the 100-th y-slice.\n")

if(len(sys.argv)!=(1+3)):
	print(f"Wrong quantity of input parameters. Exiting. Usage:\n py {sys.argv[0]} slicedim slicepos snaps.su\n")
	sys.exit()
	
#######################################################################################################################
# DO STUFF
#######################################################################################################################
# Input dic
indic = {
	"z": "ns",
	"x": "gx",
	"y": "gy",
}
#	"0": "1st",
#	"1": "mid",
#	"2": "last"
#}

# Check inpars
if(sys.argv[1] not in indic):
	print(f"Wrong options for input parameters. Exiting.\n"); sys.exit()
if(sys.argv[3][-3:]!='.su'):
	print(f"Please enter .su file as 3rd parameter. Exiting.\n"); sys.exit()

# Surange
wos('rm tmp.txt')
wos('mysurange.exe {sys.argv[3]} 2>&1 >>tmp.txt')
hdrdic = {}

fp = open('tmp.txt','r')
for i,line in enumerate(fp):
	string = line.split()
	hdrdic.update({string[0]:string[1:]})
fp.close()

d1 = float(hdrdic['d1'][0])	
n1 = int(hdrdic['ns'][0])
gx = int(hdrdic['gx'][1])
scalco = int(hdrdic['scalco'][0])
d2 = float(hdrdic['d2'][0])
n2 = int(gx/(-1*scalco*d2))+1
gy = int(hdrdic['gy'][1])
n3 = int(gy/(-1*scalco*d2))+1 #Warning! Assumes d3=d2

# Get suwind key
if(sys.argv[1]=='y'):
	#mantem tudo igual
	pos = gy
elif(sys.argv[1]=='x'):
	pos = gx				
elif(sys.argv[1]=='z'):
	pos = n1
	
# Get suwind min, max
#if(sys.argv[2]=='0'):
#	pos = pos*0
#elif(sys.argv[2]=='1'):
#	pos = pos/2
#elif(sys.argv[2]=='2'):
#	pos = pos
pos = int(pos*strfrac2float(sys.argv[2]))


title = f"Snaps of {pos}-th {sys.argv[1]}-slice"

tmpfile="tmp.su"

# x,y slicing
if( (sys.argv[1]=='x') | (sys.argv[1]=='y') ): 
	wos('suwind <{sys.argv[3]} key={indic[sys.argv[1]]} min={pos} max={pos} >{tmpfile}')
# z slicing	
else:
	wos('suwind <{sys.argv[3]} key={indic[sys.argv[1]]} itmin={pos} itmax={pos} >{tmpfile}')	

# Sustrip
wos('sustrip <{tmpfile} >test.bin')

# y slicing  
if(sys.argv[1]=='y'):
	wos('nimage n1={n1} n2={n2} <test.bin clip=60 title="{title}" &')
# x slicing	
elif(sys.argv[1]=='x'):
	wos('nimage n1={n1} n2={n3} <test.bin clip=60 title="{title}" &')
# z slicing	
elif(sys.argv[1]=='z'):
	wos('nimage n1={n3} n2={n2} <test.bin clip=60 title="{title}" &')

wos('rm {tmpfile}')

wos('rm test.bin')

#######################################################################################################################
# END
#######################################################################################################################
print('='*twid)
print(f'END {sys.argv[0]}'.center(twid,'='))
print('='*twid)

