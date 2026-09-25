/*
 * Pack a near-memory source into a caller-provided memory destination.
 *
 * The prologue forwards the five word arguments to the common pack-state
 * initializer.  The subsequent stores show that the last word is the
 * source/count value used by the memory reader: its far representation is
 * formed with a zero high word, and the same word seeds the reader's
 * remaining-count field.  The two unnamed strategy slots are private
 * memory-reader/memory-writer callbacks; Encode consumes the initialized
 * state and publishes its far result in PackResult.
 */
typedef unsigned int word;

extern void far PackInitialize(word, word, word, word, word);
extern void far Encode(void);
extern void far PackMemoryRead(void);
extern void far PackMemoryWrite(void);

extern word near PackSourceOffset;
extern word near PackSourceSegment;
extern word near PackReadCount;
extern void (far *near PackReadStrategy)(void);
extern void (far *near PackWriteStrategy)(void);
extern word near PackResultOffset;
extern word near PackResultSegment;

void far *PackMemoryToMemory(word first, word second, word third,
                             word fourth, volatile word sourceCount)
{
    PackInitialize(first, second, third, fourth, sourceCount);
    PackSourceOffset = sourceCount;
    PackSourceSegment = 0;
    PackReadCount = sourceCount;
    PackReadStrategy = PackMemoryRead;
    PackWriteStrategy = PackMemoryWrite;
    Encode();
    return (void far *)((unsigned long)PackResultSegment << 16 |
                        PackResultOffset);
}
