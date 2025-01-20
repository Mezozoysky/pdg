inc_incdir = include_directories('include')
sources = []
subdir('include')
subdir('src')

deps = [
    pdg_core_dep,
]

pdg_log = library(
    'pdg-log',
    sources,
    version: meson.project_version(),
    soversion: meson.project_version().split('.')[0],
    include_directories: [inc_incdir],
    dependencies: deps,
    install: true,
)

pdg_log_dep = declare_dependency(
    dependencies: deps,
    include_directories: [inc_incdir],
    link_with: [pdg_log],
)


if get_option('pdg_build_ut')
    ut_sources = []
    subdir('ut')

    core_ut = executable(
        'pdg-log-ut',
        ut_sources,
        include_directories: [include_directories('ut')],
        dependencies: [pdg_log_dep, catch2_with_main_dep],
        install: true,
    )
endif
