/*
 * This file is part of libcjabber.
 *
 * cjabber is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * cjabber is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cjabber; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "libcjabber.h"
#include <unistd.h>

/* creates a new jabberid of out type jabberID */
jabberID *createJabberID(char *jid);
/* creates a new jabber message */
char *createMessage(char *text, char *to, char *from, int type, char *subject, char *thread);
/* creates a new presence message */
char *createPresenceMsg(int state, char *text, char *to, char *from, int priority);
/* creates some subscription stanzas */
char *createSubscriptionMsg(int type, char *to, char *from);
/* forms a new request of the whole roster */
char *requestRoster(char *from, char *id);
/* sets an entry in the roster */
char *setRoster(char *from, char *id, char *jid, char *name, char *group, int subscription);
/* checks if the given jabberid is valid */
int jidIsValid(char *jid);

/* base64 stuff */
char *encode_base64(char *message);
char *decode_base64(char *bs64str);

/* sha stuff */
char *create_sha_hash(char *data);

/* 2 functions stolen from René Nussbaumer and Nico Schottelius */
int ltostr(long value, unsigned int base, char* converted, size_t size);
int ultostr(unsigned long value, unsigned int base, char* converted, size_t size);
