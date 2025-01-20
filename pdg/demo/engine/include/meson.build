headers = [
    'pdg/demo/engine.hpp',
    'pdg/demo/game.hpp',
    'pdg/demo/player.hpp',
]

sources += files(headers)

include_subdir = ''
foreach header: headers
    file_path = header.split('/')
    header_subdir = ''

    foreach part: file_path
        if part != file_path[-1]
            header_subdir = header_subdir / part
        endif
    endforeach

    install_headers(header, subdir: join_paths(include_subdir, header_subdir))
endforeach
