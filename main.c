/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1) Gerardo Arturo Rodriguez  garodriguez-cardenas@myseneca.ca

   +--------------------------------------------------------+
   |                   FILE: main.c                         |
   +--------------------------------------------------------+
   |           2  0  2  0  ~  W  I  N  T  E  R              |
   |                 I  P  C  :  B  T  P                    |
   |                 1  4  4  :  1  0  0                    |
   |              FINAL ASSESSMENT PART - 2                 |
   |                                                        |
   |     S  E  N  E  C  A            C  O  L  L  E  G  E    |
   +--------------------------------------------------------+ */

#define _CRT_SECURE_NO_WARNINGS


#include "file_helper.h"
#include "report.h"

#define MAXRIDERS 5000  //By changing this to 5000 we get error C6262 function uses 360024 bytes of stack... stack size 16384

int main(void)
{
	struct RiderInfo info[MAXRIDERS] = { 0 };

	startReportManager(info, MAXRIDERS);

	return 0;
}
