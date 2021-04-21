#!/bin/bash
# build and test the fun library using the makefile at /src
make clean
make
make install
./testfun
# test.sce runs in cli mode, no gui prompts allowed while using builder.sce
# removed the  tbx_builder_gateway(toolbox_dir) and tbx_build_localization(toolbox_dir) funciton calls from buider.sce

cd ..
sed '40,41d' ./builder.sce
sed -i '37d' ./builder.sce