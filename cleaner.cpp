/*
                 The Cleaner
            v1.1 by Snake Man, PMC.
          Copyright (c) PMC 1996-2015.

   (compiled at 06-05-2000 by Linux G++).

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char version[] = "v1.1 rev3"; /* version number */

FILE * StripFile;
FILE * File2;
FILE * Nuke;
FILE * CleanEd;
FILE * CFGfile;

char line[82];
char temp1[82];
char temp2[82];
char dizzy[600][82];    /* 600 dizzy lines. */
char nfostring[82];     /* nfo/ulby string */
char fakestring[82];    /* fake string ;) */
char NlinesChar[82];    /* number of lines in nfo/ulby string */
char FlinesChar[82];    /* number of lines in fake string */

char newline[13] = "";    /* stuff related to Extra & Psycho modes */
char templine1[82];
char templine2[82];
char *pmcptr;           /* pointer for the string-split action */
char *temp_ptr;
char temp_param[4];

int i, last_diz, cx1, cx2, Nlines, Flines, Cntr, Nukd, Wipe = 0; /* integers */
long OrgFileSize = 0, NewFileSize = 0;

/*
 ***************************************************************************
 *******[ NFO string capture ]***********************************************
 ***************************************************************************
 */
int CFGreading()
{
	fgets(nfostring, 82, CFGfile);  /* read nfo/ulby string */
	fgets(NlinesChar, 82, CFGfile); /* read how many lines are in ulby stuff */
	fgets(fakestring, 82, CFGfile); /* read fake string */
	fgets(FlinesChar, 82, CFGfile); /* read how many lines are in fake stuff */

	Nlines = atoi(NlinesChar); /* convert NlinesChar char into int */
	Flines = atoi(FlinesChar); /* convert FlinesChar char into int */

	strncpy(temp1, nfostring, strlen(nfostring) - 1); /* copy the string minus "\0" char */
	strncpy(temp2, fakestring, strlen(fakestring) - 1);

	return 0;
}

/*
 ***************************************************************************
 *******[ Reading the nukes ]************************************************
 ***************************************************************************
 */
void ReadNukes()
{
	char tempbitch[82];

	while (!feof(Nuke))
	{
		fgets(tempbitch, 82, Nuke); /* read into array "dizzy[i]" */
		strncpy(dizzy[i], tempbitch, strlen(tempbitch) - 1);
		i++;

		if (i == 600)
			break;   /* if dizzy grows too looong, we'll break. */
	}
	last_diz = i - 1;            /* minus oneline, so there wont be empty line */
}

/*
 ***************************************************************************
 *******[ Scanning function ]************************************************
 ***************************************************************************
 */
int Scanning() /* main motherfucking cleaning function. */
{
	for (i = 0; i < last_diz; i++) /* until we are at the last grouplogo array */

		if (strstr(line, dizzy[i]))
		{
			Nukd++;
			return 0; /* exit immediately from the function */
		}

	if (i == last_diz)             /* if not found and its the last line */
		fputs(line, CleanEd);  /* then write it down to clean file */

	return 0;
}

/*
 ***************************************************************************
 *******[ Nuking NFO&ulby ]**************************************************
 ***************************************************************************
 */
void NFOing()
{
	if (strstr(line, temp1))                   /* do we have a match? */
		for (cx1 = 0; cx1 < Nlines; cx1++) /* for loop... */
		{
			Cntr++;
			fgets(line, 82, StripFile); /* skip the "Nlines" amount of lines */
		}

	if (strstr(line, temp2))         /* do we have a FAKE line? */
		for (cx2 = 0; cx2 < Flines; cx2++)
		{
			Cntr++;
			fgets(line, 82, StripFile); /* skip the "Flines" amout of lines */
		}
}

/*
 ***************************************************************************
 *******[ Header info ]******************************************************
 ***************************************************************************
 */
void Header()
{
	printf("\n.-------------------------------------------------------.\n");
	printf("|  The Cleaner %s (c) Snake Man, PMC 1996-2015.  |\n", version);
	printf("`-------------------------------------------------------'\n\n");
}

/*
 ***************************************************************************
 *******[ Footer info ]******************************************************
 ***************************************************************************
 */
void Footer()
{
	printf("Done!\n\n");
	printf("   lines processed: %i\n", Cntr);
	printf("   file-lines left: %i\n", Nukd);
	printf("   Original size  : %ld bytes\n", OrgFileSize);

	fseek (CleanEd, 0, SEEK_END);
	NewFileSize = ftell(CleanEd);
	fseek (CleanEd, 0, SEEK_SET);

	printf("   Stripped size  : %ld bytes\n", NewFileSize);
	printf("   nuked from it  : %ld bytes\n\n", OrgFileSize - NewFileSize);
	printf("Thank you for using The Cleaner %s - Have a nice day.\n\n", version);
}

/*
 ***************************************************************************
 *******[ Lowercase ]********************************************************
 ***************************************************************************
 */
void LowerCase()
{
	strcpy(templine1, "");
	strcpy(templine2, "");
	pmcptr = 0;
	pmcptr = line;  /* lets put the line to pointer. */

	strncat(templine1, line, 34);   /* write first 33 chars to templine */
	strcpy(templine2, pmcptr + 34); /* copy FROM 34 char to end (null). */
	                                /* yes, 34 not 33. */

	temp_ptr = 0;
	temp_ptr = templine2;

	for (i = 0; i < 46; i++)
	{
		temp_ptr[i] = tolower(temp_ptr[i]);
	}

	strcat(templine1, temp_ptr);   /* append the lowered 34->nul to 1->33 */
	strcpy(line, "");
	strcpy(line, templine1);
	strcpy(temp_ptr, temp_ptr);
}

/*
 ***************************************************************************
 *******[ WipeOut Mode ]*****************************************************
 ***************************************************************************
 */
int WipeOut()
{
/* Routine that cleans everything out except the filename lines. */

	printf("  ** WipeOut Mode Selected **\n");
	char newline[13] = "";
	char fishline[200];
	printf(" + Cleaning the subject material: ");

	fseek (StripFile, 0, SEEK_END);
	OrgFileSize = ftell(StripFile);
	fseek (StripFile, 0, SEEK_SET);

/*
   pcboard shit
    fgets(line,82,StripFile);
                fputs(line,CleanEd);
    fgets(line,82,StripFile);
                fputs(line,CleanEd);*/

	fgets(fishline, 200, StripFile);

	while (!feof(StripFile))
	{
		Cntr++;
		strncpy(line, fishline, 82);
/*	   fgets(line,82,StripFile); */
		strcpy(newline, "             ");
		strncpy(newline, line, 13);

		if (strcmp(newline, "             ") != 0) /* if filename found... */
		{
			Nukd++;

			if (Wipe == 1)
				LowerCase();

			fputs(line, CleanEd);    /* write it. */
		}

		fgets(fishline, 200, StripFile);
	}

	Footer();

	fclose(StripFile); /* closes all the opened files */
	fclose(CFGfile);
	fclose(Nuke);
	fclose(CleanEd);
	exit(1);
	return 0;
}

/*
 ***************************************************************************
 *******[ PSYCHO Mode ]******************************************************
 ***************************************************************************
 */
int PSYCHO()
{
	printf("  ** PSYCHO Mode Selected **\n");

/* routine build by MIZ (c) PMC 1998. */
	char TempFileName[82];
	char NextFile[13];
	int diz = 0;

	printf(" + Cleaning the subject material: ");

	fseek (StripFile, 0, SEEK_END);
	OrgFileSize = ftell(StripFile);
	fseek (StripFile, 0, SEEK_SET);

	fgets(TempFileName, 82, File2);

	while (!feof(StripFile))
	{
		Cntr++;
		fgets(line, 82, StripFile);

		strcpy(newline, "             ");
		strncpy(newline, line, 13);
		strcpy(NextFile, "             ");

		if (diz == 1 && strcmp(newline, "             ") == 0)

			if (!feof(StripFile)) /* to not put the "DUPE" last line of output. */

			{
				if (Wipe == 1)
					LowerCase();
				fputs(line, CleanEd);
			}

		if (strcmp(newline, "             ") != 0) /* if filename found... */
		{
			diz = 0;
			fgets(TempFileName, 82, File2);
			strncpy(NextFile, TempFileName, 13);

			while(strcmp(NextFile, "             ") == 0  && !feof(File2))
			{
				fgets(TempFileName, 82, File2);
				strncpy(NextFile, TempFileName, 13);
			}

			if (strspn(newline, NextFile) < 5)
				diz = 1;
			Nukd++;

			if (feof(StripFile))
			{
				Footer();
				fclose(StripFile);
				fclose(CFGfile);
				fclose(Nuke);
				fclose(CleanEd);
				fclose(File2);
				exit(1);
			}

			if (Wipe == 1)
				LowerCase();

			fputs(line, CleanEd);     /* write it. */
		}
	}

	Footer();

	fclose(StripFile); /* closes all the opened files */
	fclose(CFGfile);
	fclose(Nuke);
	fclose(CleanEd);
	fclose(File2);

	exit(1);
	return 0;
}

/*
 ***************************************************************************
 *******[ the main ]*********************************************************
 ***************************************************************************
 */
int main(int x, char *param[])
{
	Header();

	if (x < 4) /* basic exe is 0 param. first param = 1, second = 2 jne. */
	{
		printf("   command line parameters:\n");
		printf("   original file. cleaned file. parameters.\n");
		printf("   parameter " "/W" "  is for WipeOut mode.\n");
		printf("   parameter " "/P" "  is for PSYCHO mode.\n");
		printf("   parameter " "/WL" " is for WipeOut Lowercase mode.\n");
		printf("   parameter " "/PL" " is for PSYCHO Lowercase mode.\n");
		printf("   parameter " "/N" "  is for Normal mode.\n");
		printf("   as example:\n");
		printf("   CLEANER directory.001 directory.txt /P\n\n");
		return(1);
	}

	printf("        Configuration file  : CLEANER.CFG\n");
	printf("        To be stripped file : %s", param[1]);
	printf("\n        Output file         : %s\n\n", param[2]);

	StripFile = fopen(param[1], "rt");
	if (!StripFile)
	{
		printf("\nERROR at: %s file!", param[1]);
		return(1);
	}

	File2 = fopen(param[1], "rt");

	Nuke = fopen("cleaner.dat", "rt");
	if (!Nuke)
	{
		printf("\nERROR at: cleaner.dat file!");
		return(1);
	}

	CleanEd = fopen(param[2], "wt");
	if (!CleanEd)
	{
		printf("\nERROR at: %s file!", param[2]);
		return(1);
	}

	CFGfile = fopen("cleaner.cfg", "rt");
	if (!CFGfile)
	{
		printf("\nERROR at: cleaner.cfg, please check your setup.");
		return(1);
	}

	if (strcasecmp(param[3], "/N") != 0)
	{
		if (strcasecmp(param[3], "/W")  == 0)
			WipeOut();
		if (strcasecmp(param[3], "/WL") == 0)
		{
			Wipe = 1;
			WipeOut();
		}
		if (strcasecmp(param[3], "/P")  == 0)
			PSYCHO();
		if (strcasecmp(param[3], "/PL") == 0)
		{
			Wipe = 1;
			PSYCHO();
		}
	}

	printf(" + Reading the targetted material: ");
	CFGreading(); /* reads the configuration file */
	ReadNukes();  /* reads the group logos */
	printf("Done!\n");
	printf(" + Cleaning the subject material: ");
	Cntr = 1;

	fseek (StripFile, 0, SEEK_END);
	OrgFileSize = ftell(StripFile);
	fseek (StripFile, 0, SEEK_SET);

	while (!feof(StripFile)) /* will read the stripped file until it ends */
	{
		Cntr++;
		fgets(line, 82, StripFile); /* reads one target line */
		NFOing();                   /* check for ULBY lines */
		Scanning();                 /* does the actual comparing */
	}

	printf("Done!\n");
	printf("   To_be_nuked_dizzys read : %i\n", last_diz);
	printf("   Filelist lines processed: %i\n", Cntr);
	printf("   Filelist Diz-lines nuked: %i\n", Nukd);
	printf("   Filelist Original size  : %ld bytes\n", OrgFileSize);

	Footer();

	fclose(StripFile); /* closes all the opened files */
	fclose(CFGfile);
	fclose(Nuke);
	fclose(CleanEd);
	return 0;
}
/* *****[ the end ]********************************************************* */
