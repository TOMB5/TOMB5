#include "MEMCARD.H"

#include "SPECIFIC.H"

#include <LIBMCRD.H>

unsigned char mcInit;
unsigned char mcStatus;
unsigned long mcNumFiles;
unsigned char mcBlocksFree;
char mcFileNames[7][20];
int mcFileLengths[7];
static unsigned char mcActualStatus;

int dword_A1AA0 = 0x2A;//init me 0x2a? looks like name string

void mcDir()//61EE8
{
	int i; // $s3
	int j; // $s4
	int k; // $s1
	struct DIRENTRY* dir;// $s2

#if 0
	int a0 = 0;
	int a1 = dword_A1AA0;
				 
				
	//lui	$v0, 0x001F0000
	//sw	$s2, 0x30 + var_10($sp)
	struct TSV* a2 = &tsv_buffer[0];
	
	//sw	$s0, 0x30 + var_18($sp)
	int s0 = 0xF;
	a3 = &mcNumFiles;
	//sw	$ra, 0x30 + var_4($sp)
	//sw	$s4, 0x30 + var_8($sp)
	//sw	$s3, 0x30 + var_C($sp)
	//sw	$s1, 0x30 + var_14($sp)
	//sw	$zero, 0x30 + var_20($sp)
				
	MemCardGetDirentry(0, dword_A1AA0, &tsv_buffer[0], &mcNumFiles, 0, 0);//	jal	sub_6B08C
	//sw	$s0, 0x30 + var_1C($sp)
	int s4 = 0;//j
	int s3 = 0;//i
	
	lw	$v0, 0x41E0($gp)
	sb	$s0, 0x41DC($gp)
	beqz	$v0, loc_62028
	move	$s1, $zero
	move	$s0, $s2
	addiu	$s2, $gp, 0x41E4

				 loc_61F50:
			 lw	$v0, 0x18($s0)
				 nop
				 addiu	$v1, $v0, 0x1FFF
				 bgez	$v1, loc_61F68
				 move	$a1, $s0
				 addiu	$v1, $v0, 0x3FFE

				 loc_61F68:
			 sra	$v1, 13
				 lbu	$v0, 0x41DC($gp)
				 lw	$a0, dword_800A202C
				 subu	$v0, $v1
				 sb	$v0, 0x41DC($gp)
				 lhu	$v1, 0x194($a0)
				 lw	$a0, dword_800A203C
				 li	$a2, 0xC
				 jal	sub_68A84
				 addu	$a0, $v1
				 bnez	$v0, loc_62014
				 nop
				 lwl	$v0, 3($s0)
				 lwr	$v0, 0($s0)
				 lwl	$v1, 7($s0)
				 lwr	$v1, 4($s0)
				 lwl	$a0, 0xB($s0)
				 lwr	$a0, 8($s0)
				 lwl	$a1, 0xF($s0)
				 lwr	$a1, 0xC($s0)
				 swl	$v0, 3($s2)
				 swr	$v0, 0($s2)
				 swl	$v1, 7($s2)
				 swr	$v1, 4($s2)
				 swl	$a0, 0xB($s2)
				 swr	$a0, 8($s2)
				 swl	$a1, 0xF($s2)
				 swr	$a1, 0xC($s2)
				 lwl	$v0, 0x13($s0)
				 lwr	$v0, 0x10($s0)
				 nop
				 swl	$v0, 0x13($s2)
				 swr	$v0, 0x10($s2)
				 addiu	$s2, 0x14
				 sll	$v0, $s4, 2
				 addiu	$s4, 1
				 addiu	$s1, 1
				 addiu	$v1, $gp, 0x4274
				 lw	$a0, 0x18($s0)
				 addu	$v0, $v1
				 sw	$a0, 0($v0)

				 loc_62014:
			 lw	$v0, 0x41E0($gp)
				 addiu	$s3, 1
				 sltu	$v0, $s3, $v0
				 bnez	$v0, loc_61F50
				 addiu	$s0, 0x28

				 loc_62028 :
				 lw	$ra, 0x30 + var_4($sp)
				 lw	$s4, 0x30 + var_8($sp)
				 lw	$s3, 0x30 + var_C($sp)
				 lw	$s2, 0x30 + var_10($sp)
				 sw	$s1, 0x41E0($gp)
				 lw	$s1, 0x30 + var_14($sp)
				 lw	$s0, 0x30 + var_18($sp)
				 jr	$ra
				 addiu	$sp, 0x30
				 # End of function sub_61EE8
#endif

}

void mcOpen(int sync)//6204C(<), 62730(<) (F)
{
	int i;

	mcInit = 1;
	mcNumFiles = 0;
	mcBlocksFree = 0;
	mcStatus = 4;
	mcActualStatus = 0;

	MemCardStart();

	if (sync != 0)
	{
		for (i = 0; i < 4; i++)
		{
			//loc_62084
			mcGetStatus();
			VSync(0);
		}
	}

	//loc_6209C
	return;
}

void mcClose()//620AC
{
	MemCardStop();
	mcInit = 0;
	
	return;
}

unsigned char mcGetStatus()//620CC(<), ? (F)
{
	long stat;
	unsigned long cmd;
	unsigned long res;

	stat = MemCardSync(1, &cmd, &res);
	
	//Locked, Asynchronous memory card function is running.
	if (stat == 0)
	{
		//loc_62130
		if(cmd == McFuncReadFile)
		{
			return mcStatus = 5;
		}
		else if(cmd == McFuncWriteData)
		{
			//loc_62150
			return mcStatus = 6;
		}
		else if(cmd == McFuncAccept)
		{
			//loc_62164
			return mcStatus = 4;
		}
	}
	else if(stat > 0)
	{
		//loc_62110
		if(stat == 1)
		{
			//loc_62178
			if(cmd == McFuncAccept)
			{
				//loc_62210
				if(res == 3)
				{
					//loc_62248
					mcDir();
					mcActualStatus = 0;
					mcStatus = 0;
				}
				else if(res > 3)
				{
					//loc_62238
					if(res == 4)
					{
						//loc_6225C
						mcActualStatus = mcStatus = cmd;
					}
					else
					{
						mcActualStatus = mcStatus = 3;
					}
				}
				else if(res == 0)
				{
					//loc_6228C
					mcStatus = 0;
				}
				else
				{
					mcActualStatus = mcStatus = 3;
				}
				
				return 3;
			}
			else if(cmd > McFuncAccept)
			{
				//loc_621A0
				if(cmd == McFuncReadFile)
				{
					//loc_6227C
					if(res != 0)
					{
						//loc_622B8
						MemCardAccept(0);
						mcStatus = 3;
					}
					else
					{
						//loc_6228C
						mcStatus = 0;
					}
					
					return res;
				}
				else if(cmd == McFuncWriteData)
				{
					//loc_62298
					if(res != 0)
					{
						MemCardAccept(0);
						mcStatus = 3;
					}
					else
					{
						mcStatus = 0;
					}
					
					return res;
				}
				
				return 6;
			}
			else if(cmd == stat)
			{
				//loc_621B8
				if(res == 0)
				{
					//loc_621D8
					return mcStatus = mcActualStatus;
				}
				else if(res == 3)
				{
					//loc_621EC
					MemCardAccept(0);
					mcStatus = 4;
					return 1;
				}
				else
				{
					//loc_62204
					mcStatus = 1;
					return 1;
				}
			}
		}
		
		return 2;
	}
	else if(stat == -1)
	{
		//loc_62120
		MemCardExist(0);
	}
	
	return -1;
}

long mcFormat()//622D8(<), 629BC(<) (F)
{
	unsigned long cmd;
	unsigned long res;

	MemCardSync(0, &cmd, &res);

	res = MemCardFormat(0);
	if (res == 0)
	{
		mcActualStatus = 0;
		mcDir();
	}

	//loc_6230C
	return res;
}