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

#include <openssl/sha.h>
#include <openssl/evp.h>

/* remove me */
#include <string.h>

/*
 * a function to create a sha-1 hash of data.
 * args:
 *    -> data - the data, the hash will be created from
 *    -> size - size of the data
 */
char *create_sha_hash(char *data, int size) {
  if(!data)
    return NULL;

  EVP_MD_CTX mdctx;
  const EVP_MD *md;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len;
  int i;

  OpenSSL_add_all_digests();
  
  md = EVP_get_digestbyname("sha1");

  EVP_MD_CTX_init(&mdctx);
  EVP_DigestInit_ex(&mdctx, md, NULL);
  EVP_DigestUpdate(&mdctx, data, size);
  EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
  EVP_MD_CTX_cleanup(&mdctx);
#ifdef DEBUG
  printf("SHA: ");
  for(i = 0; i < md_len; i++){
    printf("%02x", md_value[i]);
  }
  printf("\nmd_len: %d, i: %d\n",md_len, i);
#endif
  data=NULL;
  data=malloc(md_len);
  if(!data)
    return NULL;
  char *buf=NULL;
  buf=malloc(3);
  if(!buf)
    return NULL;
  for(i = 0; i < md_len; i++){
    snprintf(buf, 3, "%02x", md_value[i]);
#ifdef DEBUG
    printf("%02x",md_value[i]); 
#endif
    /* TODO: remove strncat and strlen! */
    strncat(data,buf,strlen(buf));
  }
  if(!data)
    return NULL;
#ifdef DEBUG
  puts("");
  printf("data:%s\n",data);
#endif
  return data;
}
