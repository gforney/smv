#!/bin/bash

for file in */*.ini; do
  ./checkframe.sh $file
done
