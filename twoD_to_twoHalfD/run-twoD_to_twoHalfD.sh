#!/bin/bash

velOrig=vel125x383

nz=125
nx=383
ny=100

./twoD_to_twoHalfD.exe nz=$nz nx=$nx ny=$ny input2d=$velOrig.bin output3d=$velOrig-3d.bin
