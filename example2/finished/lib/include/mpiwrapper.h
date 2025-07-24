#ifndef mpiwrapper
#define mpiwrapper

int mp_init( int *argc, char ***argv);
int mp_finalize(void);
int mp_comm_rank( int *rank );
int mp_comm_size( int *size );

#endif
