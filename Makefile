#	just a Makefile to compile and link cjabber.
#	
#	This file is part of libcjabber.
#
#	cjabber is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License version 2
#	as published by the Free Software Foundation.
#	
#	cjabber is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#	GNU General Public License for more details.
#	
#	You should have received a copy of the GNU General Public License
#	along with cjabber; if not, write to the Free Software
#	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

CC=gcc
SRC=src
LIBS=-lssl `xml2-config --libs` -lcrypto
#CFLAGS=-Wall -DDEBUG -Iinclude -ggdb3 -g
CFLAGS=-Wall -DDEBUG -Iinclude -I./include -fPIC `xml2-config --cflags`
#CFLAGS=-Wall -I./include -fPIC `xml2-config --cflags` -O4
OBJ=jid.o messages.o presence.o convert.o subscription.o roster.o base64.o sha.o


all: jabber

jabber: ${OBJ} jabber.o
	${CC} -o jabber ${SRC}/*.o ${LIBS} ${CFLAGS}

jid.o:
	${CC} -c ${SRC}/jid.c -o ${SRC}/jid.o ${CFLAGS}

messages.o:
	${CC} -c ${SRC}/messages.c -o ${SRC}/messages.o ${CFLAGS}

convert.o:
	${CC} -c ${SRC}/convert.c -o ${SRC}/convert.o ${CFLAGS}

presence.o:
	${CC} -c ${SRC}/presence.c -o ${SRC}/presence.o ${CFLAGS}

subscription.o:
	${CC} -c ${SRC}/subscription.c -o ${SRC}/subscription.o ${CFLAGS}

roster.o:
	${CC} -c ${SRC}/roster.c -o ${SRC}/roster.o ${CFLAGS}

base64.o:
	${CC} -c ${SRC}/base64.c -o ${SRC}/base64.o ${CFLAGS}

sha.o:
	${CC} -c ${SRC}/sha.c -o ${SRC}/sha.o ${CFLAGS} 

jabber.o: ${OBJ}
	${CC} -c ${SRC}/jabber.c -o ${SRC}/jabber.o ${CFLAGS} 

clean:
	rm jabber ${SRC}/*.o
