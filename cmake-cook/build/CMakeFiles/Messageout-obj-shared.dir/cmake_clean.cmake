file(REMOVE_RECURSE
  "libMessageout-obj-shared.pdb"
  "libMessageout-obj-shared.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/Messageout-obj-shared.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
