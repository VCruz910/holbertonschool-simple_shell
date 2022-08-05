#include "K1ng_0f_sH3LL.h"
#define SETOWD(V) (V = ShStrDup(ShGetEnv("OLDPWD")))

int Shchdir(ShData_t *data)
{
	char *home;

	home = ShGetEnv("HOME");
	if (data->Args[1] == NULL)
	{
		SETOWD(data->OldPWD);
		if (chdir(home) < 0)
			return (FAIL);
		return (SUCCESS);
	}
	if (ShStrCMP(data->Args[1], "-") == 0)
	{
		if (data->OldPWD == 0)
		{
			SETOWD(data->OldPWD);
			if (chdir(home) < 0)
				return (FAIL);
		}
		else
		{
			SETOWD(data->OldPWD);
			if (chdir(data->OldPWD) < 0)
				return (FAIL);
		}
	}
	else
	{
		SETOWD(data->OldPWD);
		if (chdir(data->Args[1]) < 0)
			return (FAIL);
	}
	return (SUCCESS);
}
#undef GETCWD

int ShAbort(ShData_t *data)
{
	int code, I = 0;

	if (data->Args[1] == NULL)
	{
		free_data(data);
		exit(errno);
	}
	while (data->Args[1][I])
	{
		if (ShIsAlpha(data->Args[1][I++]) < 0)
		{
			data->Error_MSG = ShStrDup("Illegal number\n");
			return (FAIL);
		}
	}
	code = ShAtoI(data->Args[1]);
	free_data(data);
	exit(code);
}

int ShHelp(ShData_t *data)
{
	{
		int FD, FW, RD = 1;
		char C;

		FD = open(data->Args[1], O_RDONLY);
		if (FD < 0)
		{
			data->Error_MSG = ShStrDup("no help topics match\n");
			return (FAIL);
		}
		while (RD > 0)
		{
			RD = read(FD, &C, 1);
			FW = write(STDOUT_FILENO, &C, RD);
			if (FW < 0)
			{
				data->Error_MSG = ShStrDup("cannot write: permission denied\n");
				return (FAIL);
			}
		}
		PRINT("\n");
		return (SUCCESS);
	}
}

int ShHandleBuiltin(ShData_t *data)
{
	buil_t blt[] = {
		{"exit",ShAbort },
		{"cd", Shchdir},
		{"help", ShHelp},
		{NULL, NULL}
	};
	int i = 0;

	while ((blt + i)->ShCMD)
	{
		if (ShStrCMP(data->Args[0], (blt + i)->ShCMD) == 0)
			return ((blt + i)->f(data));
		i++;
	}
	return (FAIL);
}
