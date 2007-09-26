#include "libcjabber.h"
#include <stdlib.h>
#include <string.h>

/* 
 * a function to create a jabberid with the elements, in a struct
 *  -> user
 *  -> server
 *  -> resource
 *  -> full
 * args:    const char *jabberid (notation: user@server/resource)
 * returns: a struct of the type jabberid
 */

jabberID *createJabberID(char *jid){
  jabberID *newjid;
  char *src=NULL;
  char *tmp=NULL;
  int size=0;
  
  if (!jid) return NULL;

  newjid=malloc(sizeof(char)*strlen(jid));

  if (!newjid) return NULL;
  
  newjid->full = jid;
  tmp = strchr (jid, '/');
  if(tmp && strlen(tmp)>1)
    newjid->resource = tmp + 1;
  else
    return NULL;
  
  src=jid;
  src=strchr(src,'@');
  if(src) {
    if(tmp)
      size = strlen(++src)-strlen(tmp);
    else
      size = strlen(++src);
    tmp=malloc(size*sizeof(char));
    if(tmp) {
      tmp=strncat(tmp,src,size);
      if(strlen(tmp)>0)
        newjid->server = tmp;
      else
        return NULL;
    }
  }

  src=jid;
  tmp=strchr(jid,'@');
  if(tmp) {
    size = strlen(src)-strlen(tmp);
    tmp=malloc(size*sizeof(char));
    if(tmp) {
      tmp=strncat(tmp,src,size);
      if(strlen(tmp)>0)
        newjid->user = tmp;
      else
        return NULL;
    }
  }
  return newjid;
}

int jidIsValid(char *jid){
  return 0;
}
