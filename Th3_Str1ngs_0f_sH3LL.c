#include "K1ng_0f_sH3LL.h"

char *ShStrCat(char *First, char *Second)
{
	int LEN1, LEN2, i = 0, j = 0;
	char *result;

	LEN1 = ShStrLen(First);
	LEN2 = ShStrLen(Second);
	result = malloc((LEN1 + LEN2 + 2) * sizeof(char));
	if (!result)
	{
		return (NULL);
	}
	*result = '\0';
	while (First[j])
	{
		result[i++] = First[j++];
	}
	result[i++] = '/';
	j = 0;
	while (Second[j])
	{
		result[i++] = Second[j++];
	}
	result[i] = '\0';
	return (result);
}

int ShStrLen(char *STR)
{
	int LEN;

	for (LEN = 0; STR[LEN]; LEN++)
		;
	return (LEN);
}

int ShStrCMP(char *S1, char *S2)
{
	int cmp = 0, i;

	if (S1 == NULL || S2 == NULL)
	{
		return (1);
	}
	for (i = 0; S1[i]; i++)
	{
		if (S1[i] != S2[i])
		{
			cmp = S1[i] - S2[i];
			break;
		}
		else
		{
			continue;
		}
	}
	return (cmp);
}

char *ShStrCHR(char *STR, char C)
{
	char *PTR;

	if (STR == NULL)
	{
		return (NULL);
	}
	for (PTR = STR; *PTR; PTR++)
	{
		if (*PTR == C)
		{
			return (PTR);
		}
	}
	return (NULL);
}

char *ShStrDup(char *STR)
{
	char *DUP;

	if (STR == NULL)
	{
		return (NULL);
	}
	DUP = malloc(ShStrLen(STR) + 1);
	if (DUP == NULL)
	{
		return (NULL);
	}
	ShStrCPY(DUP, STR);
	return (DUP);
}

char *ShStrCPY(char *Dest, char *SRC)
{
	int i;

	for (i = 0; SRC[i] != '\0'; i++)
	{
		Dest[i] = SRC[i];
	}
	Dest[i] = '\0';
	return (Dest);
}

int ShIsAlpha(int C)
{
	if ((C >= 65 && C <= 90) || (C >= 97 && C <= 122))
	{
		return (SUCCESS);
	}
	return (FAIL);
}
