#!/bin/bash

binname=model10_cp-3d.bin
suname=model10_cp-3d.su
nz=401
nx=801
ny=100
dz=2.5
dx=2.5
dy=2.5

./bin2su.exe binmodel=$binname sumodel=$suname nz=$nz nx=$nx ny=$ny dz=$dz dx=$dx dy=$dy odtkey=0
#./bin2su.exe binmodel=vel125x383-3d.bin sumodel=vel125x383-3d.su nz=125 nx=383 ny=100 dz=24.0 dx=24.0 dy=24.0 >out.txt 
#./bin2su.exe binmodel=vel125x383-3d.bin sumodel=vel125x383-3d.su nz=125 nx=383 ny=100 dz=24.0 dx=24.0 dy=24.0 opendt=1 >out.txt 
