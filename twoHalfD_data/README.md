# Creating 2.5D velocity and rho models from 2D data

The goal is to create a 2.5D model from 2D data (requires [Seismic Unix](https://github.com/JohnWStockwellJr/SeisUnix), 
[fdelmodc](https://github.com/JanThorbecke/OpenSource) and [tmpUTILS](https://github.com/vkrGitHub/tmpUTILS) 
functions:

## From 2D binary data (ex. with `vel125x383.bin`):
```
#!/bin/bash

# Create 2.5-d binary model
echo "CREATING 3D BINARY VELmodel"
velName=vel125x383
nz=125
nx=383
ny=104
twoD_to_twoHalfD.exe nz=$nz nx=$nx ny=$ny input2d=$velName.bin output3d=$velName-3d.bin
echo ""

# Create rho from vel3d
echo "CREATING 3D BINARY RHOmodel"
rhoName=rho125x383
nsamp=$(($nz*$nx*$ny))
vel2rho.exe nsamp=$nsamp velfile=$velName-3d.bin rhofile=$rhoName-3d.bin #uses Gardner
echo ""

# Put SU headers on vel3d and rho3d
echo "PUTTING SU HEADERS"
dz=24.0
dx=24.0
dy=24.0
bin2su.exe binmodel=$velName-3d.bin sumodel=$velName-3d.su nz=$nz nx=$nx ny=$ny dz=$dz dx=$dx dy=$dy opendt=1
bin2su.exe binmodel=$rhoName-3d.bin sumodel=$rhoName-3d.su nz=$nz nx=$nx ny=$ny dz=$dz dx=$dx dy=$dy opendt=1
echo ""
```
The `opendt` flag on `bin2su.exe` is required to add the extra header keywords OpendTect needs to plot the data 
correctly. For a more detailed explanation of how OpendTect uses these extra header keywords, type `bin2su.exe` on 
terminal to see the documentation. Knowing the required keywords, a manual addition using `suaddhead, sushw, suchw`,etc, 
should work equally.



## From 2D SU data made with `fdelmodc`'s `makemod`:
```sh
# snippet from marchenko/demo/model.scr
#!/bin/bash
dx=2.5
dt=0.0005

makemod sizex=10000 sizez=1400 dx=$dx dz=$dx cp0=1800 ro0=1000 \
        orig=-5000,0 file_base=model10.su verbose=2 \
        intt=def x=-5000,5000 z=400,400 poly=0 cp=2300 ro=3000 \
        intt=def x=-5000,5000 z=700,700 poly=0 cp=2000 ro=1100 \
        intt=def x=-5000,5000 z=1100,1100 poly=0 cp=2500 ro=4000

# visualize model
#suximage <model10_cp.su &
```
Replicate data in the y-direction, and put corresponding header parameters. 

Example: replicates `model10_cp.su` 120 times in the y-direction with `dy=2.5`.

Shell version using `cat` to append and `sushw, suchw` to fill header parameters:
```sh
2dSU_to_3dSU_v1.sh 2.5 2.5 120 model10_cp.su
```
takes about 4 minutes (not optimal since `cat` is slow, and each `sushw, suchw` makes its own scan of the data.

Version using `tmpUTILS` C-functions:
```sh
2dSU_to_3dSU_v2.sh model10_cp.su 120 2.5
```
which takes about 38 seconds (faster since it writes the binary using `fwrite`, and fills all header parameters in a single scan).

Both output `model10_cp-3d.su`, which can be visualized using `suximage` (2d slices side-by-side), `sunimage` (see cube) or 
OpendTect (check `view_opendtect` folder in this repository).

The same process must be applied to `model10_ro.su`, and generate `model10_ro-3d.su`.






