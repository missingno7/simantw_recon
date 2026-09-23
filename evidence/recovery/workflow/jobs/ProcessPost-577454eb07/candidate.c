/*
 * Evidence-backed source outline for ProcessPost. The complete body is held
 * pending identification of the original DGROUP receive-buffer object.
 *
 * Confirmed behavior from the target and nearby _NetworkSend:
 *
 *   1. Copy one 0x40-byte NCB from ncbOffset[ncbTail] and
 *      ncbSegment[ncbTail] into a stack-local NCB, then advance ncbTail
 *      modulo ten.
 *   2. Return zero for command 0x91. Command 0x96 enters the final-status
 *      path; the other commands use the NCB name and MapPlane to select
 *      receive/send exchanges.
 *   3. Exchanges receive into DGROUP offsets 0x28e8, 0x38e8, 0x48e8,
 *      0x58e8, 0x68e8, 0x88e8, 0x98e8, or 0xac5a, with 0x1000-byte
 *      capacities; several responses are sent back with NbSend.
 *   4. Finish through NbHangUp/NbFinalStatus, then post a listen or receive
 *      using theNetBiosBuffer. Some paths call StopSimulation.
 *
 * The MAPSYM evidence names ncbTail, ncbOffset, ncbSegment, MapPlane, and
 * theNetBiosBuffer. It does not name or bound the DGROUP buffers at the
 * offsets listed above. Those offsets cannot safely be represented by an
 * invented external, an address cast, or a padding array. Recovering their
 * real owner and extent is a prerequisite to writing a compilable C body
 * without changing the private data contribution.
 */
