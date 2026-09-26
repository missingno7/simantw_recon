/* Pack a caller-owned input stream into the selected output stream.  The
   compiler-visible word fields model the packer's private SIMTWO state. */
typedef void (far *PackRoutine)(void);

extern void far PackInitialize(int chunkSize, int a, int b, int c, int d);
extern void far Encode(void);
extern void far PackComplete(void);
extern void far PackReadByte(void);
extern void far PackWriteByte(void);

static PackRoutine near packGetByte;
static PackRoutine near packPutByte;
static PackRoutine near packFinishByte;
static int near packFlags;
static int near packInputHandle;
static int near packOutputHandle;
static void far * near packInputBuffer;
static unsigned long near packResult;

/* Initialize the transfer, install its byte strategies, bind the file and
   source buffer, run the encoder, and return the byte count it records. */
unsigned long far PackFileToFile(int inputHandle, int outputHandle,
                                 void far *inputBuffer)
{
    PackInitialize(0x400, 0, 0, 0, 0);
    packGetByte = PackReadByte;
    packPutByte = Encode;
    packFinishByte = PackWriteByte;
    packFlags = -1;
    packInputHandle = inputHandle;
    packOutputHandle = outputHandle;
    packInputBuffer = inputBuffer;
    Encode();
    PackComplete();
    return packResult;
}
