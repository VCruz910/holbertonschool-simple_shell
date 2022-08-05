#include "K1ng_0f_sH3LL.h"

int ShPathForm(ShData_t *data)
{
	if (ShStrCHR(data->Args[0], '/') != 0)
	{
		data->CMD = ShStrDup(data->Args[0]);
		return (SUCCESS);
	}
	return (FAIL);
}
#define DELIMITER ":"

void ShShortForm(ShData_t *data)
{
	char *path, *token, *_path;
	struct stat st;
	int exist_flag = 0;

	path = ShGetEnv("PATH");
	_path = ShStrDup(path);
	token = strtok(_path, DELIMITER);
	while (token)
	{
		data->CMD = ShStrCat(token, data->Args[0]);
		if (stat(data->CMD, &st) == 0)
		{
			exist_flag += 1;
			break;
		}
		free(data->CMD);
		token = strtok(NULL, DELIMITER);
	}
	if (exist_flag == 0)
	{
		data->CMD = ShStrDup(data->Args[0]);
	}
	free(_path);
}
#undef DELIMITER

int ShBuiltin(ShData_t *data)
{
	buil_t blt[] = {
		{"exit", ShAbort},
		{"cd", Shchdir},
		{"help", ShHelp},
		{NULL, NULL}
	};
	int i = 0;

	while ((blt + i)->ShCMD)
	{
		if (ShStrCMP(data->Args[0], (blt + i)->ShCMD) == 0)
			return (SUCCESS);
		i++;
	}
	return (NEUTRAL);
}
