#include "common.h"
#include <stdio.h>

jabberID *foo;

int main (int argc, char **argv){
  char *message;
  char *presence;
  char *subscription;
  char *base64;
  char *clear;
  char *roster;
  char *sroster;

  foo = (jabberID*) createJabberID("foo@bar.com/cjabber");
  if(!foo) return 1;
  printf("foo->user: %s, foo->server: %s, foo->resource: %s\n",foo->user,foo->server,foo->resource);
  message=createMessage("Hello cruel world!","bar@foo.com/muh","foo@bar.com/cjabber",0,"foobar");
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
  return 0;
}
