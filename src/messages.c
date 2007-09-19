#include "libcjabber.h"
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

/*
 * a simple function using libxml creating a message
 * and returning it as an char*
 * args:
 *    -> text - the text in the message
 *    -> to   - the recipient
 *    -> from - the sender
 * TODO:  
 *        thread ids for conversations (sha?)
 */
char *createMessage(char *text, char *to, char *from, int type, char *subject){
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

  xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);

  xmlFreeDoc(doc);
  xmlCleanupParser();
  xmlMemoryDump();
  return (char *)xmlbuff;
}