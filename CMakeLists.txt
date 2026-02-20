project(CFS_SCH_LAB C)

# These references are specifically needed for the table build so that
# app-specific MsgIDs can be conditionally included in the schedule table.
foreach(EXT_APP to_lab ci_lab sample_app apqs_app hs fm ds sc lc cf)
  list(FIND TGTSYS_${SYSVAR}_APPS ${EXT_APP} HAVE_APP)
  if (HAVE_APP GREATER_EQUAL 0)
    include_directories($<TARGET_PROPERTY:${EXT_APP},INTERFACE_INCLUDE_DIRECTORIES>)
    string(TOUPPER "HAVE_${EXT_APP}" APP_MACRO)
    add_definitions(-D${APP_MACRO})
  endif()
endforeach()

# Create the app module
add_cfe_app(sch_lab fsw/src/sch_lab_app.c)
add_cfe_tables(sch_lab fsw/tables/sch_lab_table.c)

target_include_directories(sch_lab PUBLIC fsw/inc)
