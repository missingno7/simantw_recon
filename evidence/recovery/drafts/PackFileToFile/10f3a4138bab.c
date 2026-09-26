/* Pack a caller-owned input stream into the selected output stream.  The
   compiler-visible word fields model the packer's private SIMTWO state. */
typedef void (far *PackRoutine)(void);

extern void near PackInitialize(int a, int b, int c, int d, int chunkSize);
extern void far Encode(void);
extern void near PackComplete(void);
extern void far PackReadByte(void);
extern void far PackWriteByte(void);

/* These are private word/long slots observed in the target DGROUP block. */
extern PackRoutine near packGetByte;
extern PackRoutine near packPutByte;
extern int near packInputHandle;
extern int near packOutputHandle;
extern void far * near packInputBuffer;
extern unsigned long near packResult;

/* Initialize the transfer, install its byte strategies, bind the file and
   source buffer, run the encoder, and return the byte count it records. */
unsigned long far PackFileToFile(int inputHandle, int outputHandle,
                                 void far *inputBuffer)
{
    /* The target pushes the buffer length first, so it is the last formal. */
    PackInitialize(0, 0, 0, 0, 0x400);
    packGetByte = PackReadByte;
    packPutByte = PackWriteByte;
    packInputHandle = inputHandle;
    packOutputHandle = outputHandle;
    packInputBuffer = inputBuffer;
    Encode();
    PackComplete();
    return packResult;
}
