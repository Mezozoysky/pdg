sdl_dep = dependency('sdl2')

inc_incdir = include_directories('include')
sources = []
subdir('include')
subdir('src')

deps = [
    pdg_cnfg_dep,
    pdg_log_dep,
    pdg_core_dep,
    sdl_dep,
]

pdg_base = library(
    'pdg-base',
    sources,
    version: meson.project_version(),
    soversion: meson.project_version().split('.')[0],
    include_directories: [inc_incdir],
    dependencies: deps,
    install: true,
)

pdg_base_dep = declare_dependency(
    dependencies: deps,
    include_directories: [inc_incdir],
    link_with: [pdg_base],
)


if get_option('pdg_build_ut')
    ut_sources = []
    subdir('ut')

    core_ut = executable(
        'pdg-base-ut',
        ut_sources,
        include_directories: [include_directories('ut')],
        dependencies: [pdg_base_dep, catch2_with_main_dep],
        install: true,
    )
endif
