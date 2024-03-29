# Install OpendTect (linux)

Download the linux installer at https://dgbes.com/index.php/download . 
```
mkdir ~/OpendTect 
mv installer-name ~/OpendTect
cd ~/OpendTect
bash installer-name
```
Follow the instructions. If installation fails, check `INSTALL.txt` at `~/OpendTect/6.4.0`.  

The next is step is optional, but recommended; it saves good time on opening OpendTect and loading data to it.  
Create a 'standard' OpendTect data folder:
```
mkdir ~/opendtect-data-folder
```

Edit your `~/.bashrc`, adding the lines:
```sh
export ODTPATH=path/to/opendtect     #example: /home/victork/OpendTect/6.4.0
export ODTAREA=path/to/your/odtdata      #example: /home/victork/my_opendtect_data/
```
and run `source ~/.bashrc`. Some shells in `fdelmodc3D-utils` make use of these variables, so setting these up is recommended. 

# Run OpendTect

OpendTect is run from inside its main folder with `./start_dtect`. If `ODTPATH` is set, it can be run as:
```
$ODTPATH/start_dtect &
``` 
from anywhere.

# Test and visualize 3D open data

As a beginner step to use OpendTect to visualize 3D seismic data, dowload F3 Netherlands 3D data (`~9GB`)
at https://terranubis.com/datainfo/Netherlands-Offshore-F3-Block-Complete . There is also a beginner's manual 
in this same page. Creating a survey from a SEG-Y, checking header parameters, seeing some inlines/crosslines, 
getting acquainted to the 3 rotation buttons and finding best color schemes should be enough to proceed with 
custom 3D data (below).

## Visualize custom 3D velocity/density models

OpendTect is intended for seismic data; nevertheless, it is possible to visualize velocity/density models in SU format if the 
header parameters `cdp, fldr, sx, sy` are filled correctly. Check [how_to_create25d_data](https://github.com/vkrGitHub/fdelmodc3D-utils/tree/master/how_to_create25d_data) folder for more details. With this SU data 
with filled header parameters, convert file to `.sgy` in order to plot with OpendTect:
```sh
# example with model10_cp-3d.su
su2sgy.sh model10_cp-3d.su
```
which generates `model10_cp-3d.sgy`. Check the last section of this README on how to load it to OpendTect.

## Visualize a shot modeled with fdelmodc3D

To visualize a single shot with receivers in the x and y directions (hence, a cube), produced by `fdelmodc3D`, SU functions can be 
used. Since `fdelmodc3D` outputs data with SU header as a standard, one can use functions such as `suximage`, `suxmov`, or the wrapper 
around `nimage` (`sunimage.sh`) present in this repository. If SU is installed, entering the function without parameters shows the documentation, and how to use. `surange`ing the data outputs the necessary parameters in order to use these functions.


To view data with OpendTect, some extra header parameters must be added to the shot data produced by `fdelmodc3D`. The variables 
`cdp`, `fldr`, `sx` and `sy` must be added accordingly (more info on `bin2su` and `su2odtsu` modules documentation). Then, this 
new SU file must be converted to SEG-Y format in order to be read by OpendTect. The process can be done by the following shells:
```sh
# Add extra header variables to shot3D.su 
dx=25.0   #example
dy=25.0   #example
su2odtsu.sh shot3D.su $dx $dy shot3D-odt.su

# Convert data to segy format
su2sgy.sh shot3D-odt.su # produces shot3D-odt.sgy
```
Check the last section of this README on how to load it to OpendTect.

## Visualize multiple shots modeled with fdelmodc3D

Todo. For now, one can `suwind` individual shot cubes and make the process above.

# Loading SEG-Y data to OpendTect

Convert your SU data (with the necessary OpendTect header parameters - see above sections for a 3D shot and  [how_to_create25d_data](https://github.com/vkrGitHub/fdelmodc3D-utils/tree/master/how_to_create25d_data) for 3D velocity and density models) to SEG-Y 
format.


(optional) Move data to `$ODTAREA` . This process saves some time, since locating the `.sgy` 
with OpendTect's API takes some clicks. 
```
mv model10_cp-3d.sgy $ODTAREA
```

Start OpendTect: 
```sh
$ODTPATH/start_dtect &
```
or enter the folder and run `start_dtect &`.

Set the data folder to the `$ODTAREA` folder (saves time; but you can always search for the SEGY manually later).  
Click "ok", "yes" until the "Survey Setup and Selection" window opens.  
Select "New survey".  
Type a survey name (Ex: model10-survey), select "Scan SEG-Y files", check "Depth" with "Meter". 
Select the SEG-Y file (Ex: model10_cp-3d.sgy).  
Check the header parameters; for instance, "In-line range" should represent y-samples and "Cross-line range" the x-samples. 
Click "OK".  
Click "Yes, continue" (or scan file if you want).
Click "OK" in the "Edit Survey Parameters" window.  
Now the survey is set up, click it and click "Select".  
Click "Yes" for SEGY import.  
Click "Import".
Click "OK".
In the graphical window, adjust the z-stretch, click "OK". The data is probably bugged in the upper left corner. Maximizing 
OpendTect should fix this; if not, clicking the Ruler icon in the left panel should fix it after a while. 
Click "In-line">"Add default data".  
Click "Cross-line">"Add default data".  
Set colors to see the data.   
It should be enough to visualize the model data. More information on F3 Netherlands manual PDF.  












