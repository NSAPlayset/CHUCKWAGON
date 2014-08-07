#!/bin/bash

cat /dev/ttyO4 | grep --line-buffered CW: | sed -n -e 's/^CW: //p' --unbuffered | chuckwagon w
