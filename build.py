import os
import subprocess
import sys
import argparse
import shutil
import platform
import fileinput
import pathlib
import inspect
import shutil


def pathToUnix(p):
    return pathlib.PurePosixPath(p)
def pathToWindows(p):
    return pathlib.PureWindowsPath(p)

def argfmt(string): # this is literally just some space padding
    return str(" " + str(string) + " ")

if __name__ == "__main__":
    nameOfThisFile = None
    if sys.version_info[0] < 3:
        info = inspect.getframeinfo()
        nameOfThisFile = info.filename
        raise Exception("%s must be executed using Python 3" % (nameOfThisFile))

    if platform.system() != "Windows" and platform.system() != "Linux":
        print(nameOfThisFile + " only supports builds from Windows or Linux environments")
        exit(1)
    
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

    pathObject = pathlib.Path(os.path.dirname(os.path.realpath(__file__)))
    myPathAbsMinusAnchor = pathObject.relative_to(pathObject.anchor)
    unixPath = '/' + myPathAbsMinusAnchor.as_posix()
    myFullPath = pathObject.anchor + str(myPathAbsMinusAnchor)

    project_build_string = str("sh -c ")
    project_build_string += argfmt("\"")
    project_build_string += argfmt("./Scripts/build_linux.sh")
    project_build_string += argfmt("-o " + argfmt(str(args.output_dir)))
    project_build_string += argfmt("-m " + argfmt(str(args.build_mode)))
    project_build_string += argfmt("-b " + argfmt(str(args.build_dir)))
    project_build_string += argfmt("-p " + unixPath)
    project_build_string += argfmt("-d") # indicate docker build to build_linux.sh
    project_build_string += argfmt("\"")
    os.system("docker exec -it " + argfmt(container) + argfmt(project_build_string))
    os.system("docker cp " + container + ":" + unixPath + "/" + args.output_dir + " " + myFullPath)
    os.system("docker cp " + container + ":" + unixPath + "/" + args.build_dir + " " + myFullPath)
    os.system("docker container stop " + container)
    os.system("docker container rm " + container)

    # fix compile commands json in a platform-portable way so that vscode intellisense works properly
    compile_commands_filename = str(os.path.join(str(args.build_dir), str("compile_commands.json")))
    path = pathlib.Path(compile_commands_filename)
    if path is not None:
        text = path.read_text()
        newCompileCommandsJson = text.replace(unixPath, myFullPath)
        compiler_commandline_in_text = None
        for line in text.split('\n'):
            if "command" in line:
                # we can get the compile command issued in the docker image
                # from the first instance of "command key" in the json file
                compiler_commandline_in_text = line 
                break
        native_system_compiler_path = None
        if compiler_commandline_in_text is not None:

            # strip whitespace
            compile_commands_compiler_path = compiler_commandline_in_text.lstrip()
            compile_commands_compiler_path = compile_commands_compiler_path.rstrip()

            # get the value from the key
            compile_commands_compiler_path = compile_commands_compiler_path.split(' ')[1] 
             
            # this is a hacky fix for the quotations but bash and windows
            # (cmd vs powershell vs WSL ) parse quotations differently
            compile_commands_compiler_path = compile_commands_compiler_path.replace("\"", "")
            dockerCompilerPathObject = pathlib.Path(compile_commands_compiler_path)

            # the executable name will be the same
            compiler_name = dockerCompilerPathObject.name
            native_system_compiler_path = str(pathlib.Path(shutil.which(compiler_name)))
        else:
            print("Error parsing the compile field from the file " + str(compile_commands_filename))

        if native_system_compiler_path is not None:
            newCompileCommandsJson = newCompileCommandsJson.replace(compile_commands_compiler_path, native_system_compiler_path)
        else:
            print("Error determining the native compiler path on the host system. Could not update " + str(compile_commands_filename))

        path.write_text(newCompileCommandsJson)


        