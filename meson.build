# Define the project
project(
  'iw1x-server',
  'cpp',
  version: '0.1.0',
  license: 'GPL-3.0-or-later',
  default_options: [
    'cpp_std=gnu++17', 'warning_level=3', 'buildtype=debug',
    'libdir=lib/i386-linux-gnu', 'prefix=/usr/local'
  ]
)

# Define version info
branch_cmd = '''#!/bin/bash
git rev-parse --abbrev-ref HEAD
'''
res = run_command('sh', '-c', branch_cmd, check: false)
if res.returncode() == 0
  branch = res.stdout().strip()
else
  message('not a git repo')
  branch_cmd = '''#!/bin/bash
folder_name=${PWD##*/}
last_word="${folder_name##*-}"
echo "$last_word"
'''
  res = run_command('sh', '-c', branch_cmd, check: false)
  branch = res.stdout().strip()
endif

message('branch: @0@'.format(branch))

add_project_arguments(
  '-DIW1X_BRANCH="@0@"'.format(branch),
  '-DIWX_VERSION="@0@"'.format(meson.project_version()),
  language: 'cpp'
)

# Retrieve option values from meson_options.txt
enable_unsafe = get_option('enable_unsafe')
compile_sqlite = get_option('compile_sqlite')
compile_curl = get_option('compile_curl')
compile_ssl = get_option('compile_ssl')
airjumps = get_option('airjumps')

# Print configuration messages
message('---------------------')
message('iw1x-server-k ' + meson.project_version() + '-' + branch)
message('Target: ' + get_option('buildtype'))
message('Risky features: ' + enable_unsafe.to_string())
message('SQLite: ' + compile_sqlite.to_string())
message('cURL: ' + compile_curl.to_string())
message('SSL: ' + compile_ssl.to_string())
message('Airjumps: ' + airjumps.to_string())
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

# SQLite support
if compile_sqlite
  sqlite_dep = dependency('sqlite3')
  if not sqlite_dep.found()
    error('SQLite requested but library not found.')
  endif
  add_project_arguments('-DCOMPILE_SQLITE=1', language: 'cpp')
  deps += sqlite_dep
else
  add_project_arguments('-DCOMPILE_SQLITE=0', language: 'cpp')
endif

# cURL support
if compile_curl
  curl_dep = dependency('libcurl')
  if not curl_dep.found()
    error('cURL requested but library not found.')
  endif
  add_project_arguments('-DCOMPILE_CURL=1', language: 'cpp')
  deps += curl_dep
else
  add_project_arguments('-DCOMPILE_CURL=0', language: 'cpp')
endif

# SSL support with OpenSSL
if compile_ssl
  openssl_dep = dependency('openssl')
  if not openssl_dep.found()
    error('OpenSSL requested but library not found.')
  endif
  add_project_arguments('-DCOMPILE_SSL=1', language: 'cpp')
  deps += openssl_dep
else
  add_project_arguments('-DCOMPILE_SSL=0', language: 'cpp')
endif

# Source files
sources = [
  'src/gsc/gsc.cpp',
  'src/gsc/gsc_bots.cpp',
  'src/gsc/gsc_curl.cpp',
  'src/gsc/gsc_entity.cpp',
  'src/gsc/gsc_exec.cpp',
  'src/gsc/gsc_player.cpp',
  'src/gsc/gsc_sqlite.cpp',
  'src/gsc/gsc_utils.cpp',
  'src/gsc/gsc_weapons.cpp',
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
