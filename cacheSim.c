


#define AMAX 10			/* Maximum (square) array size */

#define CACHESIM 1		/* Set to 1 if simulating Cache */
#define ADDSIZE 32
#define BYTESPERBLOCK 4

#define ONESIX 0xF
#define TWOSIX 0x7
#define FOURSIX 0x3
#define ONEFIFTYSIX 0xFF
#define TWOFIFTYSIX 0x7F
#define FOURFIFTYSIX 0x3F

#define MIN(a,b) ((a) < (b) ? a : b)

#include <stdio.h>
#include <stdlib.h>

typedef struct cblock {
   unsigned int tag;
   unsigned int data;
   int valid;
   int age;
} cBlock;

static cBlock *cacheA;
static cBlock *cacheB;
static cBlock *cacheC;
static cBlock *cacheD;

static int cacheSize, assoc;
static float hits, misses, writes, reads;

/*	memory management, code density, Cache emulation - statistics generation */
/*	Generated for CSC 315 Lab 5 */


/* This function gets called with each "read" reference to memory */

void mem_read(int *mp) {
   int idx, tag, found = 0, count, temp;
   
   if (cacheSize == 16) {
      if (assoc == 1) {
         idx = (int)mp & ONESIX;
         tag = (int)mp >> 4;
         
         if(cacheA[idx].valid) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		cacheA[idx].age = 1000;

         		for (count = 0; count < 16 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 16 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         	}
         	else {
         		misses++;
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         }
         else {
         	misses++;
         	cacheA[idx].tag = tag;
         	cacheA[idx].data = *mp;
         	cacheA[idx].valid = 1;
         	cacheA[idx].age = 1000;
         }
      }
      else if (assoc == 2) {
         idx = (int)mp & TWOSIX;
         tag = (int)mp >> 3;

         if (cacheA[idx].valid && found == 0) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		cacheA[idx].age = 1000;
         		found = 1;

         		for (count = 0; count < 8 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 8 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 8; count++) {
         			cacheB[count].age--;
         		}
         	}
         }
         if (cacheB[idx].valid && found == 0) {
         	if (cacheB[idx].tag == tag) {
         		hits++;
         		cacheB[idx].age = 1000;
         		found = 1;

         		for (count = 0; count < 8; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 8 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = idx + 1; count < 8 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         	}
         }
         if (found == 0) {
         	misses++;
         	if (cacheA[idx].age > cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         	}
         	else {
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         }
      }
      else if (assoc == 4) {
         idx = (int)mp & FOURSIX;
         tag = (int)mp >> 2;

         if (cacheA[idx].valid) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheA[idx].age = 1000;

         		for (count = 0; count < 4 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 4 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheD[count].age--;
         		}
         	}
         }
         if (cacheB[idx].valid && found == 0) {
         	if (cacheB[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheB[idx].age = 1000;

         		for (count = 0; count < 4; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 4 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = idx + 1; count < 4 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheD[count].age--;
         		}
         	}
         }
         if (cacheC[idx].valid && found == 0) {
         	if (cacheC[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheC[idx].age = 1000;

         		for (count = 0; count < 4; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 4 && count != idx; count++) {
         			cacheC[count].age--;
         		}
         		for (count = idx + 1; count < 4 && count != idx; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheD[count].age--;
         		}
         	}
         }
         if (cacheD[idx].valid && found == 0) {
         	if (cacheD[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheD[idx].age = 1000;

         		for (count = 0; count < 4; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 4 && count != idx; count++) {
         			cacheD[count].age--;
         		}
         		for (count = idx + 1; count < 4 && count != idx; count++) {
         			cacheD[count].age--;
         		}
         	}
         }
         if (found == 0) {
         	misses++;
         	temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         	if (temp == cacheA[idx].age) {
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         	else if (temp == cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         	}
         	else if (temp == cacheC[idx].age) {
         		cacheC[idx].tag = tag;
         		cacheC[idx].data = *mp;
         		cacheC[idx].valid = 1;
         		cacheC[idx].age = 1000;
         	}
         	else {
         		cacheD[idx].tag = tag;
         		cacheD[idx].data = *mp;
         		cacheD[idx].valid = 1;
         		cacheD[idx].age = 1000;
         	}
         }
      }
   }
   else {
      if (assoc == 1) {
         idx = (int)mp & ONEFIFTYSIX;
         tag = (int)mp >> 8;

         if(cacheA[idx].valid) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		cacheA[idx].age = 1000;

         		for (count = 0; count < 256 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 256; count++) {
         			cacheA[count].age--;
         		}
         	}
         	else {
         		misses++;
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         }
         else {
         	misses++;
         	cacheA[idx].tag = tag;
         	cacheA[idx].data = *mp;
         	cacheA[idx].valid = 1;
         	cacheA[idx].age = 1000;
         }
      }
      else if (assoc == 2) {
         idx = (int)mp & TWOFIFTYSIX;
         tag = (int)mp >> 7;

         if (cacheA[idx].valid && found == 0) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		cacheA[idx].age = 1000;
         		found = 1;

         		for (count = 0; count < 128 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 128 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 128; count++) {
         			cacheB[count].age--;
         		}
         	}
         }
         if (cacheB[idx].valid && found == 0) {
         	if (cacheB[idx].tag == tag) {
         		hits++;
         		cacheB[idx].age = 1000;
         		found = 1;

         		for (count = 0; count < 128; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 128 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = idx + 1; count < 128 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         	}
         }
         if (found == 0) {
         	misses++;
         	if (cacheA[idx].age > cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         	}
         	else {
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         }
      }
      else if (assoc == 4) {
         idx = (int)mp & FOURFIFTYSIX;
         tag = (int)mp >> 6;

         if (cacheA[idx].valid) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheA[idx].age = 1000;

         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 64 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheD[count].age--;
         		}
         	}
         }
         if (cacheB[idx].valid && found == 0) {
         	if (cacheB[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheB[idx].age = 1000;

         		for (count = 0; count < 64; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = idx + 1; count < 64 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheD[count].age--;
         		}
         	}
         }
         if (cacheC[idx].valid && found == 0) {
         	if (cacheC[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheC[idx].age = 1000;

         		for (count = 0; count < 64; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheC[count].age--;
         		}
         		for (count = idx + 1; count < 64 && count != idx; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheD[count].age--;
         		}
         	}
         }
         if (cacheD[idx].valid && found == 0) {
         	if (cacheD[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheD[idx].age = 1000;

         		for (count = 0; count < 64; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheD[count].age--;
         		}
         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheD[count].age--;
         		}
         	}
         }
         if (found == 0) {
         	misses++;
         	temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         	if (temp == cacheA[idx].age) {
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         	else if (temp == cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         	}
         	else if (temp == cacheC[idx].age) {
         		cacheC[idx].tag = tag;
         		cacheC[idx].data = *mp;
         		cacheC[idx].valid = 1;
         		cacheC[idx].age = 1000;
         	}
         	else {
         		cacheD[idx].tag = tag;
         		cacheD[idx].data = *mp;
         		cacheD[idx].valid = 1;
         		cacheD[idx].age = 1000;
         	}
         }
      }
   }
   reads++;
	//printf("Memory read from location %p\n", mp);

}


/* This function gets called with each "write" reference to memory */

mem_write(int *mp)
	{

	//printf("Memory write to location %p\n", mp);
		int idx, tag, found = 0, count, temp;
		writes++;

		if (cacheSize == 16) {
      if (assoc == 1) {
         idx = (int)mp & ONESIX;
         tag = (int)mp >> 4;
         
         if(cacheA[idx].valid) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		cacheA[idx].age = 1000;

         		for (count = 0; count < 16 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 16 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         	else {
         		misses++;
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         }
         else {
         	misses++;
         	cacheA[idx].tag = tag;
         	cacheA[idx].data = *mp;
         	cacheA[idx].valid = 1;
         	cacheA[idx].age = 1000;
         }
      }
      else if (assoc == 2) {
         idx = (int)mp & TWOSIX;
         tag = (int)mp >> 3;

         if (cacheA[idx].valid && found == 0) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		cacheA[idx].age = 1000;
         		found = 1;

         		for (count = 0; count < 8 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 8 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 8; count++) {
         			cacheB[count].age--;
         		}
         		if (cacheA[idx].age > cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         	}
         }
         if (cacheB[idx].valid && found == 0) {
         	if (cacheB[idx].tag == tag) {
         		hits++;
         		cacheB[idx].age = 1000;
         		found = 1;

         		for (count = 0; count < 8; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 8 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = idx + 1; count < 8 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		if (cacheA[idx].age > cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         	}
         }
         if (found == 0) {
         	misses++;
         	if (cacheA[idx].age > cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         	}
         	else {
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         }
      }
      else if (assoc == 4) {
         idx = (int)mp & FOURSIX;
         tag = (int)mp >> 2;

         if (cacheA[idx].valid) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheA[idx].age = 1000;

         		for (count = 0; count < 4 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 4 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheD[count].age--;
         		}

         		temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         		if (temp == cacheA[idx].age) {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         		else if (temp == cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else if (temp == cacheC[idx].age) {
         			cacheC[idx].tag = tag;
         			cacheC[idx].data = *mp;
         			cacheC[idx].valid = 1;
         			cacheC[idx].age = 1000;
         		}
         		else {
         			cacheD[idx].tag = tag;
         			cacheD[idx].data = *mp;
         			cacheD[idx].valid = 1;
         			cacheD[idx].age = 1000;
         		}
         	}
         }
         if (cacheB[idx].valid && found == 0) {
         	if (cacheB[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheB[idx].age = 1000;

         		for (count = 0; count < 4; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 4 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = idx + 1; count < 4 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheD[count].age--;
         		}

         		temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         		if (temp == cacheA[idx].age) {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         		else if (temp == cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else if (temp == cacheC[idx].age) {
         			cacheC[idx].tag = tag;
         			cacheC[idx].data = *mp;
         			cacheC[idx].valid = 1;
         			cacheC[idx].age = 1000;
         		}
         		else {
         			cacheD[idx].tag = tag;
         			cacheD[idx].data = *mp;
         			cacheD[idx].valid = 1;
         			cacheD[idx].age = 1000;
         		}
         	}
         }
         if (cacheC[idx].valid && found == 0) {
         	if (cacheC[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheC[idx].age = 1000;

         		for (count = 0; count < 4; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 4 && count != idx; count++) {
         			cacheC[count].age--;
         		}
         		for (count = idx + 1; count < 4 && count != idx; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheD[count].age--;
         		}

         		temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         		if (temp == cacheA[idx].age) {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         		else if (temp == cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else if (temp == cacheC[idx].age) {
         			cacheC[idx].tag = tag;
         			cacheC[idx].data = *mp;
         			cacheC[idx].valid = 1;
         			cacheC[idx].age = 1000;
         		}
         		else {
         			cacheD[idx].tag = tag;
         			cacheD[idx].data = *mp;
         			cacheD[idx].valid = 1;
         			cacheD[idx].age = 1000;
         		}
         	}
         }
         if (cacheD[idx].valid && found == 0) {
         	if (cacheD[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheD[idx].age = 1000;

         		for (count = 0; count < 4; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 4; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 4 && count != idx; count++) {
         			cacheD[count].age--;
         		}
         		for (count = idx + 1; count < 4 && count != idx; count++) {
         			cacheD[count].age--;
         		}

         		temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         		if (temp == cacheA[idx].age) {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         		else if (temp == cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else if (temp == cacheC[idx].age) {
         			cacheC[idx].tag = tag;
         			cacheC[idx].data = *mp;
         			cacheC[idx].valid = 1;
         			cacheC[idx].age = 1000;
         		}
         		else {
         			cacheD[idx].tag = tag;
         			cacheD[idx].data = *mp;
         			cacheD[idx].valid = 1;
         			cacheD[idx].age = 1000;
         		}
         	}
         }
         if (found == 0) {
         	misses++;
         	temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         	if (temp == cacheA[idx].age) {
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         	else if (temp == cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         	}
         	else if (temp == cacheC[idx].age) {
         		cacheC[idx].tag = tag;
         		cacheC[idx].data = *mp;
         		cacheC[idx].valid = 1;
         		cacheC[idx].age = 1000;
         	}
         	else {
         		cacheD[idx].tag = tag;
         		cacheD[idx].data = *mp;
         		cacheD[idx].valid = 1;
         		cacheD[idx].age = 1000;
         	}
         }
      }
   }
   else {
      if (assoc == 1) {
         idx = (int)mp & ONEFIFTYSIX;
         tag = (int)mp >> 8;

         if(cacheA[idx].valid) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		cacheA[idx].age = 1000;

         		for (count = 0; count < 256 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 256; count++) {
         			cacheA[count].age--;
         		}
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         		}
         	else {
         		misses++;
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         }
         else {
         	misses++;
         	cacheA[idx].tag = tag;
         	cacheA[idx].data = *mp;
         	cacheA[idx].valid = 1;
         	cacheA[idx].age = 1000;
         }
      }
      else if (assoc == 2) {
         idx = (int)mp & TWOFIFTYSIX;
         tag = (int)mp >> 7;

         if (cacheA[idx].valid && found == 0) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		cacheA[idx].age = 1000;
         		found = 1;

         		for (count = 0; count < 128 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 128 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 128; count++) {
         			cacheB[count].age--;
         		}
         		if (cacheA[idx].age > cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         		}
         		else {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         	}
         }
         if (cacheB[idx].valid && found == 0) {
         	if (cacheB[idx].tag == tag) {
         		hits++;
         		cacheB[idx].age = 1000;
         		found = 1;

         		for (count = 0; count < 128; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 128 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = idx + 1; count < 128 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		if (cacheA[idx].age > cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         		}
         		else {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         	}
         }
         if (found == 0) {
         	misses++;
         	if (cacheA[idx].age > cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         	}
         	else {
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         }
      }
      else if (assoc == 4) {
         idx = (int)mp & FOURFIFTYSIX;
         tag = (int)mp >> 6;

         if (cacheA[idx].valid) {
         	if (cacheA[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheA[idx].age = 1000;

         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = idx + 1; count < 64 && count != idx; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheD[count].age--;
         		}

         		temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         		if (temp == cacheA[idx].age) {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         		else if (temp == cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else if (temp == cacheC[idx].age) {
         			cacheC[idx].tag = tag;
         			cacheC[idx].data = *mp;
         			cacheC[idx].valid = 1;
         			cacheC[idx].age = 1000;
         		}
         		else {
         			cacheD[idx].tag = tag;
         			cacheD[idx].data = *mp;
         			cacheD[idx].valid = 1;
         			cacheD[idx].age = 1000;
         		}
         	}
         }
         if (cacheB[idx].valid && found == 0) {
         	if (cacheB[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheB[idx].age = 1000;

         		for (count = 0; count < 64; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = idx + 1; count < 64 && count != idx; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheD[count].age--;
         		}

         		temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         		if (temp == cacheA[idx].age) {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         		else if (temp == cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else if (temp == cacheC[idx].age) {
         			cacheC[idx].tag = tag;
         			cacheC[idx].data = *mp;
         			cacheC[idx].valid = 1;
         			cacheC[idx].age = 1000;
         		}
         		else {
         			cacheD[idx].tag = tag;
         			cacheD[idx].data = *mp;
         			cacheD[idx].valid = 1;
         			cacheD[idx].age = 1000;
         		}
         	}
         }
         if (cacheC[idx].valid && found == 0) {
         	if (cacheC[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheC[idx].age = 1000;

         		for (count = 0; count < 64; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheC[count].age--;
         		}
         		for (count = idx + 1; count < 64 && count != idx; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheD[count].age--;
         		}

         		temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         		if (temp == cacheA[idx].age) {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         		else if (temp == cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else if (temp == cacheC[idx].age) {
         			cacheC[idx].tag = tag;
         			cacheC[idx].data = *mp;
         			cacheC[idx].valid = 1;
         			cacheC[idx].age = 1000;
         		}
         		else {
         			cacheD[idx].tag = tag;
         			cacheD[idx].data = *mp;
         			cacheD[idx].valid = 1;
         			cacheD[idx].age = 1000;
         		}
         	}
         }
         if (cacheD[idx].valid && found == 0) {
         	if (cacheD[idx].tag == tag) {
         		hits++;
         		found = 1;
         		cacheD[idx].age = 1000;

         		for (count = 0; count < 64; count++) {
         			cacheA[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheB[count].age--;
         		}
         		for (count = 0; count < 64; count++) {
         			cacheC[count].age--;
         		}
         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheD[count].age--;
         		}
         		for (count = 0; count < 64 && count != idx; count++) {
         			cacheD[count].age--;
         		}

         		temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         		if (temp == cacheA[idx].age) {
         			cacheA[idx].tag = tag;
         			cacheA[idx].data = *mp;
         			cacheA[idx].valid = 1;
         			cacheA[idx].age = 1000;
         		}
         		else if (temp == cacheB[idx].age) {
         			cacheB[idx].tag = tag;
         			cacheB[idx].data = *mp;
         			cacheB[idx].valid = 1;
         			cacheB[idx].age = 1000;
         		}
         		else if (temp == cacheC[idx].age) {
         			cacheC[idx].tag = tag;
         			cacheC[idx].data = *mp;
         			cacheC[idx].valid = 1;
         			cacheC[idx].age = 1000;
         		}
         		else {
         			cacheD[idx].tag = tag;
         			cacheD[idx].data = *mp;
         			cacheD[idx].valid = 1;
         			cacheD[idx].age = 1000;
         		}
         	}
         }
         if (found == 0) {
         	misses++;
         	temp = MIN(MIN(cacheA[idx].age, cacheB[idx].age), MIN(cacheC[idx].age, cacheD[idx].age));
         	if (temp == cacheA[idx].age) {
         		cacheA[idx].tag = tag;
         		cacheA[idx].data = *mp;
         		cacheA[idx].valid = 1;
         		cacheA[idx].age = 1000;
         	}
         	else if (temp == cacheB[idx].age) {
         		cacheB[idx].tag = tag;
         		cacheB[idx].data = *mp;
         		cacheB[idx].valid = 1;
         		cacheB[idx].age = 1000;
         	}
         	else if (temp == cacheC[idx].age) {
         		cacheC[idx].tag = tag;
         		cacheC[idx].data = *mp;
         		cacheC[idx].valid = 1;
         		cacheC[idx].age = 1000;
         	}
         	else {
         		cacheD[idx].tag = tag;
         		cacheD[idx].data = *mp;
         		cacheD[idx].valid = 1;
         		cacheD[idx].age = 1000;
         	}
         }
      }
   }
	}

/* Statically define the arrays a, b, and mult, where mult will become the cross product of a and b, i.e., a x b. */

static int a[AMAX][AMAX], b[AMAX][AMAX], mult[AMAX][AMAX];


void matmul( r1, c1, c2 )
   {
   int i,j,k;
   int *mp1, *mp2, *mp3;



/* Initializing elements of matrix mult to 0.*/
    for(i=0; i<r1; ++i)
     for(j=0; j<c2; ++j)
       {
       mult[i][j]=0;
       }

/* Multiplying matrix a and b and storing in array mult. */

    for(i=0; i<r1; ++i)
     for(j=0; j<c2; ++j)
      for(k=0; k<c1; ++k)
        {

#if CACHESIM		/* "Hooks" to measure memory references - enabled if CACHESIM  */

        mp1 = &mult[i][j];
	mp2 = &a[i][k];
	mp3 = &b[k][j];   
	mem_read(mp1);
 	mem_read(mp2);
	mem_read(mp3);
	mem_write(mp1); 
#endif

        mult[i][j]+=a[i][k]*b[k][j];

        }
   }





int main()
    {
    int r1, c1, r2, c2, i, j, k;

    int *mp1, *mp2, *mp3;

    reads = 0;
    writes = 0;
    hits = 0;
    misses = 0;

    printf("Size of pointer is: %d\n\n", sizeof(mp1));

    while (cacheSize != 16 && cacheSize != 256) {
    	printf("Input cache size in words (16 or 256): ");
    	scanf("%3d", &cacheSize);
    }
    while (assoc != 1 && assoc != 2 && assoc != 4) {
    	printf("Input associtivty (1, 2, or 4): ");
    	scanf("%1d", &assoc);
    }

    if (cacheSize == 16) {
    	if (assoc == 1) {
    		cacheA = calloc(16, sizeof(cBlock));
    	}
    	else if (assoc == 2) {
    		cacheA = calloc(8, sizeof(cBlock));
    		cacheB = calloc(8, sizeof(cBlock));
    	}
    	else {
    		cacheA = calloc(4, sizeof(cBlock));
    		cacheB = calloc(4, sizeof(cBlock));
    		cacheC = calloc(4, sizeof(cBlock));
    		cacheD = calloc(4, sizeof(cBlock));
    	}
    }
    else {
    	if (assoc == 1) {
    		cacheA = calloc(256, sizeof(cBlock));
    	}
    	else if (assoc == 2) {
    		cacheA = calloc(128, sizeof(cBlock));
    		cacheB = calloc(128, sizeof(cBlock));
    	}
    	else {
    		cacheA = calloc(64, sizeof(cBlock));
    		cacheB = calloc(64, sizeof(cBlock));
    		cacheC = calloc(64, sizeof(cBlock));
    		cacheD = calloc(64, sizeof(cBlock));
    	}
    }

    printf("Enter rows and column for first matrix: ");
    scanf("%d%d", &r1, &c1);
    printf("Enter rows and column for second matrix: ");
    scanf("%d%d",&r2, &c2);

/* If column of first matrix in not equal to row of second matrix, asking user to enter the size of matrix again. */
    while (c1 != r2)
        {
        printf("Error! column of first matrix not equal to row of second.\n");
        printf("Enter rows and column for first matrix: ");
        scanf("%d%d", &r1, &c1);
        printf("Enter rows and column for second matrix: ");
        scanf("%d%d",&r2, &c2);
        }

/* Storing elements of first matrix. */

    printf("\nEnter elements of matrix 1:\n");
    for(i=0; i<r1; ++i)
    for(j=0; j<c1; ++j)
          {
//        printf("Enter elements a%d%d: ",i+1,j+1);
//        scanf("%d",&a[i][j]);
	a[i][j] = i+j; // build sample data

          }

/* Storing elements of second matrix. */
    printf("\nEnter elements of matrix 2:\n");
    for(i=0; i<r2; ++i)
    for(j=0; j<c2; ++j)
    {
//        printf("Enter elements b%d%d: ",i+1,j+1);
//        scanf("%d",&b[i][j]);

         b[i][j] = 10 + i + j;
    }


   matmul(r1, c1, c2);  	/* Invoke matrix multiply function */	


/* Displaying the multiplication of two matrix. */
    printf("\nOutput Matrix:\n");
    for(i=0; i<r1; ++i)
    for(j=0; j<c2; ++j)
    {
        printf("%d  ",mult[i][j]);
        if(j==c2-1)
            printf("\n\n");
    }

    #if CACHESIM
    	printf("Read/Write ratio: %0.2f\n", reads/writes);
    	printf("Hits: %0.2f; Misses: %0.2f\n", hits, misses);
    	printf("Hit rate: %0.4f\n", hits/(hits + misses));
	#endif
    return 0;
}