#include "so_long.h"

void	error_out(char error_sign)
{
	if (error_sign == 'd') // file descriptor failed to open
		perror("\033[1;31mMap failed to open. Bad input? Typo? Perhaps a SKILL ISSUE");
	else if (error_sign == 'm') // map failed to allocate
		perror("\033[1;31mwoops, something went wrong with the process. Maybe try again? Or let Nasser fix his shit code.");
	else if (error_sign == 'h') // height value too small
		perror("\033[1;31mthat's not how you imagine a map!!! Stop trying to break me and play the damn game \033[1;37mITS FREE");
	else if (error_sign == 'l') // Failed to read line due to an incorrect character conflict
		perror("\033[1;31mwrong character found in map. Write it according to the subject!!");
	else if (error_sign == 'x')
		perror("\033[1;31mmap length uneven. Do you need a shape sorter to learn what a rectangle looks like?");
	else // dumbass used the wrong error handling sign for his own function
		perror("\033[0;31mbroskie u got the wrong error sign HOW DO YOU MESS THAT UP?????? \033[1;31mNO PLAYER EVER SEES THIS MESSAGE");
	exit(1);
}

// void	error_free()