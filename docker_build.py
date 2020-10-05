import os
import subprocess
import sys

def argfmt(string):
    return str(" " + str(string) + " ")
if __name__ == "__main__":
    print("sys.argv = " + str(args))
    docker_build_string = argfmt("docker build .")
    for i in range(1, len(args)):
        if(args[i] == "-o" or args[i] == "--output"):
            if(i == 0):
                docker_build_string += argfmt("--build-arg")
            i = i + 1
            arg = "-o=" + str(args[i])
            docker_build_string += argfmt(arg)
        elif(args[i] == "-m" or args[i] == "--mode"):
            if(i == 0):
                docker_build_string += argfmt("--build-arg")
            i = i + 1
            arg = "-m=" + str(args[i])
            docker_build_string += argfmt(arg)
        elif(args[i] == "-r" or args[i] == "--rebuild"):
            if(i == 0):
                docker_build_string += argfmt("--build-arg")
            i = i + 1
            docker_build_string += argfmt("--no-cache")
        else:
            print("Invalid command line argument \"" + str(args[i]) + "\".")
            exit(1)
    print("Executing script with docker_build_string = \"" + str(docker_build_string) + "\"\n")
    os.system(docker_build_string)
    image = str(subprocess.check_output("docker image ls -q | head -n 1", shell=True, universal_newlines=True))
    # remove trailing newline / linefeed / carriage return in a platform independent manner
    image = str(image.rstrip())
    temp_container=str("dummy")
    copy_string=str(temp_container) + ":/work/bin ./"
    os.system("docker create -ti --name" + " " + str(temp_container) + " " + str(image) + " " + "bash")
    os.system("docker cp" + " " + copy_string)
    os.system("docker rm -f" + " " + str(temp_container))
    print("Build completed. ")