if(NOT DEFINED deps_various OR deps_various)
############################ Various ############################
file(GLOB_RECURSE various_inc ${CMAKE_CURRENT_SOURCE_DIR}/various/include/various/*.h)
file(GLOB_RECURSE various_src ${CMAKE_CURRENT_SOURCE_DIR}/various/src/*.*)
add_library(various STATIC ${various_inc} ${various_src})
target_include_directories(various PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/various/include)
set_target_properties(various PROPERTIES FOLDER "Deps/src/various")

target_compile_definitions(various PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(various PRIVATE /w)
else()
	target_compile_options(various PRIVATE -w)
endif()
endif()

if(NOT DEFINED deps_glad OR deps_glad)
############################ GLAD ############################
add_library(glad STATIC 
	${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
	${CMAKE_CURRENT_SOURCE_DIR}/glad/include/KHR/khrplatform.h
	${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
set_target_properties(glad PROPERTIES FOLDER "Deps/src/glad")

target_compile_definitions(glad PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(glad PRIVATE /W2 /WX)
else()
	target_compile_options(glad PRIVATE -Werror)
endif()
endif()

if(MSVC AND (NOT DEFINED deps_pthreads OR deps_pthreads))
############################ pthreads ############################
file(GLOB pthreads_inc ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/*.h)
file(GLOB pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/*.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/ptw32_OLL_lock.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/attr.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/barrier.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/cancel.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/condvar.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/exit.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/misc.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/mutex.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/nonportable.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/private.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/pthread.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/rwlock.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/sched.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/pthread.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/semaphore.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/spin.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/sync.c)
list(REMOVE_ITEM pthreads_src ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/tsd.c)

set(pthreads_src_2 
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/attr.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/barrier.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/cancel.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/condvar.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/exit.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/misc.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/mutex.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/nonportable.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/private.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/pthread.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/rwlock.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/sched.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/semaphore.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/spin.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/sync.c
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads/tsd.c
)
#SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads PREFIX pthreads FILES ${darknet_inc})

add_library(pthreads STATIC ${pthreads_inc} ${pthreads_src})
target_include_directories(pthreads PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pthreads/pthreads)
if(MSVC)
target_compile_definitions(pthreads PUBLIC PTW32_STATIC_LIB HAVE_STRUCT_TIMESPEC)
endif()
set_target_properties(pthreads PROPERTIES FOLDER "Deps/src/pthreads")

target_compile_definitions(pthreads PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(pthreads PRIVATE /W2 /WX)
else()
	target_compile_options(pthreads PRIVATE -Werror)
endif()
endif()
