inc_incdir = include_directories('include')
sources = []
subdir('include')
subdir('src')

deps = [
    pdg_core_dep,
]
if get_option('pdg_build_cnfg_impl_default')
    deps += [ dependency('pugixml') ]
endif


pdg_cnfg = library(
    'pdg-cnfg',
    sources,
    version: meson.project_version(),
    soversion: meson.project_version().split('.')[0],
    include_directories: [inc_incdir],
    dependencies: deps,
    install: true,
)

pdg_cnfg_dep = declare_dependency(
    dependencies: deps,
    include_directories: [inc_incdir],
    link_with: [pdg_cnfg],
)


if get_option('pdg_build_ut')
    ut_sources = []
    subdir('ut')

    pdg_cnfg_ut = executable(
        'pdg-cnfg-ut',
        ut_sources,
        include_directories: [include_directories('ut')],
        dependencies: [pdg_cnfg_dep, catch2_with_main_dep],
        install: true,
    )
endif
