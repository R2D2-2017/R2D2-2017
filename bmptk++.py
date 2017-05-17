#!/usr/bin/python3

# Copyright (c) 2017, The R2D2 Team.

__author__ = 'Chris Smeele'

import os
import sys
import shutil
import re

if 'create' not in sys.argv:
    print('usage: ' + sys.argv[0] + ' create')
    exit(1)

root_dir = 'modules'

if not os.path.isdir(root_dir):
    print('Je zit in de verkeerde dir, ga naar de root van de repo')
    exit(1)

module_name = input('Modulenaam (shortname): ')
if not len(module_name): exit(0)

module_name = module_name.upper()

module_dir = root_dir + '/' + module_name

if os.path.isdir(module_dir):
    print('Modulenaam is al in gebruik')
    exit(1)

platform = ''
while platform not in ('pc', 'pi', 'duino'):
    platform = input('Platform: [pc|pi|duino] ')

if not len(platform): exit(0)

template_name = 'template-' + platform

shutil.copytree(root_dir + '/' + template_name, module_dir)

print('Created module at ' + module_dir)

os.chdir(module_dir)
os.remove('CMakeLists.txt')

# If only we had sed on Windows...

with open('../' + template_name + '/CMakeLists.txt', 'r') as src:
    with open('CMakeLists.txt', 'w') as dest:
        for line in src:
            print(line.replace(template_name, module_name.lower()), file=dest, end='')

os.mkdir('build')
os.chdir('build')

# Fixme: Pass toolchain flags for arduino / kvasir-toolchain.
os.system('cmake ..')

print('\nModule ' + module_name + ' is gemaakt in ' + module_dir)
