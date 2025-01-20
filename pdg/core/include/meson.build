subdir('pdg/core')


headers = [
    'pdg/core/macros.hpp',
    'pdg/core/assert.hpp',
    'pdg/core/assert_internal.hpp',
    'pdg/core/allocator.hpp',
    'pdg/core/allocator_utils.hpp',
    'pdg/core/dumb_allocator.hpp',
    'pdg/core/linear_allocator.hpp',
    'pdg/core/stack_allocator.hpp',
    'pdg/core/type_info.hpp',
    'pdg/core/ref_counted.hpp',
    'pdg/core/ptr.hpp',
    'pdg/core/string_hash.hpp',
    'pdg/core/fragile_bool.hpp',
    'pdg/core/string_utils.hpp',
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
