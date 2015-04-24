
#main 
add_executable(gnome-drumroll main.cpp)

#require pkg-config support
find_package(PkgConfig REQUIRED)

#required pkg-config libs
pkg_check_modules(USB REQUIRED libusb-1.0)
pkg_check_modules(ALSA REQUIRED alsa)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)


include_directories(${USB_INCLUDE_DIRS} ${ALSA_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})

target_link_libraries(gnome-drumroll ${USB_LIBRARIES} ${ALSA_LIBRARIES} ${GTKMM_LIBRARIES})

#add custom lib flags
add_definitions(-std=c++11 -O3)



