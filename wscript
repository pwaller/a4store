#! /usr/bin/env python

a4_version = "0.1.0"

from waflib.TaskGen import feature, after
from waflib.Task import Task
from waflib.Tools import c_preproc

def options(opt):
    opt.load('compiler_c compiler_cxx python')

def configure(conf):
    conf.load('compiler_c compiler_cxx python')
    
    conf.env.append_value("CXXFLAGS", ["-std=c++0x", "-ggdb"])
    conf.env.append_value("RPATH", [conf.env.LIBDIR])
    conf.env.A4_VERSION = a4_version
    
    conf.check_cfg(path="root-config", package="", uselib_store="CERN_ROOT_SYSTEM",
                   args='--libs --cflags', mandatory=False)

    conf.define("A4STORE_STANDALONE", 1)

    conf.to_log("Final environment:")
    conf.to_log(conf.env)

def build(bld):

    from os.path import join as pjoin

    bld(features="cxx cxxshlib", 
        source=bld.path.ant_glob("src/**.cpp"),
        includes="src/",
        target="a4store")
    
    bld(features="cxx cxxprogram",
        source="src/apps/a4store_standalone_test.cpp",
        includes="src/",
        target="a4store_standalone_test",
        use=["a4store", "CERN_ROOT_SYSTEM"])
    
    headers = bld.path.ant_glob("src/a4/**.h")
    
    cwd = bld.path.find_or_declare("src/a4").get_src()
    bld.install_files('${PREFIX}/include/a4', headers, cwd=cwd,
        relative_trick=True)   
    
    bld(rule=write_this_a4store, target="this_a4store.sh", install_path=bld.env.BINDIR)
    bld(rule=write_pkgcfg, target="a4store.pc", always=True, 
        install_path=pjoin(bld.env.LIBDIR, "pkgconfig"))

def write_pkgcfg(task):
    def libstr(use):
        s = []
        if task.env["LIBPATH_"+use]:
            s.extend("-L%s"%l for l in task.env["LIBPATH_"+use])
            s.extend("-l%s"%l for l in task.env["LIB_"+use])
        return " ".join(s)

    def cppstr(use):
        s = []
        s.extend(task.env.get_flat("CPPFLAGS_"+use).split())
        s.extend("-I"+i for i in task.env.get_flat("INCLUDES_"+use).split())
        return " ".join(s)

    lines = []
    from textwrap import dedent
    lines.append(dedent("""
    prefix=%(PREFIX)s
    exec_prefix=${prefix}
    includedir=${prefix}/include
    libdir=%(LIBDIR)s

    Name: a4store
    Description: An Analysis Tool for High-Energy Physics
    Version: %(A4_VERSION)s
    URL: https://github.com/a4/a4store/
    Cflags: -std=c++0x -I%(PREFIX)s/include -DHAVE_CERN_ROOT_SYSTEM -DA4STORE_STANDALONE
    Libs: -L${libdir} -la4store
    """ % dict(
        PREFIX=task.env.PREFIX,
        LIBDIR=task.env.LIBDIR,
        CXX=task.env.CXX[0],
        PROTOC=task.env.PROTOC,
        A4_VERSION=task.env.A4_VERSION,
    )))

    task.outputs[0].write("\n".join(lines))
    return 0

def write_this_a4store(task):
    import os
    lines = []

    from textwrap import dedent
    lines.append(dedent("""
    export PKG_CONFIG_PATH=${PKG_CONFIG_PATH:+$PKG_CONFIG_PATH:}%(LIBDIR)s/pkgconfig
    
    # Get compiler flags with $(pkg-config a4store --libs --cflags)
    """ % dict(LIBDIR=task.env.LIBDIR)))

    task.outputs[0].write("\n".join(lines))
    return 0
