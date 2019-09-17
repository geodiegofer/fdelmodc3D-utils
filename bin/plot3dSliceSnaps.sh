#!/bin/bash

eval "$(conda shell.bash hook)"
conda activate 

add=$(echo $PATH | grep -oP "(?<=:)[^:]+fdelmodc3D-utils/bin(?=:)" | head -1)

python "$add/plot3dSliceSnaps.py" $@

conda deactivate

