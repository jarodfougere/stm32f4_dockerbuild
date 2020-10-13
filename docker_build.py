import os
import subprocess
import sys
import argparse
import shutil

def argfmt(string): # this is literally just some space padding
    return str(" " + str(string) + " ")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="parse command line args for docker build script")
    parser.add_argument("--output", action="store", dest="output_dir", default="bin", help="The output directory name for compiled binaries")
    parser.add_argument("--mode", action="store", dest="build_mode", default="Debug", help="Build mode : [ Debug, Release, MinSizeRel, RelWithDebInfo ]")
    parser.add_argument("--build_dir", action="store", dest="build_dir", default="objects", help="directory name in which to generate the cmake build pipeline")
    args = parser.parse_args()
    build_args = ""
    build_args += argfmt("--build-arg firmware_bin_dir=" + str(args.output_dir))
    build_args += argfmt("--build-arg firmware_build_type=" + str(args.build_mode))

    tag_name = str("armgcc_image")
    tag_repo = str("local_images")
    docker_tag = str(tag_repo) + ":" + str(tag_name)
    docker_build_string = "docker build . -t " + str(docker_tag)
    docker_build_string += build_args
    os.system(docker_build_string)
    
    container = str("temporary_container")
    os.system("docker container stop" + argfmt(container))
    os.system("docker container rm " + argfmt(container))
    os.system("docker create -it --name" + argfmt(container) + argfmt(str(docker_tag)))
    os.system("docker container start " + argfmt(container))
    os.system("docker container ps -a")

    project_build_string = str("sh -c ")
    project_build_string += argfmt("\"")
    project_build_string += argfmt("./build_linux.sh")
    project_build_string += argfmt("-o" + argfmt(str(args.output_dir)))
    project_build_string += argfmt("-m " + argfmt(str(args.build_mode)))
    project_build_string += argfmt("\"")
    os.system("docker exec -it " + argfmt(container) + argfmt(project_build_string))

    cmake_build_dir = str(args.build_dir)
    compile_commands_filestring = "compile_commands.json"
    copy_string = argfmt(str(container) + ":/work/" + str(args.output_dir)) + argfmt("./")
    docker_copy_string = "docker cp" + str(copy_string)
    os.system("docker cp" + argfmt(copy_string))
    os.system("docker cp " + argfmt(str(container) + ":/work/" + str(compile_commands_filestring)) + argfmt("./"))
    os.system("docker container stop " + argfmt(container))
    os.system("docker container rm " + argfmt(container))
    if(os.path.isfile(compile_commands_filestring)):
        if(not os.path.exists(cmake_build_dir)):
            os.makedirs(cmake_build_dir)
        shutil.copy2(compile_commands_filestring, cmake_build_dir)
        os.remove(compile_commands_filestring)
        