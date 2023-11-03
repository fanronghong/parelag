#!/bin/bash 

cd /home/fan/repos/build_parelag/
rm -rf ./*

METIS_DIR=/home/fan/ENV4PKGs/metis/install
MFEM_DIR=/home/fan/ENV4PKGs/mfem/install
HYPRE_DIR=/home/fan/ENV4PKGs/hypre/install

cmake /home/fan/repos/parelag 
    -DCMAKE_BUILD_TYPE=Debug -DParElag_ENABLE_OPENMP=OFF -DParElag_ENABLE_PARMETIS=OFF 

