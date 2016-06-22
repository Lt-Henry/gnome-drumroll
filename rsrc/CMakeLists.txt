
add_custom_command(OUTPUT gresources.h COMMAND glib-compile-resources --generate-header --target=${CMAKE_BINARY_DIR}/src/gresources.h gnome-drumroll.xml WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/rsrc)
add_custom_command(OUTPUT gresources.c COMMAND glib-compile-resources --generate-source --target=${CMAKE_BINARY_DIR}/src/gresources.c gnome-drumroll.xml WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/rsrc)

add_custom_target(resources ALL DEPENDS gresources.h gresources.c)

install(FILES ${CMAKE_SOURCE_DIR}/rsrc/gnome-drumroll.svg DESTINATION share/icons/hicolor/scalable/apps/)
install(FILES ${CMAKE_SOURCE_DIR}/rsrc/gnome-drumroll.desktop DESTINATION share/applications/)
install(FILES ${CMAKE_SOURCE_DIR}/rsrc/10-gnome-drumroll.rules DESTINATION /lib/udeb/rules.d/)
