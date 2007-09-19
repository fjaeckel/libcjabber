#include "libcjabber.h"
#include <unistd.h>
jabberID *createJabberID(char *jid);
char *createMessage(char *text, char *to, char *from, int type, char *subject);
char *createPresenceMsg(int state, char *text, char *to, char *from, int priority);
char *createSubscriptionMsg(int type, char *to, char *from);
char *requestRoster(char *from, char *id);
char *setRoster(char *from, char *id, char *jid, char *name, char *group, int subscription);
int jidIsValid(char *jid);
char *encode_base64(char *message);
char *decode_base64(char *bs64str);

int ltostr(long value, unsigned int base, char* converted, size_t size);
int ultostr(unsigned long value, unsigned int base, char* converted, size_t size);
