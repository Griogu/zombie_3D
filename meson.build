project('projet_perso_sdl', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

executable('projet_perso_sdl',
           'main.c',
           dependencies : [
              dependency('sdl2'),
              meson.get_compiler('c').find_library('m')
            ],
           install : true)
