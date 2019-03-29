# Install OpendTect (linux)

Download the linux installer at https://dgbes.com/index.php/download . 
```
mkdir ~/OpendTect 
mv installer-name ~/OpendTect
cd ~/OpendTect
bash installer-name
```
Follow the instructions. If installation fails, check `INSTALL.txt` at `~/OpendTect/6.4.0`.  
Edit your `~/.bashrc`, adding the line:
```sh
ODTPATH=path/to/opendtect #example: /home/victork/OpendTect/6.4.0
```

# Run OpendTect

OpendTect is run from inside its main folder with `./start_dtect`. If `ODTPATH` is set, it can be run as:
```
$ODTPATH/start_dtect &
``` 

# Test and visualize 3D open data

As a beginner step to use OpendTect to visualize 3D seismic data, dowload F3 Netherlands 3D data (`~9GB`)
at https://terranubis.com/datainfo/Netherlands-Offshore-F3-Block-Complete . There is also a beginner's manual 
in this same page. Creating a survey from a SEG-Y, checking header parameters, seeing some inlines/crosslines, 
getting acquainted to the 3 rotation buttons and finding best color schemes should be enough to proceed with 
custom 3D data (below).

# Visualize custom 3D velocity/density models

OpendTect is intended for seismic data; nevertheless, it is possible to visualize velocity/density models following 
the steps below:

## Creating data

1. Create a 2.5D model from 2D data (requires [Seismic Unix](https://github.com/JohnWStockwellJr/SeisUnix), 
[fdelmodc](https://github.com/JanThorbecke/OpenSource) and [tmpUTILS](https://github.com/vkrGitHub/tmpUTILS) 
functions:

1.1 From 2D binary data (ex. with `vel125x383.bin`):
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

1.2 From 2D SU data (ex. with `fdelmodc`'s `makemod` layered model):
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

(stopped here)

```


2. Create a 'standard' OpendTect data folder (optional). It is a folder to move the `.sgy` you want to plot. This saves some 
time since OpendTect's API to locate files requires some clicking (specially if one is working with many subfolders). 
Personal preference is to create this folder at home directory(~).
```
mkdir ~/opendtect-data-folder
```

## Opening data

2. Convert to sgy and move to `~/opendtect-data-folder` (optional). This process saves some time, since locating the `.sgy` 
with OpendTect's API takes some clicks. 
```

```

3. Start OpendTect: 
```
$ODTPATH/start_dtect &
```

4. Set a new survey loading 
