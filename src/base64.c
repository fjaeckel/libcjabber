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

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <string.h>

char *encode_base64(char *message){
  if(!message)
    return NULL;
  BIO *bio, *b64;
  char *buffer = NULL;
  BUF_MEM *bptr;
  
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new(BIO_s_mem());
  
  b64 = BIO_push(b64, bio);
  BIO_write(b64, message, strlen(message));
  BIO_flush(b64);
  BIO_get_mem_ptr(b64, &bptr);

  buffer = (char *)malloc(bptr->length);
  if(!buffer)
    return NULL;

  memcpy(buffer, bptr->data, bptr->length-1);
  buffer[bptr->length-1] = 0;
  BIO_free_all(b64);
  return buffer;
}

char *decode_base64(char *bs64str){
  if(!bs64str)
    return NULL;
  BIO *bio, *b64;
  char *buffer = NULL;

  buffer = (char *)malloc(strlen(bs64str));
  if(!buffer)
    return NULL;

  memset(buffer, 0, strlen(bs64str));

  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new_mem_buf(bs64str, strlen(bs64str));
  bio = BIO_push(b64, bio);
  
  BIO_read(bio, buffer, strlen(bs64str));
  BIO_free_all(bio);
  return buffer;
}
