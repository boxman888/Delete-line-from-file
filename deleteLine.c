/********************************************************************
*
* Deletes a specific Line from a text file.
*
********************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fileptr1, *fileptr2; // File pointers for reading and writing.
	char fileName[40], buffer[10]; // Hold user and file data.
	char ch; // Used to move over each character.

	// delete_line is the line to delete.
	// flag is used as an error holder.
	// temp is the current count of lines crawled through.
	int delete_line, flag, temp = 1;
	printf("Enter file name: ");

	fgets(fileName, sizeof(fileName), stdin);
	flag = sscanf(fileName, "%s", fileName);	
	if (flag < 1)
	{
		printf("\nError: Could not find file.\n");
		exit(1);
	}

	// Open file in read mode.
	fileptr1 = fopen(fileName, "r");
	if (fileptr1 == NULL)
	{
		printf("Error: Could not find file.\n");
		exit(1);
	}
	// Geth the start of the file.
	ch = getc(fileptr1);
	while (ch != EOF)
	{
		printf("%c",ch);
		// Move single characters into the list.
		ch = getc(fileptr1);
	}

	// Poinr back to the start of the file.
	rewind(fileptr1);

	printf("\nEnter line number of the line to be deleted:");	
	fgets(buffer, sizeof(buffer), stdin);
	flag = sscanf(buffer, "%d", &delete_line);
	if (flag < 1)
	{
		printf("\nNot a number\n");
		exit(1);
	}

	// Open file in write mode.
	fileptr2 = fopen("tempFile.c", "w");
	ch = getc(fileptr1);
	while (ch != EOF)
	{
		// Count lines passed.
		if (ch == '\n')
			++temp;
		// Write everything but the line number to be deleted.
		if (temp != delete_line)
		{
			putc(ch, fileptr2);
		}
		// Get next character.
		ch = getc(fileptr1);
	}
	// Close file pointers.
	fclose(fileptr1);
	fclose(fileptr2);
	remove(fileName);// Delete the file fileName points to.
	
	// Rename tempFile to what name is stored in fileName.
	rename("tempFile.c", fileName);
	printf("\n The contents of file after being modified are as follows:\n");
	fileptr1 = fopen(fileName, "r");
	ch = getc(fileptr1);
	// Print the new data in the file
	while (ch != EOF)
	{
		printf("%c", ch);
		ch = getc(fileptr1);
	}
	// Close fileptr1
	fclose(fileptr1);

	return 0;
}
