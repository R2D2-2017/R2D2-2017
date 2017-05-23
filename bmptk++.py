#!/usr/bin/python3

# Copyright (c) 2017, The R2D2 Team.
import glob
import os
import shutil
import platform
import argparse
import re
import sys

__author__ = 'Chris Smeele & Robert Bezem'

header = ''' _                     _   _               
| |__  _ __ ___  _ __ | |_| | __ _     _   
| '_ \| '_ ` _ \| '_ \| __| |/ /| |_ _| |_ 
| |_) | | | | | | |_) | |_|   <_   _|_   _|
|_.__/|_| |_| |_| .__/ \__|_|\_\|_|   |_|  
                |_|                        
'''

platform_cmakes = {"pc": "",
                   "pi": "",
                   "arduino": "{0}".format("" if platform.system() is not 'Windows' else "-G\"MSYS Makefiles\"")}

root_dir = 'modules'
running_dir = os.getcwd()
if not os.path.isdir(root_dir):
    print('Please go to the root directory of the repository before running this script.')
    exit(1)


def ask_question(question, validator, error):
    inp = ""
    while True:
        inp = input(question)
        if validator(inp):
            break
        else:
            print(error)
    return inp


def create(args):
    module_name = ask_question('Module name (shortname): ',
                               lambda x: len(x) and not os.path.isdir(root_dir + '/' + x.upper()),
                               "Something is wrong with this name").upper()
    module_name = module_name.upper()
    module_dir = root_dir + '/' + module_name

    platform_question_string = 'Platform: [' + "|".join(platform_cmakes) + "] "
    build_platform = ask_question(platform_question_string, lambda x: x in platform_cmakes,
                                  "This is not a correct platform")

    template_name = 'template-' + build_platform

    shutil.copytree(root_dir + '/' + template_name, module_dir)

    print('Created module at ' + module_dir)

    os.chdir(module_dir)
    os.remove('CMakeLists.txt')

    # If only we had sed on Windows...

    with open('../' + template_name + '/CMakeLists.txt', 'r') as src:
        with open('CMakeLists.txt', 'w') as dest:
            for line in src:
                print(line.replace(template_name, module_name.lower()), file=dest, end='')

    os.chdir(running_dir)
    generate_one(module_dir)
    print('\nModule ' + module_name + ' was created in ' + module_dir)


def generate_one(path, override_generator=None):
    build_platform = ''
    with open(path + '/.bmptkpp', 'r') as bmptkpp:
        build_platform = bmptkpp.readline().strip()

    # Create build directory if it doesn't exist yet.
    build_dir = path + '/build'
    if not os.path.isdir(build_dir):
        os.mkdir(build_dir)
    os.chdir(build_dir)
    cmake_params = platform_cmakes[build_platform]
    if override_generator:
        if '-G' not in cmake_params:
            cmake_params += " -G\"{0}\"".format(override_generator)

    os.system('cmake .. {0}'.format(cmake_params))
    os.chdir(running_dir)


def generate(args):
    for filename in glob.iglob('modules/*/.bmptkpp'):
        if 'template' not in filename:
            print('Generating build directory for {0}'.format(
                re.sub(r"modules[/\\](.*)[/\\].bmptkpp", r"\1", filename)))
            generate_one(re.sub(r"[\\/].bmptkpp", "", filename), args.override_generator)


def console(parser, subcommands):
    print(header)
    print("Running in command mode type command to use")

    exit_command = subcommands.add_parser('exit', help="Exit this program", aliases=['e', 'q', 'quit'])
    exit_command.set_defaults(func=lambda x: exit())

    help_command = subcommands.add_parser('help', help="Show this help")
    help_command.set_defaults(func=lambda x: parser.print_help())

    parser.usage = argparse.SUPPRESS

    parser.print_help()

    while True:
        command = input("Command: ")
        args = None
        try:
            args = parser.parse_args(command.split())
        except SystemExit:
            pass
        if hasattr(args, 'func'):
            args.func(args)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(add_help=False)
    subcom = parser.add_subparsers(title="Commands")

    create_command = subcom.add_parser('create', help="Create a new project")
    create_command.set_defaults(func=create)

    generate_command = subcom.add_parser('generate', help="Generate all the build files")
    generate_command.set_defaults(func=generate)
    generate_command.add_argument('--override-generator',
                                  help="Overwrite the default cmake generator used, does not work for some targets")

    if len(sys.argv) > 1:
        parser.formatter_class = argparse.RawDescriptionHelpFormatter
        parser.description = header
        parser.add_argument(
            "-h", "--help",
            action='help', default=argparse.SUPPRESS,
            help='show this help message and exit')

    args = parser.parse_args()

    try:
        if hasattr(args, 'func'):
            args.func(args)
        else:
            console(parser, subcom)
    except KeyboardInterrupt:
        print()
