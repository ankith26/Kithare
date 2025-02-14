# This file is a part of the Kithare programming language source code.
# The source code for Kithare programming language is distributed under the MIT
# license.
# Copyright (C) 2021 Kithare Organization
# 
# This is a stub makefile kept for user convenience. Kithare relies on a python 
# script to build kithare. This makefile merely calls the python builder, so 
# python needs to be installed for this makefile to work

ifeq ($(OS),Windows_NT)
	PYTHON = py -3
else
	PYTHON = python3
endif

make:
	${PYTHON} build.py

test: make
	${PYTHON} build.py --make test

clean:
	${PYTHON} build.py --make clean

debug:
	${PYTHON} build.py --make debug

installer:
	${PYTHON} build.py --make installer
