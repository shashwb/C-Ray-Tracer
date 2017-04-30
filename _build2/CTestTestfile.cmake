# CMake generated Testfile for 
# Source directory: /Users/sethbalodi/CODE/project3-shashwb
# Build directory: /Users/sethbalodi/CODE/project3-shashwb/_build2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit "unittests")
add_test(test0 "vtray" "/Users/sethbalodi/CODE/project3-shashwb/tests/scene0.json" "output0.png")
add_test(test1 "vtray" "/Users/sethbalodi/CODE/project3-shashwb/tests/scene1.json" "output1.png")
add_test(test2 "vtray" "/Users/sethbalodi/CODE/project3-shashwb/tests/scene2.json" "output2.png")
add_test(test3 "vtray" "/Users/sethbalodi/CODE/project3-shashwb/tests/scene3.json" "output3.png")
set_tests_properties(test3 PROPERTIES  WILL_FAIL "ON")
add_test(test4 "vtray" "/Users/sethbalodi/CODE/project3-shashwb/tests/scene4.json" "output4.png")
set_tests_properties(test4 PROPERTIES  WILL_FAIL "ON")
