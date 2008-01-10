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

/*
 * TODO: to be implemented
 */
int jidIsValid(char *jid){
  return 0;
}

/*
 * TODO: to be implemented
 */
char *copyJabberIDtoChar(jabberID *jid){
  return NULL;
}
