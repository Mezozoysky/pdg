build_cfg = configuration_data()
version_parts = meson.project_version().split('-')
version_str = version_parts[0]
version_tag_str = ''
if version_parts[0] != version_parts[-1]
    foreach part: version_parts
      if part != version_str
          version_tag_str += part
      endif
    endforeach
endif
version_str_parts = version_str.split('.')
version_major = version_str_parts[0]
version_minor = version_str_parts[1]
version_patch = version_str_parts[2]

build_cfg.set('PDG_VERSION_MAJOR', version_major)
build_cfg.set('PDG_VERSION_MINOR', version_minor)
build_cfg.set('PDG_VERSION_PATCH', version_patch)
build_cfg.set_quoted('PDG_VERSION_STR', version_str)
build_cfg.set_quoted('PDG_VERSION_TAG_STR', version_tag_str)

system_name = host_machine.system()
if system_name == 'windows'
    build_cfg.set('PDG_SYSTEM_WINDOWS', true)
    build_cfg.set('PDG_SYSTEM_LINUX', false)
    build_cfg.set('PDG_SYSTEM_ANDROID', false)
elif system_name == 'linux'
    build_cfg.set('PDG_SYSTEM_WINDOWS', false)
    build_cfg.set('PDG_SYSTEM_LINUX', true)
    build_cfg.set('PDG_SYSTEM_ANDROID', false)
elif system_name == 'android'
    build_cfg.set('PDG_SYSTEM_WINDOWS', false)
    build_cfg.set('PDG_SYSTEM_LINUX', false)
    build_cfg.set('PDG_SYSTEM_ANDROID', true)
else
    assert(false, f'Unsupported OS: @system_name@')
endif

cxx = meson.get_compiler('cpp', native: false)

system_bitness = cxx.sizeof('size_t') * 8
if system_bitness == 64
    build_cfg.set('PDG_SYSTEM_64BIT', true)
    build_cfg.set('PDG_SYSTEM_32BIT', false)
elif system_bitness == 32
    build_cfg.set('PDG_SYSTEM_64BIT', false)
    build_cfg.set('PDG_SYSTEM_32BIT', true)
else
    assert(false, f'Unsupported OS bitness: @system_bitness@')
endif


# build_cfg.set('PDG_HAS_LOG', build_flags['pdg_build_log'])
# build_cfg.set('PDG_HAS_CNFG', build_flags['pdg_build_cnfg'])
# build_cfg.set('PDG_HAS_CNFG_IMPL_DEFAULT', build_flags['pdg_build_cnfg_impl_default'])
# build_cfg.set('PDG_HAS_APP', build_flags['pdg_build_app'])
# build_cfg.set('PDG_HAS_RNDR_COMMON', build_flags['pdg_build_rndr_common'])
# build_cfg.set('PDG_HAS_RNDR_COMMON_SDL2', build_flags['pdg_build_rndr_common_sdl2'])
# build_cfg.set('PDG_HAS_RNDR', build_flags['pdg_build_rndr'])
# build_cfg.set('PDG_HAS_RNDR_IMPL_DEFAULT', build_flags['pdg_build_rndr_impl_default'])
# build_cfg.set('PDG_HAS_BASE', build_flags['pdg_build_base'])


sources += configure_file(
    input: 'build_config.hpp.in',
    output: 'build_config.hpp',
    configuration: build_cfg,
    install: true,
    install_dir: get_option('includedir') / 'pdg' / 'core'
)

