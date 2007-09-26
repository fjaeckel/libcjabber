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
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

/*
 * a function to create presence messages
 * args:
 *    -> state (chat, dnd, away, xa, unavailable)
 *    -> text (the text which has to be displayed)
 *    -> to (the recipient which should get the message)
 *    -> from (the full JID of the resource)
 *    -> priority (the priority of the message)
 */

char *createPresenceMsg(int state, char *text, char *to, char *from, int priority){
  char *presText = NULL;
  int buffersize = 0;
  char *tmp = NULL;
  int ret = 0;
  xmlDocPtr doc = NULL;
  xmlNodePtr root_node = NULL;
  xmlChar *xmlbuff = NULL;

  switch(state){
    case PRES_CHAT:
      presText="chat";
      break;
    case PRES_DND:
      presText="dnd";
      break;
    case PRES_AWAY:
      presText="away";
      break;
    case PRES_XA:
      presText="xa";
      break;
    case PRES_UNAVAILABLE:
      presText="unavailable";
      break;
  }

  /* rfc3921 says priority has to be bigger than -129 and lower than 128 */
  if(priority != 0 && priority >= -128 && priority <= 127){
    tmp = malloc(sizeof(size_t)*8+1);
    if(tmp){
      ret=ltostr(priority,10,tmp,sizeof(size_t)*8+1);
      if(ret != 0)
        tmp=NULL;
    }
  }
  
  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "presence");
  xmlDocSetRootElement(doc, root_node);
  xmlNewProp(root_node, BAD_CAST "xml:lang", BAD_CAST "en");

  if(state == PRES_UNAVAILABLE)
    xmlNewProp(root_node, BAD_CAST "type", BAD_CAST presText);
  if(presText && state != PRES_UNAVAILABLE)
    xmlNewChild(root_node, NULL, BAD_CAST "show", BAD_CAST presText);
  if(to)
    if(strlen(to)>0)
      xmlNewProp(root_node, BAD_CAST "to", BAD_CAST to);
  if(from)
    if(strlen(from)>0)
      xmlNewProp(root_node, BAD_CAST "from", BAD_CAST from);
  if(text)
    if(strlen(text)>0 && state != PRES_AVAILABLE)
      xmlNewChild(root_node, NULL, BAD_CAST "status", BAD_CAST text);
  if(state != PRES_UNAVAILABLE){
    if(tmp){
      xmlNewChild(root_node, NULL, BAD_CAST "priority", BAD_CAST tmp);
      free(tmp);
    }
  }
  
  xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  xmlMemoryDump();
  return (char *)xmlbuff;
}
