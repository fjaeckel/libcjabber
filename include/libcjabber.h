/*
 * to define how a jid is built
 */
typedef struct jabberID {
  char *user;
  char *server;
  char *resource;
  char *partial;
  char *full;
} jabberID;

/*
 * the default resource name
 */
#define RESOURCE "libcjabber"

/*
 * the several message types
 */
#define MSG_TYPE_CHAT       0
#define MSG_TYPE_ERROR      1
#define MSG_TYPE_GROUPCHAT  2
#define MSG_TYPE_HEADLINE   3
#define MSG_TYPE_NORMAL     4

/*
 * the basic presence states
 */
#define PRES_AVAILABLE    0
#define PRES_CHAT         1
#define PRES_DND          2
#define PRES_AWAY         3
#define PRES_XA           4
#define PRES_UNAVAILABLE  5

/*
 * the basic subscriping states
 */
#define SUB_PROBE        0
#define SUB_UNAVAILABLE  1
#define SUB_SUBSCRIBE    2
#define SUB_SUBSCRIBED   3
#define SUB_UNSUBSCRIBE  4
#define SUB_UNSUBSCRIBED 5

/*
 * the basic roster request types
 */
#define ROSTER_GET       0
#define ROSTER_SET       1
#define ROSTER_RESULT    3
#define ROSTER_ERROR     4

/*
 * the xml namespaces
 */
#define XMLNS_STREAM "http://etherx.jabber.org/streams"
#define XMLNS_ROSTER  "jabber:iq:roster"
#define XMLNS_CLIENT  "jabber:client"
#define XMLNS_SERVER  "jabber:server"
#define XMLNS_DIALBACK "jabber:server:dialback"

/*
 * just to check if a jabberid is fully, partially valid or invalid
 */
#define JID_INVALID 0
#define JID_FULL    1
#define JID_PARTIAL 2
