#include <inttypes.h>
#include <stdio.h>

#include "omp.h"
#include "ompt.h"

/******************************************************************************\
 * Definitions for tool configuration
\******************************************************************************/

#include "OMPT_helpers.hpp" 
//#define DEBUG
#include "callbacks.hpp" 


int ompt_initialize(ompt_function_lookup_t lookup,
                    ompt_data_t * tool_data)
{

  // OMPT boilerplate 
  ompt_set_callback = (ompt_set_callback_t) lookup("ompt_set_callback");
  ompt_get_callback = (ompt_get_callback_t) lookup("ompt_get_callback");
  ompt_get_state = (ompt_get_state_t) lookup("ompt_get_state");
  ompt_get_task_info = (ompt_get_task_info_t) lookup("ompt_get_task_info");
  ompt_get_thread_data = (ompt_get_thread_data_t) lookup("ompt_get_thread_data");
  ompt_get_parallel_info = (ompt_get_parallel_info_t) lookup("ompt_get_parallel_info");
  ompt_get_unique_id = (ompt_get_unique_id_t) lookup("ompt_get_unique_id");
  ompt_get_num_procs = (ompt_get_num_procs_t) lookup("ompt_get_num_procs");
  ompt_get_num_places = (ompt_get_num_places_t) lookup("ompt_get_num_places");
  ompt_get_place_proc_ids = (ompt_get_place_proc_ids_t) lookup("ompt_get_place_proc_ids");
  ompt_get_place_num = (ompt_get_place_num_t) lookup("ompt_get_place_num");
  ompt_get_partition_place_nums = (ompt_get_partition_place_nums_t) lookup("ompt_get_partition_place_nums");
  ompt_get_proc_id = (ompt_get_proc_id_t) lookup("ompt_get_proc_id");
  ompt_enumerate_states = (ompt_enumerate_states_t) lookup("ompt_enumerate_states");
  ompt_enumerate_mutex_impls = (ompt_enumerate_mutex_impls_t) lookup("ompt_enumerate_mutex_impls");

  ompt_get_unique_id = (ompt_get_unique_id_t) lookup("ompt_get_unique_id"); 

  // Determine which OMPT callbacks the tool will invoke 
  register_callback(ompt_callback_task_create);
  register_callback(ompt_callback_implicit_task);
  register_callback(ompt_callback_task_dependence);
  register_callback(ompt_callback_task_dependences);
  register_callback(ompt_callback_task_schedule);
  register_callback(ompt_callback_sync_region);
  register_callback_t(ompt_callback_sync_region_wait, ompt_callback_sync_region_t);
  register_callback(ompt_callback_parallel_begin);
  register_callback(ompt_callback_parallel_end);

  register_callback(ompt_callback_thread_begin);
  register_callback(ompt_callback_thread_end);

#ifdef DEBUG
  printf("\n\n\n");
  printf("=================================================================\n");
  printf("====================== OMPT_INITIALIZE ==========================\n");
  printf("=================================================================\n");
  printf("\n\n\n");
#endif 

  // Returning 1 instead of 0 lets the OpenMP runtime know to load the tool 
  return 1;
}


void ompt_finalize(ompt_data_t *tool_data)
{
#ifdef DEBUG
  printf("0: ompt_event_runtime_shutdown\n"); 
#endif
}







/* "A tool indicates its interest in using the OMPT interface by providing a 
 * non-NULL pointer to an ompt_fns_t structure to an OpenMP implementation as a 
 * return value from ompt_start_tool." (OMP TR4 4.2.1)
 *
 * NOTE: This is a little confusing, is something of type 
 * "ompt_start_tool_result_t" equivalent to something of type 
 * "ompt_fns_t structure"? 
 */
ompt_start_tool_result_t* ompt_start_tool(unsigned int omp_version,
                                          const char *runtime_version)
{
  static ompt_start_tool_result_t ompt_start_tool_result = {&ompt_initialize,
                                                            &ompt_finalize, 
                                                            0};
  return &ompt_start_tool_result;
}
