#include "K1ng_0f_sH3LL.h"

int main(void)
{
	ShData_t data;
	int pl;

	ShMemSet((void *)&data, 0, sizeof(data));
	signal(SIGINT, ShSignalHandler);
	while (1)
	{
		ShIDX_CMD(&data);
		if (ShRead(&data) < 0)
		{
			if (isatty(STDIN_FILENO))
				PRINT("\n");
			break;
		}
		if (ShSplit(&data) < 0)
		{
			free_data(&data);
			continue;
		}
		pl = ShParse(&data);
		if (pl == 0)
		{
			free_data(&data);
			continue;
		}
		if (pl < 0)
		{
			ShPrintError(&data);
			continue;
		}
		if (ShProcCMD(&data) < 0)
		{
			ShPrintError(&data);
			break;
		}
		free_data(&data);
	}
	free_data(&data);
	exit(EXIT_SUCCESS);
}

int ShRead(ShData_t *data)
{
	char *CSR_PTR, *End_PTR, C;
	size_t Size = BUFSIZE, Read_ST, Length, NewSize;

	data->Line = malloc(Size * sizeof(char));
	if (data->Line == NULL)
	{
		return (FAIL);
	}
	if (isatty(STDIN_FILENO))
	{
		PRINT(PROMPT);
	}
	for (CSR_PTR = data->Line, End_PTR = data->Line + Size;;)
	{
		Read_ST = read(STDIN_FILENO, &C, 1);
		if (Read_ST == 0)
		{
			return (FAIL);
		}
		*CSR_PTR++ = C;
		if (C == '\n')
		{
			*CSR_PTR = '\0';
			return (SUCCESS);
		}
		if (CSR_PTR + 2 >= End_PTR)
		{
			NewSize = Size * 2;
			Length = CSR_PTR - data->Line;
			data->Line = ShRealloc(data->Line, Size * sizeof(char),
					NewSize * sizeof(char));
			if (data->Line == NULL)
				return (FAIL);
			Size = NewSize;
			End_PTR = data->Line + Size;
			CSR_PTR = data->Line + Length;
		}
	}
}

int ShSplit(ShData_t *data)
{
	char *token;
	size_t Size = TOK_SIZE, NewSize, I = 0;

	if (ShStrCMP(data->Line, "\n") == 0)
		return (FAIL);
	data->Args = malloc(Size * sizeof(char *));
	if (data->Args == NULL)
		return (FAIL);
	token = strtok(data->Line, TOK_DELIM);
	if (token == NULL)
		return (FAIL);
	while (token)
	{
		data->Args[I++] =  token;
		if (I + 2 >= Size)
		{
			NewSize = Size * 2;
			data->Args = ShRealloc(data->Args, Size * sizeof(char *),
					NewSize * sizeof(char *));
			if (data->Args == NULL)
				return (FAIL);
			Size = NewSize;
		}
		token = strtok(NULL, TOK_DELIM);
	}
	data->Args[I] = NULL;
	return (0);
}
#undef TOK_DELIM
#define TOK_DELIM ":"

int ShParse(ShData_t *data)
{
	if (ShPathForm(data) > 0)
	{
		return (SUCCESS);
	}
	if (ShBuiltin(data) > 0)
	{
		if (ShHandleBuiltin(data) < 0)
		{
			return (FAIL);
		}
		return (NEUTRAL);
	}
	ShShortForm(data);
	return (SUCCESS);
}
#undef TOK_DELIM

int ShProcCMD(ShData_t *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(data->CMD, data->Args, environ) < 0)
			data->Error_MSG = ShStrDup("not found\n");
		return (FAIL);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	return (0);
}
