#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#typedef char *string;

#if 0
string _strtok(string str, const string delimiter)
{
	static string index;

	if (str == NULL)
	{
		str = index;
	}
}

#endif


/**
 * _strspn - gets the length of a prefix substring
 * @s: the string to check in
 * @accept: the substring
 * Return: the length of the substring
 */
size_t _strspn(const string s, const string accept)
{
	const string a, p;
	size_t num;

	for (p = s; *p != '\0'; ++p)
	{
		for (a = accept; *a != '\0'; ++a)
			if (*p == *a)
				break;
		if (*a == '\0')
			return (num);
		else
			++num;
	}
	return (num);
}

int main(void)
{
	printf("%d", _strspn("hellothere", "hell")); //-> 4
	return (0);
}
