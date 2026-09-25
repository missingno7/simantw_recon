/* Keyboard lock and command-key latches all start clear. */
int __based(__segname("SIMANT_DATA_GROUP")) CapsLockKey = 0;
int __based(__segname("SIMANT_DATA_GROUP")) CommandKey = 0;
int __based(__segname("SIMANT_DATA_GROUP")) EscapeKey = 0;
int __based(__segname("SIMANT_DATA_GROUP")) HelpKey = 0;
int __based(__segname("SIMANT_DATA_GROUP")) HomeKey = 0;
