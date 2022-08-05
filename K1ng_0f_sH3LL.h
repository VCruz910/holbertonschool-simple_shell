#ifndef _KING_H_
#define _KING_H_

/*__Libraries__*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

/*__Environment Variable__*/
extern char **environ;

/*__Macros__*/
#define BUFSIZE 256
#define TOK_DELIM " \t\r\n\a"
#define PRINT(c) (write(STDOUT_FILENO, c, ShStrLen(c)))
#define TOK_SIZE 64
#define PROMPT "$ "
#define SUCCESS (1)
#define FAIL (-1)
#define NEUTRAL (0)

/*__Structure Data__*/
typedef struct ShData
{
  char *Line;
  char **Args;
  char *CMD;
  char *Error_MSG;
  char *OldPWD;
  unsigned long int IDX;
  char *env;
} ShData_t;

typedef struct  BuiltIn
{
  char *ShCMD;
  int (*f)(ShData_t *data);
} buil_t;

/*__Prototypes__*/
/*#_Process_#*/
int ShRead(ShData_t *data);
int ShSplit(ShData_t *data);
int ShParse(ShData_t *data);
int ShProcCMD(ShData_t *data);

/*#_String Management_#*/
char *ShStrDup(char *STR);
char *ShStrCat(char *First, char *Second);
int ShStrLen(char *STR);
char *ShStrCHR(char *STR, char C);
int ShStrCMP(char *S1, char *S2);
char *ShStrCPY(char *Dest, char *SRC);

/*#_Memory Management_#*/
void *ShRealloc(void *PTR, unsigned int OldSize, unsigned int NewSize);
char *ShMemSet(char *S, char BYT, unsigned int N);
char *ShMemCPY(char *Dest, char *SRC, unsigned int N);
int free_data(ShData_t *data);

/*#_Tools_#*/
void *ShFillArray(void *A, int EL, unsigned int LEN);
void ShSignalHandler(int Signo);
char *ShGetEnv(char *PathName);
void ShIDX_CMD(ShData_t *data);
void ShArrayREV(char *ARR, int LEN);
char *ShItoA(unsigned int N);
int ShIntLEN(int NUM);
int ShAtoI(char *C);
int ShPrintError(ShData_t *data);
int ShIsAlpha(int C);

/*#_Shell Builtins_#*/
int ShAbort(ShData_t *data);
int Shchdir(ShData_t *data);
int ShHelp(ShData_t *data);
int ShHandleBuiltin(ShData_t *data);
int ShCheckBuiltin(ShData_t *data);

/*#_Shell Parsing_#*/
int ShPathForm(ShData_t *data);
void ShShortForm(ShData_t *data);
int ShBuiltin(ShData_t *data);

#endif
