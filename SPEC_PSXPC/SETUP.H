#ifndef SETUP_H
#define SETUP_H

//FIXME: Not same as original
#define SETUP_MOD_FILE_SIZE (42012)
extern char setupBuff[SETUP_MOD_FILE_SIZE];

struct PSXHeader
{
	unsigned int version;
	unsigned int unk00;
	unsigned int unk01;
	unsigned int unk03;

	unsigned int unk04;
	unsigned int unk05;
	unsigned int unk06;
	unsigned int unk07;

	unsigned int unk08;
	unsigned int unk09;
	unsigned int soundWadSize;
	unsigned int unk11;

	unsigned short unk12;
	unsigned short unk12_0;
	unsigned int unk13;
	unsigned int unk14;
	unsigned int unk15;

	unsigned int unk16;
	unsigned int unk17;
	unsigned int unk18;
	unsigned int unk19;

	unsigned int unk20;
	unsigned int unk21;
	unsigned int unk22;
	unsigned int unk23;

	unsigned int unk24;
	unsigned int unk25;
	unsigned int unk26;
	unsigned int unk27;

	unsigned int unk28;
	unsigned int unk29;
	unsigned int unk30;
	unsigned int unk31;

	unsigned int unk32;
	unsigned int unk33;
	unsigned int unk34;
	unsigned int unk35;

	unsigned int unk36;
	unsigned int unk37;
	unsigned int unk38;
	unsigned int unk39;

	unsigned int unk40;
	unsigned int unk41;
	unsigned int unk42;
	unsigned int unk43;

	unsigned int unk44;
	unsigned int unk45;
	unsigned int unk46;
	unsigned int unk47;

	unsigned int unk48;
	unsigned int unk49;
	unsigned int unk50;
	unsigned int unk51;

	unsigned int unk52;
	unsigned int unk53;
	unsigned int unk54;
	unsigned int unk55;

	unsigned int unk56;
};

void sub_B3B50();
void sub_B3974(struct PSXHeader* psxHeader, char* ptr);
#endif