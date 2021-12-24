inc_test = include_directories(['./mock'])

dependency_test = [
    dependency('gtest', main : true),
    dependency('gmock'),
]

exe_test = executable('demo_test','./sourse/MobileClientTests.cpp', 
include_directories: [inc, inc_test], 
dependencies:[sysrepodep, libcredep, libcredep, dependency_test], 
link_with: source_lib)


test('demo_test', exe_test)