#!/bin/bash

DATE=$(date +"%Y-%m-%d_%H%M%S")

raspistill -vf -hf -o ../photo_$DATE.jpg -t 1
