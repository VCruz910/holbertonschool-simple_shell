#include "K1ng_0f_sH3LL.h"

void *ShRealloc(void *PTR, unsigned int OldSize, unsigned int NewSize)
{
	void *Results;

	if (NewSize == OldSize)
	{
		return (PTR);
	}
	if (NewSize == 0 && PTR)
	{
		free(PTR);
		return (NULL);
	}
	Results = malloc(NewSize);
	if (Results == NULL)
	{
		return (NULL);
	}
	if (PTR == NULL)
	{
		ShFillArray(Results, '\0', NewSize);
		free(PTR);
	}
	else
	{
		ShMemCPY(Results, PTR, OldSize);
		free(PTR);
	}
	return (Results);
}

char *ShMemSet(char *S, char BYT, unsigned int N)
{
	unsigned int I;

	for (I = 0; I < N; I++)
	{
		S[I] = BYT;
	}
	return (S);
}

int free_data(ShData_t *data)
{
	free(data->Line);
	data->Line = NULL;
	free(data->Args);
	data->Args = NULL;
	free(data->CMD);
	data->CMD = NULL;
	free(data->Error_MSG);
	data->Error_MSG = NULL;
	return (0);
}

char *ShMemCPY(char *Dest, char *SRC, unsigned int N)
{
	unsigned int I;

	for (I = 0; I < N; I++)
	{
		Dest[I] = SRC[I];
	}
	return (Dest);
}

