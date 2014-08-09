#!/bin/bash

chuckwagon r | sed -n -e 's/^CW: //p' | tr -d '\r' | bash
