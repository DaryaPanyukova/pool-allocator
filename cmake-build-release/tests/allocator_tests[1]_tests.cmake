add_test( AllocatorTestSuite.Test1 [==[D:/ITMOlabs/basics_c++/labwork-9-DaryaPanyukova/cmake-build-release/tests/allocator_tests.exe]==] [==[--gtest_filter=AllocatorTestSuite.Test1]==] --gtest_also_run_disabled_tests)
set_tests_properties( AllocatorTestSuite.Test1 PROPERTIES WORKING_DIRECTORY [==[D:/ITMOlabs/basics_c++/labwork-9-DaryaPanyukova/cmake-build-release/tests]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( AllocatorTestSuite.TestInt [==[D:/ITMOlabs/basics_c++/labwork-9-DaryaPanyukova/cmake-build-release/tests/allocator_tests.exe]==] [==[--gtest_filter=AllocatorTestSuite.TestInt]==] --gtest_also_run_disabled_tests)
set_tests_properties( AllocatorTestSuite.TestInt PROPERTIES WORKING_DIRECTORY [==[D:/ITMOlabs/basics_c++/labwork-9-DaryaPanyukova/cmake-build-release/tests]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( AllocatorTestSuite.TestDouble [==[D:/ITMOlabs/basics_c++/labwork-9-DaryaPanyukova/cmake-build-release/tests/allocator_tests.exe]==] [==[--gtest_filter=AllocatorTestSuite.TestDouble]==] --gtest_also_run_disabled_tests)
set_tests_properties( AllocatorTestSuite.TestDouble PROPERTIES WORKING_DIRECTORY [==[D:/ITMOlabs/basics_c++/labwork-9-DaryaPanyukova/cmake-build-release/tests]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( allocator_tests_TESTS AllocatorTestSuite.Test1 AllocatorTestSuite.TestInt AllocatorTestSuite.TestDouble)