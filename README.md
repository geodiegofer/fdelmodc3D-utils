# fdelmodc3D-utils

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

# LIST OF UTILITY MODULES

# suplot3dSliceSnaps.sh
Calls the python script `suplot3dSliceSnaps.py` which does:
1. suranges the file and get header info;
2. suwinds the file, making a slice in the provided dimension
3. nimage's the binary to user










