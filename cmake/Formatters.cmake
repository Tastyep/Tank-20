function(add_format_target source_files)
  add_custom_target(clangformat COMMAND clang-format -i --verbose ${source_files})
endfunction()
