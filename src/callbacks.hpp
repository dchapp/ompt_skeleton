
// For getting thread ID in callbacks 
typedef struct my_ompt_data{
  uint64_t own;
  ompt_data_t client;
} my_ompt_data_t;

uint64_t get_own_data(ompt_data_t* data)
{
  return ((my_ompt_data_t*)data->ptr)->own;
}

uint64_t alloc_and_init_own_data(ompt_data_t* data, uint64_t init_data)
{
  data->ptr = malloc(sizeof(my_ompt_data_t));
  ((my_ompt_data_t*)data->ptr)->own = init_data;
  return init_data; 
}

static uint64_t my_next_id() {
  static uint64_t ID=0;
  uint64_t ret = __sync_fetch_and_add(&ID, 1); 
  return ret; 
}


static void
on_ompt_callback_thread_begin(
  ompt_thread_type_t thread_type,
  ompt_data_t *thread_data)
{
#ifdef DEBUG
  printf("Entering thread_begin\n");
#endif
#ifdef DEBUG
  printf("Exiting thread_begin\n");
#endif
}

static void
on_ompt_callback_thread_end(
  ompt_data_t *thread_data)
{
#ifdef DEBUG
  printf("Entering thread_end\n");
#endif
#ifdef DEBUG
  printf("Exiting thread_end\n");
#endif
}

static void
on_ompt_callback_parallel_begin(
  ompt_data_t *encountering_task_data,
  const omp_frame_t *encountering_task_frame,
  ompt_data_t* parallel_data,
  uint32_t requested_team_size,
  ompt_invoker_t invoker,
  const void *codeptr_ra)
{
#ifdef DEBUG
  printf("Entering parallel_begin\n");
#endif
  if(parallel_data->ptr)
    printf("0: parallel_data initially not null\n");
  parallel_data->value = ompt_get_unique_id();
#ifdef DEBUG
  printf("Exiting parallel_begin\n");
#endif
}

static void
on_ompt_callback_parallel_end(
  ompt_data_t *parallel_data,
  ompt_data_t *encountering_task_data,
  ompt_invoker_t invoker,
  const void *codeptr_ra)
{
#ifdef DEBUG
  printf("Entering parallel_end\n");
#endif
#ifdef DEBUG
  printf("Exiting parallel_end\n");
#endif
}

static void
on_ompt_callback_task_create(
    ompt_data_t *encountering_task_data,
    const omp_frame_t *encountering_task_frame,
    ompt_data_t* new_task_data,
    int type,
    int has_dependences,
    const void *codeptr_ra)
{
}

static void
on_ompt_callback_implicit_task(
    ompt_scope_endpoint_t endpoint,
    ompt_data_t *parallel_data,
    ompt_data_t *task_data,
    unsigned int team_size,
    unsigned int thread_num)
{
}

static void
on_ompt_callback_task_dependences(
  ompt_data_t *task_data,
  const ompt_task_dependence_t *deps,
  int ndeps)
{
}

static void
on_ompt_callback_task_dependence(
  ompt_data_t *first_task_data,
  ompt_data_t *second_task_data)
{
}

static void
on_ompt_callback_task_schedule(
    ompt_data_t *first_task_data,
    ompt_task_status_t prior_task_status,
    ompt_data_t *second_task_data)
{
}

static void
on_ompt_callback_sync_region(
  ompt_sync_region_kind_t kind,
  ompt_scope_endpoint_t endpoint,
  ompt_data_t *parallel_data,
  ompt_data_t *task_data,
  const void *codeptr_ra)
{
}


static void
on_ompt_callback_sync_region_wait(
  ompt_sync_region_kind_t kind,
  ompt_scope_endpoint_t endpoint,
  ompt_data_t *parallel_data,
  ompt_data_t *task_data,
  const void *codeptr_ra)
{
}

