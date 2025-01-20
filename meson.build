project('pdg',
    'cpp',
    version : '0.1.0',
    license : 'zlib/libpng',
    meson_version : '>=1.5.1',
    default_options : [
        'warning_level=3',
        'default_library=static',
        'cpp_std=c++20',
    ]
)

cxx = meson.get_compiler('cpp')
if cxx.get_id() == 'msvc'
    add_global_arguments('/utf-8', language: 'cpp')
endif


if get_option('pdg_build_ut')
    catch2_with_main_dep = dependency('catch2-with-main')
endif


subdir('pdg')


#exe = executable('pdg', 'pdg.cpp',
#  install : true)

#test('basic', exe)
