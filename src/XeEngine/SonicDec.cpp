#ifdef DEBUG

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "XeFile.h"

bool KDecomp(char *SrcFile, char *DstFile, long Location, bool Moduled)
{
	// Files
	FILE *Src;
	FILE *Dst;

	// Bitfield Infos
	unsigned short BITFIELD;
	unsigned char BFP;
	unsigned char Bit;

	// R/W infos
	unsigned char Byte;
	unsigned char Low, High;

	// Localization Infos
	int Pointer;

	// Count and Offest
	long Count = 0;
	long Offset = 0;

	// Moduled infos
	long FullSize = 0;
	long DecBytes = 0;

	//------------------------------------------------------------------------------------------------

	Src=fopen(SrcFile,"rb");	
	if (Src==NULL) return false;
	Dst=fopen(DstFile,"w+b");
	if (Dst==NULL)
	{
		fclose(Src);
		return false;
	}

	fseek(Src, Location, SEEK_SET);

	if (Moduled)
	{
		fread(&High, 1, 1, Src);
		fread(&Low, 1, 1, Src);
		FullSize = ((long)High << 8) + (long)Low;
	}

start:
	fread(&BITFIELD, 2, 1, Src);
	BFP=0;

	//------------------------------------------------------------------------------------------------
	while(1)
	{
		if(BITFIELD & (1<<BFP++)) Bit=1; else Bit=0;
		if (BFP>=16) { fread(&BITFIELD, 2, 1, Src); BFP=0; }
		//-- Direct Copy ---------------------------------------------------------------------------------
		if (Bit)
		{
			fread(&Byte, 1, 1, Src);
			fwrite(&Byte, 1, 1, Dst);
			DecBytes+=1;
		}
		else
		{
			if(BITFIELD & (1<<BFP++)) Bit=1; else Bit=0;
			if (BFP>=16) { fread(&BITFIELD, 2, 1, Src); BFP=0; }
			//-- Embedded / Separate -------------------------------------------------------------------------
			if (Bit)
			{
				fread(&Low, 1, 1, Src);
				fread(&High, 1, 1, Src);

				Count=(long)(High & 0x07);

				if (Count==0)
				{
					fread(&Count, 1, 1, Src);
					if (Count==0) goto end;
					if (Count==1) continue;
				}
				else
				{
					Count+=1;
				}

				Offset = 0xFFFFE000 | ((long)(0xF8 & High) << 5) | (long)Low;
			}
			//-- Inline --------------------------------------------------------------------------------------
			else
			{
				if(BITFIELD & (1<<BFP++)) Low=1; else Low=0;
				if (BFP>=16) { fread(&BITFIELD, 2, 1, Src); BFP=0; }
				if(BITFIELD & (1<<BFP++)) High=1; else High=0;
				if (BFP>=16) { fread(&BITFIELD, 2, 1, Src); BFP=0; }

				Count = ((long)Low)*2 + ((long)High) + 1;

				fread(&Offset, 1, 1, Src);
				Offset|=0xFFFFFF00;
			}
			//-- Write to file for indirect copy -------------------------------------------------------------
			for (int i=0; i<=Count; i++)
			{
				Pointer=ftell(Dst);
				fseek(Dst, Offset, SEEK_CUR);
				fread(&Byte, 1, 1, Dst);
				fseek(Dst, Pointer, SEEK_SET);
				fwrite(&Byte, 1, 1, Dst);
			}
			DecBytes+=Count+1;
			//------------------------------------------------------------------------------------------------
		}
	}
	//------------------------------------------------------------------------------------------------

end:
	if (Moduled)
	{
		if (DecBytes < FullSize)
		{
			do { fread(&Byte, 1, 1, Src); } while (Byte==0);
			fseek(Src, -1, SEEK_CUR);
			goto start;
		}
	}
	fclose(Dst);
	fclose(Src);
	return true;
}


int Pow(int base, int exponent)
{
	return (int)pow(float(base), float(exponent));
}
void stage_2(long *pointer, char *rompointer, char *bufferpointer, unsigned long *tiles, short rtiles, bool alt_out, int *out_loc);
int stage_1(long *pointer, char *rompointer, char *bufferpointer);
bool NDecomp(char *SrcFile, char *DstFile, long Pointer)
{
	// In the following code, I removed the declaration of the Pointer variable as it is now passed
	// as parameters. I also removed all console I/O operation as the function does not need to ask
	// for filenames and for a pointer, as they are passed as parameters.

	//set input and output modes to hex
	//	cin.setf(ios::hex);

	//misc variables and arrays
	FILE *openrom;
	int  result = 0, out_loc = 0, loopcount = 0;
	unsigned long romsize = 0;
	long pointer = Pointer; //place in the rom to load from */
	unsigned short rtiles; //remaining tiles to decompress
	bool alt_out = false; //flag to change between the two different output modes

	XeEngine::Memory tiles_mem(0x8000 * sizeof(unsigned long));
	unsigned long* tiles = (unsigned long*)tiles_mem.GetMemoryHandle(); //output array

	openrom = fopen( SrcFile, "rb" );
	fseek(openrom, 0, SEEK_END);
	romsize = ftell(openrom);
	rewind(openrom);
	char* rompointer = (char*)calloc(romsize, 0x01);
	if (rompointer != 0)
		result = fread(rompointer, romsize, 1, openrom);

	//allocates block of memory for decompression buffer
	char* bufferpointer = (char *)calloc( 0x200, 0x01 );

	// There starts the original code by Nemesis
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//entry point into algorithm
	rtiles = (*(pointer++ + rompointer) * 0x100); //reads in the number of tiles in this block
	rtiles += (*(pointer++ + rompointer) & 0xFF);
	alt_out = (rtiles & 0x8000) ? 1 : 0; //ses the output mode based on the value of the first bit
	rtiles = 0x7FFF & rtiles; //truncates the first bit as it is no longer significant
	result = stage_1(&pointer, rompointer, bufferpointer); //calls the header decompression routine
	if(result == -1)
	{
		return false;
	}
	stage_2(&pointer, rompointer, bufferpointer, &tiles[0], rtiles, alt_out, &out_loc); //calls the main decompression routine


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Additional filehanding to read decompressed tiles from memory into file
	XeEngine::File file;
	file.Create(XeEngine::String(DstFile));
	//file = fopen(DstFile, "wb");
	
	for(loopcount = 0; loopcount < out_loc; loopcount++)
	{
		tiles[loopcount] = ((tiles[loopcount] & 0xFF000000) / 0x1000000) + 
			((tiles[loopcount] & 0xFF0000) / 0x100) + 
			((tiles[loopcount] & 0xFF00) *0x100) + 
			((tiles[loopcount] & 0xFF) * 0x1000000); //byteswaps the output before writing to the output file
		file.Write(&tiles[loopcount] , 4);
		//result = fwrite((&tiles[loopcount]) , 4, 1, file);
	}
	file.Close();
	//result = fclose(file);
	fclose(openrom);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//First stage decompression algorithm
int stage_1 (long *pointer, char *rompointer, char *bufferpointer)
{
	unsigned short in_val; //storage for value coming from rom
	unsigned short out_val = 0; //storage for output value to decompression buffer
	unsigned short num_times; //number of times the calculated output value is written to the buffer
	unsigned short offset; //stores buffer offset to write to
	//main loop. Header is terminated by the value of 0xFF in the rom
	for (in_val = (*((*pointer)++ + rompointer) & 0xFF); in_val != 0xFF; in_val = (*((*pointer)++ + rompointer) & 0xFF))
	{
		if(in_val > 0x7F) //if most significant bit is set, store the last 4 bits and discard the rest
		{
			out_val = in_val; //last four bits set here are not changed until it enters here again
			in_val = (*((*pointer)++ + rompointer) & 0xFF); //read another value from the rom
		}
		num_times = 0x08 - (in_val & 0x0F); //the last 4 bits here determine the number of times the value is written to the buffer. Never greater than 8
		in_val = ((in_val & 0xF0) / 0x10) + ((in_val & 0x0F) * 0x10); //nibble swap the value from the rom
		out_val = (out_val & 0x0F) + (in_val * 0x10); //multiply the input value by 0x10 and place it in front of the last 4 bits in the output value
		offset = (*((*pointer)++ + rompointer) & 0xFF) * Pow(2, (num_times + 1)); //read another value from the rom and use it to determine the offset
		if(offset >= 0x200)
		{
			return -1;
		}

		num_times = Pow(2, num_times); //finish setting the number of times the value is written to the buffer
		for(; num_times != 0; num_times--,offset += 2) //loop for writing the values to the buffer
		{
			*(bufferpointer + offset + 1) = (out_val & 0x00FF);
			*(bufferpointer + offset) = ((out_val & 0xFF00) / 0x100); //wriiting the values to the buffer
		}
	}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Second stage decompression algorithm
void stage_2 (long *pointer, char *rompointer, char *bufferpointer, unsigned long *tiles, short rtiles, bool alt_out, int *out_loc)
{
	unsigned short rnibbles; //remaining nibbles in this line
	unsigned long out_val; //output value
	unsigned short rom_mod = 0x10; //This one is complex. Used in maths as a power of 2, but also controls when 
	//new values are read from the rom. Just read the algorithm.
	unsigned long alt_out_val = 0; //If the alternate output method is used by this archive, each line is XOR'd with
	//the line before it prior to writing to the output.
	unsigned short rlines; //remaining lines to decompress in this tile
	unsigned short mode_val; //There are two different things it can do in the main loop. This holds the value to switch between them
	unsigned short bufferoffset; //the buffer offset to read from next
	unsigned short next_out = 0; //the next nibble to be added to the output.
	short num_times = 0; //the number of times the value is repeated in the output
	unsigned short rom_val = (*((*pointer)++ + rompointer) * 0x100); //value from the rom
	rom_val += (*((*pointer)++ + rompointer) & 0xFF);
	for(;rtiles > 0;rtiles--) //main loop for tiles
	{
		for (rlines = 8; rlines != 0; rlines--) //loop for lines in the tile
		{
			for (out_val = 0, rnibbles = 8; rnibbles != 0; rnibbles--) //loop for nibbles in the line
			{
				num_times--; //decrements number of times to write current value to output
				if (num_times == -1) //if -1, calculate new value
				{
					mode_val = rom_val / Pow(2, (rom_mod - 8)); //determines which set of commands to perform
					if ((mode_val & 0x00FF) >= 0xFC) //determining value is 0xFC or greater
					{
						if (rom_mod < 0x0F) //determines whether or not to read another value from the rom
						{
							rom_mod += 8; //and adds 8 to rom_mod if it does
							rom_val = (rom_val * 0x100) + (*((*pointer)++ + rompointer) & 0xFF);
						}
						rom_mod -= 0x0D; //subtracts 0x0D from rom_mod
						num_times = ((short)(rom_val / Pow(2, rom_mod)) & 0x70) / 0x10; //calculates number of times to write value to output
						next_out = (short)(rom_val / Pow(2, rom_mod)) & 0x0F; //calculates next output value
					}
					else
					{
						bufferoffset = (mode_val & 0xFF) * 2; //sets buffer offset
						rom_mod -= *(bufferpointer + bufferoffset); //reads a buffer value, then subtracts it from rom_mod. Never greater than 0x7
						num_times = (*(bufferpointer + bufferoffset + 1) & 0xF0) / 0x10; //set number of times based on a buffer value. Never greater than 0x7
						next_out = *(bufferpointer + bufferoffset + 1) & 0x0F; //gets next output value from buffer
					}
					if (rom_mod < 9) //again, potentially load a value from the rom
					{
						rom_mod += 8; //and add 8 to rom_mod
						rom_val = (rom_val * 0x100) + (*((*pointer)++ + rompointer) & 0xFF);
					}
				}
				out_val = out_val * 0x10 + next_out; //adds next value to output
			}
			if (alt_out == false)
			{
				*(tiles + (*out_loc)++) = out_val; //writes next line to output array
			}
			else
			{
				alt_out_val = alt_out_val ^ out_val; //Alternate output method. Only bits set are those different to the last line
				*(tiles + (*out_loc)++) = alt_out_val;
			}
		}
	}
}
namespace
{

	char processed_bits = 0;
	char packet_length = 0;
	char mode = 0;
	char output_repeatcount = 0;
	//char remaining_bits = 0x10;
	char bits_remaining_postfunc = 0;
	char bitmask = 0;
	unsigned short input_stream = 0;
	unsigned short incrementing_value = 0;
	unsigned short common_value = 0;
	unsigned short addvalue = 0;
	unsigned short outvalue = 0;
	int loopcount;

	FILE *infile;
	FILE *outfile;
	unsigned long infilelength;
	int offset = 0;
	unsigned char *pointer = 0;
	unsigned char *outpointer = 0;
	unsigned char *paddingpointer = 0;
	int outoffset = 0;
	bool done = false;
	int result;

	int remaining_bits = 8;
	unsigned char input_buffer;
	bool init = true;

}
unsigned char getbits(int number, unsigned char* input, int *offset);
bool getvalue(void);
long EDecomp(char *SrcFile, char *DstFile, long Pointer, bool padding)
{
	// The original code by Nemesis was command line based, so, in order to make as few changes as
	// possible I simply copied the arguments passed to the function into the variable that is used
	// to receive the command line arguments.
	char argv[4][260];
	//	strcpy(argv[1], SrcFile);
	//	strcpy(argv[2], DstFile);
	strcpy(argv[3], "0x");
	_itoa(Pointer, argv[3]+2, 16);

	// I prefered to initialize the following variables before starting the algorithm.
	processed_bits = 0;
	packet_length = 0;
	mode = 0;
	output_repeatcount = 0;
	//	remaining_bits = 0x10;
	bits_remaining_postfunc = 0;
	bitmask = 0;
	input_stream = 0;
	incrementing_value = 0;
	common_value = 0;
	addvalue = 0;
	outvalue = 0;
	offset = 0;
	outoffset = 0;
	done = false;

	remaining_bits = 8;
	init = true;

	// There starts the original code by Nemesis (all Console I/O operations were removed)
	infile = fopen(SrcFile, "rb");
	fseek(infile, 0, SEEK_END);
	infilelength = ftell(infile);
	rewind(infile);
	pointer = (unsigned char *)calloc(infilelength, 0x01);
	outpointer = (unsigned char *)calloc(0x100000, 0x01);
	paddingpointer = (unsigned char *)calloc(0x1000, 0x01);

	fread(pointer, infilelength, 1, infile);

	if(argv[3][1] == 'x')
	{
		loopcount = 2;
	}
	else
	{
		loopcount = 0;
	}
	for(; argv[3][loopcount] != 0x00;loopcount++)
	{
		offset <<= 4;
		if(((argv[3][loopcount] & 0xF0) == 0x40) || ((argv[3][loopcount] & 0xF0) == 0x60))
		{
			offset |= ((argv[3][loopcount] & 0x0F) + 0x09);
		}
		else
		{
			offset |= (argv[3][loopcount] & 0x0F);
		}
	}
	int originaloffset = offset;


	/////////////////////////////////////////////////////////////////////////////////////////
	//Entry point
	packet_length = getbits(8, pointer, &offset);
	bitmask = getbits(8, pointer, &offset);
	incrementing_value = getbits(8, pointer, &offset) << 8;
	incrementing_value |= getbits(8, pointer, &offset);
	common_value = getbits(8, pointer, &offset) << 8;
	common_value |= getbits(8, pointer, &offset);

	/////////////////////////////////////////////////////////////////////////////////////////
	//Main algorithm
	for(;!done;)
	{
		if((getbits(1, pointer, &offset)) == 1)
		{
			mode = getbits(2, pointer, &offset);
			switch(mode)
			{
			case 0:
			case 1:
			case 2:
				{
					output_repeatcount = getbits(4, pointer, &offset);
					getvalue();
					for(;output_repeatcount >= 0; output_repeatcount--)
					{
						*(outpointer + outoffset++) = ((outvalue >> 8) & 0x00FF);
						*(outpointer + outoffset++) = (outvalue & 0x00FF);

						switch(mode)
						{
						case 0:
							break;
						case 1:
							outvalue++;
							break;
						case 2:
							outvalue--;
							break;
						}
					}
					break;
				}
			case 3:
				{
					output_repeatcount = getbits(4, pointer, &offset);
					if(output_repeatcount != 0x0F)
					{
						for(;output_repeatcount >= 0; output_repeatcount--)
						{
							getvalue();
							*(outpointer + outoffset++) = ((outvalue >> 8) & 0x00FF);
							*(outpointer + outoffset++) = (outvalue & 0x00FF);
						}
					}
					else
					{
						done = true;
					}
					break;
				}
			}
		}
		else
		{
			if((getbits(1, pointer, &offset)) == 0)
			{
				output_repeatcount = getbits(4, pointer, &offset);
				for(; output_repeatcount >= 0; output_repeatcount--)
				{
					*(outpointer + outoffset++) = ((incrementing_value >> 8) & 0x00FF);
					*(outpointer + outoffset++) = (incrementing_value & 0x00FF);
					incrementing_value++;
				}
			}
			else
			{
				output_repeatcount = getbits(4, pointer, &offset);
				for(; output_repeatcount >= 0; output_repeatcount--)
				{
					*(outpointer + outoffset++) = ((common_value >> 8) & 0x00FF);
					*(outpointer + outoffset++) = (common_value & 0x00FF);
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	//Output completed file
	outfile = fopen(DstFile, "wb");
	if(padding)
	{
		fwrite(paddingpointer, 0x1000, 1, outfile);
		for(loopcount = 0; loopcount < 0x2000; loopcount += 0x80)
		{
			fwrite(paddingpointer, 0x20, 1, outfile);
			fwrite(outpointer + (loopcount / 2) , 0x40, 1, outfile);
			fwrite(paddingpointer, 0x20, 1, outfile);
		}
		fwrite(paddingpointer, 0x1000, 1, outfile);
	}
	else
	{
		fwrite(outpointer, outoffset, 1, outfile);
	}

	/*printf("Done!\n\n");
	printf("Archive in %s successfully extracted to file %s.\n\n", argv[1], argv[2]);
	printf("Compressed file size:\t\t0x%X\t\t%i\n", (offset - originaloffset), (offset - originaloffset));
	printf("Uncompressed file size:\t\t0x%X\t\t%i\n", ftell(outfile), ftell(outfile));
	printf("Location in file:\t\t0x%X - 0x%X\n", originaloffset, offset);
	printf("Compression rate:\t\t%.2f%%\n\n", (100 - (((float)(offset - originaloffset) / (float)(ftell(outfile))) * 100)));*/

	free(pointer);
	free(outpointer);
	free(paddingpointer);
	fclose(outfile);
	fclose(infile);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//Getvalue function		- This function extracts a 16-bit value from the compressed data.
bool getvalue(void)
{
	addvalue = 0;
	for(loopcount = 0; loopcount < 5; loopcount++)
	{
		if(((bitmask >> (4 - loopcount)) & 0x01) != 0)
		{
			addvalue |= (getbits(1, pointer, &offset) << (0xF - loopcount));
		}
	}

	if(packet_length > 8)
	{
		outvalue = getbits(packet_length - 8, pointer, &offset) << 8;
		outvalue |= getbits(8, pointer, &offset);
	}
	else
	{
		outvalue = getbits(packet_length, pointer, &offset);
	}

	outvalue &= (0xFFFF ^ (0xFFFF << packet_length));
	outvalue += addvalue;
	return true;
}


unsigned char getbits(int number, unsigned char* input, int *offset)
{
	if (init) { input_buffer = *(input + (*offset)++); init = false; }
	unsigned char value = 0;

	if(number > remaining_bits)
	{
		value = input_buffer >> (8 - number);
		input_buffer = *(input + (*offset)++);
		value |= ((input_buffer & (0xFF << (8 - number + remaining_bits))) >> (8 - number + remaining_bits));
		input_buffer <<= (number - remaining_bits);
		remaining_bits = 8 - (number - remaining_bits);
	}
	else
	{
		value = ((input_buffer & (0xFF << (8 - number))) >> (8 - number));
		remaining_bits -= number;
		input_buffer <<= number;
	}

	return value;
}

#endif