#!/bin/bash

chuckwagon r | sed -n -e 's/^CW: //p' --unbuffered | bash
