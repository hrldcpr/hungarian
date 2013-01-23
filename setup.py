def configuration(parent_package='', top_path=None):
    from numpy.distutils.misc_util import Configuration
    config = Configuration('', parent_package,top_path)
    config.add_extension('hungarian', ['asp.cpp', 'asp.h', 'hungarian.cpp'])
    return config

if __name__ == "__main__":
    from numpy.distutils.core import setup
    setup(configuration=configuration,
          name='hungarian',
          version='0.2.3',
          url='http://github.com/hrldcpr/hungarian',
          description='algorithm for the linear assignment problem',
          long_description=
"""This module is just a simple wrapper for a C++ implementation of Knuth's
Hungarian algorithm, a.k.a. Munkres' algorithm, for the linear assignment
problem.""",
          author='Dominic Battre',
          maintainer='Harold Cooper',
          maintainer_email='hrldcpr@gmail.com'
          )
