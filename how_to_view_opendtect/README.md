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
and run `source ~/.bashrc`. Some shells in `tmpUTILS` make use of these variables, so setting these up is recommended. 

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

OpendTect is intended for seismic data; nevertheless, it is possible to visualize velocity/density models in SU format if the 
header parameters `cdp, fldr, sx, sy` are filled correctly. Check [how_to_create25d_data](https://github.com/vkrGitHub/fdelmodc3D-utils/tree/master/how_to_create25d_data) folder for more details. With this SU data 
with filled header parameters, convert file to `.sgy` in order to plot with OpendTect:
```sh
# example with model10_cp-3d.su
su2sgy.sh model10_cp-3d.su
```
which generates `model10_cp-3d.sgy`.


## Opening data

Convert to sgy and move to `$ODTAREA` (optional). This process saves some time, since locating the `.sgy` 
with OpendTect's API takes some clicks. 
```
su2sgy.sh model10_cp-3d.su
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












