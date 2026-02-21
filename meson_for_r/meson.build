# Define the project
project(
  'iw1x-server',
  'cpp',
  default_options: [
    'cpp_std=gnu++17', 'warning_level=3', 'buildtype=debug',
    'libdir=lib/i386-linux-gnu', 'prefix=/usr/local'
  ]
)

# Retrieve option values from meson_options.txt
enable_unsafe = get_option('enable_unsafe')

# Print configuration messages
message('---------------------')
message('iw1x-server-r (rolling)')
message('Target: ' + get_option('buildtype'))
message('Risky features: ' + enable_unsafe.to_string())
message('---------------------')

# Set base compiler and linker flags for 32-bit compilation
add_project_arguments('-m32', '-fpic', '-fvisibility=hidden', language: 'cpp')
add_project_link_arguments('-m32', language: 'cpp')

# Handle debug build flags and definitions
if get_option('buildtype') == 'debug'
  #add_project_arguments('-g', '-ggdb', '-DDEBUG', language: 'cpp')
  add_project_arguments('-g3', '-DDEBUG', language: 'cpp')
  #add_project_link_arguments('-g', language: 'cpp')
else
# Is it safe?
  add_project_arguments('-Wno-strict-aliasing', language: 'cpp')
  add_project_arguments('-Wno-missing-field-initializers', language: 'cpp')
  add_project_arguments('-Wno-unused-parameter', language: 'cpp')
  add_project_arguments('-Wno-maybe-uninitialized', language: 'cpp')
endif

# Handle ENABLE_UNSAFE definition
if enable_unsafe
  add_project_arguments('-DENABLE_UNSAFE=1', language: 'cpp')
else
  add_project_arguments('-DENABLE_UNSAFE=0', language: 'cpp')
endif

# Dependencies
deps = [
  dependency('dl'),
  dependency('threads')
]

# Source files
sources = [
  'src/gsc.cpp',
  'src/gsc_bots.cpp',
  'src/gsc_curl.cpp',
  'src/gsc_entity.cpp',
  'src/gsc_exec.cpp',
  'src/gsc_player.cpp',
  'src/gsc_sqlite.cpp',
  'src/gsc_utils.cpp',
  'src/gsc_weapons.cpp',
  'src/jump.cpp',
  'src/hook.cpp',
  'src/iw1x.cpp'
]

i_linkargs = []
if meson.get_compiler('cpp').version().version_compare('<9.0')
  i_linkargs += '-lstdc++fs'
endif

# The shared library
iw1x = shared_library('iw1x',
  sources,
  dependencies: [deps],
  link_args: i_linkargs,
  name_prefix: '',
  cpp_pch: 'src/pch.h',
  install: true,
)
