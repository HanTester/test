# -*- coding: utf-8 -*-
from setuptools import setup
import sys

# python setup.py py2app
platform_options = {
    "setup_requires": ["py2app"],
    "app": ["test.py"],
    "options": {
        "py2app": {
            "argv_emulation": True,
            "includes": 	[],
        }
    }
}
    
setup(name="hack1",
      version="0.0.1",
      **platform_options)
