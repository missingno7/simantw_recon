/* Split literal and back-reference decoding into loop-local blocks. */
extern unsigned char near rsrvptrs[];
extern unsigned int near pack_threshold;
static unsigned char far *packed_input;
static unsigned int packed_left;
static unsigned int history_position;
static unsigned int bit_buffer;
static unsigned int saved_dx;
static unsigned int saved_cx;
static unsigned int match_left;
static unsigned int resume_state;
int far Unpack(unsigned char far *output, unsigned int output_count)
{
    unsigned int produced = 0;
    while (output_count) {
        unsigned int length;
        if ((bit_buffer & 1) != 0) {
            unsigned char value;
            if (packed_left == 0)
                break;
            value = *packed_input++;
            --packed_left;
            *output++ = value;
            rsrvptrs[history_position++] = value;
            history_position &= 0xfff;
            ++produced;
            --output_count;
        } else {
            unsigned int position;
            unsigned char lo, hi;
            if (packed_left < 2)
                break;
            lo = *packed_input++;
            hi = *packed_input++;
            packed_left -= 2;
            position = lo | ((unsigned int)(hi & 0xf0) << 4);
            length = (hi & 0x0f) + pack_threshold;
            while (length && output_count) {
                unsigned char value = rsrvptrs[position++ & 0xfff];
                *output++ = value;
                rsrvptrs[history_position++] = value;
                history_position &= 0xfff;
                ++produced;
                --output_count;
                --length;
            }
        }
        bit_buffer = (bit_buffer >> 1) | 0x8000;
    }
    return produced;
}
