/*
 * Copyright (C) 1990-2018 Andreas Kromke, andreas.kromke@gmail.com
 *
 * This program is free software; you can redistribute it or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/*
*
* Zeichensatz-Umsetzung f�r MagicMacX
*
*/

#include "config.h"
// System-Header
#include <Carbon/Carbon.h>
#include <machine/endian.h>
// Programm-Header
#include "Globals.h"
#include "Resource.h"
#include "Debug.h"
#include "TextConversion.h"

// statische Attribute:

// data 'HEXA' (131, "Text ATARI->Mac")
unsigned const char CTextConversion::s_tabAtari2MacText[256] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, /* .........��..... */
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, /* ................ */
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, /*  !"#$%&'()*+,-./ */
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, /* 0123456789:;<=>? */
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, /* @ABCDEFGHIJKLMNO */
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, /* PQRSTUVWXYZ[\]^_ */
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, /* `abcdefghijklmno */
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, /* pqrstuvwxyz{|}~. */
	0x82, 0x9F, 0x8E, 0x89, 0x8A, 0x88, 0x8C, 0x8D, 0x90, 0x91, 0x8F, 0x95, 0x94, 0x93, 0x80, 0x81, /* ���������������� */
	0x83, 0xBE, 0xAE, 0x99, 0x9A, 0x98, 0x9E, 0x9D, 0xD8, 0x85, 0x86, 0xA2, 0xA3, 0xB4, 0xA7, 0xC4, /* ��������؅������ */
	0x87, 0x92, 0x97, 0x9C, 0x96, 0x84, 0xBB, 0xBC, 0xC0, 0x2A, 0xC2, 0x2A, 0x2A, 0xC1, 0xC7, 0xC8, /* ���������*�**��� */
	0x8B, 0x9B, 0xAF, 0xBF, 0xCF, 0xCE, 0xCB, 0xCC, 0xCD, 0xAC, 0xAB, 0xA0, 0xA6, 0xA9, 0xA8, 0xAA, /* ��������ͬ������ */
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, /* **************** */
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0xA4, 0x5E, 0xB0, /* *************�^� */
	0x2A, 0xA7, 0x2A, 0xB9, 0xB7, 0x2A, 0xB5, 0x2A, 0x2A, 0x2A, 0xBD, 0xB6, 0x2A, 0x2A, 0x2A, 0x2A, /* *�*��*�***��**** */
	0x2A, 0xB1, 0xB3, 0xB2, 0xBA, 0xBA, 0xD6, 0xC5, 0xFB, 0xFA, 0xA5, 0xC3, 0x2A, 0x2A, 0x2A, 0xF8  /* *�����������***� */
};

// data 'HEXA' (130, "Text Mac->ATARI")
unsigned const char CTextConversion::s_tabMac2AtariText[256] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, /* .........��..... */
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, /* ................ */
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, /*  !"#$%&'()*+,-./ */
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, /* 0123456789:;<=>? */
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, /* @ABCDEFGHIJKLMNO */
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, /* PQRSTUVWXYZ[\]^_ */
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, /* `abcdefghijklmno */
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, /* pqrstuvwxyz{|}~. */
	0x8E, 0x8F, 0x80, 0x90, 0xA5, 0x99, 0x9A, 0xA0, 0x85, 0x83, 0x84, 0xB0, 0x86, 0x87, 0x82, 0x8A, /* ���������������� */
	0x88, 0x89, 0xA1, 0x8D, 0x8C, 0x8B, 0xA4, 0xA2, 0x95, 0x93, 0x94, 0xB1, 0xA3, 0x97, 0x96, 0x81, /* ���������������� */
	0xBB, 0xF8, 0x9B, 0x9C, 0xDD, 0xF9, 0xBC, 0x9E, 0xBE, 0xBD, 0xBF, 0xBA, 0xB9, 0x2A, 0x92, 0xB2, /* �������������*�� */
	0xDF, 0xF1, 0xF3, 0xF2, 0x9D, 0xE6, 0xEB, 0xE4, 0x2A, 0xE3, 0xF4, 0xA6, 0xA7, 0xEA, 0x91, 0xB3, /* �������*����ꑳ */
	0xA8, 0xAD, 0xAA, 0xFB, 0x9F, 0xF7, 0x7F, 0xAE, 0xAF, 0x2A, 0x2A, 0xB6, 0xB7, 0xB8, 0xB5, 0xB4, /* ������.��**����� */
	0x2D, 0x2D, 0x22, 0x22, 0xBA, 0xBA, 0xF6, 0x2A, 0x98, 0x59, 0x2F, 0x2A, 0x3C, 0x3E, 0x2A, 0x2A, // --""���*�Y/*<>**
	0x2A, 0xFA, 0x2C, 0x22, 0x2A, 0x41, 0x45, 0x41, 0x45, 0x45, 0x49, 0x49, 0x49, 0x49, 0x4F, 0x4F, /* *�,"*AEAEEIIIIOO */
	0x2A, 0x4F, 0x55, 0x55, 0x55, 0x69, 0x5E, 0x7E, 0xFF, 0x2A, 0xF9, 0xF8, 0x2C, 0x22, 0x2C, 0x2A  /* *OUUUi^~�*��,",* */
};

// data 'HEXA' (129, "Filename ATARI->Mac")
unsigned const char CTextConversion::s_tabAtari2MacFilename[256] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, /* .........��..... */
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, /* ................ */
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, /*  !"#$%&'()*+,-./ */
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, /* 0123456789:;<=>? */
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, /* @ABCDEFGHIJKLMNO */
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, /* PQRSTUVWXYZ[\]^_ */
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, /* `abcdefghijklmno */
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0xC6, /* pqrstuvwxyz{|}~� */
	0x82, 0x9F, 0x8E, 0x89, 0x8A, 0x88, 0x8C, 0x8D, 0x90, 0x91, 0x8F, 0x95, 0x94, 0x93, 0x80, 0x81, /* ���������������� */
	0x83, 0xBE, 0xAE, 0x99, 0x9A, 0x98, 0x9E, 0x9D, 0xD8, 0x85, 0x86, 0xA2, 0xA3, 0xB4, 0xA7, 0xC4, /* ��������؅������ */
	0x87, 0x92, 0x97, 0x9C, 0x96, 0x84, 0xBB, 0xBC, 0xC0, 0x7F, 0xC2, 0xAD, 0xB6, 0xC1, 0xC7, 0xC8, /* ���������.­���� */
	0x8B, 0x9B, 0xAF, 0xBF, 0xCF, 0xCE, 0xCB, 0xCC, 0xCD, 0xAC, 0xAB, 0xA0, 0xA6, 0xA9, 0xA8, 0xAA, /* ��������ͬ������ */
	0xE5, 0xE7, 0xE6, 0xE8, 0xE9, 0xEB, 0xEC, 0xED, 0xEA, 0xEF, 0xF1, 0xEE, 0xF3, 0xF4, 0xF2, 0xE3, /* ���������������� */
	0xD2, 0xD3, 0xE2, 0xD4, 0xDC, 0xDD, 0xD0, 0xD1, 0xD5, 0xC9, 0xCA, 0xD7, 0xD9, 0xA4, 0xE4, 0xB0, /* ������������٤� */
	0xDA, 0xDB, 0xDE, 0xB9, 0xB7, 0xDF, 0xB5, 0xE0, 0xF0, 0xF5, 0xBD, 0xF6, 0xBA, 0xF7, 0xF9, 0xB8, /* ��޹�ߵ��������� */
	0xFA, 0xB1, 0xB3, 0xB2, 0xFB, 0xFC, 0xD6, 0xC5, 0xA1, 0xA5, 0xE1, 0xC3, 0xFD, 0xFE, 0xFF, 0xF8  /* �������š������� */
};

//data 'HEXA' (128, "Filename Mac->ATARI")
unsigned const char CTextConversion::s_tabMac2AtariFilename[256] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, /* .........��..... */
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, /* ................ */
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, /*  !"#$%&'()*+,-./ */
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, /* 0123456789:;<=>? */
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, /* @ABCDEFGHIJKLMNO */
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, /* PQRSTUVWXYZ[\]^_ */
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, /* `abcdefghijklmno */
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0xA9, /* pqrstuvwxyz{|}~� */
	0x8E, 0x8F, 0x80, 0x90, 0xA5, 0x99, 0x9A, 0xA0, 0x85, 0x83, 0x84, 0xB0, 0x86, 0x87, 0x82, 0x88, /* ���������������� */
	0x8A, 0x89, 0xA1, 0x8D, 0x8C, 0x8B, 0xA4, 0xA2, 0x95, 0x93, 0x94, 0xB1, 0xA3, 0x97, 0x96, 0x81, /* ���������������� */
	0xBB, 0xF8, 0x9B, 0x9C, 0xDD, 0xF9, 0xBC, 0x9E, 0xBE, 0xBD, 0xBF, 0xBA, 0xB9, 0xAB, 0x92, 0xB2, /* ���������������� */
	0xDF, 0xF1, 0xF3, 0xF2, 0x9D, 0xE6, 0xAC, 0xE4, 0xEF, 0xE3, 0xEC, 0xA6, 0xA7, 0xEA, 0x91, 0xB3, /* ��������즧ꑳ */
	0xA8, 0xAD, 0xAA, 0xFB, 0x9F, 0xF7, 0x7F, 0xAE, 0xAF, 0xD9, 0xDA, 0xB6, 0xB7, 0xB8, 0xB5, 0xB4, /* ������.���ڶ���� */
	0xD6, 0xD7, 0xD0, 0xD1, 0xD3, 0xD8, 0xF6, 0xDB, 0x98, 0xDC, 0xE0, 0xE1, 0xD4, 0xD5, 0xE2, 0xE5, /* �������ۘ������� */
	0xE7, 0xFA, 0xD2, 0xCF, 0xDE, 0xC0, 0xC2, 0xC1, 0xC3, 0xC4, 0xC8, 0xC5, 0xC6, 0xC7, 0xCB, 0xC9, /* ���������������� */
	0xE8, 0xCA, 0xCE, 0xCC, 0xCD, 0xE9, 0xEB, 0xED, 0xFF, 0xEE, 0xF0, 0xF4, 0xF5, 0xFC, 0xFD, 0xFE  /* ���������������� */
};



/**********************************************************************
*
* statisch: Initialisieren
*
**********************************************************************/

int CTextConversion::Init(void)
{
	return(0);
}


/**********************************************************************
*
* statisch: Dateinamen konvertieren Atari -> Mac
*
**********************************************************************/
/*
void CTextConversion::Atari2MacFilename(unsigned char *s)
{
	short i = *s++;		// L�nge
	while(i)
	{
		*s = s_tabAtari2MacFilename[*s];
		s++;
		i--;
	}
}
*/

unsigned char CTextConversion::Atari2MacFilename(unsigned char c)
{
	return(s_tabAtari2MacFilename[c]);
}


/**********************************************************************
*
* statisch: Dateinamen konvertieren Mac -> Atari
*
**********************************************************************/
/*
void CTextConversion::Mac2AtariFilename(unsigned char *s)
{
	short i = *s++;
	while(i)
	{
		*s = s_tabMac2AtariFilename[*s];
		s++;
		i--;
	}
}
*/

unsigned char CTextConversion::Mac2AtariFilename(unsigned char c)
{
	return(s_tabMac2AtariFilename[c]);
}


/**********************************************************************
*
* statisch: Text konvertieren Atari -> Mac
*
**********************************************************************/

unsigned char CTextConversion::Atari2MacText(unsigned char c)
{
	return(s_tabAtari2MacText[c]);
}


/**********************************************************************
*
* statisch: Text konvertieren Mac -> Atari
*
**********************************************************************/

unsigned char CTextConversion::Mac2AtariText(unsigned char c)
{
	return(s_tabMac2AtariText[c]);
}