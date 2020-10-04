#!/bin/bash
#
# EXECUTE THIS SCRIPT TO BUILD THE DOCKER IMAGE AND COMPILE THE PROJECT
# 
# THE DOCKER IMAGE ONLY NEEDS TO BE BUILT ONE. AFTER THAT IT WILL BE IN YOUR
# DOCKER IMAGE CACHE
#
# YOU CAN KEEP USING THIS SCRIPT TO BUILD THE PROJECT
docker build .
IMAGE="$(docker image ls -q | head -n 1)"
docker create -ti --name dummy $IMAGE bash > /dev/null 2>&1
docker cp dummy:/work/bin ./ > /dev/null 2>&1
docker rm -f dummy > /dev/null 2>&1
chmod +xwr ./bin
chmod +wr ./bin/*
chmod +x ./bin/*.hex
chmod +x ./bin/*.bin
chmod +x ./bin/*.elf
echo ""
echo "================================================================="
echo "| Copied completed firmware files out of docker build container |"
echo "================================================================="