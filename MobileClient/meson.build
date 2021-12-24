source_cpp = files(['sourse/NetConfAgent.cpp','sourse/MobileClient.cpp','sourse/GeneratePath.cpp', 'sourse/NetConfAgent.cpp', 'sourse/MobileClient.cpp','sourse/MobileService.cpp'])
inc = include_directories(['hpp', 'api'])
sysrepodep = dependency('sysrepo-cpp')
libyangdep = dependency('libyang-cpp')
libcredep = dependency('libpcre')

source_lib = shared_library('sourse_lib', sources: source_cpp, include_directories: inc, dependencies : [sysrepodep, libyangdep, libcredep])