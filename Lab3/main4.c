#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int l_str;
	printf("Enter size: ");
	scanf("%d", &l_str);

	printf("Enter string: ");
	char s[l_str];
	scanf("%s", s);

	int l_substr;
	printf("Enter size: ");
	scanf("%d", &l_substr);

	printf("Enter string: ");
	char subs[l_str];
	scanf("%s", subs);

	char *num = 0;
	int is_it = -1;


	if(l_substr > l_str){
		printf("Wrong data!\n");
		return 0;
	}else{
		for(int i = 0; i < l_str; ++i)
		{
			int count = 0;
			if(s[i] == subs[0] && l_str - i >= l_substr){
				is_it = 0;
				char *beg = &s[i];
				count++;
				for (int j = 1; j < l_substr; j++)
				{
					if(s[i+j] == subs[j]){
						count++;
					}		
				}

				if(count == l_substr){
					num = beg;
				}
			}
		}
	}

	if(num == 0){
		printf("The substring isn't included in this string!\n");
	}else{
		printf("The substring is included in with %p character\n", num);
	}

	return 0;
}


