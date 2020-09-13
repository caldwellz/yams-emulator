# Version info
cppcomp = meson.get_compiler('cpp')
version_data = configuration_data()
version_data.set('version', meson.project_version())
version_data.set('vcs_tag_placeholder', '@VCS_TAG@')
version_data.set('compiler', cppcomp.get_id())
version_data.set('compiler_version', cppcomp.version())
versionpre = configure_file(configuration : version_data
  , input : 'version.c.in.pre'
  , output : 'version.c.in')

git = find_program('git', required : false)
versionfile = vcs_tag(command : ['git', 'rev-parse', '--short', 'HEAD'], fallback : get_option('buildtype').to_upper()
  , input : versionpre
  , output : 'version.c')
# To get commit number instead of ID: ['git', 'rev-list', '--count', 'HEAD']


# Find dependencies
# - SDL2
dep_sdl = dependency('sdl2', required : false)
if not dep_sdl.found()
    dep_sdl = cppcomp.find_library('SDL2', has_headers : ['SDL2/SDL.h'])
endif

# - SDL2_main
dep_sdlmain = dependency('sdl2main', required : false)
if not dep_sdlmain.found()
    dep_sdlmain = cppcomp.find_library('SDL2main')
endif


# List dependencies and sources
emu_deps = [dep_sdl, dep_sdlmain]
emu_srcs = files(['main.c', 'cpu_bus.c', 'cpu_special.c', 'usage.c'])
subdir('musashi')


# Create the executable target
emu_exe = executable(meson.project_name(), [emu_srcs, versionfile[0]], dependencies : emu_deps, install : true)
declare_dependency(sources : versionfile, link_with : emu_exe)
