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

char *createSubscriptionMsg(int type, char *to, char *from){
  if (!type || !to)
    return NULL;

  char *subType = NULL;
  int buffersize = 0;
  xmlDocPtr doc = NULL;
  xmlNodePtr root_node = NULL;
  xmlChar *xmlbuff = NULL;

  switch(type) {
    case SUB_PROBE:
      subType = "probe";
      break;
    case SUB_UNAVAILABLE:
      subType = "unavailable";
      break;
    case SUB_SUBSCRIBE:
      subType = "subscribe";
      break;
    case SUB_SUBSCRIBED:
      subType = "subscribed";
      break;
    case SUB_UNSUBSCRIBE:
      subType = "unsubscribe";
      break;
    case SUB_UNSUBSCRIBED:
      subType = "unsubscribed";
      break;
  }

  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "presence");
  xmlDocSetRootElement(doc, root_node);
  xmlNewProp(root_node, BAD_CAST "to", BAD_CAST to);
  if(from)
    xmlNewProp(root_node, BAD_CAST "from", BAD_CAST from);
  xmlNewProp(root_node, BAD_CAST "type", BAD_CAST subType);

  xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  xmlMemoryDump();
  return (char *)xmlbuff;
}
