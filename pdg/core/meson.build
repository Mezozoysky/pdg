fmt_dep = dependency('fmt')
xxhash_dep = dependency('libxxhash')

inc_incdir = include_directories('include')
sources = []
subdir('include')
subdir('src')

pdg_core = library(
    'pdg-core',
    sources,
    version: '0.1.0',
    soversion: '0',
    include_directories: [inc_incdir],
    dependencies: [fmt_dep, xxhash_dep],
    install: true,
)

pdg_core_dep = declare_dependency(
    dependencies: [fmt_dep, xxhash_dep],
    include_directories: [inc_incdir],
    link_with: [pdg_core],
)


if get_option('pdg_build_ut')
    ut_sources = []
    subdir('ut')

    core_ut = executable(
        'pdg-core-ut',
        ut_sources,
        include_directories: [include_directories('ut')],
        dependencies: [pdg_core_dep, catch2_with_main_dep],
        install: true,
    )
endif
