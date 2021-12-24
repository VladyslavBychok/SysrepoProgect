project('tutorial', 'cpp', default_options : 'cpp_std=c++2a')



subdir('MobileClient')
subdir('Tests')
executable('demo', 'main.cpp', dependencies : sysrepodep, link_with: source_lib, include_directories: inc)