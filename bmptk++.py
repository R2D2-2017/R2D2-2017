#!/usr/bin/python3

# Copyright (c) 2017, The R2D2 Team.
import glob

__author__ = 'Chris Smeele'

import os
import shutil
import platform
import argparse

platform_cmakes = {"pc": "",
                   "pi": "",
                   "arduino": "{0}".format("" if platform.system() is not 'Windows' else "-G\"MSYS Makefiles\"")}

root_dir = 'modules'
running_dir = os.getcwd()
if not os.path.isdir(root_dir):
    print('Je zit in de verkeerde dir, ga naar de root van de repo')
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


def create():
    module_name = ask_question('Modulenaam (shortname): ',
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
    print('\nModule ' + module_name + ' is gemaakt in ' + module_dir)


def generate_one(path):
    build_platform = ''
    with open(path + '/.bmptkpp', 'r') as bmptkpp:
        build_platform = bmptkpp.readline().strip()
    os.mkdir(path + '/build')
    os.chdir(path + '/build')
    os.system('cmake .. {0}'.format(platform_cmakes[build_platform]))
    os.chdir(running_dir)


def generate():
    for filename in glob.iglob('modules/**/.bmptkpp', recursive=True):
        if 'template' not in filename:
            generate_one(filename.replace("/.bmptkpp", ""))


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    subcom = parser.add_subparsers()

    create_command = subcom.add_parser('create')
    create_command.set_defaults(func=create)

    generate_command = subcom.add_parser('generate')
    generate_command.set_defaults(func=generate)

    args = parser.parse_args()

    try:
        args.func()
    except AttributeError:
        parser.print_help()
