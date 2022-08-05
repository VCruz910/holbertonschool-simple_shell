#include "K1ng_0f_sH3LL.h"

char *ShGetEnv(char *PathName)
{
	char **environ_cursor, *env_ptr, *name_ptr;

	environ_cursor = environ;
	while (*environ_cursor)
	{
		env_ptr = *environ_cursor;
		name_ptr = PathName;
		while (*env_ptr == *name_ptr)
		{
			if (*env_ptr == '=')
				break;
			env_ptr++;
			name_ptr++;
		}
		if ((*env_ptr == '=') && (*name_ptr == '\0'))
			return (env_ptr + 1);
		environ_cursor++;
	}
	return (NULL);
}

void ShSignalHandler(int Signo)
{
	if (Signo == SIGINT)
	{
		PRINT("\n");
		PRINT(PROMPT);
	}
}

void *ShFillArray(void *A, int EL, unsigned int LEN)
{
	char *P = A;
	unsigned int I = 0;

	while (I < LEN)
	{
		*P = EL;
		P++;
		I++;
	}
	return (A);
}

void ShArrayREV(char *ARR, int LEN)
{
	int I;
	char TMP;

	for (I = 0; I < (LEN / 2); I++)
	{
		TMP = ARR[I];
		ARR[I] = ARR[(LEN - 1) - I];
		ARR[(LEN - 1) - I] = TMP;
	}
}

void ShIDX_CMD(ShData_t *data)
{
	data->IDX += 1;
}

char *ShItoA(unsigned int N)
{
	int LEN = 0, I = 0;
	char *S;

	LEN = ShIntLEN(N);
	S = malloc(LEN + 1);
	if (!S)
	{
		return (NULL);
	}
	*S = '\0';
	while (N / 10)
	{
		S[I] = (N % 10) + '0';
		N /= 10;
		I++;
	}
	S[I] = (N % 10) + '0';
	ShArrayREV(S, LEN);
	S[I + 1] = '\0';
	return (S);
}

int ShAtoI(char *C)
{
	unsigned int VAL = 0;
	int Sign = 1;

	if (C == NULL)
	{
		return (0);
	}
	while (*C)
	{
		if (*C == '-')
			Sign *= (-1);
		else
			VAL = (VAL * 10) + (*C - '0');
		C++;
	}
	return (Sign * VAL);
}

int ShIntLEN(int NUM)
{
	int LEN = 0;

	while (NUM != 0)
	{
		LEN++;
		NUM /= 10;
	}
	return (LEN);
}

int ShPrintError(ShData_t *data)
{
	char *IDX = ShItoA(data->IDX);

	PRINT("hsh: ");
	PRINT(IDX);
	PRINT(": ");
	PRINT(data->Args[0]);
	PRINT(": ");
	PRINT(data->Error_MSG);
	free(IDX);
	return (0);
}

