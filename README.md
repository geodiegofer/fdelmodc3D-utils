# tmpUTILS

Temporary utilities to test fdelmodc3D.

# How to use

Clone the repository.
```sh
cd /path/to/UTILS/
make
```
Edit `~/.bashrc`, add the lines:
```sh
TMPUTILSPATH="path/to/tmpUTILS"
export PATH=$PATH:$TMPUTILSPATH/bin
```
Save. `source ~/.bashrc`.

## SU-like functions list
```sh
# Extend a 2D binary velField to 2.5D (3D) binary velField
twoD_to_twoHalfD.exe

# Create a binary rhoField (2D or 3D) from binary velField (2D or 3D)
vel2rho.exe

# Put SU header on a model (vel or rho, 2D or 3D), compliant with `fdelmodc`'s format
bin2su.exe
```
Documentation for each function can be seen by typing the function name on a terminal with no parameters.

# Useful BASH functions

The file `bash_tmpUTILS.sh` contains useful `bash` functions for visualizing 2D and 3D data.

To make use of these functions,
```sh
source bash_tmpUTILS.sh
```
which has to be run everytime. To load automatically on startup, you may add a line to your `~/.bashrc`:
```sh
TMPUTILSPATH="path/to/tmpUTILS"
source $TMPUTILSPATH/bash_tmpUTILS.sh
```

## Bash functions list
```sh
# Wrapper around nimage to see 3D SU files
sunimage

# Plot src and rec on top of 2D model 
# see fdelmodc's manual, page 38
plotgeometry
```
Documentation for each function can be seen by typing the function name on a terminal with no parameters.

`sunimage` requires `nimage` added to Seismic Unix. For information on installing nimage, check [this](https://github.com/vkrGitHub/Installation-Tutorials/tree/master/SU)











