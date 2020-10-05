import os
import subprocess
import sys
import argparse

def argfmt(string):
    return str(" " + str(string) + " ")



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="parse command line args for docker build script")



    parser.add_argument("--output", action="store", dest="output_dir", default="bin")
    parser.add_argument("--mode", action="store", dest="build_mode", default="Debug")
    parser.add_argument("--rebuild", action="store_true", dest="rebuild")
    args = parser.parse_args()
    build_args = ""
    build_args += argfmt("--build-arg firmware_bin_dir=" + str(args.output_dir))
    build_args += argfmt("--build-arg firmware_build_type=" + str(args.build_mode))
    build_args += argfmt(" --build-arg rebuild=-r")
    docker_build_string = "docker build . "
    docker_build_string += build_args
    print("docker_build_string = \"" + str(docker_build_string) + "\"\n")
    os.system(docker_build_string)
    image = str(subprocess.check_output("docker image ls -q | head -n 1", shell=True, universal_newlines=True))
    # remove trailing newline / linefeed / carriage return in a platform independent manner
    image = str(image.rstrip())
    temp_container=str("dummy")
    copy_string=str(temp_container) + ":/work/" + str(args.output_dir) + " ./"
    os.system("docker create -ti --name" + " " + str(temp_container) + " " + str(image) + " " + "bash")
    os.system("docker cp" + " " + copy_string)
    os.system("docker rm -f" + " " + str(temp_container))