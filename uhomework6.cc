/* Keyur Savjani
 * kss160430@utdallas.edu
 * SE 3377.501
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "cdk.h"
#include <stdint.h>
#include <sstream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

const int maxRecordStringLength = 25;

class BinaryFileRecord { // given Record class from homework
public:

  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

//class for Binary File Header
class BinaryFileHeader { // given Header class from homework

public: 

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

int main() {
  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix; // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char *rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char *columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the CDK screen.
   *
   * Make sure the putty terminal is large enough
   */

  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();
  
   /*
   * Create the matrix. Need to manually cast (const char**) to (char **)
   */

  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL) {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  ifstream binInfile("cs3377.bin", ios::in | ios::binary); // opening from file to get the contents

  BinaryFileHeader *binaryHeader = new BinaryFileHeader(); // this will create a new instance of BinaryFileHeader and BinaryFileRecord
  BinaryFileRecord *binaryRecord = new BinaryFileRecord();

  binInfile.read((char *) binaryHeader, sizeof(BinaryFileHeader)); // this will read in the BinaryFileHeader

  string magicNo="Magic: 0x"; // this block will create strings for the cells that are within the matrix
  string version="Version: ";
  string numRecords="NumRecords: ";
  string strlen1="strlen: ";
  string string1="";
  string strlen2="strlen: ";
  string string2="";
  string strlen3="strlen: ";
  string string3;
  string strlen4="strlen: ";
  string string4="";

  stringstream convertMagic; // stringstreams will now be used to get each value and then we will get the Magic Number

  convertMagic << hex << uppercase << binaryHeader->magicNumber;
  magicNo += convertMagic.str();

  stringstream convertVersion; // this will get the version number
  convertVersion << hex << binaryHeader->versionNumber;
  version+=convertVersion.str();

  stringstream convertNumRec; // this will get the number of records
  convertNumRec << binaryHeader->numRecords;
  numRecords+=convertNumRec.str();

  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord)); // this will get the first string
  stringstream convertString1;
  convertString1 << binaryRecord->stringBuffer;
  string1+=convertString1.str();

  stringstream stringLength1; // this will get the length of the first string
  stringLength1 << string1.length();
  strlen1+=stringLength1.str();

  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord)); // this will get the second string
  stringstream convertString2;
  convertString2 << binaryRecord->stringBuffer;
  string2+=convertString2.str();

  stringstream stringLength2; // this will get the length of the first string
  stringLength2 << string2.length();
  strlen2+=stringLength2.str();

  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord)); // this will get the third string
  stringstream convertString3;
  convertString3 << binaryRecord->stringBuffer;
  string3+=convertString3.str();

  stringstream stringLength3; // this will get the length of the third string
  stringLength3 << string3.length();
  strlen3+=stringLength3.str();

  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord)); // this will get the fourth string
  stringstream convertString4;
  convertString4 << binaryRecord->stringBuffer;
  string4+=convertString4.str();

  stringstream stringLength4; // this will get the length of the fourth string
  stringLength4 << string4.length();
  strlen4+=stringLength4.str();

  setCDKMatrixCell(myMatrix, 1, 1, magicNo.c_str()); // this will allocate each section of the matrix to the input, giving it a place to stay
  setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str());
  setCDKMatrixCell(myMatrix, 2, 1, strlen1.c_str());
  setCDKMatrixCell(myMatrix, 2, 2, string1.c_str());
  setCDKMatrixCell(myMatrix, 3, 1, strlen2.c_str());
  setCDKMatrixCell(myMatrix, 3, 2, string2.c_str());
  setCDKMatrixCell(myMatrix, 4, 1, strlen3.c_str());
  setCDKMatrixCell(myMatrix, 4, 2, string3.c_str());
  setCDKMatrixCell(myMatrix, 5, 1, strlen4.c_str());
  setCDKMatrixCell(myMatrix, 5, 2, string4.c_str());

  //draw the matrix
  drawCDKMatrix(myMatrix, true); /* required */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
