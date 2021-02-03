Import("env")
import shutil
import os

def copy_firmware(source, target, env):
    firmware_name = "/" + env['PROGNAME'] + ".bin"
    firmware_path = env.subst('$BUILD_DIR') + firmware_name
    if os.path.exists("binaries") == False:
        os.mkdir("binaries")
    output_path = "binaries/" + env['PIOENV']
    if os.path.exists(output_path) == False:
        os.mkdir(output_path)
    shutil.copyfile(firmware_path, output_path + firmware_name)

env.AddPostAction("buildprog", copy_firmware)
