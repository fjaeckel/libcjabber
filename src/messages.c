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
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

/*
 * a simple function using libxml creating a message
 * and returning it as an char*
 * args:
 *    -> text    - the text in the message
 *    -> to      - the recipient
 *    -> from    - the sender
 *    -> type    - the message type
 *    -> subject - the subject of the message
 *    -> thread  - the thread id in sha form (actually only a char pointer)
 */
char *createMessage(char *text, char *to, 
                    char *from, int type, 
                    char *subject, char *thread){
  if(!to)
    return NULL;
  char *msgType = NULL;
  switch(type){
    case MSG_TYPE_CHAT:
      msgType = "chat";
      break;
    case MSG_TYPE_ERROR:
      msgType = "error";
      break;
    case MSG_TYPE_GROUPCHAT:
      msgType = "groupchat";
      break;
    case MSG_TYPE_HEADLINE:
      msgType = "headline";
      break;
    case MSG_TYPE_NORMAL:
      msgType = "normal";
      break;
  }

  xmlDocPtr doc = NULL;
  xmlNodePtr root_node = NULL;
  xmlChar *xmlbuff = NULL;
  int buffersize = 0;
  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "message");
  xmlDocSetRootElement(doc, root_node);
  xmlNewProp(root_node, BAD_CAST "xml:lang", BAD_CAST "en");
  xmlNewProp(root_node, BAD_CAST "to", BAD_CAST to);
  xmlNewProp(root_node, BAD_CAST "from", BAD_CAST from);
  if(msgType)
    xmlNewProp(root_node, BAD_CAST "type", BAD_CAST msgType);
  if(subject)
    xmlNewChild(root_node, NULL, BAD_CAST "subject", BAD_CAST subject);
  xmlNewChild(root_node, NULL, BAD_CAST "body", BAD_CAST text);
  if(thread)
    xmlNewChild(root_node, NULL, BAD_CAST "thread", BAD_CAST thread);

  xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);

  xmlFreeDoc(doc);
  xmlCleanupParser();
  xmlMemoryDump();
  return (char *)xmlbuff;
}
