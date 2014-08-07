#!/bin/bash

cat /dev/ttyO4 | grep --line-buffered CW: | chuckwagon w
