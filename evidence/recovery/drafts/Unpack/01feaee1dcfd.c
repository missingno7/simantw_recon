/* Unpack one output block with the file's persistent LZSS state. */
extern unsigned char __based(__segname("PACK")) pack_buf[];
extern unsigned int near pack_threshold;
static unsigned char far *text_buf = pack_buf;
static unsigned char far *input_buffer = 0;
static unsigned int input_left = 0;
static unsigned int history_position = 0;
static unsigned int bit_buffer = 0;
static unsigned int saved_dx = 0;
static unsigned int saved_cx = 0;
static unsigned int match_left = 0;
static unsigned int resume_state = 1;
static unsigned int buffer_size = 0;
static unsigned char far *buffer_pointer = 0;
#define ADVANCE_HISTORY() history_position = (history_position + 1) & 0xfff;
#define HAS_OUTPUT(count) count != 0
int far Unpack(unsigned char far *output, unsigned int output_count)
{
    unsigned int produced;
    unsigned int source_position;
    unsigned int length;
    unsigned char flags;
    unsigned char first;
    unsigned char second;
    unsigned char value;
    unsigned char far *out;
    produced = 0;
    out = output;
    flags = (unsigned char)bit_buffer;
    while (HAS_OUTPUT(output_count)) {
        if ((flags & 0x100) == 0) {
            if (input_left == 0)
                break;
            flags = *input_buffer++;
            --input_left;
            bit_buffer = flags | 0xff00;
        } else {
            bit_buffer >>= 1;
            flags = (unsigned char)bit_buffer;
        }
        if (flags & 1) {
            if (input_left == 0)
                break;
            value = *input_buffer++;
            --input_left;
            *out++ = value;
            text_buf[history_position] = value;
            ADVANCE_HISTORY();
            ++produced;
            --output_count;
        } else {
            if (input_left < 2)
                break;
            first = *input_buffer++;
            second = *input_buffer++;
            input_left -= 2;
            source_position = first | ((unsigned int)(second & 0xf0) << 4);
            length = (second & 0x0f) + pack_threshold;
            while (length != 0 && HAS_OUTPUT(output_count)) {
                value = text_buf[source_position];
                source_position = (source_position + 1) & 0xfff;
                *out++ = value;
                text_buf[history_position] = value;
                ADVANCE_HISTORY();
                ++produced;
                --output_count;
                --length;
            }
        }
        bit_buffer >>= 1;
    }
    resume_state = 0;
    saved_cx = bit_buffer;
    saved_dx = 0;
    match_left = 0;
    return produced;
}
