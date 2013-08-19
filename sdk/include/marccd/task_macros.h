#ifndef task_macros_h
#define task_macros_h

#define FRAME_PIPELINE_COMMAND_TYPE_ANY		0
#define FRAME_PIPELINE_COMMAND_TYPE_INTEGRATE	1
#define FRAME_PIPELINE_COMMAND_TYPE_READOUT	2
#define FRAME_PIPELINE_COMMAND_TYPE_DEZINGER	3
#define FRAME_PIPELINE_COMMAND_TYPE_CORRECT	4
#define FRAME_PIPELINE_COMMAND_TYPE_WRITEFILE	5

#define STATE_MASK		0xf
#define STATUS_MASK		0xf
#define TASK_STATUS_MASK(task)	(STATUS_MASK << (4*((task)+1)))

/* Task Status bits */
#define TASK_STATUS_QUEUED	(1)
#define TASK_STATUS_EXECUTING	(1 << 1)
#define TASK_STATUS_ERROR	(1 << 2)
#define TASK_STATUS_RESERVED	(1 << 3)

/* Task numbers */
#define TASK_ACQUIRE			0
#define TASK_READ			1
#define TASK_CORRECT			2
#define TASK_WRITE			3
#define TASK_DEZINGER			4
#define TASK_SERIES			5
#define TASK_MAX			5

#define TASK_GONIOSTAT_MOTION		0
#define TASK_GONIOSTAT_EXPOSURE		1
#define TASK_GONIOSTAT_ALIGNMENT	2
#define TASK_GONIOSTAT_SAMPLE_CHANGER	3
#define TASK_GONIOSTAT_SAMPLE_ALIGNMENT	4
#define TASK_GONIOSTAT_MAX		4

#define PIPELINE_STATUS_MASK (TASK_STATUS_MASK(TASK_ACQUIRE) | TASK_STATUS_MASK(TASK_READ) | TASK_STATUS_MASK(TASK_CORRECT) | TASK_STATUS_MASK(TASK_WRITE) | TASK_STATUS_MASK(TASK_DEZINGER) | TASK_STATUS_MASK(TASK_SERIES))
#define GONIOSTAT_STATUS_MASK (TASK_STATUS_MASK(TASK_GONIOSTAT_MOTION) | TASK_STATUS_MASK(TASK_GONIOSTAT_EXPOSURE) | TASK_STATUS_MASK(TASK_GONIOSTAT_ALIGNMENT) | TASK_STATUS_MASK(TASK_GONIOSTAT_SAMPLE_CHANGER) | TASK_STATUS_MASK(TASK_GONIOSTAT_SAMPLE_ALIGNMENT))

#define TASK_STATUS(current_status, task) (((current_status) & TASK_STATUS_MASK(task)) >> (4*((task) + 1)))
#define TEST_TASK_STATUS(current_status, task, status) (TASK_STATUS(current_status, task) & (status))
#define SET_TASK_STATUS(current_status, task, status) ((current_status) | ((status) << (4*((task)+1))))
#define CLEAR_TASK_STATUS(current_status, task, status) ((current_status) & ~((status) << (4*((task)+1))))
#define ZERO_TASK_STATUS(current_status, task) ((current_status) & (~(TASK_STATUS_MASK(task))))
#define SERVER_STATUS(current_status) ((current_status) & ~STATE_MASK)
#define SET_STATE(current_status, state) (((current_status) & (0xfffffff0)) | ((state) & 0xf))
#define SERVER_STATE(current_status) ((current_status) & STATE_MASK)
#define ADD_TO_TASKLIST(tasklist, task)	(tasklist |= (1 << task))

#define READ_DESTINATION_NONE	-1
#define READ_DESTINATION_RAW	0
#define READ_DESTINATION_BACKGROUND	1
#define READ_DESTINATION_SCRATCH	2

#define WRITE_SOURCE_NONE	0
#define WRITE_SOURCE_RAW	1
#define WRITE_SOURCE_CORRECTED	2
#define WRITE_SOURCE_BACKGROUND	3
#define WRITE_SOURCE_SCRATCH	4

#define DEZINGER_DESTINATION_NONE	-1
#define DEZINGER_DESTINATION_RAW	0
#define DEZINGER_DESTINATION_BACKGROUND	1
#define DEZINGER_DESTINATION_SCRATCH	2

#endif /* task_macros_h */
