import os
import subprocess
import sys
import argparse
import shutil
import platform
import fileinput
import pathlib
import inspect


def pathToUnix(p):
    return pathlib.PurePosixPath(p)
def pathToWindows(p):
    return pathlib.PureWindowsPath(p)

def argfmt(string): # this is literally just some space padding
    return str(" " + str(string) + " ")

if __name__ == "__main__":
    if sys.version_info[0] < 3:
        info = inspect.getframeinfo()
        raise Exception("%s must be executed using Python 3" % (info.filename))
    
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

    myPathWithDrive = os.path.dirname(os.path.realpath(__file__))
    pathObject = pathlib.Path(myPathWithDrive)
    myDrive = pathObject.drive
    myPathWithoutDrive = pathObject.relative_to(pathObject.drive)
    unixPath = pathObject.relative_to(pathObject.drive).as_posix()
    project_build_string = str("sh -c ")
    project_build_string += argfmt("\"")
    project_build_string += argfmt("./build_linux.sh")
    project_build_string += argfmt("-o " + argfmt(str(args.output_dir)))
    project_build_string += argfmt("-m " + argfmt(str(args.build_mode)))
    project_build_string += argfmt("-b " + argfmt(str(args.build_dir)))
    project_build_string += argfmt("-p " + unixPath)
    project_build_string += argfmt("\"")
    os.system("docker exec -it " + argfmt(container) + argfmt(project_build_string))
    os.system("docker cp " + container + ":" + unixPath + "/" + args.output_dir + " " + myPathWithDrive)
    os.system("docker cp " + container + ":" + unixPath + "/" + args.build_dir + " " + myPathWithDrive)
    os.system("docker container stop " + container)
    os.system("docker container rm " + container)

    # fix compile commands json in a platform-portable way so that vscode intellisense works properly
    compile_commands_filepath = str(os.path.join(str(args.build_dir), str("compile_commands.json")))
    path = pathlib.Path(compile_commands_filepath)
    text = path.read_text()
    newtext = text.replace(unixPath, myDrive + unixPath)
    path.write_text(newtext)