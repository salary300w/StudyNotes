file(REMOVE_RECURSE
  "libMessageout-obj-static.pdb"
  "libMessageout-obj-static.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/Messageout-obj-static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
