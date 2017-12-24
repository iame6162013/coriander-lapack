#!/bin/bash

cd ~/coriander/bin/
python cocl_plugins.py install --repo-url https://github.com/iame6162013/coriander-solver

cd -
cp -r ./kernels ~/coriander
