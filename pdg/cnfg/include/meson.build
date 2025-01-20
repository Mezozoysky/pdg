headers = [
    'pdg/cnfg/config.hpp',
    'pdg/cnfg/config_impl.hpp',
]

if get_option('pdg_build_cnfg_impl_default')
    headers += [
        'pdg/cnfg/impl/default_config_impl.hpp',
        'pdg/cnfg/impl/config_entry.hpp',
        'pdg/cnfg/impl/parsing.hpp',
    ]
endif

sources += files(headers)

include_subdir = ''
foreach header: headers
    file_path = header.split('/')
    header_subdir = ''

    foreach part : file_path
        if part != file_path[-1]
            header_subdir = header_subdir / part
        endif
    endforeach

    install_headers(header, subdir: join_paths(include_subdir, header_subdir))
endforeach

