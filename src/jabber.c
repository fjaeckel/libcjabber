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

#include "common.h"
#include <stdio.h>
#include <string.h>

jabberID *foo;

int main (int argc, char **argv){
  char *message=NULL;
  char *presence=NULL;
  char *subscription=NULL;
  char *base64=NULL;
  char *clear=NULL;
  char *roster=NULL;
  char *sroster=NULL;
  char *sha=NULL;
  foo = (jabberID*) createJabberID("foo@bar.com/cjabber");
  if(!foo) return 1;
  printf("foo->user: %s, foo->server: %s, foo->resource: %s, foo->full: %s\n",foo->user,foo->server,foo->resource,foo->full);
  message=createMessage("Hello cruel world!","bar@foo.com/muh","foo@bar.com/cjabber",0,"foobar",create_sha_hash("foobarblubb", 11));
  printf("%s",message);
  presence=createPresenceMsg(2,"away from keyboard","mouse@comput.er/input", "foo@bar.com/bla", 23);
  printf("%s",presence);
  subscription=createSubscriptionMsg(1,NULL,NULL);
  printf("%s",subscription);
  roster=requestRoster("foo@bar.com/cjabber", "roster_1");
  printf("%s",roster);
  sroster=setRoster("foo@bar.com/cjabber", "roster_2", "mouse@comput.er/input", "mouse", "device", SUB_SUBSCRIBED);
  printf("%s",sroster);
  base64=encode_base64("<show>dnd</show><status>away from keyboard</status><priority>23</priority>");
  printf("base64: %s\n",base64);
  clear=decode_base64(base64);
  printf("clear: %s\n",clear);
  sha=create_sha_hash("foobarblubb", 11);
  printf("sha: %s\n",sha);

  return 0;
}
