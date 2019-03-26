#!/bin/bash

velName=vel125x383
rhoName=rho125x383

nz=125
nx=383
ny=100

nsamp=$(($nz*$nx))

./vel2rho.exe nsamp=$nsamp velfile=$velName.bin rhofile=$rhoName.bin

