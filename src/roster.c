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
#include <libxml/parser.h>
#include <libxml/tree.h>

/*
 * a standard function to request the users roster
 * args:
 *    -> from - the jid of the user
 *    -> id - a unique ID which don't have a proper form
 */
char *requestRoster(char *from, char *id){
  if(!id || !from)
    return NULL;
  
  int buffersize = 0;
  xmlDocPtr doc = NULL;
  xmlNodePtr root_node = NULL, node = NULL;
  xmlChar *xmlbuff = NULL;

  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "iq");
  xmlDocSetRootElement(doc, root_node);
  xmlNewProp(root_node, BAD_CAST "xml:lang", BAD_CAST "en");
  xmlNewProp(root_node, BAD_CAST "from", BAD_CAST from);
  xmlNewProp(root_node, BAD_CAST "type", BAD_CAST "get");
  xmlNewProp(root_node, BAD_CAST "id", BAD_CAST id);
  node=xmlNewChild(root_node, NULL, BAD_CAST "query", NULL);
  xmlNewProp(node, BAD_CAST "xmlns", BAD_CAST XMLNS_ROSTER);

  xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  xmlMemoryDump();
  return (char *)xmlbuff;
}

/*
 * a standard function to set roster items such as adding new participants
 * args:
 *    -> from - the jid of the user
 *    -> id - a unique ID which don't have a proper form
 *    -> jid - the jid of the participant
 *    -> name - the name which is displayed in the roster
 *    -> group - the group displayed in the roster
 */
char *setRoster(char *from, char *id, char *jid, char *name, char *group, int subscription){
  if(!from || !id || !jid)
    return NULL;
  int buffersize=0;
  xmlDocPtr doc = NULL;
  xmlNodePtr root_node=NULL, node=NULL, node2=NULL;
  xmlChar *xmlbuff = NULL;
  
  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "iq");
  xmlDocSetRootElement(doc, root_node);
  xmlNewProp(root_node, BAD_CAST "from", BAD_CAST from);
  xmlNewProp(root_node, BAD_CAST "type", BAD_CAST "set");
  xmlNewProp(root_node, BAD_CAST "id", BAD_CAST id);
  node=xmlNewChild(root_node, NULL, BAD_CAST "query", NULL);
  xmlNewProp(node, BAD_CAST "xmlns", BAD_CAST XMLNS_ROSTER);
  node2=xmlNewChild(node, NULL, BAD_CAST "item", NULL);
  xmlNewProp(node2, BAD_CAST "jid", BAD_CAST jid);
  if(name)
    xmlNewProp(node2, BAD_CAST "name", BAD_CAST name);
  if(group)
    xmlNewChild(node2, NULL, BAD_CAST "group", BAD_CAST group);

  xmlDocDumpFormatMemory(doc,&xmlbuff,&buffersize,1);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  xmlMemoryDump();
  return (char *)xmlbuff;
}
