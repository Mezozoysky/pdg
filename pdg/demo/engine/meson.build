inc_incdir = include_directories('include')
sources = []
subdir('include')
subdir('src')

pdg_demo_engine = library(
    'pdg-demo-engine',
    sources,
    version: '0.1.0',
    soversion: '0',
    include_directories: [inc_incdir],
    dependencies: [pdg_base_dep],
    install: true,
)

pdg_demo_engine_dep = declare_dependency(
    dependencies: [pdg_base_dep],
    include_directories: [inc_incdir],
    link_with: [pdg_demo_engine],
)


if get_option('pdg_build_ut')
    ut_sources = []
    subdir('ut')

    core_ut = executable(
        'pdg-demo-engine-ut',
        ut_sources,
        include_directories: [include_directories('ut')],
        dependencies: [pdg_core_dep, catch2_with_main_dep],
        install: true,
    )
endif
