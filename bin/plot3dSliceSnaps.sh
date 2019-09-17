#!/bin/bash

eval "$(conda shell.bash hook)"
conda activate 

python ../plot3dSliceSnaps/plot3dSliceSnaps.py $@

conda deactivate

