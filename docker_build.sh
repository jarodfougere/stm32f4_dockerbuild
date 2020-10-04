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

echo ""
echo ""
echo "========================================================"
echo "|  Docker image Complete. Transitioning to build stage |"
echo "========================================================"
echo ""
echo ""
docker run -it $IMAGE # run the latest image (interactive mode)