# include <stdio.h>
# include <string.h>
# include <assert.h>
# include "file_popularity.h"

void create_file_with_given_name_and_content(char *name, char *content)
{
	FILE *file = fopen(name, "w");
	assert(file);

	rewind(file);
	assert(fwrite(content, 1, strlen(content), file) == strlen(content));
	
	fclose(file);
}

/*
void test_1(void)
{
	FILE_POPULARITY *file_popularity = NULL;
	FILE *popularity_file = NULL;
	int i = 0;

	create_file_with_given_name_and_content("popul_test.txt", 
		"0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n");

	popularity_file = fopen("popul_test.txt", "r");

	file_popularity = load_file_popularity(popularity_file, 10);
	
	for (; i < 10; i++)
	{
		assert(file_popularity->popularity[i] == i);	
	}

	destruct_file_popularity(file_popularity);
	fclose(popularity_file);
}
*/
void test_system_popularity(void)
{
	FILE_POPULARITY *file_popularity = construct_file_popularity(10, 1);
	int expected_system_popularity = 0;
	int i = 0;
	
	for ( ; i < 10; i++)
	{
		file_popularity->popularity[i] = i + 1;
		expected_system_popularity += (i + 1);
	}
	
	assert(system_popularity(file_popularity) 
			== expected_system_popularity);	

	destruct_file_popularity(file_popularity);
}

void test_popularity_is_zero_filled(void)
{
	FILE_POPULARITY *file_popularity = NULL;
	int number_of_files = 10;
	int number_of_machines = 1;

	for ( ; number_of_machines <= 10; number_of_machines++)
	{
		int i = 0;
		file_popularity = construct_file_popularity(number_of_files, 
							number_of_machines);
		assert(file_popularity);
		for ( ; i < number_of_machines*number_of_files; i++)
		{
			assert(file_popularity->popularity[i] =='\0');
		}
		
		destruct_file_popularity(file_popularity);	
	}	
}

int main(void)
{
/*	test_1();
	puts("passed test_1");*/
	test_system_popularity();
	puts("passed test_system_popularity");
	test_popularity_is_zero_filled();
	puts("passed test_popularity_is_zero_filled");

	return 0;
}
