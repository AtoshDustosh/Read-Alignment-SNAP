#ifndef SAM_H_INCLUDED
#define SAM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>



/*
 * Flags for the SAM file format; see http://samtools.sourceforge.net/SAM1.pdf for details.
 */

const int SAM_MULTI_SEGMENT      = 0x001; // Read had multiple segments (i.e., paired ends).
const int SAM_ALL_ALIGNED        = 0x002; // All segments of a multi-segment read were aligned.
const int SAM_UNMAPPED           = 0x004; // This segment of the read is unmapped.
const int SAM_NEXT_UNMAPPED      = 0x008; // Next segment of the read is unmapped.
const int SAM_REVERSE_COMPLEMENT = 0x010; // This segment of the read is reverse complemented.
const int SAM_NEXT_REVERSED      = 0x020; // Next segment of the read is reverse complemented.
const int SAM_FIRST_SEGMENT      = 0x040; // This is the first segment in the read.
const int SAM_LAST_SEGMENT       = 0x080; // This is the last segment in the read.
const int SAM_SECONDARY          = 0x100; // Secondary alignment for a read with multiple hits.
const int SAM_FAILED_QC          = 0x200; // Not passing quality controls.
const int SAM_DUPLICATE          = 0x400; // PCR or optical duplicate.
const int SAM_SUPPLEMENTARY      = 0x800; // Supplementary alignment








#endif // SAM_H_INCLUDED
