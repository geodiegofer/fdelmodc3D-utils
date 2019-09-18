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

# plot3dSliceSnaps.sh
Calls C executable that slices a binary(float) 4D snapscube and nimage's it to user. Must provide nz, nx, ny. Doc:
```
------- plot3dSliceSnaps --------
Slices a 3D snapscube binary in one of 3 dimensions (z,x,y) producing a 2D snapcube in the selected slice. Slicing is done by specifying a dimension and a factor 'fac'. The maximum of selected dim is multiplied by fac,therefore fac must be <1.

Usage: ./plot3dSliceSnaps.exe nz nx ny slicedim fac snaps.bin
```

# suplot3dSliceSnaps.sh
Calls the python script `suplot3dSliceSnaps.py` that slices a SU 4D snapscube and nimage's it to user. No need to provide any 
parameters since this guy's got a header. Doc:
```
------- suplot3dSliceSnaps --------
Slices a 3D snapscube SUfile in one of 3 dimensions (z,x,y) producing a 2D snapcube in the selected slice. Slicing is done by specifying a dimension and a factor 'fac'. The maximum of selected dim is multiplied by fac; therefore fac must be <1.
```









